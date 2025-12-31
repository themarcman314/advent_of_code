#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Assuming the lab is a grid, we can just load into a 2D array */


//#define PRINT_MATRIX_AS_INT

void print_file(FILE *f);
void lab_map_determine_dimention(FILE *f, int *width, int *length);
void lab_map_load_from_file(FILE *f, const int width, const int length, char map[length][width]);
void lab_map_print(const int width, const int length, char map[][width]);
void lab_map_find_initial_position(int *x, int *y, const int width, const int length, char map[length][width]);
void lab_map_copy(const int width, const int length, const char map[length][width], char new_map[length][width]);

enum direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
};


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
	fclose(f);

	lab_map_print(w, l, map);
	int x,y;
	lab_map_find_initial_position(&x, &y, w, l, map);
	//printf("x: %d\ny: %d\n", x, y);

	char guarded_map[l][w];
	// need to track uniqueness since guard can walk over same square more than once
	lab_map_copy(w, l, map, guarded_map);
	//printf("guarded map:\n");
	//lab_map_print(w, l, guarded_map);

	int dir = NORTH; // assume initial direction is north
	//printf("\n\nx=4, y=0, char: %c\n\n", map[1][4]);
	//while (map[y][x] != '#') {
	//	printf("character: %c\n", map[y][x]);
	//	printf("x: %d y: %d\n", x, y);
	//	switch (dir) {
	//		case NORTH:
	//			y--;
	//			break;
	//		case SOUTH:
	//			break;
	//		case EAST:
	//			break;
	//		case WEST:
	//			break;
	//	}
	//	if(x < 0 || x >= (w - 2) || y < 0 || y >= l) // if out of bounds stop
	//		break;
	//}


	printf("\n\n");
	lab_map_print(w, l, map);


	return 0;
}

void print_file(FILE *f) {
	rewind(f);
	char c;
	while ((c = getc(f)) != EOF) { putchar(c); }
}

void lab_map_print(const int width, const int length, char map[length][width])
{
	for (int l = 0 ; l < length; l++) {
		printf("%s", map[l]);
	}

	printf("\n\n");

#ifdef PRINT_MATRIX_AS_INT
	for (int l = 0 ; l < length; l++) {
		for (int w = 0 ; w < width; w++) {
			printf("%d ", map[l][w]);
		}
		printf("\n");
	}
#endif

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

void lab_map_copy(const int width, const int length, const char map[length][width], char new_map[length][width]) {
	for(int l = 0; l < length; l++) {
		for(int w = 0; w < width; w++) {
			new_map[l][w] = map[l][w];
		}
	}
}
