// -*- c-file-style:"bsd"; c-basic-offset:4; indent-tabs-mode:nil; -*-
/*
 * Copyright (c) 2006-2013
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
 * API for TCP
 *
 * @author Junkeun Song (ETRI)
 * @author Jongsoo Jeong (ETRI)
 * @date 2014. 2. 27.
 */

#ifndef TCP_API_H
#define TCP_API_H

/**
 * @brief Initialize the TCP protocol.
 *
 * Initialize the TCP port list.
 */
void tcp_core_init(UINT8 max_conn);

/**
 * @brief Open a TCP connection.
 *
 * Send a segment using established connection @a conn_idx .
 * The segment is at @a buf and has @a len bytes.
 *
 * @param[in] tcp_conn_idx The index of tcp connection.
 * @param[in] buf The segment to be sent.
 * @param[in] len The length of @a buf.
 *
 * @return index of established tcp connection. -1 if  An error code.
 */
int tcp_connect(IP6_ADDRESS ip, UINT16 port);

/**
 * @param[in] listening tcp_conn index
 * @param[out] client ip address, client port
 *
 * @return new connection index
 */
int tcp_accept(UINT8 listen_tc_idx, IP6_ADDRESS *cli_ip, UINT16 *cli_port);

ERROR_T tcp_listen(UINT8 tc_idx);

int tcp_bind(IP6_ADDRESS ip, UINT16 port);

#define MSG_DONTWAIT	1

/**
 *
 */
int tcp_recv(UINT8 tc_idx, void *buf, UINT16 len, UINT8 flags);

/**
 * @brief Send a segment.
 *
 * Send a segment using established connection @a conn_idx .
 * The segment is at @a buf and has @a len bytes.
 *
 * @param[in] tcp_conn_idx The index of tcp connection.
 * @param[in] buf The segment to be sent.
 * @param[in] len The length of @a buf.
 *
 * @return An error code.
 */
int nos_tcp_send(UINT8 tcp_conn_idx,void *user_data, UINT16 len);

int tcp_send(UINT8 tcp_conn_idx,void *user_data, UINT16 len);

/**
 * @brief Close a tcp connection.
 *
 * Close the connection and put in a closing state.
 * Resources are freed in tcp timer.
 *
 * @param[in] tcp_conn_idx The index of tcp connection.
 *
 * @return An error code.
 */
int tcp_close(UINT8 tc_idx);


/**
 * @brief Get # of max connection initalized.
 *
 * return a value initalized by tcp_core_init();
 *
 * @return the number of maximum connections.
 */
UINT8 get_tcp_max_conn();


#endif //TCP_API_H
