#pragma once

#ifndef FC_CORE_H
#define FC_CORE_H

#include <cstdint>
#include <stdexcept>
#include <memory>

#include <mdutils.h>

namespace fc
{
#ifdef _WIN32
	typedef wchar_t tchar;
#else
	typedef uint16_t tchar;
#endif

	template<typename T>
	using uptr = std::unique_ptr<T>;

	constexpr static int32_t MonthsCount = 9;
	constexpr static int32_t DaysInMonth = 31;
	constexpr static int32_t DaysInYear = MonthsCount * DaysInMonth;
	constexpr static int32_t NameMaxLen = 64;

	constexpr const char* UnnamedStudent = "БЕЗЫМЯННЫЙ КТО-ТО";

	enum class EMonth
	{
		Sep = 0, Oct = 1, Nov = 2, Dec = 3, Jan = 4, Feb = 5, Mar = 6, Apr = 7, May = 8
	};
	
	class DateError : public std::runtime_error
	{
	public:
		explicit DateError(const std::string& message) : runtime_error(message) {}
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