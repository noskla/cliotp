#include<unistd.h>

std::string get_working_directory()
{
	char* user = getlogin();
	std::string home_path = ("/home/" + std::string(user) + "/");

	if (!std::filesystem::exists(home_path + ".cliotp/"))
	{
		print_debug(home_path + ".cliotp/ does not exist. Creating...");
		std::filesystem::create_directory(home_path + ".cliotp/");
	
	}
	
	return home_path;

}
