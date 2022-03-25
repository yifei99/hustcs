#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum
{
  TK_NOTYPE = 256,
  TK_ADD,
  TK_EQ,
  TK_LP,
  TK_RP,
  TK_DEC,
  TK_STAR,
  TK_DIV,
  TK_NONEQ,
  TK_HEXINT,
  TK_INT,
  TK_REGISTER_VALUE,
  TK_AND,
  TK_DEREF,
  TK_PREFIXDEC

  /* TODO: Add more token types */

};

static struct rule
{
  char *regex;
  int token_type;
} rules[] = {

    /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

    {" +", TK_NOTYPE}, // spaces
    {"\\+", TK_ADD},   // plus
    {"==", TK_EQ},     // equal
    {"\\(", TK_LP},
    {"\\)", TK_RP},
    {"-", TK_DEC},
    {"\\*", TK_STAR},
    {"/", TK_DIV},
    {"u", TK_NOTYPE},
    {"\n", TK_NOTYPE},
    {"!=", TK_NONEQ},
    {"0x[0-9|a-f|A-F]+", TK_HEXINT},
    {"[0-9]+", TK_INT},
    {"\\$[0-9|a-z]+", TK_REGISTER_VALUE},
    {"&&", TK_AND}

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++)
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0)
    {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token
{
  int type;
  char str[32];
} Token;

static Token tokens[10000] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool make_token(char *e)
{
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  int count_TK = 0;
  while (e[position] != '\0')
  {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++)
    {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
      {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type)
        {
        case TK_INT:
          tokens[nr_token].type = TK_INT;
          assert(substr_len < 33);                                 //assert??
          strncpy(tokens[nr_token].str, substr_start, substr_len); //copy
          tokens[nr_token].str[substr_len] = '\0';
          nr_token++;
          break;
        case TK_HEXINT:
          tokens[nr_token].type = TK_HEXINT;
          assert(substr_len < 11);                                 //assert??
          strncpy(tokens[nr_token].str, substr_start, substr_len); //copy
          tokens[nr_token].str[substr_len] = '\0';
          nr_token++;
          break;
        case TK_REGISTER_VALUE:
          tokens[nr_token].type = TK_REGISTER_VALUE;
          assert(substr_len < 35);                                 //assert??
          strncpy(tokens[nr_token].str, substr_start, substr_len); //copy
          tokens[nr_token].str[substr_len] = '\0';
          nr_token++;
          break;
        case TK_NOTYPE:
          break;
        default:
          tokens[nr_token].type = rules[i].token_type;
          nr_token++;
          break;
        }

        break;
      }
    }
    if (i == NR_REGEX)
    {
      printf("match tokens time: %d\n", count_TK);
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
    count_TK++;
  }
  printf("match tokens: %d\n", count_TK);

  for (i = 0; i < nr_token; i++)
  {
    if (tokens[i].type == TK_STAR && (i == 0 || tokens[i - 1].type == TK_LP || tokens[i - 1].type == TK_ADD || tokens[i - 1].type == TK_DEC || tokens[i - 1].type == TK_STAR || tokens[i - 1].type == TK_DIV || tokens[i - 1].type == TK_EQ || tokens[i - 1].type == TK_NONEQ || tokens[i - 1].type == TK_AND))
    {
      tokens[i].type = TK_DEREF;
    }
  }
  for (i = 0; i < nr_token; i++)
  {
    if (tokens[i].type == TK_DEC && (i == 0 || tokens[i - 1].type == TK_LP || tokens[i - 1].type == TK_ADD || tokens[i - 1].type == TK_DEC || tokens[i - 1].type == TK_STAR || tokens[i - 1].type == TK_DIV || tokens[i - 1].type == TK_EQ || tokens[i - 1].type == TK_NONEQ || tokens[i - 1].type == TK_AND))
    {
      tokens[i].type = TK_PREFIXDEC;
    }
  }
  return true;
}
bool check_parentheses(int p, int q, bool *success)
{
  int NUMLP = 0;
  int i = 0;
  for (; i <= q; i++)
  {
    if (tokens[i].type == TK_LP)
      NUMLP++;
    else if (tokens[i].type == TK_RP)
      NUMLP--;
    if (NUMLP < 0)
    {
      *success = false;
      return false;
    }
  }
  if (NUMLP < 0)
  {
    *success = false;
    return false;
  }
  // judge if the number of LP and RP are same

  NUMLP = 0;
  for (i = p; i <= q; i++)
  {
    if (tokens[i].type == TK_LP)
      NUMLP++;
    else if (tokens[i].type == TK_RP)
      NUMLP--;
    if (i != q && NUMLP == 0) //such as :(4 + 3) * (2 - 1)
    //false, the leftmost '(' and the rightmost ')' are not matched
    {
      return false;
    }
  }
  return true;
}
int find_maincalsymbol(int p, int q, bool *success)
{
  int starpos = -1, addpos = -1, eqpos = -1, andpos = -1;
  int i = p, LPNUM = 0;
  ;
  for (; i <= q; i++)
  {
    if (tokens[i].type == TK_LP)
    {
      LPNUM++;
    }
    else if (tokens[i].type == TK_RP)
    {
      LPNUM--;
    }
    if (LPNUM > 0)
      continue;
    // count over

    if (tokens[i].type == TK_STAR || tokens[i].type == TK_DIV)
    {
      starpos = i;
    }
    if (tokens[i].type == TK_ADD || tokens[i].type == TK_DEC)
    {
      addpos = i;
    }
    if (tokens[i].type == TK_EQ || tokens[i].type == TK_NONEQ)
    {
      eqpos = i;
    }
    if (tokens[i].type == TK_AND)
    {
      andpos = i;
    }
  }
  int ret = -1;
  if (andpos == -1)
  {
    if (eqpos == -1)
    {
      if (addpos == -1)
      {
        if (starpos != -1)
          ret = starpos;
      }
      else
        ret = addpos;
    }
    else
      ret = eqpos;
  }
  else
    ret = andpos;
  if (ret == -1)
  {
    *success = false;
    return 0;
  }
  // assert(ret != -1);
  return ret;
}
uint32_t eval(int p, int q, bool *success)
{
  if (p > q)
  {
    /* Bad expression */
    *success = false;
    return 0;
  }
  else if (p == q)
  {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    uint32_t number = 0;
    switch (tokens[p].type)
    {
    case TK_INT:
      sscanf(tokens[p].str, "%u", &number);
      break;
    case TK_HEXINT:
      sscanf(tokens[p].str + 2, "%x", &number);
      break;
    case TK_REGISTER_VALUE:
    {
      uint32_t isa_reg_str2val(const char *, bool *);
      number = isa_reg_str2val(tokens[p].str, success);
      break;
    }
    default:
      break;
    }
    return number;
  }
  else if (check_parentheses(p, q, success) == true)
  {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    int number = eval(p + 1, q - 1, success);
    if (*success == false)
    {
      return 0;
    }
    return number;
  }
  else
  {
    if (*success == false)
    {
      return 0;
    }
    if (q == p + 1)
    {
      uint32_t val = 0;
      if(tokens[p].type == TK_DEREF)
      {
        uint32_t paddr_read(paddr_t, int);
        val = eval(p+1, q, success);
        if(*success == false)
        {
					return 0;
				}
        val = paddr_read(val, 1);
				return val;
      }
      else if(tokens[p].type == TK_PREFIXDEC)
      {
        val = eval(p+1, q, success);
        if(*success == false)
        {
					return 0;
				}
        val = ~val +1;
				return val;
      }
      else{
				/* now impossibly get other situation*/
				assert(0);
			}
    }
    else
    {

      int op = find_maincalsymbol(p, q, success);
      if (*success == false)
      {
        return 0;
      }
      uint32_t val1 = eval(p, op - 1, success);
      if (*success == false)
      {
        return 0;
      }
      uint32_t val2 = eval(op + 1, q, success);
      if (*success == false)
      {
        return 0;
      }
      switch (tokens[op].type)
      {
      case TK_ADD:
        return val1 + val2;
      case TK_DEC:
        return val1 - val2;
      case TK_STAR:
        return val1 * val2;
      case TK_DIV:
        if (val2 == 0)
        {
          *success = false;
          return 0;
        }
        return val1 / val2;
      case TK_EQ:
        return (val1 == val2) ? 1 : 0;
      case TK_NONEQ:
        return (val1 != val2) ? 1 : 0;
      case TK_AND:
        return (val1 == 1 && val2 == 1) ? 1 : 0;
      default:
        assert(0);
      }
    }
  }
}
uint32_t expr(char *e, bool *success)
{
  if (!make_token(e))
  {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  uint32_t val = eval(0, nr_token - 1, success);
  return val;
}
