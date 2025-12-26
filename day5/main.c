#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
/*
 * Start by identifying which updates are in the correct order.
 * Then determine the middle page number from each update.
 * Add the middle page numbers up.
 * */

int main(void) {
	//FILE *f = fopen("./input", "r");
	FILE *f = fopen("./smallexample", "r");
	if (f == NULL) {
		return -1;
	}
	int c;
	// Print our file
	int maxsizeline = 0;
	int sizeline = 0;
	while ((c = fgetc(f)) != EOF) {
		//putchar(c);
		if(c != '\n') sizeline++;
		else {
			if (sizeline > maxsizeline) maxsizeline = sizeline;
			sizeline = 0;
		}
	}
	maxsizeline++; // include '\n'
	//printf("biggest line is %d characters\n", maxsizeline);
	rewind(f);

	char data[7]; // 2x2 digit numbers, 1 seperator, 1 newline, and 1 NULL terminator
	int rule_size = sizeof(data);
	int number_of_rules = 0;
	while(fgets(data, rule_size, f) != NULL)
	{
		number_of_rules++;
		if(strlen(data) == 1)
		{
			number_of_rules--;
			break;
		}
	}
	//printf("There are %d rules\n", number_of_rules);
	rewind(f);

	char order_rules[number_of_rules][rule_size];

	for(int r = 0; r < number_of_rules; r++)
	{
		fgets(order_rules[r], rule_size, f);
	}
	int order_rules_num[number_of_rules][2];
	for(int r = 0; r < number_of_rules; r++)
	{
		order_rules_num[r][0] = atoi(order_rules[r]);
		order_rules_num[r][1] = atoi(&order_rules[r][3]);
	}
	
	for(int r = 0; r < number_of_rules; r++)
	{
		printf("%d ", order_rules_num[r][0]);
		printf("%d\n", order_rules_num[r][1]);
	}
	
	fclose(f);
	return 0;
}
