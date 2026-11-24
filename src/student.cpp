#include <student.h>

#include <cstdlib>
#include <cstring>
#include <stdexcept>

using namespace fc;

#pragma region PRICES_T

prices_t::prices_t(const int16_t* prices)
{
	memcpy(m_prices, prices, days_in_year);
}

constexpr bool prices_t::set_used(const date_t& date, bool used)
{
	if (!date.is_valid()) return false;
	m_used[date.to_index()] = used;
	return true;
}
constexpr bool prices_t::set_price(const date_t& date, int16_t price)
{
	if (!date.is_valid()) return false;
	m_prices[date.to_index()] = price;
	return true;
}

#pragma endregion

#pragma region STUDENT_T

student_t::student_t(const char* name, int16_t initial_balance = 0)
{
	if (name != nullptr && *name != 0)
	{
		strcpy(m_name, name);
	}
	else
	{
		strcpy(m_name, unnamed_student);
	}
	*m_money = initial_balance;
}

constexpr int32_t student_t::get_balance() const
{
	int32_t res = 0;
	for (int32_t i : m_money)
	{
		res += i;
	}
	return res;
}

constexpr int32_t student_t::get_balance(const date_t& date) const
{
	int32_t res = 0;
	for (int32_t i = 0; i < date.to_index(); ++i)
	{
		res += m_money[i];
	}
	return res;
}

constexpr int32_t student_t::get_remainder(int32_t* prices) const
{
	if (prices == nullptr) throw std::runtime_error("Получен пустой массив цен");

	int32_t balance = 0;
	int32_t spent = 0;

	for (int i = 0; i < days_in_year; ++i)
	{
		if (m_eaten[i])
		{
			spent += prices[i];
		}
		balance += m_money[i];
	}
	
	return balance - spent;
}
constexpr int32_t student_t::get_remainder(const date_t& date, int32_t* prices) const
{
	if (prices == nullptr) throw std::runtime_error("Получен пустой массив цен");

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

constexpr bool student_t::set_eaten(const date_t& date, bool state = false)
{
	if (!date.is_valid()) return false;
	m_eaten[date.to_index()] = state;
	return true;
}
constexpr bool student_t::set_money(const date_t& date, int32_t money = 0)
{
	if (!date.is_valid()) return false;
	m_money[date.to_index()] = money;
	return true;
}

constexpr const int32_t student_t::eaten_count() const
{
	int32_t res = 0;
	for (bool i : m_eaten)
	{
		if (i) ++res;
	}
	return res;
}
constexpr const int32_t student_t::eaten_count(const date_t& date) const
{
	int32_t res = 0;
	for (int i = 0; i < date.to_index(); ++i)
	{
		if (m_eaten[i]) ++res;
	}
	return res;
}

#pragma endregion

#pragma region GROUP_T

group_t::group_t(const char* name)
{
	if (name != nullptr && *name != 0)
	{
		strcpy(m_name, name);
	}
	else
	{
		strcpy(m_name, unnamed_group);
	}
}
group_t::~group_t()
{
	for (student_t* s : m_students)
	{
		if (s != nullptr)
		{
			delete s;
			s = nullptr;
		}
	}
}

constexpr int32_t group_t::find_index(const char* name) const
{
	for (int i = 0; i < m_students.size(); ++i)
	{
		if (strcmp(m_students[i]->name(), name) == 0) return i;
	}
	return -1;
}

constexpr int32_t group_t::find_index(student_t* s) const
{
	for (int i = 0; i < m_students.size(); ++i)
	{
		if (strcmp(m_students[i]->name(), s->name()) == 0) return i;
	}
	return -1;
}

constexpr bool group_t::contains(const char* name) const
{
	for (student_t* s : m_students)
	{
		if (strcmp(s->name(), name) == 0) return true;
	}
	return false;
}

constexpr bool group_t::contains(student_t* s) const
{
	for (student_t* s : m_students)
	{
		if (strcmp(s->name(), s->name()) == 0) return true;
	}
	return false;
}

constexpr bool group_t::add_new(const char* name, int16_t initial_balance)
{
	if (this->contains(name)) return false;

	student_t* s = new student_t(name, initial_balance);
	m_students.push_back(s);
	
	return true;
}

constexpr bool group_t::delete_one(const char* name)
{
	int32_t index = find_index(name);
	if (index == -1) return false;

	m_students.erase(m_students.begin() + index);
	
	return true;	
}

constexpr bool group_t::delete_one(student_t* s)
{
	int32_t index = find_index(s);
	if (index == -1) return false;

	m_students.erase(m_students.begin() + index);

	return true;
}

constexpr student_t* group_t::get_student(const char* name) const
{
	int32_t index = find_index(name);
	if (index == -1) return nullptr;

	return m_students[index];
}

bool group_t::save()
{

}
bool group_t::load()
{

}



#pragma endregion