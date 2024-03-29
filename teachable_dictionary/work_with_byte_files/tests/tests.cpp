#include <gtest/gtest.h>

#include "work_with_bytes.hpp"

using work_with_bytes::reader;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(reader, constr)
{
    reader rdr {PROJECT_DIR_PATH + std::string("/work_with_byte_files/tests/text.txt")};

    std::cout << rdr.get_punct();
    std::cout << rdr.get_word();
    std::cout << rdr.get_punct();
    std::cout << rdr.get_word();
    std::cout << rdr.get_punct() << std::endl;
    rdr.get_punct();
    rdr.get_punct();

    std::string empty_word = rdr.get_word();
    if (!empty_word.size()) {
        std::cout << "empty" << std::endl;
    }
}
