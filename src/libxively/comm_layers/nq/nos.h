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
 * Application Programming Interfaces for user applications
 *
 * @author Sangcheol Kim (ETRI)
 * @author Haeyong Kim (ETRI)
 * @author Jongsoo Jeong (ETRI)
 */

#ifndef NOS_H
#define NOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nq_typedef.h"
#include "errorcodes.h"

#include "ip6-api.h"


#include "tcp.h"
#define tcp_init()	nos_tcp_init()
#define tcp_test(port)	nos_tcp_test(port)
#define tcp_connect(ip6, port)	nos_tcp_connect(ip6,port)
#define tcp_accept(listen_idx, cli_ip,cli_port)	nos_tcp_accept(listen_idx,cli_ip, cli_port);
#define tcp_listen(tc_idx)	nos_tcp_listen(tc_idx)
#define tcp_bind(ip,port)	nos_tcp_bind(ip,port)
#define tcp_recv(idx,buf,len,f)	nos_tcp_recv(idx,buf,len,f)
#define tcp_send(idx,buf,len)	nos_tcp_send(idx,buf,len)
#define tcp_close(idx)	nos_tcp_close(idx)



#endif /* NOS_H */
