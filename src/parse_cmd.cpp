#include "parse_cmd.h"
#include <string>

namespace TC {

/* Returns true if parsing succeeds, otherwise return false */
bool parse_cmd::parsing(int argc, char* argv[], cmd_type& cmd)
{
    cmd = cmd_type::invaild_command;
    // File names with Spaces are not currently supported
    // This will be fixed in future releases
    if (argc != 2)
        return false;

    std::string cmd_str = argv[1];

    if (cmd_str == "help")
    {
        cmd = cmd_type::help;
        return true;
    }

    if (cmd_str == "list")
    {
        cmd = cmd_type::list_direcotory_to_copy;
        return true;
    }

    if (cmd_str.find_first_of(":") != std::string::npos)
    {
        cmd = cmd_type::copy_directory;
        return true;
    }

    if (cmd_str.find_first_of("=") != std::string::npos)
    {
        cmd = cmd_type::set_variable;
        return true;
    }

    return false;
}

} // namespace TC