#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 10000
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
** Input substitution matrix from the given file
*/
/* -------------------------------------------------------------------------*/
int read_substitution_matrix(FILE* inFile, char protein_list[128], char sub_matrix[128][128]) {
	char heading[128], order = 0;

	/* read heading */
	while(fscanf(inFile, "%c", &heading[order]) == 1) {
		if(isspace(heading[order]))
			continue;

		if(!order && heading[order] != '*')
			return printf("Wrong format\n"), 0; /* should never happen */
	
		if(order && heading[order] == '*') {
			order++;		
			break;
		}
		order++;
	}

	/* read values */
	for(int i = 1; i < order; i++) {
		char c;		
		while(fscanf(inFile, "%c", &c) == 1 && isspace(c)) { /* do nothing */ }

		if(c != heading[i])
			return printf("Wrong format\n"), 0; /* should never happen */
		
		for(int j = 1; j < order; j++) {
			int score;
			fscanf(inFile, "%d", &score);
			sub_matrix[heading[i]][heading[j]] = score;
		}
	}
	
	memset(protein_list, 0, 128);
	for(int i = 0; i < order; i++)
		protein_list[heading[i]] = 1;

	return 0;
}

/* -------------------------------------------------------------------------*/
/*
** Input sequences from the given file
*/
/* -------------------------------------------------------------------------*/
int read_sequences(FILE *inFile, const char protein_list[128], sequence_t sl[], int size) {
	int sequence_count = 0, c;
	while((c = fgetc(inFile)) != EOF && sequence_count < size) {
		if(c == '>') {
			sequence_t *seq = &sl[sequence_count];

			fscanf(inFile, "%*[^[]%*c%"STRINGIZE(MAX_SEQUENCE_NAME_LENGTH)"[^]]%*[^\n]", seq->name);

			int slen = 0;
			while((c = fgetc(inFile)) != EOF) {
				if(c == '>') {
					ungetc(c, inFile); /* put it back so that the outer loop sees it */
					break;
				}
				if(protein_list[c])
					seq->sequence[slen++] = c;
				if(slen >= MAX_SEQUENCE_LENGTH) {
					printf("[ERROR] Sequence is too large.\n");
					break;
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
int score_sequence(char sub_matrix[128][128], const char seq1[], const char seq2[], size_t len) {
	int mismatch_count = 0;
	for(int pos = 0; pos < len; pos++)
		mismatch_count += sub_matrix[seq1[pos]][seq2[pos]];
	return mismatch_count;
}

typedef int distance_t;
distance_t calculate_distance(char sub_matrix[128][128], const sequence_t *seq1, const sequence_t *seq2) {
	const sequence_t *seq_larger = (seq1->length > seq2->length) ? seq1 : seq2,
			   		 *seq_smaller = (seq1->length > seq2->length) ? seq2 : seq1;

	int diff = seq_larger->length - seq_smaller->length;

	int max_match_count = 0;
	while(diff >= 0) {
		int match_count = score_sequence(sub_matrix, seq_larger->sequence + diff, seq_smaller->sequence, seq_smaller->length);
		if(match_count > max_match_count)
			max_match_count = match_count;
		diff--;
	}
	return max_match_count;
}

int main () {
	const char inputFile[] = "Protein.txt",
			   outputFile[] = "Pdistance.txt",
			   subMatrixFile[] = "BLOSUM62.txt";

	FILE *inFile = fopen(subMatrixFile, "r");
	if(!inFile)
		return fprintf(stderr, "Could not open the substitution matrix file (%s)\n", subMatrixFile), 0;		
	
	char protein_list[128], matrix[128][128];
	read_substitution_matrix(inFile, protein_list, matrix);
	fclose(inFile);

	/* ---- READ SEQUENCES ---- */
	inFile = fopen(inputFile, "r");
	if(!inFile)
		return fprintf(stderr, "Could not open the input file (%s)\n", inputFile), 0;		

	sequence_t list[MAX_SEQUENCES];
	int count = read_sequences(inFile, protein_list, list, sizeof(list)/sizeof(list[0]));
	fclose(inFile);

	/* ---- PROCESS SEQUENCES ---- */
	FILE *outFile = fopen(outputFile, "w");
	if(!outFile)
		return fprintf(stderr, "Could not open/create the output file (%s)\n", outputFile), 0;	

	fprintf(outFile, "%25d,", count);
	for(int i = 0; i < count; i++)
		fprintf(outFile, "%25s,", list[i].name);
	fprintf(outFile, "\n");

	for(int i = 0; i < count; i++) {
		fprintf(outFile, "%25s,", list[i].name);
		for(int j = 0; j < count; j++)
			fprintf(outFile, (i + j == 2*count - 2) ? "%25d" : "%25d,", calculate_distance(matrix, &list[i], &list[j]));
		fprintf(outFile, "\n");
	}
	fclose(outFile);	
}
