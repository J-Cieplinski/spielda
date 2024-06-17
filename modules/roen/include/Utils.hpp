#ifndef ROEN_UTILS_HPP
#define ROEN_UTILS_HPP

#include <cstdint>
#include <string>

namespace roen
{

constexpr std::int32_t pow(std::int32_t base, std::uint32_t exponent)
{
    if(exponent == 0)
    {
        return 1;
    }
    if(exponent % 2 == 0)
    {
        std::uint32_t curr = pow(base, exponent / 2);
        return curr * curr;
    }
    else
    {
        return base * pow(base, exponent - 1);
    }
}

/*
 * Hashes string used for loaded asset identification
 */
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

class Functor
{
public:
    virtual ~Functor() = default;
    virtual void operator() () = 0;
};

} // roen


#endif //ROEN_UTILS_HPP
