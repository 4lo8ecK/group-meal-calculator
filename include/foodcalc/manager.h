#pragma once

#ifndef FC_MANAGER_H
#define FC_MANAGER_H

#include <vector>
#include <cstring>

#include <foodcalc/student.h>

#include <mdutils.h>

namespace fc
{
	struct load_file_t {explicit load_file_t() = default; };
	inline constexpr load_file_t load_file{};
	
	struct by_name_t {explicit by_name_t() = default; };
	inline constexpr by_name_t by_name{};

	// Группа управляет классом
	// Он хранит данные в директории класса 
	// назвние хранит сам класс и годы учебного года
	// например '7А_2026_2027' или '5_2027_2028'
	class StudentsGroup
	{
	private:
		char group_name[32];
		std::vector<Student*> students;
		
	public:
		StudentsGroup(const std::string& name, by_name_t)
		{
			strncat(group_name, name.c_str(), name.size());
			md::LOG("group name = %s\n", group_name);
		}
		StudentsGroup(const char* path_to_dir, load_file_t);
		~StudentsGroup();

		int32_t find_index(const char* name) const;
		bool contains(const char* name) const;

		bool add_new(const char* name, int32_t initial_balance = 0);
		bool delete_one(const char* name);

		Student* get_student(const char* name) const;

		void save_data() const;
		bool load_data();

		const std::vector<Student*>& get_students() const { return students; }

	};
}
	
#endif