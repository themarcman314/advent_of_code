#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Assuming the lab is a grid, we can just load into a 2D array */

void print_file(FILE *f);
void lab_map_determine_dimention(FILE *f, int *width, int *length);
void lab_map_load_from_file(FILE *f, const int width, const int length, char map[length][width]);
void lab_map_print(int width, int length, char map[][width]);


int main(void) {
	FILE *f = fopen("./smallinput", "r");
	//FILE *f = fopen("./input", "r");
	if (f == NULL) {
		return -1;
	}
	print_file(f);
	int w;
	int l;
	lab_map_determine_dimention(f, &w, &l);
	w += 2; // account for '\n' and '\0'
	char map[l][w];
	lab_map_load_from_file(f, w, l, map);
	printf("\n\n");
	lab_map_print(w, l, map);

	fclose(f);
	return 0;
}

void print_file(FILE *f) {
	rewind(f);
	char c;
	while ((c = getc(f)) != EOF) { putchar(c); }
}

void lab_map_print(int width, int length, char map[][width])
{
	for (int l = 0 ; l < length; l++) {
		printf("%s", map[l]);
	}
}

void lab_map_determine_dimention(FILE *f, int *width, int *length) {
	*width = 0;
	*length = 0;
	rewind(f);
	char c;
	while ((c = getc(f)) != '\n') {
		(*width)++;
	}
	(*length)++;
	while ((c = getc(f)) != EOF) {
		if(c == '\n')(*length)++;
	}
}

void lab_map_load_from_file(FILE *f, const int width, const int length, char map[length][width]) {
	rewind(f);
	for(int l = 0; l < length; l++) {
		fgets(map[l], width, f);
	}
}
