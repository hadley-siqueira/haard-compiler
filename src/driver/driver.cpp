#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>

#include "driver/driver.h"
#include "parser/parser.h"

using namespace hdc;
using namespace hdc::ast;

Driver::Driver() {
    path_delimiter = '/';
    output_name = "a.out";
    env_var = "HDC_PATH";
}

Driver::~Driver() {
    std::map<std::string, SourceFile*>::iterator it = source_files.begin();

    while (it != source_files.end()) {
        delete it->second;
        it++;
    }
}

void Driver::run() {
    set_root_path_from_main_file();
    configure_search_path();
    parse_program();
}

void Driver::set_flags(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (strstr(argv[i], ".hd") != nullptr) {
            main_file_path = std::string(argv[i]);
        } else if (strcmp(argv[i], "-o") == 0) {
            ++i;
            output_name = std::string(argv[i]);
        } else if (strcmp(argv[i], "-i") == 0) {
            ++i;
            search_path.push_back(argv[i]);
        } else if (strcmp(argv[i], "-info") == 0) {
            print_information();
        }
    }
}

void Driver::parse_program() {
    parse_imports(parse_file(main_file_path));
}

void Driver::parse_imports(SourceFile* file) {
    if (file == nullptr)
        return;

    int count = file->imports_count();

    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            parse_import(file->get_import(i));
        }
    }
}

void Driver::print_information() {
    std::cout << "Main file: " << main_file_path << std::endl;
    std::cout << "Root path: " << root_path << std::endl;

    std::cout << "Search path:\n";

    for (int i = 0; i < search_path.size(); ++i) {
        std::cout << search_path[i] << std::endl;
    }
}

void Driver::parse_import(Import* import) {
    parse_simple_import(import);
}

void Driver::parse_simple_import(Import* import) {
    SourceFile* file = nullptr;
    std::string path = build_import_path(import);

    if (source_files.count(path) > 0) {
        file = source_files[path];
    }

    if (file != nullptr) {
        import->set_source_file(file);
    } else {
        file = parse_file(path);
        import->set_source_file(file);
        parse_imports(file);
    }
}

SourceFile* Driver::parse_file(std::string path) {
    std::cout << "Parsing: " << path << std::endl;

    if (source_files.count(path) == 0) {
        Parser parser;
        source_files[path] = parser.read(path.c_str());
    }

    return source_files[path];
}

std::string Driver::build_import_path(Import* import) {
    std::string str;

    for (int i = 0; i < import->path_size(); ++i) {
        str += path_delimiter;
        str += import->get_path(i).get_value();
    }

    str += ".hd";

    for (int i = 0; i < search_path.size(); ++i) {
        std::string full_path = search_path[i] + str;

        if (file_exists(full_path)) {
            return full_path;
        }
    }

    return str;
}

bool Driver::file_exists(std::string path) {
    std::ifstream f(path.c_str());
    return f.good();
}

std::string Driver::get_env_path(std::string key) {
    char* val;
    val = std::getenv(key.c_str());
    std::string retval = "";

    if (val != nullptr) {
        retval = val;
    }

    return retval;
}

void Driver::configure_search_path() {
    std::string tmp;

    search_path.push_back(root_path);
    std::string env_path = get_env_path(env_var);

    for (int i = 0; i < env_path.size(); ++i) {
        if (env_path[i] != ':') {
            tmp += env_path[i];
        } else {
            search_path.push_back(tmp);
            tmp = "";
        }
    }

    if (tmp.size() > 0) {
        search_path.push_back(tmp);
    }
}

void Driver::set_root_path_from_main_file() {
    int c;

    for (c = main_file_path.size() - 1; c >= 0; --c) {
        if (main_file_path[c] == path_delimiter) break;
    }

    for (int i = 0; i < c; ++i) {
        root_path += main_file_path[i];
    }
}

std::vector<std::string> Driver::get_files_from_dir(std::string path) {
    std::vector<std::string> files;

    DIR* dirp;
    struct dirent* dp;

    dirp = opendir(path.c_str());

    if (dirp == nullptr) {
        // err = 1;
        return files;
    }

    while ((dp = readdir(dirp)) != nullptr) {
        char* name = dp->d_name;

        if (strlen(name) > 3) {
            while (*name != '\0') {
                ++name;
            }

            name = name - 3;

            if (strcmp(name, ".hd") == 0) {
                files.push_back(std::string(dp->d_name));
            }
        }
    }

    return files;
}
