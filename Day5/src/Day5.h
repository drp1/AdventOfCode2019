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
	int position;
};

int GetParameterValue(IntCodeProgram& program, int index);
ParameterMode GetParameterCode(int instruction, int index);
Opcode GetOpCode(IntCodeProgram const& program);
Opcode GetOpCode(int instruction);
int GetDigitLength(int instruction);
int GetDigit(int num, int index);
void IntCodeAdd(std::vector<int>& program, int const baseIndex);
void IntCodeMultiply(std::vector<int>& program, int const baseIndex);
Opcode GetNextOpcode(std::vector<int> const& program, int const baseIndex);
int InstructionPointerIncreaseAmount(Opcode const instruction);

// @returns length of intCodeProgram
bool ReadFile(std::string const filePath, std::vector<int>& program);
bool IsNounAndVerbTheAnswer(std::vector<int>& program, int noun, int verb);

#endif 