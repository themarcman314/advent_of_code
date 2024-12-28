#include <stdio.h>
#include <stdlib.h>

#define SAFE 1
#define UNSAFE -1

#define INCREASING 1
#define DECREASING -1

int max_size_of_line(FILE *f);
int num_of_lines(FILE *f);
void fill_line(FILE *f, int *line_array, int line_size);
int inc_decr_safety(int *line_array, int line_size);

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
		printf("safety : %d\n", inc_decr_safety(data[j], lines));
		if(inc_decr_safety(data[j], lines) == SAFE)
			number_of_safe_vales++;
	}
	

	printf("\n");
	printf("\n");
	printf("\n");

	printf("number of safe values = %d\n", number_of_safe_vales);

	//printf("safety : %d\n", inc_decr_safety(data[18], lines));
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
int inc_decr_safety(int *line_array, int line_size)
{
	int safety_status = 0;
	int tendancy = 0;
	int a, b;
	int index = 0;
	int check_num = 0;

	while(index != line_size-2)
	{
		a = line_array[index];
		b = line_array[index+1];
		if(b < 0)
			break;
		//printf("check num : %d\n", check_num++);
		//printf("index = %d\n",index);
		//printf("a = %d\n",a);
		//printf("b = %d\n",b);
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
				return UNSAFE;
			else if(a>b && tendancy == INCREASING)
				return UNSAFE;
		}
		if(a == b)
			return UNSAFE;
		int diff = abs(a-b);
		if(diff>3)
			return UNSAFE;

		index++;

	}
	return SAFE;
}
