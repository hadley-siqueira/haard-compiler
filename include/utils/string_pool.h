#ifndef HDC_UTILS_STRING_POOL_H
#define HDC_UTILS_STRING_POOL_H

#include <set>
#include <string>

namespace hdc {
    class StringPool {
        public:
            static const char* add(const char* value);
            static const char* add(std::string value);

        public:
            static std::set<std::string> pool;
    };
}

#endif

