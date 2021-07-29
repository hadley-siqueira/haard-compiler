#include "ast/source_file.h"

using namespace hdc;
using namespace hdc::ast;

SourceFile::SourceFile() {
    set_kind(AST_SOURCEFILE);
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
