// Copyright (c) 2003-2013, LogMeIn, Inc. All rights reserved.
// This is part of Xively C library, it is under the BSD 3-Clause license.

/**
 * \file    nq_comm_layer_data_specific.h
 * \author 	junkeun song(jun361@etri.re.kr)
 * \brief   Declares layer-specific data structure
 */

#ifndef __NQ_COMM_LAYER_DATA_SPECIFIC_H__
#define __NQ_COMM_LAYER_DATA_SPECIFIC_H__

typedef struct {
    unsigned int tc_idx;	// index of a tcp connection 
} nq_comm_layer_data_specific_t;

#endif // __NQ_COMM_LAYER_DATA_SPECIFIC_H__
