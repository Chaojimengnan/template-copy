#pragma once
#include <filesystem>
#include <memory>

namespace TC {

enum class cmd_type;
class tem_file_operation;
namespace fs = std::filesystem;

/* All file operations are in this class */
class file_operation
{
public:
    explicit file_operation(char* argv[]);
    ~file_operation() = default;
    bool exec(cmd_type& cmd);

private:
    static bool split_str(const std::string& sc_str, std::string& lsub_str,
        std::string& rsub_str, char split_char);
    char** argv;
    bool copy_directory();
    bool set_variable();
    bool list_directory_to_copy();
    fs::path working_path;
    /* Path of the tc executable */
    fs::path tc_path;
    std::unique_ptr<tem_file_operation> tem_oper;
};

void help_info();

} // namespace TC
