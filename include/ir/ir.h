#ifndef HDC_IR_H
#define HDC_IR_H

#include "defs.h"

namespace hdc {
    class IR {
        public:
            IR(IRKind kind, int dst, int src1, int src2);
            IR(IRKind kind, const char* label);
            IR(IRKind kind, int dst, const char* literal);

        public:
            void set_kind(IRKind kind);
            IRKind get_kind();

            int get_dst();
            int get_src1();

            std::string to_str();

        private:
            std::string to_bin_str(const char* op);

        private:
            IRKind kind;

            union {
                struct {
                    int dst;
                    int src1;
                    int src2;
                } t1;

                const char* label;

                struct {
                    int src1;
                    int src2;
                    char* label;
                } t2;

                struct {
                    int dst;
                    const char* literal;
                } t3;
            } ops;
    };
}

#endif
