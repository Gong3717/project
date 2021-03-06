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
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "olsr_debug.h"
#include "olsr_conf.h"
#include "def.h"
#include "proc_proc_set.h"
#include "olsr_list.h"
#include "olsr_util.h"
#include "olsr_util_inline.h"

#define OLSR_MAX_DUPLICATE_MPR 50

/* static function prototypes */
static
void insert_proc_set(struct olsrv2 *olsr,
             union olsr_ip_addr orig_addr,
             olsr_u16_t seq_number,
             olsr_u8_t type);
static
OLSR_LIST *
search_proc_set(struct olsrv2 *olsr,
        union olsr_ip_addr orig_addr,
        olsr_u16_t seq_number,
        olsr_u8_t type);
static
olsr_bool delete_proc_set_for_timeout_handler(void *, void *, void *);
static
olsr_bool search_proc_set_handler(void *, void *, void *);


/* function implimentations */
void init_proc_set(struct olsrv2 *olsr)
{
  olsr->change_proc_set = OLSR_FALSE;
  OLSR_InitHashList(olsr->proc_set);
}

olsr_bool proc_proc_set(struct olsrv2 *olsr,
            const struct message_header *m)
{
  OLSR_LIST *retList = NULL;
  olsr_u8_t type;

  //4.5.2
  if ((m->semantics & 0x02) == 0){ //bit 2
    type = 0;
  }
  else{
    type = m->message_type;
  }
  retList = search_proc_set(olsr,
                m->orig_addr,
                m->message_seq_num,
                type);
  //4.5.2.1
  if (retList == NULL){
    insert_proc_set(olsr,
            m->orig_addr,
            m->message_seq_num,
            type);
    olsr->change_proc_set = OLSR_TRUE;
    return OLSR_TRUE;
  }else{
    OLSR_DeleteList_Search(retList);
    return OLSR_FALSE;
  }
}

void insert_proc_set(struct olsrv2 *olsr,
             union olsr_ip_addr orig_addr,
             olsr_u16_t seq_number,
             olsr_u8_t type)
{
  OLSR_PROC_TUPLE data;

  data.P_type = type;
  data.P_addr = orig_addr;
  data.P_seq_number = seq_number;

  get_current_time(olsr, &data.P_time);
  update_time(&data.P_time,(olsr_32_t)olsr->qual_cnf->duplicate_hold_time);

  //struct olsrv2
  OLSR_InsertList(&olsr->proc_set[olsr_hashing(olsr,&orig_addr)].list, &data, sizeof(OLSR_PROC_TUPLE));
}

void delete_proc_set_for_timeout(struct olsrv2 *olsr)
{
  olsr_time_t time;
  int i;
  get_current_time(olsr, &time);


  for (i = 0; i < HASHSIZE; i++)
  {
      if (OLSR_DeleteListHandler((void*)olsr,&olsr->proc_set[i].list, (void* )&time,
                &delete_proc_set_for_timeout_handler) == OLSR_TRUE)
      {
      olsr->change_proc_set = OLSR_TRUE;
      }
  }
}

olsr_bool delete_proc_set_for_timeout_handler(void* olsr, void *arg_a, void *arg_b)
{
  OLSR_PROC_TUPLE *data = NULL;
  olsr_time_t *todelete = NULL;

  data = (OLSR_PROC_TUPLE *)arg_a;
  todelete = (olsr_time_t *)arg_b;

  return (olsr_bool) (olsr_cmp_time(data->P_time, *todelete) < 0);
}


