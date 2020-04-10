#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "walkSAT.h"


int main() {
	int N = 20; // number of variables
	for (int i = 0; i < 20; i++) {
		changed[i] = 0;
	}

	int randNum = 0; // random value to assign to the clause and boolClause
	int allSuccesses; // counts the number of walkSAT successfully terminates
	int allFlips; // counts the number of flips in the set of 50 3-sats given C|N
	int i = 0; //  holds the number of variables in a clause
	int C = 0; // holds number of clauses
	srand(time(0));
	// create random 3-sat problems and analyze them with walkSAT
	for (int index = 1; index < 11; index++) { // go through each ratio of C\N, from 1 to 10
		C = ((index - 1) * N + N); // number of clauses
		i = C * 3;
		allSuccesses = 0; // reset successes for new ratio
		allFlips = 0; // reset flips fpr new ratio
		for (int j = 0; j < 50; j++) { // generate 50 random 3-sats using the current C\N ratio
			memset(changed, 0, N*sizeof(int)); //  resets the variables
			clauses = (int*)calloc(i, sizeof(int)); // create clauses of all variables
			negClauses = (int*)calloc(i, sizeof(int)); // create boolClauses of variable negations
			valClauses = (int*)calloc(i, sizeof(int)); // create valClauses of addressed of variable values

			// sets random values for all N variables
			for (int p = 0; p < N; p++) {
				changed[p] = rand() % 2; // set random values of changed for the 20 variables (0 or 1)
			}

			for (int k = 0; k < i; k++) { // set up the temporary clause
				randNum = rand() % 20; // choose random variables from 0-19
					*(clauses+k) = randNum;
					*(valClauses+k) = &changed[randNum];
				randNum = rand() % 2; // choose random bool value from 0-1
					*(negClauses+k) = randNum;
			}
			allSuccesses += walkSAT(N, C);
			allFlips += numFlips;
		}
		printf("\nfor ratio = %d, successes = %d", C, allSuccesses);
		if (allSuccesses != 0)
			printf("\n                median number of flips = %ld", allFlips / allSuccesses);
		free(clauses);
		free(negClauses);
		free(valClauses);
	}
}

