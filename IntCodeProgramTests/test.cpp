#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../IntCodeProgram/IntCodeProgram.h"

using namespace std;
using namespace testing;

TEST(IntCodeTestSuite, Should_Get_Digit_Length)
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

TEST(IntCodeTestSuite, Should_Get_OpCode)
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

TEST(IntCodeTestSuite, Should_Get_ParameterMode)
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

TEST(IntCodeTestSuite, Should_Get_Correct_Digit)
{
	EXPECT_EQ(GetDigit(12345, 0), 5);
	EXPECT_EQ(GetDigit(12345, 1), 4);
	EXPECT_EQ(GetDigit(12345, 2), 3);
	EXPECT_EQ(GetDigit(12345, 3), 2);
	EXPECT_EQ(GetDigit(12345, 4), 1);
	EXPECT_EQ(GetDigit(12345, 5), 0);
}

TEST(IntCodeTestSuite, Should_Get_Parameter_Value)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1002,4,3,4,33 });
	EXPECT_EQ(GetParameterValue(program, 0), 33); // Grab value from position 
	EXPECT_EQ(GetParameterValue(program, 1), 3);  // Use immediate value
}

TEST(IntCodeTestSuite, Program_Position_Should_Start_At_Zero)
{
	IntCodeProgram program;
	EXPECT_EQ(program.position, 0);
}

TEST(IntCodeTestSuite, Input_Code_Should_Save_To_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 3,5,0,0,0,0 });
	IntCodeInput(program, 1);
	EXPECT_EQ(program.instructions[5], 1);
}

TEST(IntCodeTestSuite, Output_Code_Should_Output_Value_At_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 4,5,0,0,0,2 });
	auto const output = IntCodeOutput(program);
	EXPECT_EQ(program.instructions[5], output);
}

TEST(IntCodeTestSuite, Add_Code_Should_Store_At_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1,4,5,6,10,	11,0 });
	program.position = 0;
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[6], 10 + 11);
}

TEST(IntCodeTestSuite, Add_Code_Should_Use_Immediate_Values)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1101,13,11,4,0 });
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[4], 13 + 11);

	program.instructions = vector<int>({ 1001,4,9,5,16,0 });
	program.position = 0;
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[5], 16 + 9);

	program.instructions = vector<int>({ 101,7,4,5,11,0 });
	program.position = 0;
	IntCodeAdd(program);
	EXPECT_EQ(program.instructions[5], 7 + 11);
}

TEST(IntCodeTestSuite, Multiply_Code_Should_Store_At_Position)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1,4,5,6,7,9,0 });
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[6], 7 * 9);
}

TEST(IntCodeTestSuite, Multiply_Code_Should_Use_Immediate_Values)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ 1102,13,11,4,0 });
	program.position = 0;
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[4], 13 * 11);

	program.instructions = vector<int>({ 1001,4,9,5,16,0 });
	program.position = 0;
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[5], 16 * 9);

	program.instructions = vector<int>({ 101,7,4,5,11,0 });
	program.position = 0;
	IntCodeMultiply(program);
	EXPECT_EQ(program.instructions[5], 7 * 11);
}

TEST(IntCodeTestSuite, Add_Code_Should_Advance_Instruction_Pointer)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ CreateInstruction(Opcode::Add),4,5,6,10,	11,0 });
	EXPECT_EQ(program.position, 0);

	IntCodeAdd(program);
	EXPECT_EQ(program.position, 4);
}

TEST(IntCodeTestSuite, Multiply_Code_Should_Advance_Instruction_Pointer)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ CreateInstruction(Opcode::Multiply),4,5,6,10,11,0 });
	EXPECT_EQ(program.position, 0);

	IntCodeMultiply(program);
	EXPECT_EQ(program.position, 4);
}

TEST(IntCodeTestSuite, Input_iterator_tag_Code_Should_Advance_Instruction_Pointer)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ CreateInstruction(Opcode::Input),5,0,0,0,0 });
	EXPECT_EQ(program.position, 0);

	IntCodeInput(program, 1);
	EXPECT_EQ(program.position, 2);
}

