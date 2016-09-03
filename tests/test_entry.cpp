
/**
	GTest Entry Point, Just separating things
	
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

