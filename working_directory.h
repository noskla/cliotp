#include<unistd.h>

std::string get_working_directory()
{
	#ifdef __linux__
	char* user = getlogin();
	std::string home_path = ("/home/" + std::string(user) + "/");

	if (!std::filesystem::exists(home_path + ".cliotp/"))
	{
		print_debug(home_path + ".cliotp/ does not exist. Creating...");
		std::filesystem::create_directory(home_path + ".cliotp/");
	
	}
	
	#elif _WIN32
	std::string home_path = getenv("LOCALAPPDATA");
	
	if (!std::filesystem::exists(home_path + "cliotp/"))
	{
		print_debug("Could not find cliotp directory in %LOCALAPPDATA%. Creating...");
		std::filesystem::create_directory(home_path + "cliotp/");	
	}
	
	#endif
	
	return home_path;

}