TEST(IntCodeTestSuite, Output_Code_Should_Advance_Instruction_Pointer)
{
	IntCodeProgram program;
	program.instructions = vector<int>({ CreateInstruction(Opcode::Output),4,5,6,10,11,0 });
	EXPECT_EQ(program.position, 0);

	IntCodeOutput(program);
	EXPECT_EQ(program.position, 2);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Position_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 8;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,0, 0),3,4,checkValue,expectedJumpAmount });
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Position_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,0, 1),3,expectedJumpAmount,checkValue });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}
TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Immediate_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,1, 0),checkValue,3,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Immediate_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 65;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,1, 1),checkValue,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Position_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 8;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,0, 0),3,4,checkValue,expectedJumpAmount });
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Position_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,0, 1),3,expectedJumpAmount,checkValue });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Immediate_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,1, 0),checkValue,3,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfTrue_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Immediate_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 65;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfTrue,1, 1),checkValue,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfTrue(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Position_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 8;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,0, 0),3,4,checkValue,expectedJumpAmount });
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Position_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,0, 1),3,expectedJumpAmount,checkValue });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Immediate_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,1, 0),checkValue,3,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_True_Param1_Immediate_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 0;
	int const expectedJumpAmount = 65;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,1, 1),checkValue,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, expectedJumpAmount);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Position_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 8;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,0, 0),3,4,checkValue,expectedJumpAmount });
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Position_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,0, 1),3,expectedJumpAmount,checkValue });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Immediate_Param2_Position)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 435;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,1, 0),checkValue,3,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, JumpIfFalse_Code_Should_Not_Advance_Instruction_Pointer_If_False_Param1_Immediate_Param2_Immediate)
{
	IntCodeProgram program;
	int const checkValue = 1;
	int const expectedJumpAmount = 65;
	program.instructions = vector<int>({ CreateInstruction(Opcode::JumpIfFalse,1, 1),checkValue,expectedJumpAmount });
	program.position = 0;
	EXPECT_EQ(program.position, 0);
	IntCodeJumpIfFalse(program);
	EXPECT_EQ(program.position, 3);
}

TEST(IntCodeTestSuite, LessThan_Code_Should_Set_1_If_Param1_Less_Than_Param2)
{
	IntCodeProgram program;
	int const param1 = 1;
	int const param2 = 65;
	program.instructions = vector<int>({
		CreateInstruction(Opcode::LessThan,1, 1),
		param1,
		param2,
		4,
		0
		});

	EXPECT_EQ(program.instructions[4], 0);
	IntCodeLessThan(program);
	EXPECT_EQ(program.instructions[4], 1);
}

TEST(IntCodeTestSuite, LessThan_Code_Should_Set_0_If_Param1_Greater_Than_Or_Equal_To_Param2)
{
	IntCodeProgram program;
	int const param1 = 65;
	int const param2 = 1;
	program.instructions = vector<int>({
		CreateInstruction(Opcode::LessThan,1, 1),
		param1,
		param2,
		4,
		0
		});

	EXPECT_EQ(program.instructions[4], 0);
	IntCodeLessThan(program);
	EXPECT_EQ(program.instructions[4], 0);
}

TEST(IntCodeTestSuite, Equal_Code_Should_Set_1_If_Param1_Is_Equal_To_Param2)
{
	IntCodeProgram program;
	int const param1 = 1;
	int const param2 = 1;
	program.instructions = vector<int>({
		CreateInstruction(Opcode::Equals,1, 1),
		param1,
		param2,
		4,
		0
		});

	EXPECT_EQ(program.instructions[4], 0);
	IntCodeEquals(program);
	EXPECT_EQ(program.instructions[4], 1);
}

TEST(IntCodeTestSuite, Equal_Code_Should_Set_0_If_Param1_Is_Not_Equal_To_Param2)
{
	IntCodeProgram program;
	int const param1 = 0;
	int const param2 = 1;
	program.instructions = vector<int>({
		CreateInstruction(Opcode::Equals,1, 1),
		param1,
		param2,
		4,
		0
		});

	EXPECT_EQ(program.instructions[4], 0);
	IntCodeEquals(program);
	EXPECT_EQ(program.instructions[4], 0);
}

TEST(IntCodeTestSuite, CreateInstruction_Should_Return_Correct_Instruction)
{
	int instruction;
	instruction = CreateInstruction(Opcode::Input, 0, 0);
	EXPECT_EQ(instruction, 3);
	instruction = CreateInstruction(Opcode::Input, 0, 1);
	EXPECT_EQ(instruction, 3);
	instruction = CreateInstruction(Opcode::Input, 1, 0);
	EXPECT_EQ(instruction, 3);
	instruction = CreateInstruction(Opcode::Input, 1, 1);
	EXPECT_EQ(instruction, 3);

	instruction = CreateInstruction(Opcode::Output, 0, 0);
	EXPECT_EQ(instruction, 4);
	instruction = CreateInstruction(Opcode::Output, 0, 1);
	EXPECT_EQ(instruction, 4);
	instruction = CreateInstruction(Opcode::Output, 1, 0);
	EXPECT_EQ(instruction, 104);
	instruction = CreateInstruction(Opcode::Output, 1, 1);
	EXPECT_EQ(instruction, 104);

	instruction = CreateInstruction(Opcode::Add, 0, 0);
	EXPECT_EQ(instruction, 1);
	instruction = CreateInstruction(Opcode::Add, 0, 1);
	EXPECT_EQ(instruction, 1001);
	instruction = CreateInstruction(Opcode::Add, 1, 0);
	EXPECT_EQ(instruction, 101);
	instruction = CreateInstruction(Opcode::Add, 1, 1);
	EXPECT_EQ(instruction, 1101);
}

TEST(IntCodeTestSuite, Should_Convert_String_To_IntCodeProgram)
{
	IntCodeProgram program;
	string const inputProgram = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0";
	StringToIntCodeProgram(inputProgram, program);
	EXPECT_THAT(program.instructions, ElementsAre(3, 15, 3, 16, 1002, 16, 10, 16, 1, 16, 15, 15, 4, 15, 99, 0, 0));
}
