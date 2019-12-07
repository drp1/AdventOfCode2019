#include <gtest/gtest.h>

bool NumberContainsTwoOrMoreAdjacentDigits(int num, int numDigits)
{
	int lastDigit = num % 10; // Isolate least significant digit
	for (int i = 0; i < numDigits; i++)
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
	for (int i = 0; i < numDigits; i++)
	{
		num /= 10; // Remove least significant digit
		int currentDigit = num % 10;
		if (currentDigit > lastDigit)
			return false;
		lastDigit = currentDigit;
	}

	return true;
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
