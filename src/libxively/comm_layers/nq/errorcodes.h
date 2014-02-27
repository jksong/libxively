// -*- c-file-style:"bsd"; c-basic-offset:4; indent-tabs-mode:nil; -*-
/*
 * Copyright (c) 2006-2012
 * Electronics and Telecommunications Research Institute (ETRI)
 * All Rights Reserved.
 *
 * Following acts are STRICTLY PROHIBITED except when a specific prior written
 * permission is obtained from ETRI or a separate written agreement with ETRI
 * stipulates such permission specifically:
 *
 * a) Selling, distributing, sublicensing, renting, leasing, transmitting,
 * redistributing or otherwise transferring this software to a third party;
 *
 * b) Copying, transforming, modifying, creating any derivatives of, reverse
 * engineering, decompiling, disassembling, translating, making any attempt to
 * discover the source code of, the whole or part of this software in source or
 * binary form;
 *
 * c) Making any copy of the whole or part of this software other than one copy
 * for backup purposes only; and
 *
 * d) Using the name, trademark or logo of ETRI or the names of contributors in
 * order to endorse or promote products derived from this software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS," WITHOUT A WARRANTY OF ANY KIND. ALL
 * EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY
 * IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NON-INFRINGEMENT, ARE HEREBY EXCLUDED. IN NO EVENT WILL ETRI (OR ITS
 * LICENSORS, IF ANY) BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR FOR
 * DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE DAMAGES,
 * HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN
 * IF ETRI HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * Any permitted redistribution of this software must retain the copyright
 * notice, conditions, and disclaimer as specified above.
 */

/**
 * @brief Error codes
 * @author Jongsoo Jeong (ETRI)
 * @date 2011. 6. 20.
 */

#ifndef ERRORCODES_H_
#define ERRORCODES_H_

enum {
    SUCCESS_BYPASS = 4,
    SUCCESS_OPERATION_RESERVED = 3,
    SUCCESS_6LOWPAN_REASSEMBLY_COMPLETE = 2,
    SUCCESS_NOTHING_HAPPENED = 1,
    ERROR_SUCCESS = 0,
    ERROR_FAIL = -1,
    ERROR_GENERAL_FAILURE = -1, //TODO will be replaced to ERROR_FAIL.
    ERROR_NOT_ENOUGH_MEMORY = -2,
    ERROR_INVALID_ARGS = -3,
    ERROR_MORE_ARGS_REQUIRED = -4,
    ERROR_NOT_SUPPORTED = -5,
    ERROR_NOT_FOUND = -6,
    ERROR_BUSY = -7,

    //802.15.4 Communication errors: -31 ~ -40
    ERROR_802154_FRAME_TOO_BIG = -31,
    ERROR_802154_SECURING_FAIL = -32,
    ERROR_802154_UNSECURING_FAIL = -33,
    ERROR_802154_INVALID_SEC_FRAME = -34,
    ERROR_802154_INVALID_KEY_IDX = -35,
    ERROR_802154_TX_FAIL = -36,

    //6LoWPAN errors: -41 ~ -50
    ERROR_6LOWPAN_INVALID_FRAME = -41,
    ERROR_6LOWPAN_SEND_FAILURE = -42,
    ERROR_6LOWPAN_COMPRESSION_FAIL = -43,
    ERROR_6LOWPAN_DECOMPRESSION_FAIL = -44,
    ERROR_6LOWPAN_INVALID_CONTEXT = -45,

    //IP Communication errors: -51 ~ -60
    ERROR_IP6_TIME_EXCEEDED = -52,
    ERROR_IP6_INVALID_CHECKSUM = -53,
    ERROR_IP6_INVALID_PACKET = -54,
    ERROR_IP6_ADDR_DUPLICATE = -55,
    ERROR_IP6_UNKNOWN_SCOPE = -56,
    ERROR_IP6_NOT_READY = -57,
    ERROR_IP6_LINK_FAIL = -58,
    ERROR_ICMP6_INVALID_MESSAGE = -61,
    ERROR_COAP_REQUEST_TIMEOUT = -62,
    ERROR_RPL_IS_NOT_WORKING = -63,
};

typedef INT8 ERROR_T;

#endif
