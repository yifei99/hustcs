#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static WP virtual_head = {.NO = -1, .next = NULL};
static WP virtual_free_ = {.NO = -1, .next = NULL};

void init_wp_pool()
{
  int i;
  for (i = 0; i < NR_WP; i++)
  {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
    memset(wp_pool[i].expression, 0, sizeof(wp_pool[0].expression));
    wp_pool[i].old_val = 0; //default value
  }
  wp_pool[NR_WP - 1].next = NULL;
  head = &virtual_head;
  free_ = &virtual_free_;
  virtual_free_.next = &wp_pool[0];
}
void insert_wp_list(WP *head, WP *node)
{
  WP *p = head;
  while (p->next != NULL && p->next->NO < node->NO)
  {
    p = p->next;
  }
  node->next = p->next;
  p->next = node;
  return ;
}
WP *new_wp()
{
  WP *p = free_;
  assert(p->next != NULL);
  WP *ret = p->next;
  p->next = p->next->next;

  insert_wp_list(head, ret);

  return ret;
}
void free_wp(int NO_to_delete,bool *success)
{
  WP *p = head;
  while (p->next)
  {
    if (p->next->NO == NO_to_delete)
    {
      WP *temp = p->next;
      p->next = p->next->next;

      insert_wp_list(free_, temp);

      temp->old_val = 0;
      memset(temp->expression, 0, sizeof(temp->expression));

      return ;
    }
    else
    {
      p = p->next;
    }
  }
  *success=false;
  return ;
}
WP* get_head()
{
  return head;
}
// WP* get_free_()
// {
//   return free_;
// }
void visit_wp(WP *head)
{
  WP *p=head;
  while(p->next)
  {
    printf("Watchpoint %d : %s -> %08x\n", p->next->NO, p->next->expression, p->next->old_val);
    p=p->next;
  }
  return ;
}
/* TODO: Implement the functionality of watchpoint */