OLSR_LIST *
search_proc_set(struct olsrv2 *olsr,
              union olsr_ip_addr orig_addr,
              olsr_u16_t seq_number,
              olsr_u8_t type)
{
  OLSR_LIST *result = NULL;
  //WIN FIX: explicit typecast required
  char *search = (char *)olsr_malloc(sizeof(union olsr_ip_addr)+sizeof(olsr_u16_t)+sizeof(olsr_u8_t), __FUNCTION__);

  memcpy(search, &orig_addr, sizeof(union olsr_ip_addr));
  search += sizeof(union olsr_ip_addr);
  memcpy(search, &seq_number, sizeof(olsr_u16_t));
  search += sizeof(olsr_u16_t);
  memcpy(search, &type, sizeof(olsr_u8_t));

  search -= sizeof(olsr_u16_t);
  search -= sizeof(union olsr_ip_addr);

  //struct olsrv2
  result =
    OLSR_SearchList((void*)olsr,&olsr->proc_set[olsr_hashing(olsr,&orig_addr)].list,
            (void* )&search, &search_proc_set_handler);

  free(search);
  return result;
}

//WIN FIX: changed type from void* to char*
olsr_bool search_proc_set_handler(void *olsr, void *arg_a, void *arg_vb)
{
  OLSR_PROC_TUPLE *data = NULL;
  union olsr_ip_addr *orig_addr = NULL;
  olsr_u16_t *seq_number = NULL;
  olsr_u8_t *type = NULL;

  //WIN FIX: changed type from void* to char*
  char *arg_b = (char *)arg_vb;

  data = (OLSR_PROC_TUPLE *)arg_a;
  orig_addr = (union olsr_ip_addr *)arg_b;
  arg_b += sizeof(union olsr_ip_addr);
  seq_number = (olsr_u16_t *)arg_b;
  arg_b += sizeof(olsr_u16_t);
  type = (olsr_u8_t *)arg_b;

  arg_b -= sizeof(olsr_u16_t);
  arg_b -= sizeof(union olsr_ip_addr);

  //WIN FIX: explicit typecast required
  return (olsr_bool)(equal_ip_addr((struct olsrv2* )olsr, &data->P_addr, orig_addr)
      && data->P_seq_number == *seq_number
      && data->P_type == *type);
}


void print_proc_set(struct olsrv2 *olsr)
{
  OLSR_LIST_ENTRY *tmp = NULL;
  OLSR_PROC_TUPLE *data = NULL;
  struct olsrd_config* olsr_cnf = olsr->olsr_cnf;
  int i;

  if (olsr_cnf->debug_level < 2)
    return;

  olsr_printf("--- Processed Set ---\n");
  //struct olsrv2
  for (i=0; i<HASHSIZE; i++)
  {
      tmp = olsr->proc_set[i].list.head;

      if (tmp != NULL){
      if (olsr_cnf->ip_version == AF_INET){
          char str[INET_ADDRSTRLEN];

          olsr_printf("%-16s %-12s %-12s\n", "P_addr", "P_seq_number", "P_time");
          while (tmp != NULL){
          char time[30];

          data = (OLSR_PROC_TUPLE *)tmp->data;
          //WIN FIX: Need to resolve this
          //inet_ntop(AF_INET, &data->P_addr.v4, str, sizeof(str));
          ConvertIpv4AddressToString(data->P_addr.v4, str);

          qualnet_print_clock_in_second(data->P_time, time);
          olsr_printf("%-16s %-12d %s [sec]\n", str, data->P_seq_number, time);

          tmp = tmp->next;
          }

      }

      else if (olsr_cnf->ip_version == AF_INET6){
          char str[INET6_ADDRSTRLEN];

          olsr_printf("%-46s %-12s %-12s\n", "P_addr", "P_seq_number", "P_time");
          while (tmp != NULL){
          char time[30];

          data = (OLSR_PROC_TUPLE *)tmp->data;
          //WIN FIX: Need to resolve this
          //inet_ntop(AF_INET6, data->P_addr.v6.s6_addr, str, sizeof(str));
          ConvertIpv6AddressToString(&data->P_addr.v6, str, OLSR_FALSE);

          qualnet_print_clock_in_second(data->P_time, time);
          olsr_printf("%-46s %-12d %s [sec]\n", str, data->P_seq_number, time);

          tmp = tmp->next;
          }

      }

      else{
          olsr_error("Un known ip_version");
          assert(OLSR_FALSE);
      }
      }
  }
  olsr_printf("-------------------\n");
}
