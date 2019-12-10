#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Day5.h"
#include <gtest/gtest.h>


using namespace std;

TEST(Day5TestSuite, Should_Get_Digit_Length)
{
	EXPECT_EQ(GetDigitLength(0), 1);
	EXPECT_EQ(GetDigitLength(1), 1);
	EXPECT_EQ(GetDigitLength(9), 1);
	EXPECT_EQ(GetDigitLength(10), 2);
	EXPECT_EQ(GetDigitLength(11), 2);
	EXPECT_EQ(GetDigitLength(99), 2);
	EXPECT_EQ(GetDigitLength(100), 3);
	EXPECT_EQ(GetDigitLength(101), 3);
	EXPECT_EQ(GetDigitLength(999), 3);

	EXPECT_EQ(GetDigitLength(-1), 1);
	EXPECT_EQ(GetDigitLength(-9), 1);
	EXPECT_EQ(GetDigitLength(-10), 2);
	EXPECT_EQ(GetDigitLength(-11), 2);
	EXPECT_EQ(GetDigitLength(-99), 2);
	EXPECT_EQ(GetDigitLength(-100), 3);
	EXPECT_EQ(GetDigitLength(-101), 3);
	EXPECT_EQ(GetDigitLength(-999), 3);
}

TEST(Day5TestSuite, Should_Get_OpCode)
{
	EXPECT_EQ(GetOpCode(1), Opcode::Add);
	EXPECT_EQ(GetOpCode(1101), Opcode::Add);

	EXPECT_EQ(GetOpCode(2), Opcode::Multiply);
	EXPECT_EQ(GetOpCode(1102), Opcode::Multiply);

	EXPECT_EQ(GetOpCode(3), Opcode::Input);

	EXPECT_EQ(GetOpCode(4), Opcode::Output);
	EXPECT_EQ(GetOpCode(104), Opcode::Output);

	EXPECT_EQ(GetOpCode(99), Opcode::Exit);

	auto program = IntCodeProgram{};
	program.instructions = vector<int>({ 1002,4,3,4,33 });
	program.position = 0;

	EXPECT_EQ(GetOpCode(program), Opcode::Multiply);
}

TEST(Day5TestSuite, Should_Get_ParameterMode)
{
	EXPECT_EQ(GetParameterCode(1, 0), ParameterMode::Position);
	EXPECT_EQ(GetParameterCode(1, 1), ParameterMode::Position);
	EXPECT_EQ(GetParameterCode(1, 2), ParameterMode::Position);

	EXPECT_EQ(GetParameterCode(1101, 0), ParameterMode::Immediate);
	EXPECT_EQ(GetParameterCode(1101, 1), ParameterMode::Immediate);
	EXPECT_EQ(GetParameterCode(1101, 2), ParameterMode::Position);

	EXPECT_EQ(GetParameterCode(1001, 0), ParameterMode::Position);
}

TEST(Day5TestSuite, Should_Get_Correct_Digit)
{
	EXPECT_EQ(GetDigit(12345, 0), 5);
	EXPECT_EQ(GetDigit(12345, 1), 4);
	EXPECT_EQ(GetDigit(12345, 2), 3);
	EXPECT_EQ(GetDigit(12345, 3), 2);
	EXPECT_EQ(GetDigit(12345, 4), 1);
	EXPECT_EQ(GetDigit(12345, 5), 0);
}

TEST(Day5TestSuite, Should_Get_Parameter_Value)
{
	auto program = IntCodeProgram{};
	program.instructions = vector<int>({ 1002,4,3,4,33});
	program.position = 0;
	
	EXPECT_EQ(GetParameterValue(program, 0), 33);
	EXPECT_EQ(GetParameterValue(program, 1), 3);
}


ParameterMode GetParameterCode(int const instruction, int const index)
{
	auto const digitLength = GetDigitLength(instruction);
	auto const digit = GetDigit(instruction, index + 2);
	return ParameterMode(digit);
}

Opcode GetOpCode(IntCodeProgram const& program)
{
	return GetOpCode(program.instructions[program.position]);
}

Opcode GetOpCode(int const instruction)
{
	return Opcode(instruction % 100);
}


// Digit position starts at one's place = 0, tenth's place = 1, hundred's place = 2, etc..
int GetDigit(int const num, int const digitPosition)
{
	int resultDigit = num;
	resultDigit /= static_cast<int>(pow(10, digitPosition));
	resultDigit %= 10;
	return resultDigit;
}

int GetDigitLength(int const instruction)
{
	int digitLength = 1;
	int const instructionAbs = abs(instruction);
	while (instructionAbs >= static_cast<int>(pow(10, digitLength)))
	{
		digitLength++;
	}
	return digitLength;
}

void AdvanceProgram(IntCodeProgram& program)
{
	Opcode const instruction = GetOpCode(program);
	switch (instruction) {
	case Opcode::Add:
	case Opcode::Multiply:
		program.position += 4;
		break;
	case Opcode::Input:
	case Opcode::Output:
		program.position += 2;
		break;
	case Opcode::Exit:
		program.position += 1;
	default:
		break;
	}
}

int InstructionPointerIncreaseAmount(Opcode const instruction)
{
	switch (instruction) {
	case Opcode::Add:
	case Opcode::Multiply:
		return 4;
	case Opcode::Input:
	case Opcode::Output:
		return 2;
	case Opcode::Exit:
		return 1;
	default:
		return -1;
	}
}

int GetParameterValue(IntCodeProgram& program, int const index)
{
	if (GetParameterCode(program.instructions[program.position], index) == ParameterMode::Position)
	{
		int const address = program.instructions[program.position + index + 1];
		return program.instructions[address];
	}
	return program.instructions[program.position + index + 1];
}

void IntCodeInput(IntCodeProgram& program, int const input)
{
	program.instructions[program.position + 1] = input;
}

void IntCodeOutput(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	cout << param1;
}

void IntCodeAdd(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	program.instructions[program.position] = param1 + param2;
}

void IntCodeMultiply(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	program.instructions[program.position] = param1 * param2;
}


// @returns length of intCodeProgram
bool ReadFile(string const filePath, vector<int>& program)
{
	ifstream fin(filePath);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			char nextChar;
			string numberString;
			do {
				nextChar = fin.get();
				if (isdigit(nextChar))
				{
					numberString.push_back(nextChar);
				}
			} while (isdigit(nextChar) && !fin.eof());

			if (numberString.length() > 0)
				program.push_back(stoi(numberString));
		}
		fin.close();
		return true;
	}
	else
	{
		return false;
	}
}

Opcode GetNextOpcode(vector<int> const& program, int const baseIndex)
{
	return static_cast<Opcode>(program[baseIndex]);
}

void Part1(vector<int>& program)
{
	program[1] = 12;
	program[2] = 2;

	Opcode nextOpcode = Opcode::Add;

	for (size_t i = 0; nextOpcode != Opcode::Exit; i += 4)
	{
		nextOpcode = GetNextOpcode(program, i);
		switch (nextOpcode)
		{
		case Opcode::Add:
			IntCodeAdd(program, i);
			break;
		case Opcode::Multiply:
			IntCodeMultiply(program, i);
			break;
		case Opcode::Exit:
			cout << "Value at position 0: " << program[0] << endl;
			break;
		default:
			break;
		}
	}
}