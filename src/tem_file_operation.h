#pragma once
#include <memory>
#include <string>

namespace TC {

class text_editor;
class variable_operation;

class tem_file_operation
{
public:
    tem_file_operation(const std::string& base_path);
    ~tem_file_operation();
    /* Convert the TEM file to the normal file in destination location */
    bool tem_translate(const std::string& from, const std::string& to);
    /* Forward to var_oper */
    bool set_variable(const std::string& var_name, const std::string& var_val);

private:
    /* Look for a variable name from src_str and replace it */
    void find_variable_to_replace(std::string& src_str);
    std::unique_ptr<text_editor> editor;
    std::unique_ptr<variable_operation> var_oper;
};

} // namespace TC
