#include <gtest/gtest.h>

int GetDigitAtIndex(int const num, int const index, int const numDigits)
{
	int resultDigit = num;
	resultDigit /= static_cast<int>(pow(10, numDigits - index - 1)); 
	resultDigit %= 10;
	return resultDigit;
}

bool NumberContainsOnlyTwoAdjacentDigits(int const num, int const numDigits)
{
	int i = 0;

	// Left edge of window
	if (numDigits < 2)
	{
		return false;
	}
	if (numDigits == 2)
	{
		int const leftDigit = GetDigitAtIndex(num, i, numDigits);
		int const rightDigit = GetDigitAtIndex(num, i + 1, numDigits);
		return leftDigit == rightDigit;
	}
	if (numDigits > 2) {
		int const leftDigit = GetDigitAtIndex(num, i, numDigits);
		int const centerDigit = GetDigitAtIndex(num, i + 1, numDigits);
		int const rightDigit = GetDigitAtIndex(num, i + 2, numDigits);

		if (leftDigit == centerDigit && centerDigit != rightDigit)
		{
			return true;
		}
	}
	
	// Center
	while (++i <= numDigits - 2 - 1) // Minus 2 because we are checking two elements ahead, and minus 1 because zero-based index
	{
		int const leftDigit = GetDigitAtIndex(num, i - 1, numDigits);
		int const leftCenterDigit = GetDigitAtIndex(num, i, numDigits);
		int const rightCenterDigit = GetDigitAtIndex(num, i + 1, numDigits);
		int const rightDigit = GetDigitAtIndex(num, i + 2, numDigits);

		if (leftCenterDigit == rightCenterDigit && (leftDigit != leftCenterDigit && rightDigit != rightCenterDigit))
		{
			return true;
		}
	}

	// Right edge of window
	int const leftDigit = GetDigitAtIndex(num, i - 1, numDigits);
	int const centerDigit = GetDigitAtIndex(num, i, numDigits);
	int const rightDigit = GetDigitAtIndex(num, i + 1, numDigits);

	if (leftDigit != centerDigit && centerDigit == rightDigit)
	{
		return true;
	}

	return false;
}


bool NumberContainsTwoOrMoreAdjacentDigits(int num, int numDigits)
{
	int lastDigit = num % 10; // Isolate least significant digit
	for (int i = 1; i < numDigits; i++)
	{
		num /= 10; // Remove least significant digit
		int currentDigit = num % 10;
		if (currentDigit == lastDigit)
			return true;
		lastDigit = currentDigit;
	}
	return false;
}

bool DigitsDoNotDecreaseLeftToRight(int num, int numDigits)
{
	// It is actually easier to prove if we find there are no increasing numbers from right to left
	
	int lastDigit = num % 10; // Isolate least significant digit
	for (int i = 1; i < numDigits; i++)
	{
		num /= 10; // Remove least significant digit
		int currentDigit = num % 10;
		if (currentDigit > lastDigit)
			return false;
		lastDigit = currentDigit;
	}

	return true;
}

TEST(Day4TestSuite, Should_Return_Correct_Digit)
{
	EXPECT_EQ(GetDigitAtIndex(12345, 0, 6), 0);
	EXPECT_EQ(GetDigitAtIndex(12345, 1, 6), 1);
	EXPECT_EQ(GetDigitAtIndex(12345, 2, 6), 2);
	EXPECT_EQ(GetDigitAtIndex(12345, 3, 6), 3);
	EXPECT_EQ(GetDigitAtIndex(12345, 4, 6), 4);
	EXPECT_EQ(GetDigitAtIndex(12345, 5, 6), 5);
}


TEST(Day4TestSuite, Should_Return_Numbers_With_At_Only_Two_Adajcent_Numbers)
{
	EXPECT_TRUE(NumberContainsOnlyTwoAdjacentDigits(112233, 6));
	EXPECT_FALSE(NumberContainsOnlyTwoAdjacentDigits(123444, 6));
	EXPECT_TRUE(NumberContainsOnlyTwoAdjacentDigits(111122, 6));
}

TEST(Day4TestSuite, Should_Return_Numbers_With_At_Least_Two_Adajcent_Numbers)
{
	EXPECT_TRUE(NumberContainsTwoOrMoreAdjacentDigits(122345, 6));
	EXPECT_TRUE(NumberContainsTwoOrMoreAdjacentDigits(111111, 6));
	EXPECT_FALSE(NumberContainsTwoOrMoreAdjacentDigits(123789, 6));
}


TEST(Day4TestSuite, Should_Return_Numbers_With_No_Decreasing_Digits_Left_To_Right)
{
	EXPECT_TRUE(DigitsDoNotDecreaseLeftToRight(111123, 6));
	EXPECT_TRUE(DigitsDoNotDecreaseLeftToRight(135679, 6));
	EXPECT_FALSE(DigitsDoNotDecreaseLeftToRight(223450, 6));
}

TEST(Day4TestSuite, Part1)
{
	int const numberOfDigits = 6;
	int numberOfValidNumbers = 0;
	int start = 347312, end = 805915;
	
	for (int i = start; i <= end; i++)
	{
		if (!NumberContainsTwoOrMoreAdjacentDigits(i, numberOfDigits))
			continue;
		if (!DigitsDoNotDecreaseLeftToRight(i, numberOfDigits))
			continue;
		numberOfValidNumbers++;
	}

	std::cout << "Part 1: " << numberOfValidNumbers;
}


TEST(Day4TestSuite, Part2)
{
	int const numberOfDigits = 6;
	int numberOfValidNumbers = 0;
	int start = 347312, end = 805915;

	for (int i = start; i <= end; i++)
	{
		if (!NumberContainsOnlyTwoAdjacentDigits(i, numberOfDigits))
			continue;
		if (!DigitsDoNotDecreaseLeftToRight(i, numberOfDigits))
			continue;
		numberOfValidNumbers++;
	}

	std::cout << "Part 2: " << numberOfValidNumbers;
}
