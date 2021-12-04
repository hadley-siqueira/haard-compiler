#include "ast/program.h"

using namespace hdc;
using namespace hdc::ast;

Program::Program() {
    set_kind(AST_PROGRAM);
}

Program::~Program() {
    for (int i = 0; i < source_files.size(); ++i) {
        delete source_files[i];
    }
}

void Program::add_source_file(std::string path, SourceFile* source_file) {
    source_files_map[path] = source_file;
    source_files.push_back(source_file);
    source_file->set_parent_node(this);
}

SourceFile* Program::get_source_file(std::string path) {
    if (has_source_file(path)) {
        return source_files_map[path];
    }

    return nullptr;
}

SourceFile* Program::get_source_file(int i) {
    if (i < source_files.size()) {
        return source_files[i];
    }

    return nullptr;
}

bool Program::has_source_file(std::string path) {
    return source_files_map.count(path) > 0;
}

int Program::source_files_count() {
    return source_files.size();
}
