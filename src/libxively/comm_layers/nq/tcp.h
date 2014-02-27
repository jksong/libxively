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
 * @brief Header for the UDP.
 * @author Jongsoo Jeong (ETRI)
 * @author Junkeun Song (ETRI)
 * @date 2013. 8. 16.
 */

/*
 * $LastChangedDate$
 * $Id$
 */

#ifndef TCP_H
#define TCP_H


#define TCP_MAX_CONNS	10	// max conn
#define TCP_MAX_EVENTS	20


#define TCP_TIMER_INTERVAL	300	// in millisecond

#define TMP_IP_MTU	127	
#define DEFAULT_MSS	100

// to limit using heap memory for buffer
#define TCP_LIMIT_SND_BUF	2048		
#define TCP_LIMIT_RCV_BUF	2048

// defalut window size for send & recv. at least (2*DEFAULT_MSS) 
#define TCP_DEFAULT_SND_WND		(4*DEFAULT_MSS)	
#define TCP_DEFAULT_RCV_WND		(4*DEFAULT_MSS)


#define MSG_DONTWAIT	1



// 
/**
 * @brief Initialize the TCP protocol.
 *
 * Initialize the TCP port list.
 */
extern void nos_tcp_init(void);

/**
 * @brief Open a TCP connection.
 *
 * Send a segment using established connection @a conn_idx .
 *
 * The segment is at @a buf and has @a len bytes.
 *
 * @param[in] tcp_conn_idx The index of tcp connection.
 *
 * @param[in] buf The segment to be sent.
 *
 * @param[in] len The length of @a buf.
 *
 * @return index of established tcp connection. -1 if  An error code.
 */
extern int nos_tcp_connect(IP6_ADDRESS ip, UINT16 port);

// 바로 오픈. or 할당만 하고 추후 오픈?
// contiki는 나중에 오픈함.

/**
 * @brief Close a tcp connection.
 *
 * Close the connection and put in a closing state.
 *
 * Resources are freed in tcp timer.
 *
 * @param[in] tcp_conn_idx The index of tcp connection.
 *
 * @return An error code.
 */
extern int nos_tcp_close(UINT8 tcp_conn_idx);


/**
 * @brief Send a segment.
 *
 * Send a segment using established connection @a conn_idx .
 *
 * The segment is at @a buf and has @a len bytes.
 *
 * @param[in] tcp_conn_idx The index of tcp connection.
 *
 * @param[in] buf The segment to be sent.
 *
 * @param[in] len The length of @a buf.
 *
 * @return An error code.
 */
extern int nos_tcp_send(UINT8 tcp_conn_idx,void *user_data, UINT16 len);

/**
 * @brief Pass an IPv6 packet to the UDP layer to receive.
 *
 * Pass the UDP packet @a udp whose IPv6 header is @a ip6, and head of PACKET
 * list is @a head to the UDP layer. Then, post @link udp_recv_task() @endlink
 * to the Task Queue.
 *
 * @param[in] head
 *
 * @param[in] ip6
 *
 * @param[in] udp
 *
 * @return
 */

extern int nos_tcp_recv(UINT8 tc_idx, void *buf, UINT16 len, UINT8 flags);


extern int nos_tcp_bind(IP6_ADDRESS ip, UINT16 port);

extern  ERROR_T nos_tcp_listen(UINT8 tc_idx);

extern int nos_tcp_accept(UINT8 listen_tc_idx, IP6_ADDRESS *cli_ip, UINT16 *cli_port);


#endif
