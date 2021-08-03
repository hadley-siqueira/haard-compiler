#include "ast/source_file.h"

using namespace hdc;
using namespace hdc::ast;

SourceFile::SourceFile() {
    set_kind(AST_SOURCEFILE);
}

SourceFile::~SourceFile() {
    for (int i = 0; i < imports.size(); ++i) {
        delete imports[i];
    }

    for (int i = 0; i < functions.size(); ++i) {
        delete functions[i];
    }
}

void SourceFile::set_path(std::string path) {
    this->path = path;
}

std::string SourceFile::get_path() {
    return path;
}

void SourceFile::add_import(Import* import) {
    imports.push_back(import);
}

void SourceFile::add_function(Function* function) {
    functions.push_back(function);
    function->set_source_file(this);
}
