#pragma once

#ifndef FC_STUDENT_H
#define FC_STUDENT_H

#include "fccore.h"
#include <vector>

namespace fc
{
	class prices_t
	{
	private:
		bool	m_used[days_in_year]{0};
		int16_t m_prices[days_in_year]{0};
	
	public:
		explicit prices_t() = default;
		prices_t(const int16_t* prices);

		constexpr inline int16_t& operator[](size_t index) { return m_prices[index]; }
		constexpr inline const int16_t& operator[](size_t index) const { return m_prices[index]; }

		constexpr bool set_used(const date_t& date, bool used = true);
		constexpr bool set_price(const date_t& date, int16_t price = 0); 
	};

	class student_t
	{
	private:
		char 	m_name[name_max_len]{0};
		bool 	m_eaten[days_in_year]{false};
		int16_t	m_money[days_in_year]{0};

	public:
		explicit student_t() = default;
		student_t(const char* name, int16_t initial_balance = 0);

		constexpr inline const char* name() const { return m_name; }				// имя ученика
		constexpr inline const bool* eaten() const { return m_eaten; }				// массив статусов 'ел/не ел'
		constexpr inline const int16_t* money() const { return m_money; }			// массив внесенных денег

		constexpr int32_t get_balance() const;										// возвращает вообще все деньги
		constexpr int32_t get_balance(const date_t& date) const;					// возвращает все деньги на определённый момент
		constexpr int32_t get_remainder(int32_t* prices) const;						// возвращает остаток за всё время
		constexpr int32_t get_remainder(const date_t& date, int32_t* prices) const;	// возвращает остаток за указанный день

		constexpr bool set_eaten(const date_t& date, bool state = false);			// устанавливает статус 'ел/не ел' на определённый день. 
		constexpr bool set_money(const date_t& date, int32_t money = 0);			// устанавливает пополнение баланса

		constexpr const int32_t eaten_count() const;								// возвращает всего дней, когда ученик ел
		constexpr const int32_t eaten_count(const date_t& date) const;				// возвращает количество дней когда ученик ел до указанной даты
	};

	class group_t
	{
	private:
		char					m_name[name_max_len]{0};
		std::vector<student_t*>	m_students;

	public:
		explicit group_t() = default;
		group_t(const char* name);
		~group_t();

		constexpr inline student_t& operator[](size_t index) { return *m_students[index]; }
		constexpr inline const student_t& operator[](size_t index) const { return *m_students[index]; }

		constexpr int32_t find_index(const char* name) const;
		constexpr int32_t find_index(student_t* s) const;
		constexpr bool contains(const char* name) const;
		constexpr bool contains(student_t* s) const;

		constexpr bool add_new(const char* name, int16_t initial_balance = 0);
		constexpr bool delete_one(const char* name);
		constexpr bool delete_one(student_t* s);

		constexpr student_t* get_student(const char* name) const;
		constexpr inline std::vector<student_t*> students() const { return m_students; }

		bool save();
		bool load();

	};
}

#endif