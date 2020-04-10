#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "walkSAT.h"


int walkSAT(int N, int C) {
	srand(time(0));
	int randNum = 0; // holds random values calculated
	int i = 0; // holds the index of the unsatisfied clause
	int end = 0; // ends the while loop
	int var1 = 0; // holds number of satisifed clauses given flipped var 1 in 3SAT
	int var2 = 0; // holds number of satisifed clauses given flipped var 2 in 3SAT
	int var3 = 0; // holds number of satisifed clauses given flipped var 3 in 3SAT
	int success = 0; // becomes 1 once there is a success, if there is one
	numFlips = 0; // reset numFLips for new set of clauses for new 3-SAT problem
	while (end < 10000) { // repeat 10000 times
		i = rand() % C; // choose a random clause
		// check if the clause is false
			// if so, then flip, choosing between randomly/minimize # of unsatisfied clauses
		if (!is_everyClauseSatisfied(C)) {

			if (!is_clauseTrue(i)) {
				// choose between 0 or 1
					// 0, flip randomly, 1 minimize # of unsatisfied clauses
				randNum = rand() % 2;
				if (randNum == 0) { // flip a random variabled
					randNum = rand() % N;
					flipVariable(randNum);
					numFlips++;
				}
				else { // flip the variabled that minimizes the # of unsatisfied clauses
					var1 = numSatisfiedClauses(i * 3, N, C); // first variable in the clause
					var2 = numSatisfiedClauses(i * 3 + 1, N, C); // second variable in the clause
					var3 = numSatisfiedClauses(i * 3 + 2, N, C); // third variable in the clause
					//printf("\n walkSat: flipping var 1: %d", var1);
					//printf("\n walkSat: flipping var 2: %d", var2);
					//printf("\n walkSat: flipping var 3: %d", var3);
					numFlips++;
					if (var1 > var2&& var1 > var3) {// choose first variable to flip
						flipVariable(*(clauses + i * 3));
					}
					else if (var2 > var1&& var2 > var3) { // choose second variable to flip
						flipVariable(*(clauses + (i * 3 + 1)));
					}
					else { //  choose third variable to flip
						flipVariable(*(clauses + (i * 3 + 2)));
					}
				}
				end++;
			}
			else {
				// do nothing and repeat loop
			}
		}
		else {
			success = 1;
			break;
		}
	}
	if (success == 1) {
		return 1;
	}
	else {
		numFlips = 0;
		return 0;
	}
}

// check if every clause is satisfied
	// if so, return 1, otherwise return 0
int is_everyClauseSatisfied(int C) {
	for (int i = 0; i < C; i++) {
		if (!is_clauseTrue(i))
			return 0;
	}
	return 1;
}

// counts the number of satisfied clauses
	// i is the variable, N is number of variable, C is number of caluses
int numSatisfiedClauses(int i, int N, int C) {
	flipVariable(*(clauses+i)); //  flip the variable temporarily
	int count = 0; // keeps track of number of satisifed clauses
	for (int j = 0; j < C; j++) { // loop through all clauses, counting which are true
		count += is_clauseTrue(j);
	}

	flipVariable(*(clauses+i)); //  undo flipped variable
	return count;
}

// flip variable i
void flipVariable(int i) {
	if (changed[i] == 1) {
		changed[i] = 0;
	}
	else {
		changed[i] = 1;
	}
}

// checks if 'clause' i is true, then return 1
	// otherwise, return 0
int is_clauseTrue(int i) {
	int* ptr1 = *(valClauses + i * 3);
	int* ptr2 = *(valClauses + i * 3+1);
	int* ptr3 = *(valClauses + i * 3+1);
	// check if first variable of clause i is true
	if ((*ptr1 == 1 && *(negClauses+i * 3) == 0)
		|| (*ptr1 == 0 && *(negClauses+i * 3) == 1)) {
		return 1;
	}
	// check if second variable of clause i is true
	else if ((*ptr2 == 1 && *(negClauses+i * 3 + 1) == 0)
		|| (*ptr2 == 0 && *(negClauses+i * 3 + 1) == 1)) {
		return 1;
	}
	// check if third variable of clause i is true
	else if ((*ptr3 == 1 && *(negClauses+i * 3 + 2) == 0)
		|| (*ptr3 == 0 && *(negClauses+i * 3 + 2) == 1)) {
		return 1;
	}
	else {
		return 0;
	}
}