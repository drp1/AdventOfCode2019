#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Day5.h"
#include <gtest/gtest.h>

using namespace std;

int CreateInstruction(Opcode opcode, int const param1Mode, int const param2Mode)
{
	if (param1Mode > 1)
		throw invalid_argument(string(__FUNCTION__) + ": Invalid param1Mode");
	if (param2Mode > 1)
		throw invalid_argument(string(__FUNCTION__) + ": Invalid param3Mode");

	int const opcodeNumber = static_cast<int>(opcode);
	int const param1Digit = 100 * param1Mode;
	int const param2Digit = 1000 * param2Mode;

	switch (opcode)
	{
	case Opcode::Add:
	case Opcode::Multiply:
	case Opcode::LessThan:
	case Opcode::Equals:
	case Opcode::JumpIfTrue:
	case Opcode::JumpIfFalse:
		return opcodeNumber + param1Digit + param2Digit;
	case Opcode::Output:
		return opcodeNumber + param1Digit;
	case Opcode::Input:
	case Opcode::Exit:
		return opcodeNumber;
	default:
		throw invalid_argument(string(__FUNCTION__) + ": Unknown Opcode: " + to_string(opcodeNumber));
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
	program.position += 2; // Advance instruction pointer
}

int IntCodeOutput(IntCodeProgram& program)
{
	int const output = GetParameterValue(program, 0);
	program.position += 2; // Advance instruction pointer
	return output;
}

void IntCodeAdd(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	int const writeIndex = program.instructions[program.position + 3];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = param1 + param2;
	program.position += 4; // Advance instruction pointer
}

void IntCodeMultiply(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	int const writeIndex = program.instructions[program.position + 3];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = param1 * param2;
	program.position += 4; // Advance instruction pointer
}

void IntCodeJumpIfTrue(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	if (param1 != 0)
	{
		program.position = param2;
		return;
	}
	program.position += 3; // Advance instruction pointer
}

void IntCodeJumpIfFalse(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	if (param1 == 0)
	{
		program.position = param2;
		return;
	}
	program.position += 3; // Advance instruction pointer
}

void IntCodeLessThan(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	int const writeIndex = program.instructions[program.position + 3];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = (param1 < param2 ? 1 : 0);
	program.position += 4; // Advance instruction pointer
}

void IntCodeEquals(IntCodeProgram& program)
{
	int const param1 = GetParameterValue(program, 0);
	int const param2 = GetParameterValue(program, 1);
	int const writeIndex = program.instructions[program.position + 3];
	if (writeIndex >= program.instructions.size())
		throw std::out_of_range(string(__FUNCTION__) + ": Out of range");
	program.instructions[writeIndex] = (param1 == param2 ? 1 : 0);
	program.position += 4; // Advance instruction pointer
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
