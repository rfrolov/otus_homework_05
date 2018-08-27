#include "../lib/version.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(lib, version) {
    EXPECT_GT(version(), 0);
}
