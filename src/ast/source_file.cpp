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

    for (int i = 0; i < classes.size(); ++i) {
        delete classes[i];
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
    import->set_parent_node(this);
}

void SourceFile::add_function(Function* function) {
    functions.push_back(function);
    function->set_source_file(this);
    function->set_parent_node(this);
}

void SourceFile::add_class(Class* klass) {
    classes.push_back(klass);
    klass->set_source_file(this);
    klass->set_parent_node(this);
}
