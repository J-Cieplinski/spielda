#ifndef ROEN_UTILS_HPP
#define ROEN_UTILS_HPP

#include <cstdint>
#include <string>

namespace roen
{

constexpr std::uint32_t hashString(const std::string& str)
{
    return str.size();
}

} // roen


#endif //ROEN_UTILS_HPP
