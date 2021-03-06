/*
 *
 * Copyright (c) 2006, Graduate School of Niigata University,
 *                                         Ad hoc Network Lab.
 * Developer:
 *  Yasunori Owada  [yowada@net.ie.niigata-u.ac.jp],
 *  Kenta Tsuchida  [ktsuchi@net.ie.niigata-u.ac.jp],
 *  Taka Maeno      [tmaeno@net.ie.niigata-u.ac.jp],
 *  Hiroei Imai     [imai@ie.niigata-u.ac.jp].
 * Contributor:
 *  Keita Yamaguchi [kyama@net.ie.niigata-u.ac.jp],
 *  Yuichi Murakami [ymura@net.ie.niigata-u.ac.jp],
 *  Hiraku Okada    [hiraku@ie.niigata-u.ac.jp].
 *
 * This software is available with usual "research" terms
 * with the aim of retain credits of the software.
 * Permission to use, copy, modify and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies,
 * and the name of NIIGATA, or any contributor not be used in advertising
 * or publicity pertaining to this material without the prior explicit
 * permission. The software is provided "as is" without any
 * warranties, support or liabilities of any kind.
 * This product includes software developed by the University of
 * California, Berkeley and its contributors protected by copyrights.
 */
#ifndef __PROC_ASSN_HISTORY_SET_H
#define __PROC_ASSN_HISTORY_SET_H

#include <time.h>

#include "olsr_types.h"
#include "olsr_common.h"
#include "olsr_list.h"

#include "olsr.h"

typedef struct olsr_assn_history_tuple
{
  union olsr_ip_addr AS_Address;
  olsr_u16_t AS_seq;
  olsr_time_t AS_time;
}OLSR_ASSN_HISTORY_TUPLE;

/* function prototypes */
#if defined __cplusplus
extern "C" {
#endif
  void print_assn_history_set(struct olsrv2 *);
#if defined __cplusplus
}
#endif

void init_assn_history_set(struct olsrv2 *);

void delete_assn_history_set_for_timeout(struct olsrv2 *);

olsr_bool proc_assn_history_set(struct olsrv2*,
                union olsr_ip_addr *,
                olsr_u16_t);
#endif
