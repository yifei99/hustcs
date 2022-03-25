#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char expression[128];//watch point tag
  uint32_t old_val;//old val
  /* TODO: Add more members if necessary */

} WP;

WP* new_wp();
void free_wp(int NO_to_delete,bool *success);
WP* get_head();
// WP* get_free_();
void visit_wp(WP *head);
#endif
