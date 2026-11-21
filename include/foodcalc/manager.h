#pragma once

#ifndef FC_MANAGER_H
#define FC_MANAGER_H

#include <vector>
#include <algorithm>
#include <cstdlib>

#include <foodcalc/student.h>

namespace fc
{
	// Группа управляет классом
	// Он хранит данные в директории класса 
	// назвние хранит сам класс и годы учебного года
	// например '7А_2026_2027' или '5_2027_2028'
	class StudentsGroup
	{
	private:
		char group_name[16];
		std::vector<Student*> students;

		
	public:
		StudentsGroup(uint8_t _Grade, uint8_t _Year, tchar _Literal = 0)
		{
			if (_Literal != 0) { sprintf(group_name, "%d%s-%d", _Grade, _Year, _Literal); }
			else { sprintf(group_name, "%d-%d", _Grade, _Year); }
		}
		StudentsGroup(const char* path_to_dir);
		
		int32_t find_index(const char* name) const;
		bool contains(const char* name) const;

		bool add_new(const char* name, int32_t initial_balance = 0);
		bool delete_one(const char* name);

		Student* get_student(const char* name) const;

		void save_data() const;
		bool load_data();
	};
}
	
#endif