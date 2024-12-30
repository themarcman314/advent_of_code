#include <stdio.h>
#include <stdlib.h>

#define SAFE 1000
#define UNSAFE -1

#define INCREASING 1
#define DECREASING -1

int max_size_of_line(FILE *f);
int num_of_lines(FILE *f);
void fill_line(FILE *f, int *line_array, int line_size);
int check_safety(int *line_array, int line_size);
void rewrite_line(int *line, int *newline, int index_to_remove, int size_of_line);
int rewrite_line_and_check_safety(int *line, int size_of_line);

int main(void)
{
	FILE *f;
	f = fopen("input", "r");
	if(f == NULL)
	{
		printf("File does not exist\n");
		return -1;
	}

	int lines = num_of_lines(f);

	printf("num lines : %d\n", lines);

	int max_size_line = max_size_of_line(f);
	printf("max number of values in a line: %d\n", max_size_line);


	int data[lines][max_size_line];
	for (int i = 0; i < lines; i++) 
	{
		for (int j = 0; j < max_size_line; j++) 
			data[i][j] = -1;
	}
	

	char c = 'a';
	int rank = 0;
	int line = 0;
	int unsafe_value_used = 0;
	int safety = 0;
	int other_safe = 0;


	for(int i = 0; i < lines; i++)
	{
		fill_line(f, data[i], max_size_line);
	}

	int number_of_safe_vales = 0;
	for(int j = 0; j < lines; j++)
	{
		for (int i=0; i < max_size_line; i++)
		{
			printf("%d\t", data[j][i]);
		}
		printf("safety : %d\n", check_safety(data[j], max_size_line));
		safety = check_safety(data[j], max_size_line);
		if(safety == SAFE)
		{
			number_of_safe_vales++;
		}
		else
		{
			printf("\n");
			printf("\n");
			if(rewrite_line_and_check_safety(data[j], max_size_line) == 0)
				other_safe++;
		}
	}
	
	printf("\n");
	printf("\n");

	printf("other safe : %d\n", other_safe);

	printf("total safe : %d\n", other_safe+number_of_safe_vales);


	


	//printf("number of safe values = %d\n", number_of_safe_vales);

	//rewrite_line(data[5], 7, max_size_line);

	return 0;
}

int max_size_of_line(FILE *f)
{
	int max_num_vals = 0;
	int current_num_vals = 1;
	char c = 'a'; // initialising character

	// max amount of numbers in a line ?
	while(c != EOF)
	{
		c = fgetc(f);
		if(c == ' ')
		{
			current_num_vals++;
		}
		else if(c == 10)
		{
			if(current_num_vals > max_num_vals)
				max_num_vals = current_num_vals;
			current_num_vals = 1;
		}
	}
	fseek(f, 0, SEEK_SET);
	return max_num_vals;
}

int num_of_lines(FILE *f)
{
	// count number of lines
	char ch = 0;
	int lines = 0;
	while(!feof(f))
	{
		ch = fgetc(f);
		if(ch == '\n')
		{
			lines++;
		}
	}
	fseek(f, 0, SEEK_SET);
	return lines;
}

void fill_line(FILE *f, int *line_array, int line_size)
{
	int number = 0;
	int in_number = 0;
	int rank = 0;
	char c = 'a';

	while(c != 10)
	{
		c = fgetc(f);
		if(c != ' ' && c != 10) // is a number
		{
			number = number*10+atoi(&c);
			in_number = 1;
		}
		else if (in_number)
		{
			line_array[rank++] = number;
			number = 0;
		}
	}
}
int check_safety(int *line_array, int line_size)
{
	int tendancy = 0;
	int a, b;

	for(int index = 0; index  <= line_size -2; index++)
	{
		a = line_array[index];
		b = line_array[index+1];
		if(b < 0)
		{
			continue;
		}
		if(tendancy == 0)
		{
			if(a<b)
				tendancy = INCREASING;
			else if (a>b)
				tendancy = DECREASING;
		}
		else
		{
			if(a<b && tendancy == DECREASING)
			{
				return UNSAFE;
			}
			else if(a>b && tendancy == INCREASING)
			{
				return UNSAFE;
			}
		}
		if(a == b)
		{
			return UNSAFE;
		}
		int diff = abs(a-b);
		if(diff>3)
		{
			return UNSAFE;
		}
	}
	return SAFE;
}

/*
 * returns -1 if could not find any safe combination
 */
int rewrite_line_and_check_safety(int *line, int size_of_line)
{
	int safety = 0;
	int new_buf[size_of_line];

	// rewrite the line by erasing every possible number and check for safety every time
	for(int i = 0; i < size_of_line; i++)
	{
		rewrite_line(line, new_buf, i, size_of_line);
		safety = check_safety(new_buf, size_of_line);
		if(safety == SAFE)
		{
			printf("line safe with line %d removed\n", i);
			return 0;
		}
		else safety = UNSAFE;
		printf("\n");
	}
	if(safety == UNSAFE)
	{
		printf("safe combination not found\n");
	}
	return -1;
}

void rewrite_line(int *line, int *newline, int index_to_remove, int size_of_line)
{
	int old_buf_index = 0;
	
	// initialise new buffer
	for(int i = 0; i < size_of_line; i++)
	{
		newline[i] = -1;
	}
	for(int new_buf_index = 0; new_buf_index < size_of_line; new_buf_index++)
	{
		if(old_buf_index == index_to_remove && old_buf_index == size_of_line-1);
		else if(old_buf_index == index_to_remove)
		{
			old_buf_index++;
			newline[new_buf_index] = line[old_buf_index];
		}
		else if(old_buf_index < size_of_line)
		{
			newline[new_buf_index] = line[old_buf_index];
		}
		old_buf_index++;
	}
	for(int i = 0; i < size_of_line; i++)
	{
		printf("%d\t", newline[i]);
	}
}
