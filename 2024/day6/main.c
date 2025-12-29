#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Assuming the lab is a grid, we can just load into a 2D array */

void print_file(FILE *f);
void lab_map_determine_dimention(FILE *f, int width, int length);
void lab_map_load_from_file(FILE *f, const int width, const int length, int map[length][width]);


int main(void) {
	FILE *f = fopen("./smallinput", "r");
	//FILE *f = fopen("./input", "r");
	if (f == NULL) {
		return -1;
	}
	print_file(f);
	int w;
	int l;
	lab_map_determine_dimention(f, w, l);

	fclose(f);
	return 0;
}

void print_file(FILE *f) {
	rewind(f);
	char c;
	while ((c = getc(f)) != EOF) { putchar(c); }
}

void lab_map_determine_dimention(FILE *f, int width, int length) {
	width = 0;
	length = 0;
	rewind(f);
	char c;
	while ((c = getc(f)) != '\n') {
		width++;
	}
	length++;
	while ((c = getc(f)) != EOF) {
		if(c == '\n')length++;
	}
}

void lab_map_load_from_file(FILE *f, const int width, const int length, int map[length][width]) {
}
