// Copyright (c) 2003-2013, LogMeIn, Inc. All rights reserved.
// This is part of Xively C library, it is under the BSD 3-Clause license.
#include "comm_layer.h"
#include "nq_comm.h"

/**
 * \file 	nq_comm_layer.c
 * \author 	junkeun song(jun361@etri.re.kr)
 * \brief   Implements nq_communication layer_ functions [see comm_layer.h]
 */

 /**
  * \brief   Initialise nq implementation of the nq_communication layer_
  */
const comm_layer_t* get_comm_layer()
{
    static comm_layer_t __nq_comm_layer =
    {
          &nq_open_connection
        , &nq_send_data
        , &nq_read_data
        , &nq_close_connection
    };

    return &__nq_comm_layer;
}
