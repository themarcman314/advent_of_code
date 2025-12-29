#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(void) {
	FILE *f = fopen("./smallinput", "r");
	if (f == NULL) {
		return -1;
	}
	char c;
	while ((c = getc(f)) != EOF) {
		putchar(c);
	}
	fclose(f);
	return 0;
}
