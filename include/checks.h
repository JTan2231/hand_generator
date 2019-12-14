#include <iostream>
#include <map>
#include <random>

using namespace std;

enum magnitudes {ace=1, two, three,
            four, five, six,
            seven, eight, nine,
            ten, jack, queen, king};

enum suits {diamond=1, heart, spade, club};

enum handRank {royalFlush=0, straightFlush, fourKind,
               fullHouse, flush, straight, threeKind,
               twoPair, pair};

random_device randomDevice;
default_random_engine generator(randomDevice());
uniform_int_distribution<int> cardDist(0, 51);

struct Card {
    int magnitude;
    int suit;

    Card() :magnitude(ace), suit(spade) {}
    Card(int m, int s) :magnitude(m), suit(s) {}

    void set(int m, int s) {
        this->magnitude = m;
        this->suit = s;
    }

    Card& operator=(const Card &c) {
        this->magnitude = c.magnitude;
        this->suit = c.suit;

        return *this;
    }

    friend ostream& operator<<(ostream& os, const Card& c);
};

ostream& operator<<(ostream& os, const Card& c) {
    os << c.magnitude << " of " << c.suit;
    return os;
}

void initializeDeck(Card deck[52]) {
    int index = 0;
    for (int s = 1; s < 5; s++) {
        for (int m = 1; m < 14; m++) {
            deck[index++] = Card(m, s);
        }
    }
}

void generateHand(Card deck[52], Card hand[5]) {
    //cout << "New hand: " << endl;
    for (int i = 0 ; i < 5; i++) {
        int index = cardDist(generator);

        while (deck[index].magnitude == 0)
            index = cardDist(generator);

        hand[i] = deck[index];
        deck[index].magnitude = 0;
        //cout << hand[i] << endl;
    }
}

int royalFlushCheck(Card hand[5]) {
    bool a = false, 
		 k = false, 
		 q = false, 
		 j = false, 
		 t = false;
    int suit = hand[0].suit;
    int suitCount = 0;

    for (int i = 0; i < 5; i++) {
        switch (hand[i].magnitude) {
            case ace: 
                a = true; break;
            case king:
                k = true; break;
            case queen:
                q = true; break;
            case jack:
                j = true; break;
            case ten:
                t = true; break;
        }
        if (hand[i].suit == suit)
            suitCount++;
    }

    if (a && k && q && j && t && suitCount == 5) {
        //cout << "ROYAL" << endl;
        return 1;
    }
    else return 0;
}

int straightFlushCheck(Card hand[5]) {
    int least = 15;
    int suit = hand[0].suit;
    int suitCount = 0;

    for (int i = 0; i < 5; i++) {
    	if (hand[i].magnitude < least) {
            least = hand[i].magnitude;
        }
    }
    if (least == king)
        return 0;

	for (int i = 1; i < 5; i++) {
        if (hand[i].suit == suit) 
			suitCount++;
	}

    //cout << least << endl;

    int temp, count = 0;
    do {
        temp = least;
        for (int i = 0; i < 5; i++) {
            if (hand[i].magnitude == (least + 1)) {
                count++;
                least = hand[i].magnitude;
                break;
            }
        }
    } while (temp != least);

    //cout << "count, suitCount: " << count << ", " << suitCount << endl;

    if (count == 4 && suitCount == 4) return 1;
    else return 0;
}

int fourCheck(Card hand[5]) {
	int count;
	for (int i = 0; i < 5; i++) {
		count = 0;
		for (int j = 0; j < 5; j++) {
			if (i != j) {
				if (hand[i].magnitude == hand[j].magnitude)
					count++;
			}
		}
		if (count == 3)
			return 1;
	}
	return 0;
}

int houseCheck(Card hand[5]) {
	int mag1 = hand[0].magnitude;
	int mag1Count = 1;
	int mag2 = -1;
	int mag2Count = 0;

	for (int i = 1; i < 5; i++) {
		if (hand[i].magnitude == mag1)
			mag1Count++;
		else if (hand[i].magnitude == mag2) 
			mag2Count++;
		else if (mag2 == -1) {
			mag2 = hand[i].magnitude;
			mag2Count++;
		}
	}

	if (mag1Count == 3 && mag2Count == 2)
		return 1;
	return 0;
}

int flushCheck(Card hand[5]) {
	int suit = hand[0].suit;
	int suitCount = 1;
	for (int i = 1; i < 5; i++) {
		if (hand[i].suit == suit)
			suitCount++;
	}

	if (suitCount == 5) return 1;
	return 0;
}

int straightCheck(Card hand[5]) {
	int least = 15;
	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude < least)
			least = hand[i].magnitude;
	}
	
	int temp, count = 0;
    do {
        temp = least;
        for (int i = 0; i < 5; i++) {
            if (hand[i].magnitude == (least + 1)) {
                count++;
                least = hand[i].magnitude;
                break;
            }
        }
    } while (temp != least);

	if (count == 4) return 1;
	return 0;
}

int threeCheck(Card hand[5]) {
	int count;
	for (int i = 0; i < 5; i++) {
		count = 0;
		for (int j = 0; j < 5; j++) {
			if (i != j) {
				if (hand[i].magnitude == hand[j].magnitude)
					count++;
			}
		}
		if (count == 2)
			return 1;
	}
	return 0;
}

int twoPairCheck(Card hand[5]) {
	int mag1 = hand[0].magnitude;
	int mag2 = -1;
	int mag3 = -1;
	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude != mag1) {
			mag2 = hand[i].magnitude;
			break;
		}
	}
	
	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude != mag1 && hand[i].magnitude != mag2) {
			mag3 = hand[i].magnitude;
			break;
		}
	}

	int count1 = 0;	int count2 = 0; int count3 = 0;

	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude == mag1)
			count1++;
		else if (hand[i].magnitude == mag2)
			count2++;
		else if (hand[i].magnitude == mag3)
			count3++;
	}
	
	if (count1 == 2 && count2 == 2
	 || count1 == 2 && count3 == 2
	 || count2 == 2 && count3 == 2)
		return 1;
	return 0;
}

int pairCheck(Card hand[5]) {
	int mag1 = hand[0].magnitude;
	int mag2 = -1;
	int mag3 = -1;
	int mag4 = -1;
	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude != mag1) {
			mag2 = hand[i].magnitude;
			break;
		}
	}
	
	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude != mag1 && hand[i].magnitude != mag2) {
			mag3 = hand[i].magnitude;
			break;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude != mag1 && hand[i].magnitude != mag2 && hand[i].magnitude != mag3) {
			mag4 = hand[i].magnitude;
			break;
		}
	}

	int count1 = 0;	int count2 = 0; int count3 = 0; int count4 = 0;

	for (int i = 0; i < 5; i++) {
		if (hand[i].magnitude == mag1)
			count1++;
		else if (hand[i].magnitude == mag2)
			count2++;
		else if (hand[i].magnitude == mag3)
			count3++;
		else if (hand[i].magnitude == mag4)
			count4++;
	}

	if (count1 == 2 || count2 == 2
	 || count3 == 2 || count4 == 2)
		return 1;
	return 0;
}

int evaluate(Card hand[5]) {
	if (royalFlushCheck(hand)) return 0;
	else if (straightFlushCheck(hand)) return 1;
	else if (flushCheck(hand)) return 4;
	else if (straightCheck(hand)) return 5;

	if (fourCheck(hand)) return 2;
	if (houseCheck(hand)) return 3;
	else if (threeCheck(hand)) return 6;
	else if (twoPairCheck(hand)) return 7;
	else if (pairCheck(hand)) return 8;
	else return 9;
}
