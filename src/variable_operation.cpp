#include "variable_operation.h"
#include "text_editor.h"
#ifndef NDEBUG
#    include <iostream>
#endif

#include <chrono>
#include <iomanip>
#include <sstream>

namespace TC {

std::unordered_map<std::string, std::string> build_in_variables = {
    { "__project_name__", "" },
    { "__time__", "" },
    { "__template_name__", "" }
};

variable_operation::variable_operation() : variable_operation("variable.txt") { }

variable_operation::variable_operation(const std::string& variable_path)
    : variable_path(variable_path), editor(std::make_unique<text_editor>(variable_path)) { }

variable_operation::~variable_operation()
{
    if (is_modify)
        save();
}

bool variable_operation::open(bool is_clear)
{
    return editor->load_text(is_clear);
}

bool variable_operation::save()
{
    if (is_modify)
    {
        is_modify = false;
        return editor->save_text(true);
    } else
        return false;
}

void variable_operation::set_path(const std::string& variable_path)
{
    this->variable_path = variable_path;
    editor->set_path(variable_path);
}

bool variable_operation::get_variable(const std::string& var_name, std::string& var_val)
{
    bool is_find = false;

    // Check if it is a built-in variable
    auto&& iter = build_in_variables.find(var_name);
    if (iter != build_in_variables.end())
    {
        var_val = iter->second;
        return true;
    }

    auto line_num = editor->find_text_line(var_name);
    if (line_num != std::string::npos)
    {
        is_find = true;
        std::string variable_item;
        editor->get_line(line_num, variable_item);
        var_val = variable_item.substr(var_name.size() + 1);
    }
#ifndef NDEBUG
    else
    {
        std::cerr << "The variable ${" << var_name << "} could not be found\n";
    }
#endif

    return is_find;
}

bool variable_operation::set_variable(const std::string& var_name, const std::string& var_val)
{
    // Check if it is a built-in variable
    auto&& iter = build_in_variables.find(var_name);
    if (iter != build_in_variables.end())
    {
        return false;
    }

    // Find if the variable exists
    auto line_num = editor->find_text_line(var_name);
    if (line_num != std::string::npos)
    {
        // replace it
        editor->replace_line(line_num, var_name + "=" + var_val);
    } else { // Otherwise put it at the end
        if (!editor->insert_line(editor->line_size(), var_name + "=" + var_val))
        {
#ifndef NDEBUG
            std::cerr << "Cannot set variables\n";
#endif
            return false;
        }
    }

    is_modify = true;

    return true;
}

void init_build_in_variables(const std::string& source, const std::string& target)
{
    build_in_variables["__project_name__"] = target;
    build_in_variables["__template_name__"] = source;

    std::stringstream ostr;
    auto now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ostr << std::put_time(std::localtime(&now_time), "%F %T");

    build_in_variables["__time__"] = ostr.str();
}

} // namespace TC