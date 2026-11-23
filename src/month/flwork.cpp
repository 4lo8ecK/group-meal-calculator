#include <foodcalc/flwork.h>

#include <stdexcept>
#include <mdutils.h>

namespace fc::path
{
	// На unix возвращает путь к домашней директории пользователя
	// на windows должен возвращать путь к AppData/Local
	
#if defined(__linux__)
	std::string get_usr_home()
	{
	#ifdef NDEBUG
		const char* home = std::getenv("HOME");
	#else
		const char* home = "./";
	#endif
		md::LOG("homedir = %s\n", home);
		if (*home != '\0' && home != nullptr) { return home; }
		throw std::runtime_error("Не удалось получить путь к HOME");
#elif defined(_WIN32)

		// TODO: НАПИСАТЬ РЕАЛИЗАЦИЮ ПОД WINDOWS!!!
#endif
	}

	// Возвращает путь к директории приложения
	// на unix "/home/<username>/.4lo8eck/FoodCalc/"
	// на windows "С:users/<username>/Appdata/Local/4lo8ecK/FoodCalc/"	
	std::string get_app_dir()
	{
		std::string res = get_usr_home() + "/" + developer_name + "/" + app_name;
		// sprintf(res.data(), "%s/%s/%s", get_usr_home(), developer_name, app_name);
		md::LOG("app_dir = %s\n", res.c_str());
		return res;
	}

	void mkdir(const std::string& path)
	{
		if (!fs::exists(path) && !fs::is_directory(path))
		{
			fs::create_directories(path);
			md::LOG("Создана директория %s\n", path.c_str());
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