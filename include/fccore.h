#pragma once

#ifndef FC_CORE_H
#define FC_CORE_H

#include <cstdint>

namespace fc
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

	constexpr static const int32_t months_count = 9;
	constexpr static const int32_t days_in_month = 31;
	constexpr static const int32_t days_in_year = months_count * days_in_month;
	constexpr static const int32_t name_max_len = 64;

	constexpr const char* unnamed_student = "БЕЗЫМЯННЫЙ КТО-ТО";
	constexpr const char* unnamed_group = "БЕЗЫМЯННАЯ ГРУППА";

	enum class emonth_t
	{
		Sep = 0, Oct = 1, Nov = 2, Dec = 3, Jan = 4, Feb = 5, Mar = 6, Apr = 7, May = 8
	};

	struct date_t
	{
		emonth_t month{emonth_t::Sep};
		uint32_t day{0};
		
		explicit date_t(emonth_t _Month, uint32_t _Day) : month(_Month), day(_Day) {}
		
		constexpr inline const bool is_valid() const
		{
			return (day <= 31) && (cast<int32_t>(month) >= 0 && cast<int32_t>(month) < months_count);
		}
		constexpr inline const int32_t to_index() const
		{
			if (this->is_valid())
			{
				return cast<int32_t>(month) * days_in_month + day;
			}
			return -1;
		}
	};

}

#endif