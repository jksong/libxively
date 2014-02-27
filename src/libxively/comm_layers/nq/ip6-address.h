// -*- c-basic-offset:4; tab-width:4; indent-tabs-mode:nil; -*-
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
 * IPv6 Address
 *
 * @author Jongsoo Jeong (ETRI)
 * @date 2013. 6. 17.
 */

#ifndef IP6_ADDRESS_H
#define IP6_ADDRESS_H

enum ip6_addrtype
{
    IP6_ADDRTYPE_GLOBAL       = (-1),
    IP6_ADDRTYPE_ANY          = (-2),
    IP6_ADDRTYPE_UNSPECIFIED  = (-3),
    IP6_ADDRTYPE_LINKLOCAL    = (-4),
    IP6_ADDRTYPE_MULTICAST    = (-5),
    IP6_ADDRTYPE_LOOPBACK     = (-6),
};
typedef INT8 IP6_ADDRTYPE;

/**
 * @brief Unicast IPv6 address
 */
#pragma pack(1)
struct ip6_unicast
{
    UINT8 prefix[8];
    UINT8 iid[8];
} ;
#pragma pack()
typedef struct ip6_unicast IP6_UNICAST;

enum ip6_mc_gid
{
    MC_GID_LENGTH = 14,
};

/**
 * @brief Multicast IPv6 address
 */
#pragma pack(1)
struct ip6_multicast
{
    UINT8 prefix;
    UINT8 flag_scope;
    UINT8 group_id[MC_GID_LENGTH];
};
#pragma pack()
typedef struct ip6_multicast IP6_MULTICAST;

/**
 * @brief IPv6 address
 */
#pragma pack(1)
union ip6_address
{
    UINT8 s6_addr[16];      // 'struct in6_addr'-compatible
    UINT16 s6_addr16[8];    // 'struct in6_addr'-compatible
    UINT32 s6_addr32[4];    // 'struct in6_addr'-compatible

    IP6_UNICAST u;
    IP6_MULTICAST m;
};
#pragma pack()
typedef union ip6_address IP6_ADDRESS;

enum ip6_maddr_wellknown_scope
{
    MADDR_WELLKNOWN_SCOPE_NODELOCAL = 0x01,
    MADDR_WELLKNOWN_SCOPE_LINKLOCAL = 0x02,
    MADDR_WELLKNOWN_SCOPE_SITELOCAL = 0x05,
    MADDR_WELLKNOWN_SCOPE_ORGNLOCAL = 0x08,
};

#define UNSPECIFIED_ADDR                                                \
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define LOOPBACK_ADDR                                                   \
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01"
#define UNICAST_LL_PREFIX                       \
    "\xFE\x80\x00\x00\x00\x00\x00\x00"

/// Well-known multicast group IDs.
enum ip6_mcgid
{
    MCGID_ALL_NODE = 1,
    MCGID_ALL_RT = 2,
    MCGID_ALL_RPL_NODES = 0x1a,
};

#define MADDR_LL_ALL_NODE                                               \
    "\xFF\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01"
#define MADDR_LL_ALL_ROUTER                                             \
    "\xFF\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02"
#define MADDR_LL_ALL_RPL_NODE                                           \
    "\xFF\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1A"

// ff02::1:ff00/104
#define MADDR_LL_SOLICITED_NODE                             \
    "\xFF\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\xFF"

#define NOS_IP6_SET_MADDR_LL_ALL_NODE(p_addr)   \
    memcpy((p_addr), MADDR_LL_ALL_NODE, 16)

#define NOS_IP6_IS_MADDR_LL_ALL_NODE(p_addr)        \
    (memcmp((p_addr), MADDR_LL_ALL_NODE, 16) == 0)

#define NOS_IP6_SET_MADDR_LL_ALL_ROUTER(p_addr) \
    memcpy((p_addr), MADDR_LL_ALL_ROUTER, 16)

#define NOS_IP6_IS_MADDR_LL_ALL_ROUTER(p_addr)          \
    (memcmp((p_addr), MADDR_LL_ALL_ROUTER, 16) == 0)

#define NOS_IP6_SET_MADDR_LL_ALL_RPL_NODE(p_addr)   \
    memcpy((p_addr), MADDR_LL_ALL_RPL_NODE, 16)

#define NOS_IP6_IS_MADDR_LL_ALL_RPL_NODE(p_addr)        \
    (memcmp((p_addr), MADDR_LL_ALL_RPL_NODE, 16) == 0)

#define NOS_IP6_SET_MADDR_LL_SOLICITED_NODE(p_dst, p_sol_iid)   \
    do {                                                        \
        memcpy((p_dst), MADDR_LL_SOLICITED_NODE, 13);           \
        (p_dst)->s6_addr[13] = (p_sol_iid)[5];                  \
        (p_dst)->s6_addr[14] = (p_sol_iid)[6];                  \
        (p_dst)->s6_addr[15] = (p_sol_iid)[7];                  \
    } while(0)

#define NOS_IP6_IS_MADDR_LL_SOLICITED_NODE(p_addr, p_sol_iid)   \
    (memcmp((p_addr), MADDR_LL_SOLICITED_NODE, 13) == 0 &&      \
     (p_addr)->s6_addr[13] == (p_sol_iid)[5] &&                 \
     (p_addr)->s6_addr[14] == (p_sol_iid)[6] &&                 \
     (p_addr)->s6_addr[15] == (p_sol_iid)[7])

/**
 * @brief A list node to manage global addresses by using linked-list.
 */
struct ip6_global_address
{
    IP6_ADDRESS addr;
    UINT16 lifetime;
};
typedef struct ip6_global_address IP6_GLOBAL_ADDRESS;


#endif //IP6_ADDRESS_H
