#include "cards.h"

#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a ITPVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(smcVector<Card>& deck)
{
	//take 5 cards from the back of the deck and remove them from the deck
	for(int i = 0; i < 5; i++)
	{
		mHand.push_back(deck.back());
		deck.pop_back();
	}
	//sort the hand
	sortHand();
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
	//retval for hand message
	std:: string retval;
	//order hands in the order of rank
	//better hands will override worse hands even if both functions are true
	if(hasStraight() && hasFlush())
	{
		retval = "straight flush";
	}
	else if(hasFourOfAKind() == 1)
	{
		retval = "four of a kind";
	}
	else if(hasFullHouse() == 1)
	{
		retval = "full house";
	}
	else if(hasFlush() == 1)
	{
		retval = "flush";
	}
	else if(hasStraight() == 1)
	{
		retval = "straight";
	}
	else if(hasThreeOfAKind() == 1)
	{
		retval = "three of a kind";
	}
	else if(hasTwoPairs() == 1)
	{
		retval = "two pairs";
	}
	else if(hasPair() == 1)
	{
		retval = "pair";
	}
	else
	{
		retval = "high card";
	}
	return retval;
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
	//move through all 5 cards (size-1 because indexx i+1 is in the loop)
	for(int i = 0; i < mHand.size()-1; i++)
	{
		//check if hand doesnt meet straight requirement
		if(mHand[i].mRank != mHand[i+1].mRank - 1)
		{
			return false;
		}
	}
	//if it doesnt fail return true
	return true;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
	//iterate through hand (size-1 because indexx i+1 is in the loop)
	for(int i = 0; i < mHand.size() - 1; i++)
	{
		//check if any suit does not align with neighboring card
		if(mHand[i].mSuit != mHand[i+1].mSuit)
		{
			return false;
		}
	}
	//if all suits are same
	return true;
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
	//iterate through hand (size-3 because index i+3 is in the loop)
	//for loop tecnically only runs 2 times
	for(int i = 0; i< mHand.size() - 3; i++)
	{
		//check if 4 neighboring cards have the same value
		if(mHand[i].mRank == mHand[i+1].mRank && mHand[i+1].mRank == mHand[i+2].mRank && mHand[i+2].mRank == mHand[i+3].mRank)
		{
			return true;
		}
	}
	return false;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
	//integer to count changes in card rank
	int diffCounter = 0;
	//iterate through hand
	for(int i = 0; i<mHand.size()-1; i++)
	{
		//check how many times the rank changes while iterating
		if(mHand[i].mRank!=mHand[i+1].mRank)
		{
			//add to the counter each time
			diffCounter++;
		}
	}
	//full house has diffcounter = 1 (the minimum in a standard deck)
	if(diffCounter<= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
	//iterate through hand (only executes 3 times)
	for(int i = 0; i<mHand.size()-2; i++)
	{
		//check for 3 neighboring cards with same rank
		if(mHand[i].mRank == mHand[i+1].mRank && mHand[i+1].mRank == mHand[i+2].mRank)
		{
			return true;
		}
	}
	return false;
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
	//check first 3 cards for a pair
	for(int i = 0; i < mHand.size()-3; i++)
	{
		//if there is a pair in the first 2 or 3 check the next 2 or 3
		if(mHand[i].mRank == mHand[i+1].mRank)
		{
			int index = i;
			//check for pair in 2nd half of hand
			for(int j = index+2; j< mHand.size() - 1; j++)
			{
				//if another pair is found
				if(mHand[j].mRank == mHand[j+1].mRank)
				{
					return true;
				}
			}
		}
	}
	//if <2 pair is found
	return false;
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
	//iterate through hand
	for(int i = 0; i<mHand.size()-1; i++)
	{
		//check neighbors for any equivalent values
		if(mHand[i].mRank == mHand[i+1].mRank)
		{
			return true;
		}
	}
	return false;
}

void PokerHand::sortHand()
{
	//iterate through hand (until last card)
	for(int i = 0; i < mHand.size()-1; i++)
	{
		//create integer to represent the index of the minimum value
		int minIndex = i;
		//j is index after minumim
		for (int j = i+1; j< mHand.size(); j++)
		{
			//if the proceeding index (j) is a lower value than i
			if(mHand[j].mRank<mHand[minIndex].mRank)
			{
				//j is new minimum index
				minIndex = j;
			}
			//if the indeces have the same value
			else if(mHand[j].mRank == mHand[minIndex].mRank)
			{
				//compare lower suit
				if(mHand[j].mSuit<mHand[minIndex].mSuit)
				{
					minIndex = j;
				}
			}
		}
		//if i card is lower will already be proceeding j card
		//create a temporary low card (the card found in previous loop)
		Card tempLow = mHand[minIndex];
		//add the low card to index [i]
		mHand[minIndex] = mHand[i];
		mHand[i] = tempLow;
	}
}

// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(smcVector<Card>& deck, std::mt19937& g)
{
	//iterate through each suit
	for(int i = 0; i <= 3; i++)
	{
		Suit cardSuit;
		switch(i)
		{
			case 0: cardSuit = CLUBS;
			break;

			case 1: cardSuit = DIAMONDS;
			break;

			case 2: cardSuit = HEARTS;
			break;

			case 3: cardSuit = SPADES;
			break;
		}
		//iterate through each card inside of each suit (2-A)
		for(unsigned j = 2; j <= 14; j++)
		{
		//create new card
		Card newCard(j, cardSuit);
		//add the card to the deck
		deck.push_back(newCard);
		}
	}

	// LEAVE THIS HERE!
	// Shuffle the deck
	std::sort(&deck[0], &deck[0] + deck.size());
	std::shuffle(&deck[0], &deck[0] + deck.size(), g);
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	//nested switch for suits and ranks
	//suit switch
	switch(card.mSuit)
	{
		case SPADES:
		//rank switch
		switch(card.mRank)
		{
			//take edge cases (face cards)
			case 11:
			os<< "Jack of Spades";
			break;

			case 12:
			os<< "Queen of Spades";
			break;

			case 13:
			os<< "King of Spades";
			break;

			case 14:
			os<<"Ace of Spades";
			break;
			
			//default is all non face (2-10)
			default:
			os << card.mRank << " of Spades";
			break;
		}
		break;

		//repeat for all suits
		case HEARTS:
		switch(card.mRank)
		{
			case 11:
			os<< "Jack of Hearts";
			break;

			case 12:
			os<< "Queen of Hearts";
			break;

			case 13:
			os<< "King of Hearts";
			break;

			case 14:
			os<<"Ace of Hearts";
			break;
			
			default:
			os << card.mRank << " of Hearts";
			break;
		}
		break;

		case DIAMONDS:
		switch(card.mRank)
		{
			case 11:
			os<< "Jack of Diamonds";
			break;

			case 12:
			os<< "Queen of Diamonds";
			break;

			case 13:
			os<< "King of Diamonds";
			break;

			case 14:
			os<<"Ace of Diamonds";
			break;
			
			default:
			os << card.mRank << " of Diamonds";
			break;
		}
		break;

		case CLUBS:
		switch(card.mRank)
		{
			case 11:
			os<< "Jack of Clubs";
			break;

			case 12:
			os<< "Queen of Clubs";
			break;

			case 13:
			os<< "King of Clubs";
			break;

			case 14:
			os<<"Ace of Clubs";
			break;
			
			default:
			os << card.mRank << " of Clubs";
			break;
		}
		break;
	}
	//return whichever os was targeted in the nested switch
	return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
	//compare ranks
	if(left.mRank<right.mRank)
	{
		return true;
	}
	//if ranks are the same
	else if(left.mRank == right.mRank)
	{
		//compare suits
		if(left.mSuit<right.mSuit)
		{
			return true;
		}
		else if(left.mSuit>right.mSuit)
		{
			return false;
		}
	}
		return false;	
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
	//same as other comparrison
	if(left.mRank>right.mRank)
	{
		return true;
	}
	//if ranks same compare suits
	else if(left.mRank == right.mRank)
	{
		if(left.mSuit>right.mSuit)
		{
			return true;
		}
		else if(left.mSuit<right.mSuit)
		{
			return false;
		}
	}
		return false;
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
	//following github sample
	os<< "{ ";
	//iterate through first four cards
	for(int i = 0; i<hand.mHand.size() - 1; i++)
	{
		//hand os with a comma
		os<<hand.mHand[i] << ", ";
	}
	//for last card no comma
	os<<hand.mHand[hand.mHand.size()-1]<< " }";
	return os;
}
