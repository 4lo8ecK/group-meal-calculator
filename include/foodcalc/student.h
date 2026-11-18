#pragma once

#include <foodcalc/fccore.h>

namespace fc
{
	class Prices
	{
	private:
		int32_t m_money[DaysInYear]{0};
	
	public:
		explicit Prices() = default;
		Prices(const int32_t* arr);
	};

	class Student
	{
	private:
		bool 	m_eaten[DaysInYear]{false};
		int32_t	m_money[DaysInYear]{0};
		char	m_name[NameMaxLen]{0};
		
	public:
		explicit Student(const char* name, int32_t initial_balance = 0);
		
		constexpr const char* get_name() const { return m_name; }	// имя ученика
		constexpr const int32_t* get_money() const { return m_money; } // массив внесенных денег
		constexpr const bool* get_eaten() const { return m_eaten; }	// массив статусов 'ел/не ел'
				
		constexpr int32_t get_money(const Date& date) const { return m_money[date.to_index()]; }	// возвращает внесённую в указанный день сумму
		constexpr bool get_eaten(const Date& date) const { return m_eaten[date.to_index()]; };	// возвращает статус 'ел/не ел' на указанный день
		
		constexpr bool set_eaten(const Date& date, bool state = false);	// устанавливает статус 'ел/не ел' на определённый день. 
		constexpr bool set_money(const Date& date, int32_t money);	// устанавливает пополнение баланса

		constexpr int32_t get_balance() const;	// возвращает вообще все деньги
		constexpr int32_t get_balance(const Date& date) const;	// возвращает все деньги на определённый момент
		constexpr int32_t get_remainder(const Date& date, int32_t* prices) const;	// возвращает остаток за указанный день
		
		const int32_t eaten_count() const;	// возвращает всего дней, когда ученик ел
		const int32_t eaten_count(const Date& date) const;	// возвращает количество дней когда ученик ел до указанной даты
	};
}