#include <gtest/gtest.h>
#include <list>
#include <string>
#include "../../IntCodeProgram/IntCodeProgram.h"

using namespace std;
using namespace testing;

int RunPhaseSettings(list<int> const& phaseSettings, IntCodeProgram const& inputProgram)
{
	int inputSignal = 0;
	for (auto const& phaseSetting : phaseSettings)
	{
		IntCodeProgram programCopy = IntCodeProgram(inputProgram);
		string const outputSignal = RunProgramWithPhaseSetting(programCopy, phaseSetting, inputSignal);
		inputSignal = stoi(outputSignal);
	}
	return inputSignal;
}

TEST(Day7TestSuite, ExamplePhaseSettings)
{
	list<int> phaseSettings = { 4,3,2,1,0 };
	string programText = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0";
	int expectedOutput = 43210;
	IntCodeProgram program;
	StringToIntCodeProgram(programText, program);
	auto inputSignal = RunPhaseSettings(phaseSettings, program);
	EXPECT_EQ(inputSignal, expectedOutput);

	phaseSettings = { 0,1,2,3,4 };
	programText = "3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0";
	expectedOutput = 54321;
	program = IntCodeProgram();
	StringToIntCodeProgram(programText, program);
	inputSignal = RunPhaseSettings(phaseSettings, program);
	EXPECT_EQ(inputSignal, expectedOutput);

	phaseSettings = { 1,0,4,3,2 };
	programText = "3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0";
	expectedOutput = 65210;
	program = IntCodeProgram();
	StringToIntCodeProgram(programText, program);
	inputSignal = RunPhaseSettings(phaseSettings, program);
	EXPECT_EQ(inputSignal, expectedOutput);
}

void swap(int* p, int const a, int const b)
{
	int const temp = p[a];
	p[a] = p[b];
	p[b] = temp;
}

void Permutations(int a[], int n, vector<list<int>>& phaseSettingList)
{
	if (n == 1)
	{
		phaseSettingList.push_back(list<int>({ a[0],a[1],a[2],a[3],a[4]}));
		return;
	}
	for (int i = 0; i < n; i++) {
		swap(a, i, n - 1);  // (remove the ith element)
		Permutations(a, n - 1, phaseSettingList);
		swap(a, i, n - 1);  // (restore for the next round)
	}
}

TEST(Day7TestSuite, Part1)
{
	auto const inputFilePath = "src/input.txt";
	IntCodeProgram program;
	vector<list<int>> phasePermutations;
	int phaseSet[] = { 0,1,2,3,4 };
	Permutations(phaseSet, 5, phasePermutations);
	int maxSignal = 0; // TODO: this should be assigned to the output first phase settings we test
	if (ReadFile(inputFilePath, program))
	{
		for (auto const& phaseSettings : phasePermutations)
		{
			auto const signal = RunPhaseSettings(phaseSettings, program);
			if (signal > maxSignal)
				maxSignal = signal;
		}
	}

	cout << "Max Signal:" << maxSignal << endl;
	EXPECT_EQ(maxSignal, 95757);
}