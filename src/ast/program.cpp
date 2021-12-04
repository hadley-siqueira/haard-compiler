#include "ast/program.h"

using namespace hdc;
using namespace hdc::ast;

Program::Program() {
    set_kind(AST_PROGRAM);
}

Program::~Program() {
    std::map<std::string, SourceFile*>::iterator it = source_files.begin();

    while (it != source_files.end()) {
        delete it->second;
        it++;
    }
}

void Program::add_source_file(std::string path, SourceFile* source_file) {
    source_files[path] = source_file;
}

SourceFile* Program::get_source_file(std::string path) {
    if (has_source_file(path)) {
        return source_files[path];
    }

    return nullptr;
}

bool Program::has_source_file(std::string path) {
    return source_files.count(path) > 0;
}

