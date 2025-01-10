#pragma once
#include <sstream>
#include <ostream>
#include <stdexcept>

/*
DONE 1. Add three member variables.

DONE 2. Implement the capacity function that returns the capacity of the smcVector

DONE 3. Implement the size function that returns the size of the smcVector

4. Implement the data function that returns the pointer to the underlying array.

5. Implement the empty function that returns true if the smcVector is empty.

6. Implement the smcVector constructor. This constructor should initialize the capacity to
INITIAL_CAPACITY and the size to 0. It should then proceed to dynamically allocate the
underlying array of Ts to have capacity elements in it.

7. Implement the paramterized smcVector constructor. This constructor should initialize
the capacity to the inputted capacity and the size to 0. It should then proceed to
dynamically allocate the underlying array of Ts to have capacity elements in it.

8. Implement the smcVector destructor. The destructor should delete the underlying array
and set the capacity and size to 0.

9. Implement the push_back function. If the current size is less than the current capacity,
there’s enough room on the underlying array to just add the value. However, if the
current size is equal to the capacity (meaning the insertion will go over the capacity),
you will need to create new underlying array data – use CAPACITY_MULTIPLIER to
create the new underlying array. Consult the lecture notes for a discussion of this.

10. Implement the two subscript operators. Note that both implementations should check
for an out-of-bounds index, in which case the std::out_of_range exception should be
thrown with an appropriate error message.

11. Implement the << operator. This should loop through the vector from the start to end
indices, and output a comma separated list of the elements in the vector.

12. Implement the back function. This should return the last element in the smcVector.
Note that if the size of the vector is 0, this function should throw the
std::out_of_range exception with an appropriate error message.

13. Implement the pop_back function. This removes the last element in the smcVector.
Note that if the size of the vector is 0, this function should throw the
std::out_of_range exception with an appropriate error message.

14. Implement the clear function that deletes the current underlying array then creates a
new underlying array of identical capacity. Note that this isn’t the way STD vector’s
clear behaves – you will learn how to mimic that behavior in another class.

15. Implement the assignment operator to create a deep copy of the other smcVector.

16. Implement the copy constructor to create a deep copy of the other smcVector.
• It is a GoodIdea™ to write tests to verify each function before moving on to the next.*/


template <typename T>
class smcVector
{
	const unsigned INITIAL_CAPACITY = 10;
	const unsigned CAPACITY_MULTIPLIER = 2;
public:
	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of INITIAL_SIZE and a size of 0.
	// It also dynamically allocates the underlining array data
	// Input: None
	// Returns: Nothing
	smcVector()
	{
		//default member variables
		mSize = 0;
		mCapacity = INITIAL_CAPACITY;
		mArray = new T[mCapacity];
	}

	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of inputted value.
	// It also dynamically allocates the underlining array data
	// Input: Unsigned integer
	// Returns: Nothing
	smcVector(unsigned inCapacity)
	{
		mSize = 0;
		mCapacity = inCapacity;
		mArray = new T[mCapacity];
	}

	// Function: Copy Constructor
	// Purpose: Initializes the ITP vector to have a
	// copy of the inputted vector
	// Input: Another smcVector
	// Returns: Nothing
	smcVector(const smcVector<T>& other)
	{
		//1. Set the new capacity to the other’s size and size = 0
		mCapacity = other.size();
		mSize = 0;
		//2. Create a new underlying array with the new capacity
		mArray = new T[mCapacity];
		//3. Iterate over the other vector and push_back items to the new vector
		for(int i = 0; i < other.size(); ++i)
    	{
       		push_back(other[i]);
    	}
	}

	// Function: Assignment operator
	// Purpose: Clears the current vector and sets
	// the vector to have a copy of the inputted vector
	// Input: Another smcVector
	// Returns: Nothing
	smcVector<T>& operator=(const smcVector<T>& other) 
	{
		//1. Call the clear function
		clear();
		//2. Delete the current array
		delete[] mArray;
		//3. Set the new capacity to the other’s size and size = 0
		mCapacity = other.size();
		mSize = 0;
		//4. Create a new underlying array with the new capacity
		mArray = new T[mCapacity];
		//5. Iterate over the other vector and push_back items to the new vector
		for(int i = 0; i < other.size(); i++)
		{
			push_back(other[i]);
		}
		//6. By convention, operator= returns *this
		return *this;
	}

