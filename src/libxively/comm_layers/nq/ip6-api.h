// -*- c-file-style:"bsd"; c-basic-offset:4; indent-tabs-mode:nil; -*-
/*
 * Copyright (c) 2013
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
 * IPv6 Application Programming Interface
 *
 * @author Jongsoo Jeong (ETRI)
 * @date 2013. 11. 28.
 */

#ifndef IP6_API_H
#define IP6_API_H

#include "ip6-address.h"

/**
 * @brief Parse @p src IPv6 address to abbreviated string type, and store it to @p dst.
 *
 * @param[in] src The IPv6 address to be parsed.
 * @param[in] dst The buffer pointer where parsed address should be stored in.
 *
 * @return Parsed string.
 */
extern char *ip6_ntop(const IP6_ADDRESS *src, char *dst);


/**
 * @brief Parse @p src text form ipv6 address to binary type, and store it to @p dst.
 *
 * @param[in] src Text formed IPv6 address.
 * @param[in] dst numeric IPv6 address.
 *
 * @return return 1 if the parsing succeeds. 
			return 0 if src is not a valid ipv6 address. 
			return -1 for error.
 */
extern int ip6_pton(char *src, IP6_ADDRESS *dst);




#endif //IP6_API_H
