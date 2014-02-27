// Copyright (c) 2003-2013, LogMeIn, Inc. All rights reserved.
// This is part of Xively C library, it is under the BSD 3-Clause license.

/**
 * \file    nq_comm.c
 * \author  junkeun song(jun361@etri.re.kr)
 * \brief   Implements nq_communication layer_ abstraction interface [see comm_layer.h]
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "nq_comm.h"
#include "comm_layer.h"
#include "xi_helpers.h"
#include "xi_allocator.h"
#include "nq_comm_layer_data_specific.h"
#include "xi_debug.h"
#include "xi_err.h"
#include "xi_macros.h"
#include "xi_globals.h"

char *ipv6_xively_address = "2001:470:1f10:333::2";

// param address is ignored. 'ipv6_xively_address' is used instead of 'address'.
connection_t* nq_open_connection( const char* address, int32_t port )
{
    // PRECONDITIONS
    //assert( address != 0 );	// address is ignored

	// DNS isn't supported in nanoqplus.
	// Using IPv6 address in https://xively.com/dev/docs/api/communicating/
	IP6_ADDRESS ip6_addr;
	ip6_pton(ipv6_xively_address, &ip6_addr);


    // variables
    nq_comm_layer_data_specific_t* nq_comm_data   = 0;
    connection_t* conn                                  = 0;

    // allocate memory for the nq data specific structure
    nq_comm_data
        = ( nq_comm_layer_data_specific_t* ) xi_alloc(
                sizeof( nq_comm_layer_data_specific_t ) );

    XI_CHECK_MEMORY( nq_comm_data );

    // allocate memory for the connection layer
    conn
        = ( connection_t* ) xi_alloc(
                sizeof( connection_t ) );

    XI_CHECK_MEMORY( conn );

    // make copy of an address
    conn->address = xi_str_dup( ipv6_xively_address );	
    conn->port = port;

    XI_CHECK_MEMORY( conn->address );

	// initalize the tcp connection
	nq_comm_data->tc_idx = tcp_connect(ip6_addr, port);	// blocked for handshaking
	if( nq_comm_data->tc_idx == TCP_MAX_CONNS)
	{
        xi_set_err( XI_SOCKET_CONNECTION_ERROR );
        goto err_handling;
    }
	
	// remember the layer specific part
    conn->layer_specific = ( void* ) nq_comm_data;

    // POSTCONDITIONS
    assert( conn != 0 );
    assert( nq_comm_data->tc_idx != ERROR_FAIL );

    return conn;

err_handling:
    // cleanup the memory
    if( nq_comm_data ) { XI_SAFE_FREE( nq_comm_data ); }
    if( conn ) { XI_SAFE_FREE( conn->address ); }
    XI_SAFE_FREE( conn );

    return (connection_t*)0;
}

int nq_send_data( connection_t* conn, const char* data, size_t size )
{
    // PRECONDITIONS
    assert( conn != 0 );
    assert( conn->layer_specific != 0 );
    assert( data != 0 );
    assert( size != 0 );

    // extract the layer specific data
    nq_comm_layer_data_specific_t* nq_comm_data
        = ( nq_comm_layer_data_specific_t* ) conn->layer_specific;


	int bytes_written = tcp_send( nq_comm_data->tc_idx, data, size);

    if( bytes_written == - 1 )
    {
        xi_set_err( XI_SOCKET_WRITE_ERROR );
    }

    // store the value
    conn->bytes_sent += bytes_written;

    return bytes_written;
}

int nq_read_data( connection_t* conn, char* buffer, size_t buffer_size )
{
    // PRECONDITIONS
    assert( conn != 0 );
    assert( conn->layer_specific != 0 );
    assert( buffer != 0 );
    assert( buffer_size != 0 );

    // extract the layer specific data
    nq_comm_layer_data_specific_t* nq_comm_data
        = ( nq_comm_layer_data_specific_t* ) conn->layer_specific;

    memset( buffer, 0, buffer_size );

	// blocking recv. use MSG_DONTWAIT flag for non-blocking
	int bytes_read = tcp_recv( nq_comm_data->tc_idx, buffer, buffer_size,0 );	

    if( bytes_read == -1 )
    {
        xi_set_err( XI_SOCKET_READ_ERROR );
    }

    // store the value
    conn->bytes_received += bytes_read;

    return bytes_read;
}

void nq_close_connection( connection_t* conn )
{
    // PRECONDITIONS
    assert( conn != 0 );

    // extract the layer specific data
    nq_comm_layer_data_specific_t* nq_comm_data
        = ( nq_comm_layer_data_specific_t* ) conn->layer_specific;

    // close the connection & the socket
    if( tcp_close( nq_comm_data->tc_idx ) == -1 )
    {
        xi_set_err( XI_SOCKET_CLOSE_ERROR );
        goto close_err_handling;
    }

	// success
	return;

close_err_handling:
    // cleanup the memory
    if( conn ) { XI_SAFE_FREE( conn->layer_specific ); }
    if( conn ) { XI_SAFE_FREE( conn->address ); }
    XI_SAFE_FREE( conn );

    return;
}
