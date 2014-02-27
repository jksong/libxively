// Copyright (c) 2003-2013, LogMeIn, Inc. All rights reserved.
// This is part of Xively C library, it is under the BSD 3-Clause license.

/**
 * \file 	nq_comm.h
 * \author 	junkeun song(jun361@etri.re.kr)
 * \brief   Implements nanoqplus_communication layer_ functions 
 */

#ifndef __NQ_COMM_H__
#define __NQ_COMM_H__

#include "connection.h"
#include "nos.h"

connection_t* nq_open_connection( const char* address, int32_t port );

int nq_send_data( connection_t* conn, const char* data, size_t size );

int nq_read_data( connection_t* conn, char* buffer, size_t buffer_size );

void nq_close_connection( connection_t* conn );

#endif // __NQ_COMM_H__
