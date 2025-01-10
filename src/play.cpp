#include "smcVector.hpp"
#include "cards.h"

#include <random>

#include <fstream>
#include <iostream>

void playPoker(std::istream& in, std::ostream& out, unsigned seed)
{
	std::mt19937 g(seed);

	while (true)
	{
		smcVector<Card> deck;
		createDeck(deck, g);
		PokerHand hand(deck);
		out << "You drew: " << hand << std::endl;
		out << "You have a " << hand.getBestPokerHand() << std::endl;

		out << "Try again (y/n): ";
		std::string choice;
		std::getline(in, choice);
		if (choice != "y" && choice != "Y")
		{
			break;
		}
	}
}


void playPoker(const std::string& inFile, const std::string& outFile, unsigned seed)
{
	std::ifstream inStream(inFile);

	if (!inStream.is_open())
	{
		std::cout << "Failed to open the file successfully" << std::endl;
	}

	std::ofstream outStream(outFile);

	playPoker(inStream, outStream, seed);
}
