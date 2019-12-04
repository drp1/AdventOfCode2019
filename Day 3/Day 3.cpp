#include "pch.h"

bool testFunc() {
	return true;
}

TEST(TestCaseName, TestName) {
	EXPECT_TRUE(testFunc());
}