//
// Created by jc on 09.12.2021.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ClassName.h"

using testing::Eq;
namespace {
    class ClassDeclaration : public testing::Test {
    public:
        Snake obj;
        ClassDeclaration() {
            obj;
        }
    };
}
TEST_F(ClassDeclaration,test_1) {
    ASSERT_EQ("", "");
}
TEST_F(ClassDeclaration, test_2) {
    ASSERT_EQ("", "");
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}