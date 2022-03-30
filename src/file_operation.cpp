#include <iostream>
#ifndef NDEBUG
#    include <cassert>
#endif

#include "file_operation.h"
#include "parse_cmd.h"
#include "tem_file_operation.h"
#include "variable_operation.h"

namespace TC {

file_operation::file_operation(char* argv[])
    : argv(argv), working_path(fs::current_path()), tc_path(fs::path(argv[0]).parent_path()),
      tem_oper(std::make_unique<tem_file_operation>(fs::path(argv[0]).parent_path().string() + "/variable.txt"))
{
#ifndef NDEBUG
    std::cout << "argv[0]=" << argv[0] << "\n";
    std::cout << "working_path=" << working_path << "\n";
    std::cout << "tc_path=" << tc_path << "\n";
#endif
}

bool file_operation::exec(cmd_type& cmd)
{
    switch (cmd)
    {
    case cmd_type::invaild_command:
        // It shouldn't be here
        std::terminate();
        break;
    case cmd_type::help:
        help_info();
        break;
    case cmd_type::copy_directory:
#ifndef NDEBUG
        std::cout << "cmd = copy_directory\n";
#endif
        if (!copy_directory())
        {
            std::cerr << "Copy directory fails!\n";
            return false;
        }
        break;
    case cmd_type::list_direcotory_to_copy:
#ifndef NDEBUG
        std::cout << "cmd = list_direcotory_to_copy\n";
#endif
        if (!list_directory_to_copy())
        {
            std::cerr << "The template directory does not exist on the TC location\n";
            return false;
        }
        break;
    case cmd_type::set_variable:
#ifndef NDEBUG
        std::cout << "cmd = set_variable\n";
#endif
        if (!set_variable())
        {
            std::cerr << "Set variable fails!\n";
            return false;
        }
        break;
    default:
        // It shouldn't be here
        std::terminate();
        break;
    }
    return true;
}

bool file_operation::copy_directory()
{
    std::string base_cmd = argv[1];
    std::string source_str, target_str;
    if (!split_str(base_cmd, source_str, target_str, ':'))
        return false;

    fs::path target_dir = working_path / target_str;
    fs::path source_dir = tc_path / source_str;

#ifndef NDEBUG
    std::cout << "source_str=" << source_str << "\n";
    std::cout << "target_str=" << target_str << "\n";
#endif
    // Check whether the directory exists
    if (!fs::exists(source_dir))
    {
        std::cout << "The source directory \"" << source_str << "\" does not exist!\n";
        return false;
    }
    if (fs::exists(target_dir) && !fs::is_directory(target_dir))
    {
        std::cerr << "The target directory already has a file with the same name!\n";
        return false;
    }
    fs::create_directory(target_dir);

    auto make_target = [&](fs::path source_path) -> fs::path {
        bool find_source = false;
        fs::path target_path = target_dir;
        for (auto&& i : source_path)
        {
            if (find_source)
                target_path /= i;
            if (i == source_str)
                find_source = true;
        }
        return target_path;
    };

    init_build_in_variables(source_str, target_str);

    fs::recursive_directory_iterator re_iter(source_dir);
    for (auto&& i : re_iter)
    {
        fs::path current_source_path = i.path();
        fs::path current_target_path = make_target(current_source_path);
        std::cerr << current_target_path << "\n";
        if (current_source_path.extension() != ".tem")
        {
            if (fs::is_directory(current_source_path))
                fs::create_directory(current_target_path);
            else
                fs::copy_file(current_source_path, current_target_path);
            // fs::copy(current_source_path, "." / current_target_path.filename());
        } else {
            tem_oper->tem_translate(current_source_path.string(), current_target_path.replace_extension().string());
        }
    }

    return true;
}

bool file_operation::set_variable()
{
    std::string base_cmd = argv[1];
    std::string var_name, var_val;
    if (!split_str(base_cmd, var_name, var_val, '='))
        return false;
    if (!tem_oper->set_variable(var_name, var_val))
        return false;
    return true;
}

bool file_operation::list_directory_to_copy()
{
    fs::directory_iterator iter(tc_path);
    bool empty = true;
    for (auto&& i : iter)
        if (i.is_directory())
            std::cout << i.path().filename().string() << "\n", empty = false;
    return !empty;
}

bool file_operation::split_str(const std::string& sc_str, std::string& lsub_str, std::string& rsub_str, char split_char)
{
    auto split_point = sc_str.find_first_of(split_char);
    if (split_point == std::string::npos)
        return false;

    lsub_str = sc_str.substr(0, split_point);
    rsub_str = sc_str.substr(split_point + 1);
    return true;
}

void help_info()
{
    std::cout << "\n\ntemplate-copy\n\n"
                 "usage: tc command\n\n"
                 "command:\n"
                 "    help\n"
                 "    list\n"
                 "    variable=value\n"
                 "    source-directory:target-directory\n\n"
                 "build-in-variable:\n";
    for (auto &&i : build_in_variables)
    {
        std::cout << "    " << i.first << "\n";
    }
}

} // namespace TC