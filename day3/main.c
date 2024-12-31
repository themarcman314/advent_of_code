#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_number_of_chars(FILE *f);
int detect_char_sequence(char *);
int multiply(int *);
int add_total(int *);

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
	// print array to stdout
	for (int i = 0; i < total_num_of_chars; i++) 
	{
		printf("%c",data[i]);
	}

	printf("\n");
	printf("\n");
	printf("\n");

	detect_char_sequence(data);



	fclose(f);
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

int detect_char_sequence(char *data)
{
	char sequence[] = "mul(";
	int char_in_seq = 0;
	int rank_of_first_num = 0;


	// look for sequence for every character
	for (int i = 0; i < strlen(data)-sizeof(sequence); i++)
	{
		for(char_in_seq = 0; char_in_seq < sizeof(sequence)-1; char_in_seq++)
		{
			if(data[i+char_in_seq] != sequence[char_in_seq])
			{
				printf("nothing here\n");
				break;
			}
			else
			{
				printf("found character : '%c'\n", sequence[char_in_seq]);
			}
		}
		// if "mul(" detected
		if(char_in_seq == sizeof(sequence)-1)
		{
			rank_of_first_num = i+char_in_seq;
			printf("first number positioned at %d\n", rank_of_first_num);
		}
	}

	return rank_of_first_num;
}
