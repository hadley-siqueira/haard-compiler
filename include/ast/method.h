#ifndef HDC_AST_METHOD_H
#define HDC_AST_METHOD_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "variable.h"
#include "type.h"
#include "function.h"

namespace hdc {
    namespace ast {
        class Class;

        class Method : public Function {
            public:
                Method();
                ~Method();

            public:
                void set_class(Class* klass);

                Class* get_class();

            private:
                Class* klass;
        };
    }
}

#endif
