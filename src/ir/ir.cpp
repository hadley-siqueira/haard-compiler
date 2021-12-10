#include <sstream>

#include "ir/ir.h"
#include "utils/string_pool.h"

using namespace hdc;

IR::IR(IRKind kind, int dst, int src1, int src2) {
    this->kind = kind;
    ops.t1.dst = dst;
    ops.t1.src1 = src1;
    ops.t1.src2 = src2;
}

IR::IR(IRKind kind, int src1, int src2) {
    this->kind = kind;
    ops.t4.src1 = src1;
    ops.t4.src2 = src2;
}

IR::IR(IRKind kind, const char* label) {
    this->kind = kind;
    ops.label = StringPool::add(label);
}

IR::IR(IRKind kind, int dst, const char* literal) {
    this->kind = kind;
    ops.t3.dst = dst;
    ops.t3.literal = StringPool::add(literal);
}

void IR::set_kind(IRKind kind) {
    this->kind = kind;
}

IRKind IR::get_kind() {
    return kind;
}

int IR::get_dst() {
    switch (kind) {
    case IR_INTEGER:
        return ops.t3.dst;

    default:
        return ops.t1.dst;
    }
}

int IR::get_src1() {
    switch (kind) {
    default:
        return ops.t1.src1;
    }
}

std::string IR::to_str() {
    std::stringstream s;

    switch (kind) {
    case IR_LABEL:
        s << ops.label << ":";
        break;

    case IR_SW_FP:
        s << "sw %" << ops.t4.src2 << ", fp(" << ops.t4.src1 << ")";
        break;

    case IR_PLUS:
        return to_bin_str("add");

    case IR_MINUS:
        return to_bin_str("sub");

    case IR_INTEGER:
        s << "li %" << ops.t3.dst << ", " << ops.t3.literal;
        break;
    }

    return s.str();
}


std::string IR::to_bin_str(const char* op) {
    std::stringstream s;

    s << op << " %" << ops.t1.dst
      << ", %" << ops.t1.src1
      << ", %" << ops.t1.src2;

    return s.str();
}
