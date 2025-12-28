#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PART2


int total_number_of_chars(FILE *f);

bool found_xmas_forwards(FILE *f);
bool found_xmas_backwards(FILE *f);

// treat as big table
// character offsets

int main(void)
{
	FILE *f;
	f = fopen("input", "r");
	if(f == NULL)
	{
		printf("File does not exist\n");
		return -1;
	}

	int number_of_colums = 0;
	while (fgetc(f) != '\n') {
		number_of_colums++;
	}
	number_of_colums++; // account for newline
	while (fgetc(f)!=EOF);
	fseek(f, 0L, SEEK_END);
	long size = ftell(f);
	rewind(f);
	printf("number of colums: %d\n", number_of_colums);
	int number_of_lines =  size/(int)number_of_colums;
	printf("number of lines: %d\n", number_of_lines);
	
	char word_matrix[number_of_lines][number_of_colums];

	printf("\n");

	for (int l=0; l < number_of_lines ; l++) {
		for (int c=0; c < number_of_colums ; c++) {
			word_matrix[l][c] = fgetc(f);
		}
	}
	fclose(f);

	for (int l=0; l < number_of_lines ; l++) {
		for (int c=0; c < number_of_colums ; c++) {
			printf("%c", word_matrix[l][c]);
		}
	}
	printf("\n");
	

	int count = 0;
	#ifdef PART1
	char pattern[] = "XMAS";
	for (int l=0; l < number_of_lines ; l++) {
		for (int c=0; c < number_of_colums ; c++) {
			//printf("%c", word_matrix[0][c]);
			//
			printf("%c", word_matrix[l][c]);
			if(word_matrix[l][c] == pattern[0]) // found 'X'
			{
				// NORTH
				if(	//l >= 3 &&
					word_matrix[l-1][c] == pattern[1] &&// M
					word_matrix[l-2][c] == pattern[2] &&// A
					word_matrix[l-3][c] == pattern[3])  // S
				{
					count++;
				}

				// NORTH WEST
				if(	//l >= 3 && c <= number_of_colums-3 &&
					word_matrix[l-1][c+1] == pattern[1] &&// M
					word_matrix[l-2][c+2] == pattern[2] &&// A
					word_matrix[l-3][c+3] == pattern[3])  // S
				{
					//printf("found");
					count++;
				}

				// WEST
				if(	//c <= number_of_colums-4 &&
					word_matrix[l][c+1] == pattern[1] &&// M
					word_matrix[l][c+2] == pattern[2] &&// A
					word_matrix[l][c+3] == pattern[3])  // S
				{
					count++;
				}

				// SOUTH WEST
				if(	
					word_matrix[l+1][c+1] == pattern[1] &&// M
					word_matrix[l+2][c+2] == pattern[2] &&// A
					word_matrix[l+3][c+3] == pattern[3])  // S
				{
					count++;
				}

				// SOUTH
				if(	word_matrix[l+1][c] == pattern[1] &&// M
					word_matrix[l+2][c] == pattern[2] &&// A
					word_matrix[l+3][c] == pattern[3])  // S
				{
					count++;
				}

				// SOUTH EAST
				if(	word_matrix[l+1][c-1] == pattern[1] &&// M
					word_matrix[l+2][c-2] == pattern[2] &&// A
					word_matrix[l+3][c-3] == pattern[3])  // S
				{
					count++;
				}

				// EAST
				if(	word_matrix[l][c-1] == pattern[1] &&// M
					word_matrix[l][c-2] == pattern[2] &&// A
					word_matrix[l][c-3] == pattern[3])  // S
				{
					count++;
				}

				// NORTH EAST
				if(	word_matrix[l-1][c-1] == pattern[1] &&// M
					word_matrix[l-2][c-2] == pattern[2] &&// A
					word_matrix[l-3][c-3] == pattern[3])  // S
				{
					count++;
				}
			}
		}
	}
	#endif


	#ifdef PART2
	
/* Assuming X's are always diagonal. */
	for (int l=0; l < number_of_lines ; l++) {
		for (int c=0; c < number_of_colums ; c++) {
			if (word_matrix[l][c] == 'A') {
				if ((	word_matrix[l-1][c-1] == 'M' && //M
					word_matrix[l+1][c+1] == 'S' ||	// A
									//  S
					
					word_matrix[l-1][c-1] == 'S' && //S
					word_matrix[l+1][c+1] == 'M')&&	// A
									//  M
					
				(	word_matrix[l-1][c+1] == 'S' && //  S
					word_matrix[l+1][c-1] == 'M' ||	// A
									//M
					
					word_matrix[l-1][c+1] == 'M' && //  M
					word_matrix[l+1][c-1] == 'S')	// A
				){					//S
					count++;
				}
			}
		}
	}

	#endif

	printf("\n\ntotal: %d\n", count);
	
	return 0;
}


