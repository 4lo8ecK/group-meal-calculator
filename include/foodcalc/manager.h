#pragma once

#ifndef FC_MANAGER_H
#define FC_MANAGER_H

#include <vector>
#include <algorithm>

#include <foodcalc/student.h>
namespace fc
{
	// Группа управляет классом
	// Он хранит данные в директории класса 
	// назвние хранит сам класс и годы учебного года
	// например '7А_2026_2027' или '5_2027_2028'
	// 
	class StudentsGroup
	{
	private:
		uint8_t grade;
		uint8_t year;
		tchar literal;
		std::vector<fc::uptr<Student>> students;

		
	public:
		StudentsGroup(uint8_t _Grade, uint8_t _Year, tchar _Literal) : grade(_Grade), year(_Year), literal(_Literal) {};
		StudentsGroup(const char* path_to_dir);
		
		int32_t find_index(const char* name) const;
		bool contains(const char* name) const;

		bool add_new(const char* name, int32_t initial_balance = 0);

	};

}
	
#endif