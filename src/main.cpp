#include <iostream>

#include "parse_cmd.h"
#include "file_operation.h"
#include "tem_file_operation.h"

using TC::cmd_type;
using TC::parse_cmd;
using TC::file_operation;
using TC::help_info;


int main(int argc, char* argv[])
{
    cmd_type cmd;
    if (!parse_cmd::parsing(argc, argv, cmd))
    {
        std::cerr << "Invaild command!\n";
        help_info();
        return 1;
    }

    file_operation file_oper(argv);

    if (file_oper.exec(cmd))
        std::cout << "Operation successfully completed!\n";
    else return 1;

    return 0;
}
