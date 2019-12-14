#include <iostream>
#include <random>
#include "../include/checks.h"

using namespace std;

const int hands = 1000000;
const int epochs = 10;

void average(float counts[10], int n) {
	for (int i = 0; i < 10; i++)
		counts[i] = counts[i]/(float)n;
}

int main() {
	Card deck[52];
	initializeDeck(deck);

	Card hand[5];

	int rankCount[10] = {0};
	float rankSums[10] = {0};
	
	/*int inc = 0;
	do {
		inc++;
		if (inc % 10 == 0)
			initializeDeck(deck);

		generateHand(deck, hand);
	} while (!pairCheck(hand));

	for (int i = 0; i < 5; i++) {
		cout << "Card " << i << ": " << endl;
		cout << hand[i] << endl << endl;
	}*/

	for (int j = 0; j < hands; j++) {
		initializeDeck(deck);

		generateHand(deck, hand);

		rankCount[evaluate(hand)]++;
	}

	cout << "Out of 1000000 hands," << endl;
	cout << "	Royal flush -> " << rankCount[0] << endl;
	cout << "	Straight flush -> " << rankCount[1] << endl;
	cout << "	Four of a kind -> " << rankCount[2] << endl;
	cout << "	Full house -> " << rankCount[3] << endl;
	cout << "	Flush -> " << rankCount[4] << endl;
	cout << "	Straight -> " << rankCount[5] << endl;
	cout << "	Three of a kind -> " << rankCount[6] << endl;
	cout << "	Two pair -> " << rankCount[7] << endl;
	cout << "	Pair -> " << rankCount[8] << endl;
	cout << "	No hand -> " << rankCount[9] << endl;
}

