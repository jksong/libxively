#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "xi_stated_sscanf.h"
#include "xi_coroutine.h"
#include "xi_layer_interface.h"
#include "xi_macros.h"

#include "errors.h"
#include "message.h"

#include "parser.h"

static layer_state_t read_string(int len, xi_stated_sscanf_state_t * xi_stated_state, void ** into, const_data_descriptor_t * data)
{
    char strpat[ 32 ];
    memset( strpat, 0, sizeof( strpat ) );
    sprintf( strpat, "%%%d.", len );

    signed char sscanf_state = 0;
    static uint16_t cs       = 0;
    const const_data_descriptor_t pat = { strpat, strlen(strpat), strlen(strpat), 0 };

    BEGIN_CORO(cs)
    
    while( sscanf_state == 0 )
    {
        sscanf_state = xi_stated_sscanf(
                      xi_stated_state
                    , ( const_data_descriptor_t* ) &pat
                    , ( const_data_descriptor_t* ) data
                    , into );
    
        if( sscanf_state == 0 )
        {
            YIELD( cs, LAYER_STATE_WANT_READ )
            continue;
        }
    }

    RESTART(cs, sscanf_state == -1 ? LAYER_STATE_OK : LAYER_STATE_ERROR )
    END_CORO()
}



#define READ_STRING(into) \
{ \
    if ((len - *nread) == 0) { \
      YIELD( cs, LAYER_STATE_WANT_READ ) \
      continue; \
    } \
    \
    parser->str_length = (data[*nread] << 8); \
    *nread += 1; \
    if ((len - *nread) == 0) { \
      YIELD( cs, LAYER_STATE_WANT_READ ) \
      continue; \
    } \
    parser->str_length += data[*nread]; \
    *nread += 1; \
    \
    if ((len - *nread) == 0) { \
      YIELD( cs, LAYER_STATE_WANT_READ ) \
      continue; \
    } \
    src.curr_pos = *nread;\
    do { \
      read_string_state = read_string(parser->str_length, &(parser->sscanf_state), into.data, &src); \
      if( read_string_state == LAYER_STATE_WANT_READ ) \
      { \
        YIELD( cs, LAYER_STATE_WANT_READ ); \
        continue; \
      }\
    } while( read_string_state != LAYER_STATE_OK ); \
}

void mqtt_parser_init(mqtt_parser_t* parser) {
  parser->state = MQTT_PARSER_STATE_INITIAL;
  parser->buffer_pending = 0;
  parser->buffer = NULL;
  parser->buffer_length = 0;
}

void mqtt_parser_buffer(mqtt_parser_t* parser, uint8_t* buffer, size_t buffer_length) {
  parser->buffer_pending = 1;
  parser->buffer = buffer;
  parser->buffer_length = buffer_length;
}

