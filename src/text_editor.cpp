#include "text_editor.h"
#ifndef NDEBUG
#    include <iostream>
#endif
#include <filesystem>

namespace TC {

namespace fs = std::filesystem;

text_editor::text_editor() : text_editor("") { }

text_editor::text_editor(std::string path)
    : path(std::move(path)), text_vec(), f() { }

text_editor::~text_editor() { }

bool text_editor::load_text(bool is_clear)
{
    if (is_clear)
        text_vec.clear();

    f.open(path, std::fstream::in);
    if (!f)
    {
#ifndef NDEBUG
        std::cerr << "Unable to open file\n";
#endif
        return false;
    }

    std::string temp;
    while (std::getline(f, temp))
        text_vec.push_back(temp);

    f.close();

    return true;
}

bool text_editor::save_text(bool is_override)
{
    if (!is_override)
        if (fs::exists(path))
        {
#ifndef NDEBUG
            std::cerr << "It already has a file here\n";
#endif
            return false;
        }

    f.open(path, std::fstream::out | std::fstream::trunc);
    if (!f)
    {
#ifndef NDEBUG
        std::cerr << "Cannot open the file\n";
#endif
        return false;
    }

    for (auto&& i : text_vec)
        f << i << "\n";

    f.close();
    return true;
}

bool text_editor::get_line(size_t line_num, std::string& str)
{
    if (!check_line(line_num))
        return false;
    str = text_vec[line_num];
    return true;
}

bool text_editor::replace_line(size_t line_num, const std::string& str)
{
    if (!check_line(line_num))
        return false;
    text_vec[line_num] = str;
    return true;
}

bool text_editor::insert_line(size_t line_num, const std::string& str)
{
    if (line_num > text_vec.size())
        return false;
    text_vec.insert(text_vec.cbegin() + line_num, str);
    return true;
}

size_t text_editor::find_text_line(const std::string& str)
{
    for (auto iter = text_vec.begin(); iter != text_vec.end(); ++iter)
        if (iter->find(str) != std::string::npos)
            return iter - text_vec.begin();

    return std::string::npos;
}

} // namespace TC