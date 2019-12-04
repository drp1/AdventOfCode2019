// Day 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Day 2.h"

using namespace std;

#define FILE_PATH "input.txt"
#define PART2_EXPECTED_OUTPUT 19690720

enum Opcode {
	Add = 1,
	Multiply = 2,
	Exit = 99
};

void IntCodeAdd(vector<int>& program, int const baseIndex)
{
	int const
		operand1Index = program[baseIndex + 1],
		operand2Index = program[baseIndex + 2],
		destIndex = program[baseIndex + 3];
	program[destIndex] = program[operand1Index] + program[operand2Index];
}

void IntCodeMultiply(vector<int>& program, int const baseIndex)
{
	int const
		operand1Index = program[baseIndex + 1],
		operand2Index = program[baseIndex + 2],
		destIndex = program[baseIndex + 3];
	program[destIndex] = program[operand1Index] * program[operand2Index];
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
		case Add:
			IntCodeAdd(program, i);
			break;
		case Multiply:
			IntCodeMultiply(program, i);
			break;
		case Exit:
			cout << "Value at position 0: " << program[0] << endl;
			break;
		default:
			break;
		}
	}
}

void Part2(vector<int>& program)
{
	for (size_t noun = 0; noun < 100; noun++)
	{
		for (size_t verb = 0; verb < 100; verb++)
		{
			vector<int> copyOfProgram(program);
			if (IsNounAndVerbTheAnswer(copyOfProgram, noun, verb))
			{
				cout << "Noun: " << noun << " Verb: " << verb << endl;
				cout << "100 * noun + verb = " << (100 * noun) + verb;
				return;
			}
		}
	}
}

bool IsNounAndVerbTheAnswer(std::vector<int>& program, int noun, int verb)
{
	program[1] = noun;
	program[2] = verb;

	Opcode nextOpcode = Opcode::Add;

	for (size_t i = 0; nextOpcode != Opcode::Exit; i += 4)
	{
		nextOpcode = GetNextOpcode(program, i);
		switch (nextOpcode)
		{
		case Add:
			IntCodeAdd(program, i);
			break;
		case Multiply:
			IntCodeMultiply(program, i);
			break;
		case Exit:
			if (program[0] == PART2_EXPECTED_OUTPUT) {
				return true;
			}

			break;
		default:
			break;
		}
	}

	return false;
}


int main()
{
	vector<int> program;
	if (ReadFile(FILE_PATH, program))
	{
		Part2(program);
	}
	else
	{
		cerr << "Unable to read input file" << endl;
		return 1;
	}
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
