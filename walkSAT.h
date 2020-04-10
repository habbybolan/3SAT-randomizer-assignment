#ifndef WALKSAT_H
#define WALKSAT_H

int changed[20];
int numFlips;

int* clauses; // holds the variables of the clauses
int* negClauses; //  holds if the value of clauses has a negation (1 means negation, 0 means no negation)
int* valClauses; //  holds the true/false value of the clause (1/0)

int walkSAT(int N, int C);
int numSatisfiedClauses(int i, int N, int C);
void flipVariable(int i);
int is_clauseTrue(int i);
int is_everyClauseSatisfied(int C);



#endif WALKSAT_H
