#pragma once

#ifndef __Day5_h_
#define __Day5_h_

enum class ParameterMode
{
	Position = 0,
	Immediate = 1
};

enum class Opcode {
	Add = 1,
	Multiply = 2,
	Input = 3,
	Output = 4,
	Exit = 99
};

struct IntCodeProgram
{
	std::vector<int> instructions;
	int position = 0;
};

void AdvanceProgram(IntCodeProgram& program);
int GetParameterValue(IntCodeProgram& program, int index);
ParameterMode GetParameterCode(int instruction, int index);
Opcode GetOpCode(IntCodeProgram const& program);
Opcode GetOpCode(int instruction);
int GetDigitLength(int instruction);
int GetDigit(int num, int digitPosition);

void IntCodeInput(IntCodeProgram& program, int input);
int IntCodeOutput(IntCodeProgram& program);
void IntCodeAdd(IntCodeProgram& program);
void IntCodeMultiply(IntCodeProgram& program);

Opcode GetNextOpcode(std::vector<int> const& program, int baseIndex);

bool ReadFile(std::string const& filePath, IntCodeProgram& program);

#endif 