#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace TC {
class text_editor;

class variable_operation
{
public:
    variable_operation();
    explicit variable_operation(const std::string& variable_path);
    ~variable_operation();
    bool open(bool is_clear);
    bool save();
    void set_path(const std::string& variable_path);
    bool get_variable(const std::string& var_name, std::string& var_val);
    bool set_variable(const std::string& var_name, const std::string& var_val);

private:
    std::unique_ptr<text_editor> editor;
    std::string variable_path;
    bool is_modify;
};

extern std::unordered_map<std::string, std::string> build_in_variables;

void init_build_in_variables(const std::string& source, const std::string& target);

} // namespace TC