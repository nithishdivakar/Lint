#include "gtest/gtest.h"
#include "Lint.h"
#include <iostream>


TEST(Lint ,to_string){
	Lint L1(1);
	EXPECT_STREQ("1",L1.to_string().c_str());
}


TEST(Lint ,addition){
	Lint L1(1);
	Lint L2(9999999);
	EXPECT_STREQ("10000000",(L1+L2).to_string().c_str());
	EXPECT_STREQ("10000000",(L2+L1).to_string().c_str());
}

TEST(Lint ,substraction){
	Lint L1(1);
	Lint L2(9999999);
	EXPECT_STREQ("-9999998",(L1-L2).to_string().c_str());
	EXPECT_STREQ("9999998",(L2-L1).to_string().c_str());
}
