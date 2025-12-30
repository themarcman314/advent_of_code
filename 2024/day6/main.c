#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Assuming the lab is a grid, we can just load into a 2D array */

void print_file(FILE *f);
void lab_map_determine_dimention(FILE *f, int *width, int *length);
void lab_map_load_from_file(FILE *f, const int width, const int length, char map[length][width]);
void lab_map_print(const int width, const int length, char map[][width]);
void lab_map_find_initial_position(int *x, int *y, const int width, const int length, char map[length][width]);


int main(void) {
	FILE *f = fopen("./smallinput", "r");
	//FILE *f = fopen("./input", "r");
	if (f == NULL) {
		return -1;
	}
	int w;
	int l;
	lab_map_determine_dimention(f, &w, &l);
	w += 2; // account for '\n' and '\0'
	char map[l][w];
	lab_map_load_from_file(f, w, l, map);
	lab_map_print(w, l, map);
	int x,y;
	lab_map_find_initial_position(&x, &y, w, l, map);
	printf("x: %d\ny: %d\n", x, y);
	

	fclose(f);
	return 0;
}

void print_file(FILE *f) {
	rewind(f);
	char c;
	while ((c = getc(f)) != EOF) { putchar(c); }
}

void lab_map_print(const int width, const int length, char map[][width])
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
void lab_map_find_initial_position(int *x, int *y, const int width, const int length, char map[length][width]) {
	for(int l = 0; l < length; l++) {
		for(int w = 0; w < width; w++) {
			if( map[l][w] == '^') {
				*x = w;
				*y = l;
				return;
			}
		}
	}
}

