#include <foodcalc/student.h>

#include <stdexcept>

#include <cstring>
#include <cstdlib>

#define ARR_SIZE(arr) sizeof(arr) / sizeof(*arr)

using namespace fc;

Prices::Prices(const int32_t* arr)
{
	if (arr == nullptr) return;
	memmove(m_money, arr, ARR_SIZE(m_money));
}

Student::Student(const char* name, int32_t initial_balance)
{
	if (name == nullptr) strncpy(m_name, UnnamedStudent, NameMaxLen);
	strncpy(m_name, name, NameMaxLen);
	m_money[0] = initial_balance;
}

bool Student::operator==(const Student& s) const
{
	if (strcmp(m_name, s.m_name) != 0) return false;
	if (memcmp(m_eaten, s.m_eaten, sizeof(m_eaten)) != 0) return false;
	if (memcmp(m_money, s.m_money, sizeof(m_money)) != 0) return false;
	return true;
}

constexpr int32_t Student::get_balance() const
{
	int32_t res = 0;
	for (int i = 0; i < ARR_SIZE(m_money); ++i)
	{
		res += m_money[i];
	}
	return res;
}

constexpr int32_t Student::get_balance(const Date& date) const
{
	if (!date.is_valid()) throw DateError("Неверное значение даты");
	int32_t res = 0;
	for (int i = 0; i < date.to_index(); ++i)
	{
		res += m_money[i];
	}
	return res;
}

constexpr int32_t Student::get_remainder(const Date& date, int32_t* prices) const
{
	if (!date.is_valid()) throw DateError("Неверное значение даты");
	if (prices == nullptr) throw std::invalid_argument("Ошибка получения массива цен");

	int32_t balance = 0;
	int32_t spent = 0;

	for (int i = 0; i < date.to_index(); ++i)
	{
		if (m_eaten[i])
		{
			spent += prices[i];
		}
		balance += m_money[i];		
	}

	return balance - spent;
}

const int32_t Student::eaten_count() const
{
	int32_t res = 0;
	for (int i = 0; i < DaysInYear; ++i)
	{
		res += md::cast<int32_t>(m_eaten[i]);
	}
	return res;
}
const int32_t Student::eaten_count(const Date& date) const
{
	int32_t date_index = 0;
	if (!date.is_valid()) { date_index = DaysInYear; }
	int32_t res = 0;
	for (int i = 0; i < date_index; ++i)
	{
		res += md::cast<int32_t>(m_eaten[i]);
	}
	return res;
}

constexpr bool Student::set_eaten(const Date& date, bool state)
{
	if (!date.is_valid()) return false;
	m_eaten[date.to_index()] = state;
	return true;
}

constexpr bool Student::set_money(const Date& date, int32_t money)
{
	if (!date.is_valid()) return false;
	m_money[date.to_index()] = money;
	return true;
}

