#include "gtest.h"
#include "polynomials.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Polynomials, testig_test)
{
	EXPECT_NO_THROW(std::cout << 1);
}