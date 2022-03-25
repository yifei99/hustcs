#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h> //new

// this should be enough
int choose(int n);
static char *gen_num();
static char *gen_rand_op();
static char *gen_blank();
static char *gen_rand_expr();


#define GEN_BLANK_NUM 3
static char buf[65536];
static char code_buf[65536];
static char *code_format =
    "#include <stdio.h>\n"
    "int main() { "
    "  unsigned result = %s; "
    "  printf(\"%%u\", result); "
    "  return 0; "
    "}";

int main(int argc, char *argv[])
{
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1)
  {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i++)
  {
    char *str = gen_rand_expr();
    strcat(buf, str);
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0)
      continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    int x = fscanf(fp, "%d", &result);
    assert(x == 1);
    pclose(fp);

    printf("%u %s\n", result, buf);
    memset(buf, 0, sizeof(buf));
    free(str);
  }
  return 0;
}

int choose(int n)
{
  int r = rand();
  return r % n;
}
static char *gen_num()
{
  char *strtemp = (char *)malloc(40);
  int num = choose(0x3fffffff);
  sprintf(strtemp, "%du", num);
  return strtemp;
}
static char *gen_rand_op()
{
  char *strtemp = NULL;
  switch (choose(4))
  {
  case 0:
    strtemp = strdup("+");
    break;
  case 1:
    strtemp = strdup("-");
    break;
  case 2:
    strtemp = strdup("*");
    break;
  case 3:
    strtemp = strdup("/");
    break;
  }
  return strtemp;
}
static char *gen_blank()
{
  char *strblank = (char *)malloc(GEN_BLANK_NUM);
  memset(strblank, 0, GEN_BLANK_NUM);
  int i = choose(GEN_BLANK_NUM);
  for (; i > 0; i--)
  {
    strcat(strblank, " ");
  }
  strcat(strblank, "\0");
  return strblank;
}
static char *gen_rand_expr()
{
  char *strtemp = (char *)malloc(65536);
  memset(strtemp, 0, 65536);
  switch (choose(3))
  {
  case 0:
  {
    char *case1 = gen_num();
    strcat(strtemp, case1);
    free(case1);
    break;
  }
  case 1:
  {
    char *blank1 = gen_blank();
    char *blank2 = gen_blank();
    char *blank3 = gen_blank();
    char *case2 = gen_rand_expr();
    if (strlen(blank1) + strlen(blank2) + strlen(blank1) + strlen(case2) + 2 > 65535)
    {
      free(blank1);
      free(blank2);
      free(blank3);
      return case2;
    }
    strcat(strtemp, "(");
    strcat(strtemp, blank1);
    strcat(strtemp, case2);
    strcat(strtemp, blank2);
    strcat(strtemp, ")");
    strcat(strtemp, blank3);
    free(blank1);
    free(blank2);
    free(blank3);
    break;
  }
  default:
  {
    char *case3 = gen_rand_expr();
    char *case4 = gen_rand_op();
    char *case5 = gen_rand_expr();
    char *blank4 = gen_blank();
    char *blank5 = gen_blank();
    char *blank6 = gen_blank();
    if (strlen(case3) + strlen(case4) + strlen(case5) + strlen(blank4) + strlen(blank5) + strlen(blank6 + 40) > 65536)
    {
      free(case3);
      free(case4);
      free(blank4);
      free(blank5);
      free(blank6);
      return case5;
    }
    strcat(strtemp, case3);
    strcat(strtemp, blank4);
    strcat(strtemp, case4);
    strcat(strtemp, blank5);
    strcat(strtemp, "((");
    strcat(strtemp, case5);
    strcat(strtemp, ") / 1000000u + 1u)");
    strcat(strtemp, blank6);
    free(case3);
    free(case4);
    free(case5);
    free(blank4);
    free(blank5);
    free(blank6);
    break;
  }
  }
  return strtemp;
}
