#ifndef layer_INTERFACE_H__
#define layer_INTERFACE_H__

// C
#include <stdio.h>

// local
#include "layer_connectivity.h"

/**
 * \file    layer_interface.h
 * \author  Olgierd Humenczuk
 * \brief   Containes the layer interface implementation as long as base structure declarations
 *          required by the layer to work.
 */

/**
 * \brief   layer states it simplifies the between layer communication
 * \note    This is part of the standarized protocol of communication that
 *          has been designed in order to provide the minimum restrictions,
 *          in order to make the usage safe, with maximum capabilities. This
 *          structure may be used to provide very simple communication between layers.
 */
typedef enum
{
    LAYER_STATE_OK = 0,
    LAYER_STATE_FULL,
    LAYER_STATE_TIMEOUT,
    LAYER_STATE_ERROR
} layer_state_t;


/*
 * \brief   set of function types used across the layer system
 */
typedef layer_state_t ( on_demand_t )       ( layer_connectivity_t* context, char* buffer, size_t size, const char impulse );
typedef layer_state_t ( on_data_ready_t )   ( layer_connectivity_t* context, const char* buffer, size_t size, const char impulse );
typedef layer_state_t ( close_t )           ( layer_connectivity_t* context );
typedef layer_state_t ( on_close_t )        ( layer_connectivity_t* context );

/**
 * \struct layer_interface_t
 *
 * \brief   The raw interface of the purly raw layer that combines both: simplicity and functionality
 *     of the 'on demand processing' idea.
 *
 *              The design idea is based on the assumption that the communication with the server
 *          is bidirectional and the data is processed in packages. This interface design is
 *          very generic and allows to implement different approaches as an extension of the
 *          basic operations that the interface is capable of. In very basic scenario the client
 *          wants to send some number of bytes to the server and then awaits for the response.
 *          After receiving the response the response is passed by to the processing layer through
 *          on_data_ready function which signals the processing layer that there is new data to process.
 *
 *              Term 'on demand processing' refers to the processing managed by the connection.
 *          With the observation that all of the decision in the software depends on the network
 *          capabilities it is clear that only the connection has ability to give the signals about
 *          the processing to the rest of the components. The 'demand' takes it source in the
 *          connection and that is the layer that has command over the another layers.
 */
typedef struct layer_interface
{
    /**
     * \brief the function that is called whenever the prev layer wants more data to process/send over some kind of the connection
     */
    on_demand_t         *on_demand;

    /**
     * \brief the function that is called whenever there is data that is ready and it's source is the prev layer
     */
    on_data_ready_t     *on_data_ready;

    /**
     * \brief whenever the processing chain suppose to be closed
     */
    close_t             *close;

    /**
     * \brief whenver the processing chain is going to be closed it's source is in the prev layer
     */
    on_close_t          *on_close;

} layer_interface_t;



#endif
