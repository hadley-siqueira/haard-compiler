#ifndef HDC_DRIVER_H
#define HDC_DRIVER_H

#include <map>
#include "ast/source_file.h"
#include "ast/program.h"

namespace hdc {
    class Driver {
        public:
            Driver();
            ~Driver();

        public:
            void run();
            void set_flags(int argc, char* argv[]);

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
            void build_scopes();
            void build_ir();
            void build_cpp();

            bool file_exists(std::string path);

            void print_information();
            void run_flags();

        private:
            char path_delimiter;
            std::string main_file_path;
            std::string root_path;
            std::string output_name;
            std::string env_var;
            std::vector<std::string> search_path;
            ast::Program* program;

            // flags
            bool print_information_flag;
            bool cpp_flag;
    };
}

#endif
