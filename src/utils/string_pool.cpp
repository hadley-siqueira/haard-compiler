#include "utils/string_pool.h"

using namespace hdc;

std::set<std::string> StringPool::pool;

const char* StringPool::add(const char* value) {
    std::string s(value);

    return pool.insert(s).first->c_str();
}

const char* StringPool::add(std::string value) {
    return pool.insert(value).first->c_str();
}
