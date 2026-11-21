#include <foodcalc/manager.h>

#include <cstring>
#include "flwork.h"

using namespace fc;

int32_t StudentsGroup::find_index(const char* name) const
{
	if (name == nullptr) throw std::runtime_error("Пустая строка вместо имени нового ученика");
	auto iter = std::find_if(students.begin(), students.end(), [name](const auto& ptr) {return strcmp(name, ptr->get_name()) == 0; });
	if (iter == students.end()) return -1;
	return md::cast<int32_t>(std::distance(students.begin(), iter));
}
bool StudentsGroup::contains(const char* name) const
{
	if (name == nullptr) throw std::runtime_error("Пустая строка вместо имени нового ученика");
	auto iter = std::find_if(students.begin(), students.end(), [name](const auto& ptr) {return strcmp(name, ptr->get_name()) == 0; });
	return iter != students.end();
}

bool StudentsGroup::add_new(const char* name, int32_t initial_balance)
{
	if (name == nullptr) throw std::runtime_error("Пустая строка вместо имени нового ученика");
	if (contains(name)) return false;
	
	students.push_back(new Student(name, initial_balance));
	return true;
}

bool StudentsGroup::delete_one(const char* name)
{
	if (name ==  nullptr) throw std::runtime_error("Пустая строка вместо имени ученика");
	int32_t index = find_index(name);

	if (index != -1)
	{
		delete students[index];
		students.erase(students.begin() + index);
		return true;
	}
	return false;
}

Student* StudentsGroup::get_student(const char* name) const
{
	if (name ==  nullptr) throw std::runtime_error("Пустая строка вместо имени ученика");
	int32_t index = find_index(name);
	if (index == -1) return nullptr;
	return students[index];
}

void StudentsGroup::save_data() const
{
	fs::path app_path = fs::path(fc::path::get_app_dir()) / group_name;
	
	for (const auto& s : students)
	{
		fs::path student_path = app_path / s->get_name();
		FILE* fl = fopen(student_path.c_str(), "wb");
		fwrite(s, sizeof(Student), 1, fl);
		fclose(fl);
	}
}

bool StudentsGroup::load_data()
{
	// fs::path app_path = fc::path::get_app_dir();
	// std::vector<fs::path> files = 

	return false;
}