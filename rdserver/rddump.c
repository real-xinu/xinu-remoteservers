/* rddump.c - main */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define	NUMBLOCKS	100

/*------------------------------------------------------------------------
 * main - dump a remote disk file
 *
 *  use:   rddump [-n] [file]
 *
 #  The optional file argument specifies a file that contains the data for
 *	a remote disk.  If the argument is omitted, rddump uses stdin.
 *
 *  The optional -n argument specifies the maximum number of blocks to
 *	dump; if omitted, rddump uses NUMBLOCKS.  Note that rddump starts
 *	at block zero, so a dump of N blocks, contains blocks 0 through N-1.
 *
 *------------------------------------------------------------------------
 */
int	main (int argc, char *argv[]) 
{
	int	blk;			/* Iterates through blocks	*/
	int	byte;			/* Iterates through 512 bytes	*/
	char	buf[512];		/* Data for one block		*/
	int	nread;			/* Nuber of bytes read		*/
	char	ch;			/* input character		*/
	int	nblks = NUMBLOCKS;	/* Number to dump		*/
	int	indesc = 0;		/* Input descriptor		*/
	
	char	errmsg[] = "error: use is  rddump [-n] [file]";

	/* Check arguments */

	if (argc > 2) {
		fprintf(stderr, "%s\n", errmsg);
		exit(1);
	}

	if (argc > 1) {
		if (argv[1][0] == '-') {
			nblks = atoi(&argv[1][1]);
			if (nblks <= 0) {
				fprintf(stderr, "%s\n", errmsg);
				exit(1);
			}
			argv++;
			argc--;
		}
	}

	if (argc > 1) {
		if (argv[1][0] == '-') {
			fprintf(stderr, "%s\n", errmsg);
			exit(1);
		}
		indesc = open(argv[1], O_RDONLY);
		if (indesc < 0) {
			fprintf(stderr, "Cannot open file %s\n", argv[1]);
			exit(1);
		}
	}

	/* Dump successive blocks */

	for (blk=0; blk < nblks; blk++) {
		nread = read(indesc, buf, 512);
		if (nread < 0) {
			fprintf(stderr, "Error reading input file\n");
			exit(1);
		}
		if (nread == 0) {
			printf("\nEnd of file\n");
			exit(0);
		}
		if (nread < 512) {
			fprintf(stderr, "File does not contain a multiiple of blocks\n");
			exit(1);
		}

		/* See if the block is completely empty (all zero bytes) */
		for (byte=0; byte<512; byte++) {
			if ( buf[byte] != '\0') {
				break;
			}
		}
		char	strs[] = "********************";
		if (byte >= 512) {
			printf("\nBlock %d %s Is Completely Empty %s\n", blk, strs, strs);
			continue;
		}
		printf("\nBlock %d\n\n", blk);
		for (byte=0; byte<512; byte++) {
			ch = buf[byte];
			if ( isprint(ch) ) {
				printf("%c", ch);
			} else {
				printf("?");
			}
			if ( (byte+1)%128 == 0 ) {
				printf("\n");
			}
		}
	}
	exit(0);
}
