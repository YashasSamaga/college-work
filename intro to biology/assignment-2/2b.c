#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_NAME_LENGTH 100

/*
** main
*/
int main (int argc, char *argv[]) {
	const char distMatrixFile[] = "Pdistance.txt";

	/* ---- READ DISTANCE MATRIX ---- */
	FILE *inFile = fopen(distMatrixFile, "r");
	if(!inFile)
		return fprintf(stderr, "Could not open the distance matrix file (%s)\n", distMatrixFile), 0;

	/* static to ensure that segmentation fault (due to small stack size) does not occur because of large sizes */
	static char names[MAX_SEQUENCES][MAX_SEQUENCES*MAX_SEQUENCE_NAME_LENGTH];

	//TODO: sanity checking on input format
	int count;
	fscanf(inFile, "%d%*[^,]", &count); 
	getc(inFile); /* read count and go to first label */

	/* read the name of the taxons */
	for(int i = 0; i < count; i++) {
		fscanf(inFile, "%*[ \t]%[^,]", names[i]); 
		getc(inFile); /* skip the comma */
	}

	/* read the distance matrix */
	int matrix[count][count];
	for(int i = 0; i < count; i++) /* read rows */ {
		fscanf(inFile, "%*[^,]"); getc(inFile); /* skip row heading */
		for(int j = 0; j < count; j++) {
			fscanf(inFile, "%d%*[^,]", &matrix[i][j]); 
			getc(inFile); /* skip the comma */
		}
	}

	/* --------------------------- PROCESSING --------------------------- */
	const int SKIP = INT_MIN;

	/* ignore diagonal elements */
	for(int i = 0; i < count; i++)
		matrix[i][i] = SKIP;

	int x = 0, y = 0;
	for(int paired = 0; paired < (count - 1); paired++)
	{	
		/* find maximum */
		for(int i = 0; i < count; i++) {
			for(int j = 0; j < count; j++) {
				if(matrix[x][y] < matrix[i][j]) {
					x = i;
					y = j;
				}					
			}
		}

		/* use x'th row and column as the row/column for the pair */
		for(int k = 0; k < count; k++) {
			if(matrix[x][k] == SKIP) /* if matrix[x][k] is SKIP, it implies that matrix[k][x] is also SKIP */
				continue;

			matrix[x][k] = 
			matrix[k][x] = (matrix[x][k] + matrix[y][k])/2;
		}

		/* delete y'th row and column */
		for(int k = 0; k < count; k++) {
			matrix[y][k] = 
			matrix[k][y] = SKIP;
		}
		
		static char temp[MAX_SEQUENCES*MAX_SEQUENCE_NAME_LENGTH];
		strcpy(temp, names[x]);
		sprintf(names[x], "(%s,%s)", temp, names[y]); 
	}
	printf("%s\n", names[x]);
	return 0;
}
