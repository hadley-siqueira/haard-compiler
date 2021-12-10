#ifndef HDC_IR_BUILDER_H
#define HDC_IR_BUILDER_H

#include <vector>

#include "defs.h"
#include "ir.h"


#include "ast/expression.h"
#include "ast/program.h"
#include "ast/source_file.h"
#include "ast/function.h"
#include "ast/binary_expression.h"
#include "ast/unary_expression.h"
#include "ast/literal_expression.h"

namespace hdc {
    class IRBuilder {
        public:
            IRBuilder();
            ~IRBuilder();

        public:
            void generate_program(ast::Program* program);
            void debug();

        private:
            void generate_source_file(ast::SourceFile* source_file);
            void generate_function(ast::Function* function);

            void generate_statement(ast::Statement* stmt);
            void generate_statements(ast::CompoundStatement* stmts);

            IR* generate_expression(ast::Expression* expr);

            IR* generate_assignment(ast::BinaryExpression* expr);
            IR* generate_binop(IRKind kind, ast::BinaryExpression* expr);
            IR* get_value(ast::Expression* expr);

        private:
            int new_temporary();
            void add_instruction(IR* ir);

        private:
            std::vector<IR*> instructions;
            int temp_counter;
    };
}

#endif
