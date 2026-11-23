#pragma once

namespace md
{

template <typename target_t, typename source_t>
inline constexpr target_t cast(source_t&& val) 
{
    return static_cast<target_t>(val);
}

template <typename target_t, typename source_t>
inline constexpr target_t rcast(source_t&& val)
{
	return reinterpret_cast<target_t>(val);
}

template <typename target_t, typename source_t>
inline constexpr target_t ccast(source_t&& val)
{
	return const_cast<target_t>(val);
}

void LOG(const char* format, ...);

}