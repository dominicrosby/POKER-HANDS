#include "catch.hpp"

#include "cards.h"
#include "play.h"
#include "smcVector.hpp"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

TEST_CASE("Vector tests", "[student]") 
{
	SECTION("Default constructor, size, capacity, and destructor")
	{
		//create empty vector
		smcVector<Card> testVec;
		//make sure members are default
		REQUIRE(testVec.size() == 0);
		REQUIRE(testVec.capacity() == 10);
	}

	SECTION("Parameterized constructor, size, capacity, and destructor")
	{
		//return value
		bool output = true;
		//custom capacity
		unsigned testCap = 5;
		smcVector<Card> testVec(testCap);
		//make sure that size remains 0 and capacity is redefined
		if(testVec.size() != 0 ||  testVec.capacity() != testCap)
		{
			output = false;
		}
		REQUIRE(output);
	}

	SECTION("Push_back x1, back, pop_back, destructor")
	{
		//return value
		bool output = true;

		//Check that push_back adds a value to an empty vector
		smcVector<int> testVec;
		int value = 1;
		testVec.push_back(value);
		//check last (only) value
		if(testVec.back() != value)
		{
			output = false;
		}
		REQUIRE(output);

		//make sure pop_back decriments size back to 0
		testVec.pop_back();
		REQUIRE(testVec.size() == 0);
	}

	SECTION("Push_back x3, operator[], destructor")
	{
		smcVector<int> testVec;
		//push back 3 times so testVec = {0 , 1, 2}
		for(int i = 0; i < 3 ; i++)
		{
			testVec.push_back(i);
			//Check that values and indexes are same and [] works 3 times
			REQUIRE(testVec[i] == i);
		}
	}

	SECTION("Push_back (over capacity), size, capacity, destructor")
	{
		//set max size to 1 greater than default capacity
		unsigned testSize = 12;
		smcVector<int> testVec;
		//add 12 values up to index 11
		for(int i = 0; i < testSize; i++)
		{

			testVec.push_back(i);
		}
		//make sure the size is 11 (index 0 -1 0)
		REQUIRE(testVec.size() == testSize);
		//make sure capacity doubles
		REQUIRE(testVec.capacity() == 20);
	}

	SECTION("Push_back (over capacity), operator[], destructor")
	{
		unsigned testSize = 12;
		smcVector<int> testVec;
		//add 12 values up to index 11
		for(int i = 0; i < testSize; i++)
		{
			testVec.push_back(i);
		}
		//make sure that index 11 = 11
		REQUIRE(testVec[testSize-1] == testSize-1);
	}

	SECTION("Push_back, pop_back, back, operator[], exceptions")
	{
		smcVector<int> testVec;
		std::string error;
		//find back on empty vector
		try
		{
			testVec.back();
		}
		//catch the error message
		catch(std::exception &e)
		{
			error = e.what();
		}
		//make sure it aligns with my error
		REQUIRE(error == "Empty Vector");

		//make a size of 1 so all indexes other than 0 are out of bounds
		testVec.push_back(0);
		try
		{
			//attempt to access index 1 (does not exist)
			int x = testVec[1];
		}
		catch (std::exception &e)
		{
			error = e.what();
		}
		//make sure error aligns with my own
		REQUIRE(error == "Index out of Range");
		
		//set size back to 0
		testVec.pop_back();
		try
		{
			//attempt an illegal pop_back
			testVec.pop_back();
		}
		catch (std::exception &e)
		{
			error = e.what();
		}
		//make sure error aligns with my own
		REQUIRE(error == "Empty Vector");
	}

	SECTION("Push_back (over capacity), operator[] (with assignment), destructor")
	{
		unsigned testSize = 12;
		smcVector<int> testVec , testVec2;

		//for loop to go above capacity
		for(int i = 0; i < testSize; i++)
		{
			//two vectors, one with ascending numbers the other all 0s
			testVec.push_back(i);
			testVec2.push_back(0);
		}
		//set the last index of the 0 vector to the last index of the other vector (11)
		testVec2[testSize - 1] = testVec[testSize-1];
		//make sure the 2nd vector recieved the data for the final index
		REQUIRE(testVec2[testSize-1] == testSize-1);
	}

	SECTION("Clear")
	{
		//new vec with capacity 5
		smcVector<int> testVec(5);
		//size = 1
		testVec.push_back(0);
		int capacity = testVec.capacity();
		testVec.clear();

		//make sure size becomes 0 and capacity stays the same
		REQUIRE(testVec.size() ==0);
		REQUIRE(testVec.capacity() == capacity);
	}

	SECTION("Copy constructor deep copies")
	{
		//make two vectors
		smcVector<int> testVec;
		//add some values
		testVec.push_back(0);
		testVec.push_back(1);
		//use copy constructor
		smcVector<int> testVecCopy(testVec);

		//make sure same values 
		REQUIRE(testVecCopy[1] == testVec[1]);
		//make sure different memory address
		REQUIRE(testVec.data()!=testVecCopy.data());
	}

	SECTION("Assignment operator deep copies")
	{
		//same as previous make two vectors
		smcVector<int> testVec;
		//add some values
		testVec.push_back(0);
		testVec.push_back(1);
		//use assignment opperator
		smcVector<int> testVecCopy = testVec;

		//make sure same values 
		REQUIRE(testVecCopy[1] == testVec[1]);
		//make sure different memory address
		REQUIRE(testVec.data()!=testVecCopy.data());
	}
}
