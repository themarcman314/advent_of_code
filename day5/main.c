#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
/*
 * Start by identifying which updates are in the correct order.
 * Then determine the middle page number from each update.
 * Add the middle page numbers up.
 * */

void parse_file_into_rule_array(FILE *f, int number_of_rules, int char_rule_size, int rules[number_of_rules][2]);

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
	maxsizeline += 2; // include '\n' and '\0'
	//printf("biggest line is %d characters\n", maxsizeline);
	rewind(f);

	char rule_data[7]; // 2x2 digit numbers, 1 seperator, 1 newline, and 1 NULL terminator
	int rule_size = sizeof(rule_data);
	int number_of_rules = 0;
	while(fgets(rule_data, rule_size, f) != NULL)
	{
		number_of_rules++;
		if(strlen(rule_data) == 1)
		{
			number_of_rules--;
			break;
		}
	}
	char changes_data[maxsizeline];
	// number of commas = amount of changes per line - 1
	// numbers are 2 digits long
	// number of numbers = strlen/3
	while(fgets(changes_data, maxsizeline, f) != NULL)
	{
		int numbers[strlen(changes_data)/3];
		//printf("size of numbers: %d\n", sizeof(numbers)/sizeof(int));
		char *pagestring;
		pagestring = strtok(changes_data, ",");
		numbers[0] = atoi(pagestring);
		//printf("page number: %s\n", pagestring);
		int i = 1;
		while ((pagestring = strtok(NULL, ",")) != NULL)
		{
			numbers[i++] = atoi(pagestring);
		}
		for(int a =0; a < (sizeof(numbers)/sizeof(int)); a++)printf("%d\n", numbers[a]);
		printf("\n");
	}

	int order_rules_num[number_of_rules][2];
	parse_file_into_rule_array(f, number_of_rules, rule_size, order_rules_num);
	//for(int r = 0; r < number_of_rules; r++)
	//{
	//	printf("%d ", order_rules_num[r][0]);
	//	printf("%d\n", order_rules_num[r][1]);
	//}
	
	fclose(f);
	return 0;
}

void parse_file_into_rule_array(FILE *f, int number_of_rules, int char_rule_size, int rules[number_of_rules][2])
{
	rewind(f);
	char order_rules[number_of_rules][char_rule_size];
	for(int r = 0; r < number_of_rules; r++)
	{
		fgets(order_rules[r], char_rule_size, f);
	}
	int order_rules_num[number_of_rules][2];
	for(int r = 0; r < number_of_rules; r++)
	{
		rules[r][0] = atoi(order_rules[r]);
		rules[r][1] = atoi(&order_rules[r][3]);
	}
}
