/*
Copyright 2019 Samadi van Koten <samadi@vktec.org.uk>

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define try(exp) if ((exp) < 0) return 1

/* Options */
int base = 16;

void parse_args(int argc, char *argv[]) {
	static const char *optstr = "hb:";
	int opt;
	while ((opt = getopt(argc, argv, optstr)) >= 0) {
		switch (opt) {
		case 'h':
			printf("Usage: %s [-b BASE] BYTE ... >OUTPUT_FILE\n", argv[0]);
			exit(0);

		case 'b':
			base = atoi(optarg);
			if (base <= 0) base = 16;
			break;
		}
	}
}

int process(FILE *out, int argc, char *argv[]) {
	int i;
	for (i = 0; i < argc; i++) {
		try(fputc(strtol(argv[i], NULL, base), out));
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	return process(stdout, argc - optind, argv + optind);
}
