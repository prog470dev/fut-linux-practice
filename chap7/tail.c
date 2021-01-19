#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_tail(FILE *f, long nlines);

#define DEFAULT_N_LINES 3

int
main(int argc, char *argv[]) {
	int opt;
	long nlines = DEFAULT_N_LINES;

	if (argc != 2) {
		exit(1);
	} else {
		FILE *f;
		f = fopen(argv[1], "r");
		if (!f) {
			perror(argv[1]);
			exit(1);
		}
		do_tail(f, nlines);
		fclose(f);
	}
	exit(0);
}

static void
do_tail(FILE *f, long nlines) {
	int c;
	long total_nlines = 0;
	long current = 0;

      	while((c = getc(f)) != EOF){
	       	if (c == '\n') {
		       total_nlines++;
	    	}
	}
	rewind(f);
      	while((c = getc(f)) != EOF){
		if (current >= total_nlines - nlines){
	   		if (putchar(c) < 0) exit(1);
		}
	       	if (c == '\n') {
		       current++;
		       if (current == total_nlines) return;
	       	}
       }	       
}