layer_state_t mqtt_parser_execute(mqtt_parser_t* parser, mqtt_message_t* message, uint8_t* data, size_t len, size_t* nread) {
  static uint16_t cs                 = 0;
  const_data_descriptor_t src        = { data, len, len, 0 };
  void* dst[]                        = { ( void* ) &( parser->buffer ) };
  layer_state_t read_string_state    = LAYER_STATE_OK;

  BEGIN_CORO(cs)

  do {
    if (parser->state == MQTT_PARSER_STATE_INITIAL)
    {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->common.retain = (data[*nread + 0] >> 0) & 0x01;
        message->common.qos    = (data[*nread + 0] >> 1) & 0x03;
        message->common.dup    = (data[*nread + 0] >> 3) & 0x01;
        message->common.type   = (data[*nread + 0] >> 4) & 0x0f;

        *nread += 1;

        parser->state = MQTT_PARSER_STATE_REMAINING_LENGTH;

    }
    else if (parser->state == MQTT_PARSER_STATE_REMAINING_LENGTH)
    {
        parser->digit_bytes      = 0;
        parser->multiplier       = 1;
        parser->remaining_length = 0;

        do {
          parser->digit_bytes += 1;

          if ((len - *nread) == 0) {
            YIELD( cs, LAYER_STATE_WANT_READ )
            continue;
          }

          parser->remaining_length += (data[*nread] & 0x7f) * parser->multiplier;
          parser->multiplier *= 128;
          *nread += 1;
        } while (data[*nread] >= 0x80 && parser->digit_bytes < 4);

        if (data[*nread] >= 0x80) {
          parser->error = MQTT_ERROR_PARSER_INVALID_REMAINING_LENGTH;

          EXIT( cs, LAYER_STATE_ERROR )
        }

        message->common.length = parser->remaining_length;

        if (message->common.type == MQTT_TYPE_CONNECT)
        {
            parser->state = MQTT_PARSER_STATE_CONNECT;
        }
        else if (message->common.type == MQTT_TYPE_CONNACK)
        {
            parser->state = MQTT_PARSER_STATE_CONNACK;
        }
        else if (message->common.type == MQTT_TYPE_PUBLISH)
        {
            parser->state = MQTT_PARSER_STATE_PUBACK;
        }
        else if (message->common.type == MQTT_TYPE_PUBREC)
        {
            parser->state = MQTT_PARSER_STATE_PUBREC;
        }
        else if (message->common.type == MQTT_TYPE_PUBREL)
        {
            parser->state = MQTT_PARSER_STATE_PUBREL;
        }
        else if (message->common.type == MQTT_TYPE_PUBCOMP)
        {
            parser->state = MQTT_PARSER_STATE_PUBCOMP;
        }
        else
        {
            parser->error = MQTT_ERROR_PARSER_INVALID_MESSAGE_ID;
            EXIT( cs, LAYER_STATE_ERROR )
        }

      }
      else if (parser->state == MQTT_PARSER_STATE_VARIABLE_HEADER)
      {
        if (message->common.type == MQTT_TYPE_CONNECT)
        {
          parser->state = MQTT_PARSER_STATE_CONNECT_PROTOCOL_NAME;
        }
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT)
      {
        parser->state = MQTT_PARSER_STATE_CONNECT_PROTOCOL_NAME;
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_PROTOCOL_NAME)
      {
        READ_STRING(message->connect.protocol_name)

        parser->state = MQTT_PARSER_STATE_CONNECT_PROTOCOL_VERSION;
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_PROTOCOL_VERSION)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->connect.protocol_version = data[*nread];

        *nread += 1;

        parser->state = MQTT_PARSER_STATE_CONNECT_FLAGS;
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_FLAGS)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->connect.flags.username_follows = (data[*nread] >> 7) & 0x01;
        message->connect.flags.password_follows = (data[*nread] >> 6) & 0x01;
        message->connect.flags.will_retain      = (data[*nread] >> 5) & 0x01;
        message->connect.flags.will_qos         = (data[*nread] >> 4) & 0x02;
        message->connect.flags.will             = (data[*nread] >> 2) & 0x01;
        message->connect.flags.clean_session    = (data[*nread] >> 1) & 0x01;

        *nread += 1;

        parser->state = MQTT_PARSER_STATE_CONNECT_KEEP_ALIVE;

      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_KEEP_ALIVE)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->connect.keep_alive = (data[*nread] << 8);
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->connect.keep_alive += data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_CONNECT_CLIENT_IDENTIFIER;
      }

      else if (parser->state == MQTT_PARSER_STATE_CONNECT_CLIENT_IDENTIFIER)
      {
        READ_STRING(message->connect.client_id)

        parser->state = MQTT_PARSER_STATE_CONNECT_WILL_TOPIC;
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_WILL_TOPIC)
      {
        if (message->connect.flags.will) {
          READ_STRING(message->connect.will_topic)
        }

        parser->state = MQTT_PARSER_STATE_CONNECT_WILL_MESSAGE;
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_WILL_MESSAGE)
      {
        if (message->connect.flags.will) {
          READ_STRING(message->connect.will_message)
        }

        parser->state = MQTT_PARSER_STATE_CONNECT_USERNAME;

      }
      else if (parser->state == MQTT_PARSER_STATE_CONNECT_USERNAME)
      {
        if (message->connect.flags.username_follows) {
          READ_STRING(message->connect.username)
        }

        parser->state = MQTT_PARSER_STATE_CONNECT_PASSWORD;
      }

      else if (parser->state == MQTT_PARSER_STATE_CONNECT_PASSWORD)
      {
        if (message->connect.flags.password_follows) {
          READ_STRING(message->connect.password)
        }

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else if (parser->state == MQTT_PARSER_STATE_CONNACK)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->connack._unused     = data[*nread];
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->connack.return_code = data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBLISH)
      {
        parser->state = MQTT_PARSER_STATE_PUBLISH_TOPIC_NAME;
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBLISH_TOPIC_NAME)
      {
        READ_STRING(message->publish.topic_name)

        parser->state = MQTT_PARSER_STATE_PUBLISH_MESSAGE_ID;
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBLISH_MESSAGE_ID) {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->publish.message_id = (data[*nread] << 8);
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->publish.message_id += data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBACK)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->puback.message_id = (data[*nread] << 8);
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->puback.message_id += data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBREC)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->pubrec.message_id = (data[*nread] << 8);
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->pubrec.message_id += data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBREL)
      {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->pubrel.message_id = (data[*nread] << 8);
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->pubrel.message_id += data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else if (parser->state == MQTT_PARSER_STATE_PUBCOMP) {
        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->pubcomp.message_id = (data[*nread] << 8);
        *nread += 1;

        if ((len - *nread) == 0) {
          YIELD( cs, LAYER_STATE_WANT_READ )
          continue;
        }

        message->pubcomp.message_id = data[*nread];
        *nread += 1;

        parser->state = MQTT_PARSER_STATE_INITIAL;

        EXIT( cs, LAYER_STATE_OK )
      }
      else
      {
        parser->error = MQTT_ERROR_PARSER_INVALID_STATE;

        EXIT( cs, LAYER_STATE_ERROR )
      }
  } while (1);

  END_CORO()
}
