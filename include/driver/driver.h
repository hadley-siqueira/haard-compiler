#ifndef HDC_DRIVER_H
#define HDC_DRIVER_H

#include <map>
#include "ast/source_file.h"

namespace hdc {
    class Driver {
        public:
            Driver();

        private:
            std::string get_env_path(std::string key);
            void configure_search_path();
            void set_root_path_from_main_file();
            std::vector<std::string> get_files_from_dir(std::string path);
            void parse_program();
            void parse_imports(ast::SourceFile* file);
            void parse_import(ast::Import* import);
            void parse_simple_import(ast::Import* import);
            ast::SourceFile* parse_file(std::string path);

            std::string build_import_path(ast::Import* import);

            bool file_exists(std::string path);

        private:
            char path_delimiter;
            std::string main_file_path;
            std::string root_path;
            std::string output_name;
            std::string env_var;
            std::vector<std::string> search_path;
            std::map<std::string, ast::SourceFile*> source_files;
    };
}

#endif
