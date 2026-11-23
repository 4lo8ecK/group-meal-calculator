#define DEBUG

#include <foodcalc/foodcalc.h>

int main()
{	
	fc::StudentsGroup* group1 = new fc::StudentsGroup("7А класс", fc::by_name);
	group1->save_data();
	
	group1->add_new("Ебанат Натрия",  1000);
	group1->save_data();
	group1->load_data();

	delete group1;

	auto lst = fc::path::get_directories_list(fc::path::get_app_dir());
	auto* group2 = new fc::StudentsGroup(lst[lst.size() - 1].c_str(), fc::load_file);

	auto stdnts = group2->get_students();
	printf("%d\n", stdnts.size());
	printf("%s\n", stdnts[stdnts.size() - 1]->get_name());
	
	delete group2;
}