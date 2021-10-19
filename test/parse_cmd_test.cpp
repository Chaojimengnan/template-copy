#include <gtest/gtest.h>

#include "parse_cmd.h"

using namespace TC;

TEST(parse_cmd_test, invaild_input) {
  cmd_type test_cmd;
  // Normal invaild input
  char* input_str1[] = {"tc", "asdasjiod", "asfjsif"};
  EXPECT_FALSE(parse_cmd::parsing(3, input_str1, test_cmd));
  EXPECT_EQ(test_cmd, cmd_type::invaild_command);

  // Two colons
  // char* input_str2[] = {"tc", "SourceDirectory:TargetDirectory:"};
  // EXPECT_FALSE(parse_cmd::parsing(2, input_str2, test_cmd));
  // EXPECT_EQ(test_cmd, cmd_type::invaild_command);

  // Two equals
  // char* input_str3[] = {"tc", "Variable=value="};
  // EXPECT_FALSE(parse_cmd::parsing(2, input_str3, test_cmd));
  // EXPECT_EQ(test_cmd, cmd_type::invaild_command);

  // Normal invaild input2
  char* input_str4[] = {"tc", "asdasjiod"};
  EXPECT_FALSE(parse_cmd::parsing(2, input_str4, test_cmd));
  EXPECT_EQ(test_cmd, cmd_type::invaild_command);
}


TEST(parse_cmd_test, vaild_input) {
  cmd_type test_cmd;
  // Copy directory
  char* input_str1[] = {"tc", "SourceDirectory:TargetDirectory"};
  EXPECT_TRUE(parse_cmd::parsing(2, input_str1, test_cmd));
  EXPECT_EQ(test_cmd, cmd_type::copy_directory);

  // Lists the directories to copy
  char* input_str2[] = {"tc", "list"};
  EXPECT_TRUE(parse_cmd::parsing(2, input_str2, test_cmd));
  EXPECT_EQ(test_cmd, cmd_type::list_direcotory_to_copy);

  // Help
  char* input_str3[] = {"tc", "help"};
  EXPECT_TRUE(parse_cmd::parsing(2, input_str3, test_cmd));
  EXPECT_EQ(test_cmd, cmd_type::help);

  // Set a variable
  char* input_str4[] = {"tc", "variable=value"};
  EXPECT_TRUE(parse_cmd::parsing(2, input_str4, test_cmd));
  EXPECT_EQ(test_cmd, cmd_type::set_variable);
}