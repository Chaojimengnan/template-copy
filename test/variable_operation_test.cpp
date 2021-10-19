#include <gtest/gtest.h>
#include <filesystem>
#include "variable_operation.h"

using namespace TC;
namespace fs = std::filesystem;

class variable_operation_test : public ::testing::Test {
 protected:
 variable_operation_test() : var_oper("variable_test.txt")
 {
 }

  variable_operation var_oper;
  
};


TEST_F(variable_operation_test, var_test) {
  std::string temp;
  EXPECT_TRUE(var_oper.set_variable("mymy", "yryr"));
  EXPECT_TRUE(var_oper.set_variable("123asdoijas", "阿松大就啊是第几哦"));
  EXPECT_TRUE(var_oper.set_variable("哦高度", "vjaia"));
  EXPECT_TRUE(var_oper.save());

  EXPECT_TRUE(var_oper.open(true));
  EXPECT_TRUE(var_oper.get_variable("mymy", temp));
  EXPECT_EQ(temp, "yryr");
  EXPECT_TRUE(var_oper.get_variable("123asdoijas", temp));
  EXPECT_EQ(temp, "阿松大就啊是第几哦");
  EXPECT_TRUE(var_oper.get_variable("哦高度", temp));
  EXPECT_EQ(temp, "vjaia");
}
