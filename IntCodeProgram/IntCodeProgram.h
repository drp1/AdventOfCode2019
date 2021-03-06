#pragma once
#include <vector>
#include <string>

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
	JumpIfTrue = 5,
	JumpIfFalse = 6,
	LessThan = 7,
	Equals = 8,
	Exit = 99
};

struct IntCodeProgram
{
	std::vector<int> instructions;
	int position = 0;
};

int CreateInstruction(Opcode opcode, int param1Mode = 0, int param2Mode = 0);
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
void IntCodeJumpIfTrue(IntCodeProgram& program);
void IntCodeJumpIfFalse(IntCodeProgram& program);
void IntCodeLessThan(IntCodeProgram& program);
void IntCodeEquals(IntCodeProgram& program);


Opcode GetNextOpcode(std::vector<int> const& program, int baseIndex);

bool ReadFile(std::string const& filePath, IntCodeProgram& program);
std::string RunProgramWithPhaseSetting(IntCodeProgram& program, int const phaseSetting, int const inputData);
void StringToIntCodeProgram(std::string const& inputText, IntCodeProgram& program);