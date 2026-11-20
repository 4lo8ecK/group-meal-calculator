#include <foodcalc/manager.h>

#include <cstring>

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
	
	students.push_back(std::make_unique<Student>(name, initial_balance));
	return true;
}
