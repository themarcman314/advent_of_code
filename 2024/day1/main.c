#include <stdio.h>
#include <stdlib.h>

int find_minimum(int *list, const int start_idx, int size_of_list);
int calc_distance(int *list1, int *list2, int size_of_list);
int calc_similarity(int number, int *list_to_check, int size_of_list);

int main(void)
{
	FILE *f;
	f = fopen("list", "r");
	if(f == NULL)
	{
		printf("File does not exist\n");
		return -1;
	}

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
	//printf("num lines : %d\n", lines);

	int current_first_column_number;
	int current_second_column_number;

	int first_column[lines];
	int second_column[lines];

	// sort into arrays
	for(int i = 0; i < lines; i++)
	{
		fscanf(f, "%d %d", &current_first_column_number, &current_second_column_number);
		first_column[i] = current_first_column_number;
		second_column[i] = current_second_column_number;
	}


	for (int unordered_idx = 0; unordered_idx < lines; unordered_idx++)
	{
		int actual_min_idx = find_minimum(first_column, unordered_idx, lines);
		int tampon = first_column[unordered_idx];
		first_column[unordered_idx] = first_column[actual_min_idx];
		first_column[actual_min_idx] = tampon;
	}

	for (int unordered_idx = 0; unordered_idx < lines; unordered_idx++)
	{
		int actual_min_idx = find_minimum(second_column, unordered_idx, lines);
		int tampon = second_column[unordered_idx];
		second_column[unordered_idx] = second_column[actual_min_idx];
		second_column[actual_min_idx] = tampon;
	}
	
	for(int i = 0; i < lines; i++)
	{
		printf("%d\t", first_column[i]);
		printf("%d\n", second_column[i]);
	}

	printf("total distance : %d\n", calc_distance(first_column, second_column, lines));

	int total_similarity = 0;
	for(int i=0; i < lines; i++)
		total_similarity += calc_similarity(first_column[i], second_column, lines);

	printf("total sim : %d\n", total_similarity);

	fclose(f);
	
	return 0;
}

int find_minimum(int *list, const int start_idx, int size_of_list)
{
	int rank_of_minimum = start_idx;
	int min = list[start_idx];
	for(int idx = start_idx; idx < size_of_list; idx++)
	{
		if(list[idx] < min)
		{
			min = list[idx];
			rank_of_minimum = idx;
		}
	}
	return rank_of_minimum;
}

int calc_distance(int *list1, int *list2, int size_of_list)
{
	int distance = 0;
	for(int i = 0; i < size_of_list; i++)
	{
		printf("current distance : %d\n", distance);
		distance += abs(list2[i]-list1[i]);
	}
	return distance;
}

int calc_similarity(int number, int *list_to_check, int size_of_list)
{
	int occurences = 0;
	for(int i=0; i < size_of_list; i++)
	{
		if(number == list_to_check[i])
		{
			occurences++;
		}
	}
	return occurences*number;
}
