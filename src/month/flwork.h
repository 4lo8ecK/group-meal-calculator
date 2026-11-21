#pragma once

#ifndef FC_IMPL_FLWORK_H
#define FC_IMPL_FLWORK_H

#include <string>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

namespace fc::path
{
	#if defined(__linux__)
	constexpr static const char* developer_name = ".4lo8ecK";
	#elif defined(_WIN32)
	constexpr static const char* developer_name = "4lo8ecK";
	#endif
	constexpr static const char* app_name = "FoodCalc";

	// На unix возвращает путь к домашней директории пользователя
	// на windows должен возвращать путь к AppData/Local
	const char* get_usr_home();
	
	// Возвращает путь к директории приложения
	// на unix "/home/<username>/.4lo8eck/FoodCalc/"
	// на windows "С:users/<username>/Appdata/Local/4lo8ecK/FoodCalc/"	
	const char* get_app_dir();

	// для списка групп учеников
	std::vector<fs::path> get_directories_list(const std::string& path);
	// для списка учеников одной из групп
	std::vector<fs::path> get_files_list(const std::string& path);
}
#endif