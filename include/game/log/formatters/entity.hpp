#include <fmt/core.h>
#include <fmt/format.h>

#include <entt/fwd.hpp>

namespace fmt
{

template <>
struct formatter<entt::entity> : formatter<string_view>
{
public:
    auto format(entt::entity entt, format_context& ctx) const;
};

auto formatter<entt::entity>::format(entt::entity entity, format_context& ctx) const
{
    string_view enttStr {std::to_string(static_cast<std::uint32_t>(entity))};

    return formatter<string_view>::format(enttStr, ctx);
}

} // namespace fmt
