// Day 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#define FILE_PATH "input.txt"

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

int main()
{
	vector<int> program;
	if (ReadFile(FILE_PATH, program))
	{
		Part1(program);
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