	// Function: Destructor
	// Purpose: Deletes the underlying array and
	// sets size/capacity to zero
	// Input: None
	// Returns: Nothing
	~smcVector()
	{
		//delete underlying array
		delete[] mArray;
		//set capacity and size to 0
		mCapacity = 0;
		mSize = 0;
	}
	// Function: clear
	// Purpose: Empties the current vector
	// Input: None
	// Returns: None
	void clear()
	{
		//. Call delete[] on the underlying array
		delete[] mArray;
		//2. Create a new underlying array using the old capacity
		mArray = new T[mCapacity]; 
		//mArray = newArray;
		//3. Set size back to 0
		mSize = 0;
	}

	// Function: empty
	// Purpose: Returns true if the vector is empty
	// Input: None
	// Returns: Boolean
	bool empty()
	{
		//check if vector has no size
		if(mSize == 0)
		{
			return true;
		}
		return false;
	}

	// Function: capacity
	// Purpose: Returns the current capacity of the underlying array data
	// Input: None
	// Returns: Capacity of underlying array data
	unsigned capacity() const
	{
		return mCapacity;
	}

	// Function: size
	// Purpose: Returns the current size of the vector
	// Input: None
	// Returns: Size of vector
	unsigned size() const
	{
		return mSize;
	}

	// Function: data
	// Purpose: Returns the pointer to the underlying array
	// Input: None
	// Returns: T*
	T* data() const
	{
		return mArray;
	}

	// Function: Subscript operator (read/write version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	T& operator[](unsigned index)
	{
		//make sure index is in the range
		if(index < 0 || index>=mSize)
		{
			throw std::out_of_range("Index out of Range");
		}
		return mArray[index];
	}

	// Function: Subscript operator (read-only version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	const T& operator[](unsigned index) const
	{
		//same as previous
		if(index>=mSize)
		{
			throw std::out_of_range("Index out of Range");
		}
		return mArray[index];
	}

	// Function: insert_back
	// Purpose: Adds the specified element to the end of the smcVector
	// It automatically reallocates the underlying array if we are
	// going over capacity
	// Input: Value to add (by const reference)
	// Returns: Nothing
	void push_back(const T& value)
	{
		//if at capacity
		if(mSize>=mCapacity)
		{
			//1. Increase the capacity (usually double it)
			mCapacity = mCapacity * CAPACITY_MULTIPLIER;
			//2. Dynamically allocate a new underlying array w/ new capacity
			T* newArray = new T[mCapacity];
			//3. Copy the data from the old array to the new array
			for(int i = 0; i < mSize; i++)
			{
				newArray[i] = mArray[i];
			}
			//4. Delete the old array
			delete[] mArray;
			//5. Set your pointer to the new array
			mArray = newArray;
		}
		//6. Add an element at index size
		mArray[mSize] = value;
		//7. Increment size by 1
		mSize++;
	}

	// Function: get_back
	// Purpose: Returns the current last element in the vector
	// Does not remove this element from the vector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Value at back of vector, by reference
	T& back()
	{
		//check if vector is empty
		if(mSize == 0)
		{
			throw std::out_of_range("Empty Vector");
		}
		//return last index
		else
		{
			return  mArray[mSize-1];
		}
	}

	// Function: remove_back
	// Purpose: Removes the last element from the smcVector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Nothing
	void pop_back()
	{
		//check if vector is empty
		if(mSize == 0)
		{
			throw std::out_of_range("Empty Vector");
		}
		//decriment size
		else
		{
			mSize--;
		}
	}

	// Function: Output Stream Operator
	// Purpose: Prints the contents of the vector to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, vector to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const smcVector<T>& vector)
	{
		//follow os outline from card.cpp with vector indexes in place of mHand indexes 
		os << "{";
		int i;
		//all but final indexes with comma
		for(i = 0; i < vector.size()-1; i++)
		{
			os<<vector[i]<<", ";
		}
		//final index has no comma
		os<<vector.back()<<"}";
		return os;
	}

private:
	//member variables
	T* mArray;
	unsigned mCapacity;
	unsigned mSize;
};
