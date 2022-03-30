#pragma once

namespace TC {

enum class cmd_type : int
{
    invaild_command = 0,
    copy_directory = 1,
    help = 2,
    list_direcotory_to_copy = 3,
    set_variable = 4
};

class parse_cmd
{
public:
    static bool parsing(int argc, char* argv[], cmd_type& cmd);
};

} // namespace TC