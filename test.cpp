#include "gtest/gtest.h"
#include "header.h"
#include <fstream>
#include <vector>


TEST(Test, Read) {
    BMP bmp;
    bmp.bmpRead("1.bmp");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
