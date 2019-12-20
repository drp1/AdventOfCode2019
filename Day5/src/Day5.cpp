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

	IntCodeProgram program;
	program.instructions = vector<int>({ 1002,4,3,4,33 });

	EXPECT_EQ(GetOpCode(program), Opcode::Multiply);
}

TEST(Day5TestSuite, Should_Get_ParameterMode)
{
	EXPECT_EQ(GetParameterCode(1, 0), ParameterMode::Position);
	EXPECT_EQ(GetParameterCode(1, 1), ParameterMode::Position);
	EXPECT_EQ(GetParameterCode(1, 2), ParameterMode::Position);

	EXPECT_EQ(GetParameterCode(101, 0), ParameterMode::Immediate);
	EXPECT_EQ(GetParameterCode(101, 1), ParameterMode::Position);
	EXPECT_EQ(GetParameterCode(101, 2), ParameterMode::Position);
	
	EXPECT_EQ(GetParameterCode(1001, 0), ParameterMode::Position);
	EXPECT_EQ(GetParameterCode(1001, 1), ParameterMode::Immediate);
	EXPECT_EQ(GetParameterCode(1001, 2), ParameterMode::Position);
	
	EXPECT_EQ(GetParameterCode(1101, 0), ParameterMode::Immediate);
	EXPECT_EQ(GetParameterCode(1101, 1), ParameterMode::Immediate);
	EXPECT_EQ(GetParameterCode(1101, 2), ParameterMode::Position);
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
	IntCodeProgram program;
	program.instructions = vector<int>({ 1002,4,3,4,33});
	EXPECT_EQ(GetParameterValue(program, 0), 33); // Grab value from position 
	EXPECT_EQ(GetParameterValue(program, 1), 3);  // Use immediate value
}

TEST(Day5TestSuite, Program_Position_Should_Start_At_Zero)
{
	IntCodeProgram program;
	EXPECT_EQ(program.position, 0);
}

TEST(Day5TestSuite, Input_Code_Should_Save_To_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 3,5,0,0,0,0 });
	IntCodeInput(program, 1);
	EXPECT_EQ(program.instructions[5], 1);
}

TEST(Day5TestSuite, Output_Code_Should_Output_Value_At_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 4,5,0,0,0,2 });
	auto const output = IntCodeOutput(program);
	EXPECT_EQ(program.instructions[5], output);
}

TEST(Day5TestSuite, Add_Code_Should_Store_At_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1,4,5,6,10,	11,0 });
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[6], 10 + 11);
}

TEST(Day5TestSuite, Add_Code_Should_Use_Immediate_Values)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1101,13,11,4,0 });
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[4], 13 + 11);

	program.instructions = vector<int>({ 1001,4,9,5,16,0 });
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[5], 16 + 9);

	program.instructions = vector<int>({ 101,7,4,5,11,0 });
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[5], 7 + 11);
}

TEST(Day5TestSuite, Multiply_Code_Should_Store_At_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({	1,4,5,6,7,9,0 });
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[6], 7 * 9);
}

TEST(Day5TestSuite, Multiply_Code_Should_Use_Immediate_Values)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1102,13,11,4,0 });
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[4], 13 * 11);

	program.instructions = vector<int>({ 1001,4,9,5,16,0 });
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[5], 16 * 9);

	program.instructions = vector<int>({ 101,7,4,5,11,0 });
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[5], 7 * 11);
}

TEST(Day5TestSuite, Part1)
{
	// Read program from file
	auto const inputFilePath = "src/input.txt";
	IntCodeProgram program;
	
	if(ReadFile(inputFilePath, program))
	{

		// Program loop
		Opcode opcode;
		do
		{
			opcode = GetOpCode(program);
			
			switch (opcode)
			{
			case Opcode::Add:
				IntCodeAdd(program);
				break;
			case Opcode::Multiply:
				IntCodeMultiply(program);
				break;
			case Opcode::Input:
				IntCodeInput(program, 1);
				break;
			case Opcode::Output:
				cout << IntCodeOutput(program);
				break;
			case Opcode::Exit:
				break;
			default:
				throw 1;
			}

			AdvanceProgram(program);
		}	while (opcode != Opcode::Exit);
	}
	
}


ParameterMode GetParameterCode(int const instruction, int const index)
{
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
	return (num / static_cast<int>(pow(10, digitPosition))) % 10;
}

int GetDigitLength(int const instruction)
{
	int digitLength = 1;
	while (abs(instruction) >= static_cast<int>(pow(10, digitLength)))
	{
		digitLength++;
	}
	return digitLength;
}

void AdvanceProgram(IntCodeProgram& program)
{
	switch (GetOpCode(program)) {
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

int GetParameterValue(IntCodeProgram& program, int const index)
{
	int address;
	if (GetParameterCode(program.instructions[program.position], index) == ParameterMode::Position)
		address = program.instructions[program.position + index + 1u];		
	else
		address = program.position + index + 1;
	
	if (address >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	
	return program.instructions[address];
}

void IntCodeInput(IntCodeProgram& program, int const input)
{
	int const writeIndex = program.instructions[program.position + 1];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = input;
}

int IntCodeOutput(IntCodeProgram& program)
{
	return GetParameterValue(program, 0);
}

void IntCodeAdd(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	int const writeIndex = program.instructions[program.position + 3];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = param1 + param2;
}

void IntCodeMultiply(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	int const writeIndex = program.instructions[program.position + 3];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = param1 * param2;
}

bool ReadFile(string const& filePath, IntCodeProgram& program)
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
				if (isdigit(nextChar) || nextChar == '-')
				{
					numberString.push_back(nextChar);
				}
			} while ((isdigit(nextChar) || nextChar == '-') && !fin.eof());

			int a;
			stringstream(numberString) >> a;
			if (numberString.length() > 0)
				program.instructions.push_back(a);
		}
		fin.close();
		return true;
	}
	return false;
}

Opcode GetNextOpcode(vector<int> const& program, int const baseIndex)
{
	return static_cast<Opcode>(program[baseIndex]);
}