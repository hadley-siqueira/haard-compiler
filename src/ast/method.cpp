#include "ast/method.h"

using namespace hdc;
using namespace hdc::ast;

Method::Method() {
    set_kind(AST_METHOD);
}

Method::~Method() {

}

void Method::set_class(Class* klass) {
    this->klass = klass;
}

Class* Method::get_class() {
    return klass;
}
