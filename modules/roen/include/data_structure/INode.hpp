#ifndef ROEN_DATA_STRUCTURE_INODE_HPP
#define ROEN_DATA_STRUCTURE_INODE_HPP

#include <cstdint>
#include <utility>

namespace roen::data_structure
{

class INode
{
public:
    virtual bool contains(const std::pair<float, float>& entity) const = 0;
    virtual std::uint32_t cost() const = 0;
};

} // roen::data_structure

#endif //ROEN_DATA_STRUCTURE_INODE_HPP