#ifndef ROEN_UTILS_HPP
#define ROEN_UTILS_HPP

#include <cstdint>
#include <string>

namespace roen
{

constexpr std::uint32_t pow(std::int32_t base, std::uint32_t power)
{
    if(power == 0)
    {
        return 1;
    }
    if(power % 2 == 0)
    {
        std::uint32_t curr = pow(base, power / 2);
        return curr * curr;
    }
    else
    {
        return base * pow(base, power - 1);
    }
}

constexpr std::uint64_t hashString(const std::string& str)
{
    constexpr std::uint32_t PRIME_CONST {31};
    std::uint64_t hashCode {0};
    for(std::uint32_t i = 0; const auto& ch : str)
    {
        hashCode += ch * pow(PRIME_CONST, i);
    }

    return hashCode;
}

} // roen


#endif //ROEN_UTILS_HPP
