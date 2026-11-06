#ifndef TEST_SUPPORT_HPP
#define TEST_SUPPORT_HPP

#include <stdexcept>
#include <string>

inline void require(bool condition, const std::string &message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

template <typename Exception, typename Function> void requireThrows(Function function, const std::string &message) {
    try {
        function();
    } catch (const Exception &) {
        return;
    }
    throw std::runtime_error(message);
}

#endif
