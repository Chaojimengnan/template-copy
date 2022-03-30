#include <filesystem>
#ifndef NDEBUG
#    include <iostream>
#endif
#include <sstream>

#include "tem_file_operation.h"
#include "text_editor.h"
#include "variable_operation.h"

namespace TC {

namespace fs = std::filesystem;

tem_file_operation::tem_file_operation(const std::string& base_path)
    : editor(std::make_unique<text_editor>()), var_oper(std::make_unique<variable_operation>(base_path))
{
    if (fs::exists(base_path))
        if (!var_oper->open(true))
            throw std::runtime_error("Cannot open variable.txt!");
}

tem_file_operation::~tem_file_operation() { }

bool tem_file_operation::set_variable(const std::string& var_name, const std::string& var_val)
{
    return var_oper->set_variable(var_name, var_val);
}

bool tem_file_operation::tem_translate(const std::string& from, const std::string& to)
{
    // Load the text from file into memory
    editor->set_path(from);
    if (!editor->load_text(true))
    {
#ifndef NDEBUG
        std::cerr << "Cannot open file " << from << " !\n";
#endif
        return false;
    }

    for (auto&& i : *editor)
        find_variable_to_replace(i);

    editor->set_path(to);
    if (!editor->save_text(false))
    {
#ifndef NDEBUG
        std::cerr << "Cannot save file " << to << " !\n";
#endif
        return false;
    }

    return true;
}

void tem_file_operation::find_variable_to_replace(std::string& src_str)
{
    std::ostringstream os;
    std::string var_name, var_val;
    size_t cur_pos = 0, bef_pos = -1;
    size_t end_pos = 0;

    //         (bef_pos) (cur_pos) (end_pos)
    // abcd${var_name1}efgh${var_name2}

    auto input_remain = [&](size_t cut_pos) {
        os << src_str.substr(bef_pos + 1, cut_pos - (bef_pos + 1));
        bef_pos = end_pos;
    };

    auto count_backslash = [&]() -> size_t {
        size_t counts = 0;
        auto iter = src_str.begin() + cur_pos;
        for (; iter != src_str.begin(); --iter)
        {
            if (*(iter - 1) != '\\')
                break;
            ++counts;
        }
        return counts;
    };

    while (true)
    {
        cur_pos = src_str.find("${", bef_pos + 1);
        end_pos = src_str.find("}", cur_pos + 2);
        // There are no variables left, so just break
        if (cur_pos == std::string::npos || end_pos == std::string::npos)
        {
            input_remain(src_str.size());
            break;
        }

        size_t count_of_backslash = count_backslash();

        // Check escape backslash
        if (count_of_backslash % 2)
        {
            // The variable is escaped, printing the original text and backslash
            size_t backslash_num = (count_of_backslash - 1) / 2;
            input_remain(cur_pos - count_of_backslash);
            if (backslash_num)
                os << std::string(backslash_num, '\\');
            bef_pos = cur_pos - 1;
            input_remain(end_pos + 1);
            continue;
        } else {
            // Get variable name
            var_name = src_str.substr(cur_pos + 2, end_pos - (cur_pos + 2));
            // If no variable is found, print the original text
            if (!var_oper->get_variable(var_name, var_val))
            {
                input_remain(end_pos + 1);
                continue;
            }
            input_remain(cur_pos - count_of_backslash);
            // Print the backslash
            os << std::string(count_of_backslash / 2, '\\');
            os << var_val;
        }
    }

    src_str = os.str();
}

} // namespace TC