#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace TC{

    /* Classes that control text reading and writing */
    class text_editor
    {
    public:
        text_editor();
        explicit text_editor(std::string path);
        ~text_editor();
        /* The first parameter means Whether to clear the current container text */
        bool load_text(bool is_clear);
        bool save_text(bool is_override);
        bool get_line(size_t line_num, std::string& str);
        bool replace_line(size_t line_num, const std::string& str);
        /* Insert str before line_num */
        bool insert_line(size_t line_num, const std::string& str);
        /* Return the line number if found (first), otherwise return std::npos  */
        size_t find_text_line(const std::string& str);
        void set_path(const std::string& path) noexcept { this->path = path;}
        size_t line_size() { return text_vec.size();}
    public:
        auto begin() { return text_vec.begin(); }
        auto end() { return text_vec.end(); }
        auto cbegin() { return text_vec.cbegin();}
        auto cend() { return text_vec.cend(); }

    private:
        bool check_line(size_t line_num) { if (text_vec.size() <= line_num) return false; return true;}
        std::vector<std::string> text_vec;
        std::string path;
        std::fstream f;
    public:
        text_editor(const text_editor&) = delete;
        text_editor(text_editor&&) = delete;
        text_editor& operator=(const text_editor&) = delete;
        text_editor& operator=(text_editor&&) = delete;
    };
    
    
}//TC