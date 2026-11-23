#include <foodcalc/manager.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>

#include <foodcalc/flwork.h>

using namespace fc;


StudentsGroup::StudentsGroup(const char* path_to_dir, load_file_t)
{
	std::string pt;
	fs::path _path_to_dir = fs::path(path_to_dir);
	if (_path_to_dir.has_filename())
	{
		pt = _path_to_dir.filename().string();
	}
	else
	{ 
		pt = _path_to_dir.parent_path().filename();
	}
	strncpy(group_name, pt.c_str(), sizeof(group_name));

	auto files = fc::path::get_files_list(path_to_dir);

	for (auto f : files)
	{
		md::LOG("Открыт файл для чтения '%s' - ", f.c_str());

		FILE* fl = fopen(f.c_str(), "rb");
		
		Student* stdnt = new Student();
		fread(stdnt, sizeof(Student), 1, fl);
		
		students.push_back(stdnt);

		fclose(fl);
		md::LOG("OK\n");
	}
	
}

StudentsGroup::~StudentsGroup()
{
	int i = 0;
	md::LOG("Вызван деструктор StudentsGroup. Количество на удаление - %d. ", students.size());
	for (auto& s : students)
	{
		if (s != nullptr)
		{
			delete s;
			s = nullptr;
			i++;
		}
	}
	md::LOG("Удалено - %d\n", i);
}

int32_t StudentsGroup::find_index(const char* name) const
{
	if (name == nullptr)
	{
		throw std::runtime_error("Пустая строка вместо имени нового ученика");
	}
	auto iter = std::find_if(students.begin(), students.end(), [name](const auto& ptr)
	{
		return strcmp(name, ptr->get_name()) == 0;
	});
	if (iter == students.end())
	{
		return -1;
	}
	return md::cast<int32_t>(std::distance(students.begin(), iter));
}
bool StudentsGroup::contains(const char* name) const
{
	if (name == nullptr)
	{
		throw std::runtime_error("Пустая строка вместо имени нового ученика");
	}
	auto iter = std::find_if(students.begin(), students.end(), [name](const auto& ptr)
	{
		return strcmp(name, ptr->get_name()) == 0;
	});
	return iter != students.end();
}

bool StudentsGroup::add_new(const char* name, int32_t initial_balance)
{
	if (name == nullptr)
	{
		throw std::runtime_error("Пустая строка вместо имени нового ученика");
	}
	if (contains(name))
	{
		return false;
	}	
	students.push_back(new Student(name, initial_balance));
	return true;
}

bool StudentsGroup::delete_one(const char* name)
{
	if (name ==  nullptr)
	{
		throw std::runtime_error("Пустая строка вместо имени ученика");
	}
	
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
	if (name ==  nullptr)
	{
		throw std::runtime_error("Пустая строка вместо имени ученика");
	}
	int32_t index = find_index(name);
	if (index == -1)
	{
		return nullptr;
	}
	return students[index];
}

void StudentsGroup::save_data() const
{
	std::string group_dir = fc::path::get_app_dir() + "/" + this->group_name;
	md::LOG("group path = %s\n", group_dir.c_str());
	fc::path::mkdir(group_dir.c_str());

	for (const auto& f : fc::path::get_files_list(group_dir))
	{
		fs::remove(f);
	}

	for (fc::Student* s : students)
	{
		std::string student_path = group_dir + "/" + s->get_name();
		md::LOG("file path = %s", student_path.c_str());

		FILE* fl = fopen(student_path.c_str(), "wb");
		if (!fl) throw std::runtime_error("Не удалось открыть файл");
		fwrite(s, sizeof(Student), 1, fl);
		
		fclose(fl);
	}
}

bool StudentsGroup::load_data()
{
	std::string app_dir = fc::path::get_app_dir() + "/" + this->group_name;
	std::vector<fs::path> files = fc::path::get_files_list(app_dir);
	
	md::LOG("Найдено %d файлов\n", files.size());

	for (const auto& f : files)
	{
		md::LOG("Открыт файл для чтения '%s' - ", f.c_str());

		FILE* fl = fopen(f.c_str(), "rb");
		
		Student* stdnt = new Student();
		fread(stdnt, sizeof(Student), 1, fl);

		students.push_back(stdnt);
		
		fclose(fl);
		md::LOG("OK\n");
	}
	return true;
}