#include <iostream>
#include <random>
#include "../include/checks.h"

using namespace std;

const int hands = 1000000;

int main() {
	Card deck[52];

	Card hand[5];

	int rankCount[10] = {0};
	
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

