#include <stdio.h>
#include "nemu.h"
#include <stddef.h>
#include <errno.h>
int init_monitor(int, char *[]);
void ui_mainloop(int);

int main(int argc, char *argv[])
{
	/* Initialize the monitor. */
	int is_batch_mode = init_monitor(argc, argv);

	/* Receive commands from user. */
	ui_mainloop(is_batch_mode);

	// uint32_t expr(char *, bool *);

	// FILE *fp = fopen("/home/hust/ics2019/nemu/tools/gen-expr/input", "r");
	// assert(fp != NULL);
	// char *line = NULL;
	// size_t len = 0;
	// ssize_t read;
	// bool success = true;
	// uint32_t result = 0;
	// char inputexprbuf[65536];
	// int fileline = 1;
	// bool all_success = true;
	// while ((read = getline(&line, &len, fp)) != EOF)
	// {
	// 	assert(strlen(line) < 65536);
	// 	strcat(inputexprbuf, line);
	// 	char answer[20];
	// 	sscanf(inputexprbuf, "%s", answer);
	// 	int answer_len = strlen(answer);
	// 	sscanf(inputexprbuf, "%u", &result);
	// 	if (result == expr(line + answer_len + 1, &success))
	// 	{
	// 		printf("success\n");
	// 		memset(inputexprbuf, 0, sizeof(inputexprbuf));
	// 	}
	// 	else
	// 	{
	// 		printf("error occurs in %d\n", fileline);
	// 		all_success = false;
	// 		break;
	// 	}
	// 	fileline++;
	// }
	// fclose(fp);
	// if (all_success)
	// {
	// 	printf("all success!\n");
	// }
	return 0;
}
