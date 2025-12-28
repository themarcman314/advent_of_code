#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define ACTIVATED 1
#define DISACTIVATED 0

int total_number_of_chars(FILE *f);
int is_digit(char c);
int str_to_int(const char *str, int idx);
int parse_mul(const char *data, const int idx, int *first_number, int *second_number);
int multiply(int, int);

int main(void)
{
	FILE *f;
	f = fopen("input", "r");
	if(f == NULL)
	{
		printf("File does not exist\n");
		return -1;
	}


	// number of chars
	int total_num_of_chars = total_number_of_chars(f);
	printf("total number of chars : %d\n", total_num_of_chars);

	// load the file into memory
	char data[total_num_of_chars];
	for (int i = 0; i < total_num_of_chars; i++) 
	{
		data[i] = fgetc(f);
	}
	fclose(f);


	// print array to stdout
	//printf("%s",data);
	
	int first_number = 0;
	int second_number = 0;
	int old_num = 0;
	
	int index = 0;

	int result = -3;

	int sum = 0;
	
	for(int idx = 0; idx < total_num_of_chars; idx++)
	{
		result = parse_mul(data, idx, &first_number, &second_number);
		
		if(result == 0)
		{
				printf("first number : %d\n", first_number);
				printf("second number : %d\n\n", second_number);
				sum += multiply(first_number, second_number);
		}
	}
	printf("total sum : %d\n", sum);
	




	return 0;
}

int total_number_of_chars(FILE *f)
{
	int number_of_chars = 0;
	char c = 'a'; // initialising character

	while(c != EOF)
	{
		c = fgetc(f);
		number_of_chars++;
	}
	fseek(f, 0, SEEK_SET);
	return number_of_chars;
}
int is_digit(char c)
{
	return c >= '0' && c <= '9';
}
int str_to_int(const char *str, int idx)
{
	int result = 0;

	while(is_digit(str[idx]))
	{
		result = result*10 + str[idx] - '0';
		idx++;
	}
	return result;
}
int parse_mul(const char *data, const int idx, int *first_number, int *second_number)
{
	int potential_first_number = 0;
	int potential_second_number = 0;

	static int mode = ACTIVATED;

	
	if(data[idx] == 'd' && data[idx+1] == 'o' && data[idx+2] == '(' && data[idx+3] == ')')
	{
		printf("activated\n");
		mode = ACTIVATED;
		return -1;
	}

	else if(data[idx] == 'd' && data[idx+1] == 'o' && data[idx+2] == 'n' && data[idx+3] == '\'' && data[idx+4] == 't'&& data[idx+5] == '(' && data[idx+6] == ')')
	{
		printf("disactivated\n");
		mode = DISACTIVATED;
		return -1;
	}

	// detect basic patern
	else if(data[idx] != 'm' ||data[idx+1] != 'u' ||data[idx+2] != 'l' ||data[idx+3] != '(')
		return -1;

	if(mode == DISACTIVATED)
		return -1;

	int first_number_idx = idx+4;
	//printf("first number idx : %d\n", first_number_idx);
	potential_first_number = str_to_int(data, first_number_idx);

	// safety checks
	if(potential_first_number < 1)
		return -1;
	int size_of_number = (int)(log10(potential_first_number)+1);
	if(size_of_number > 3)
		return -1;

	// if there isnt a ',' immediately after the first number return error
	if(data[first_number_idx+size_of_number] != ',')
		return -1;


	int second_number_idx = first_number_idx+size_of_number+1;
	//printf("second number idx : %d\n", second_number_idx);
	potential_second_number = str_to_int(data, second_number_idx);
	
	// safety checks
	if(potential_second_number < 1)
		return -1;
	size_of_number = (int)(log10(potential_second_number)+1);
	if(size_of_number > 3)
		return -1;
	
	// if there isnt a ')' immediately after the second number return error
	if(data[second_number_idx+size_of_number] != ')')
		return -1;

	*first_number = potential_first_number;
	*second_number = potential_second_number;

	return 0;
}
int multiply(int a, int b)
{
	return a*b;
}
