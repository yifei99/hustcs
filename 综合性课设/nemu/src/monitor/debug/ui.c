#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint64_t);
void isa_reg_display();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char *rl_gets()
{
  static char *line_read = NULL;

  if (line_read)
  {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read)
  {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args)
{
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args)
{
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args)
{
  if (args == NULL)
  {
    cpu_exec(1);
  }
  else
  {
    int cnt;
    sscanf(args, "%d", &cnt);
    cpu_exec(cnt);
  }
  return 0;
}
static int cmd_info(char *args)
{
  if (args != NULL && strcmp(args, "r") == 0)
  {
    isa_reg_display();
  }
  else if (args != NULL && strcmp(args, "w") == 0)
  {
    visit_wp(get_head());
  }
  return 0;
}
static int cmd_x(char *args)
{
  if (args == NULL)
  {
    printf("Please enter paddr and size\n");
    return 0;
  }
  char *first_pa = strtok(args, " ");
  uint32_t cnt1; //first parameter
  sscanf(first_pa, "%u", &cnt1);
  char *second_pa = first_pa + strlen(first_pa) + 1;
  uint32_t cnt2; //second parameter
  sscanf(second_pa, "%x", &cnt2);
  uint32_t paddr_read(paddr_t, int);
  int i = 0;
  for (; i < cnt1; i++)
  {
    printf("paddr %08x -> %08x\n", cnt2 + 4 * i, paddr_read(cnt2 + 4 * i, 4));
  }
  return 0;
}
static int cmd_p(char *args)
{
  bool success = true;
  uint32_t result = expr(args, &success);
  if (success == true)
  {
    printf("0x%08x\n", result);
    // printf("%d\n", result);
  }
  else
  {
    printf("Expression is not legal\n");
  }
  return 0;
}
static int cmd_w(char *args)
{
  bool success = true;
  uint32_t result = expr(args, &success);
  if (success == true)
  {
    WP *wp = new_wp();
    wp->old_val = result;
    assert(expr(args, &success) == result);
    assert(success == true);
    strcat(wp->expression, args);
    printf("Watchpoint %d: %s -> %08x\n", wp->NO, wp->expression, wp->old_val);
  }
  else
  {
    printf("Expression is not legal!\n");
  }
  return 0;
}
static int cmd_d(char *args)
{
  int NO_to_delete;
  bool success = true;
  sscanf(args, "%d", &NO_to_delete);
  free_wp(NO_to_delete, &success);
  if (success)
  {
    printf("Watchpoint %d deleted\n", NO_to_delete);
  }
  else
  {
    printf("can't find the watchpoint number!\n");
  }
  return 0;
}
// static int cmd_visit_wp_list(char *args)
// {
//   if (args != NULL && strcmp(args, "h") == 0)
//   {
//     visit_wp(get_head());
//   }
//   else if(args != NULL && strcmp(args, "f") == 0)
//   {
//     visit_wp(get_free_());
//   }
//   return 0;
// }
static struct
{
  char *name;
  char *description;
  int (*handler)(char *);
} cmd_table[] = {
    {"help", "Display informations about all supported commands", cmd_help},
    {"c", "Continue the execution of thSe program", cmd_c},
    {"q", "Exit NEMU", cmd_q},
    {"si", "Execution by step", cmd_si},
    {"info", "Print Registers", cmd_info},
    {"x", "Scan Memory", cmd_x},
    {"p", "Print value of expression", cmd_p},
    {"w", "Halt the program when the expression has changed", cmd_w},
    {"d", "delete a watchpoint", cmd_d},
    // {"v", "visit wp list", cmd_visit_wp_list}
    /* TODO: Add more commands */
};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args)
{
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL)
  {
    /* no argument given */
    for (i = 0; i < NR_CMD; i++)
    {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else
  {
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(arg, cmd_table[i].name) == 0)
      {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void ui_mainloop(int is_batch_mode)
{
  if (is_batch_mode)
  {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL;)
  {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL)
    {
      continue;
    }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end)
    {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue(void);
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(cmd, cmd_table[i].name) == 0)
      {
        if (cmd_table[i].handler(args) < 0)
        {
          return;
        }
        break;
      }
    }

    if (i == NR_CMD)
    {
      printf("Unknown command '%s'\n", cmd);
    }
  }
}
