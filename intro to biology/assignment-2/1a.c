#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 1000
#define MAX_SEQUENCE_NAME_LENGTH 100

#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

/*
** sequence_t
*/
typedef struct {
	char sequence[MAX_SEQUENCE_LENGTH]; /* not null terminated */
	char name[MAX_SEQUENCE_NAME_LENGTH];

	int length; /* sequence length */
} sequence_t;

/* -------------------------------------------------------------------------*/
/*
** Input sequences from the given file
*/
/* -------------------------------------------------------------------------*/
int read_sequences(FILE *inFile, sequence_t sl[], int size) {
	int sequence_count = 0, c;
	while((c = fgetc(inFile)) != EOF && sequence_count < size) {
		if(c == '>') {
			sequence_t *seq = &sl[sequence_count];

			char name_first[MAX_SEQUENCE_NAME_LENGTH], name_second[MAX_SEQUENCE_NAME_LENGTH];
			fscanf(inFile, "%*s%"STRINGIZE(MAX_SEQUENCE_NAME_LENGTH)"s%"STRINGIZE(MAX_SEQUENCE_NAME_LENGTH)"s%*[^\n]", name_first, name_second);			
			snprintf(seq->name, MAX_SEQUENCE_NAME_LENGTH, "%s %s", name_first, name_second);

			int slen = 0;
			while((c = fgetc(inFile)) != EOF) {
				if(c == '>') {
					ungetc(c, inFile); /* put it back so that the outer loop sees it */
					break;
				}
				switch(c) {
					case 'A': /* fallthrough */
					case 'T': /* fallthrough */
					case 'G': /* fallthrough */
					case 'C': /* fallthrough */
						seq->sequence[slen++] = c;
						if(slen >= MAX_SEQUENCE_LENGTH) {
							printf("[ERROR] Sequence is too large.\n");
							break;
						}
				}
			}
			seq->length = slen;
			sequence_count++;
		}
	}
	if(sequence_count == size)
		printf("[ERROR] Too many sequences\n");
	return sequence_count;
}

/* -------------------------------------------------------------------------*/
/*
** Computes the distance between two sequences
*/
/* -------------------------------------------------------------------------*/
int string_mismatch_count(const char seq1[], const char seq2[], size_t len) {
	int mismatch_count = 0;
	for(int pos = 0; pos < len; pos++)
		if(seq1[pos] != seq2[pos])
			mismatch_count++;
	return mismatch_count;
}

typedef float distance_t;
distance_t calculate_distance(const sequence_t *seq1, const sequence_t *seq2) {
	const sequence_t *seq_larger = (seq1->length > seq2->length) ? seq1 : seq2,
			   		 *seq_smaller = (seq1->length > seq2->length) ? seq2 : seq1;

	int min_mismatch_count = INT_MAX;
	for(int diff = seq_larger->length - seq_smaller->length; diff >= 0; diff--) {
		int mismatch_count = string_mismatch_count(seq_larger->sequence + diff, seq_smaller->sequence, seq_smaller->length);
		if(mismatch_count < min_mismatch_count)
			min_mismatch_count = mismatch_count;
	}
	return ((distance_t)min_mismatch_count)/seq_smaller->length;
}

/* -------------------------------------------------------------------------*/
/*
** main
*/
/* -------------------------------------------------------------------------*/
int main (int argc, char *argv[]) {
	const char inputFile[] = "Nucleotide.txt",
			   outputFile[] = "Ndistance.txt";

	/* ---- READ SEQUENCES ---- */
	FILE *inFile = fopen(inputFile, "r");
	if(!inFile)
		return fprintf(stderr, "Could not open the input file (%s)\n", inputFile), 0;		

	sequence_t list[MAX_SEQUENCES];
	int count = read_sequences(inFile, list, sizeof(list)/sizeof(list[0]));
	fclose(inFile);

	/* ---- PROCESS SEQUENCES ---- */
	FILE *outFile = fopen(outputFile, "w");
	if(!outFile)
		return fprintf(stderr, "Could not open/create the output file (%s)\n", outputFile), 0;	

	//TODO: find the largest name length and use it as width
	fprintf(outFile, "%25d,", count);
	for(int i = 0; i < count; i++)
		fprintf(outFile, "%25s,", list[i].name);
	fprintf(outFile, "\n");

	for(int i = 0; i < count; i++) {
		fprintf(outFile, "%25s,", list[i].name);
		for(int j = 0; j < count; j++)
			fprintf(outFile, (i + j == 2*count - 2) ? "%25.3f" : "%25.3f,", calculate_distance(&list[i], &list[j]));
		fprintf(outFile, "\n");
	}
	fclose(outFile);
	return 0;
}
