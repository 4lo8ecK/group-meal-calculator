#include "flwork.h"

#include <stdexcept>



namespace fc::path
{
	// На unix возвращает путь к домашней директории пользователя
	// на windows должен возвращать путь к AppData/Local
	
#if defined(__linux__)
	const char* get_usr_home()
	{
		const char* home = std::getenv("HOME");
		if (*home != '\0' && home != nullptr) { return home; }
		throw std::runtime_error("Не удалось получить путь к HOME");
	}
#elif defined(_WIN32)
	const char* get_usr_home()
	{
		// TODO: НАПИСАТЬ РЕАЛИЗАЦИЮ ПОД WINDOWS!!!
	}
#endif

	// Возвращает путь к директории приложения
	// на unix "/home/<username>/.4lo8eck/FoodCalc/"
	// на windows "С:users/<username>/Appdata/Local/4lo8ecK/FoodCalc/"	
	const char* get_app_dir()
	{
		fs::path res = fs::path(get_usr_home()) / developer_name / app_name;
		return res.c_str();
	}


	static void mkdir(const char* path)
	{
		if (!fs::exists(path) && !fs::is_directory(path))
		{
			fs::create_directories(path);
		}
	}


	// для списка групп учеников
	std::vector<fs::path> get_directories_list(const std::string& path)
	{
		std::vector<fs::path> res;
		for (const auto& dir : fs::directory_iterator(path))
		{
			if (is_directory(dir.path()))
			{
				res.push_back(dir);
			}
		}
		return res;
	}

	// для списка учеников одной из групп
	std::vector<fs::path> get_files_list(const std::string& path)
	{
		std::vector<fs::path> res;
		for (const auto& fl : fs::directory_iterator(path))
		{
			if (fs::is_regular_file(fl.path()))
			{
				res.push_back(fl);
			}
		}
		return res;
	}
}