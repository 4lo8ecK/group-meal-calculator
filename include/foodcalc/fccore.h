#pragma once

#ifndef FC_CORE_H
#define FC_CORE_H

#include <cstdint>
#include <mdutils.h>

namespace fc
{
	constexpr static int32_t MonthsCount = 9;
	constexpr static int32_t DaysInMonth = 31;
	constexpr static int32_t DaysInYear = MonthsCount * DaysInMonth;
	constexpr static int32_t NameMaxLen = 64;

	constexpr const char* UnnamedStudent = "БЕЗЫМЯННЫЙ КТО-ТО";

	enum class EMonth
	{
		Sep = 0, Oct = 1, Nov = 2, Dec = 3, Jan = 4, Feb = 5, Mar = 6, Apr = 7, May = 8
	};
	
	enum class ErrCodes : int32_t
	{
		Success = 0, Error = 1, Date = -1, Ptr = -2
	};

	struct Date
	{
		EMonth month{EMonth::Sep};
		uint32_t day{0};
		
		explicit Date(EMonth _Month, uint32_t _Day) : month(_Month), day(_Day) {}
		
		constexpr inline const bool is_valid() const
		{
			return (day <= 31) && (md::cast<int32_t>(month) >= 0 && md::cast<int32_t>(month) < MonthsCount);
		}
		constexpr inline const int32_t to_index() const
		{
			if (this->is_valid())
			{
				return md::cast<int32_t>(month) * DaysInMonth + day;
			}
		}
	};
}

#endif