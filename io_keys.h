#include<fstream>
#include<json/json.h>
#include<json/writer.h>
#include<unistd.h>
#include<filesystem>

bool file_exists(const std::string& file_path)
{
	return std::filesystem::exists(file_path);
}

void create_json()
{

#ifdef __linux__

char* user = getlogin();
std::string home_path = "/home/" + std::string(user) + "/";

print_debug("Working in " + home_path);
if (!file_exists(home_path + ".cliotp/"))
{
	print_debug(home_path + ".cliotp/ does not exist. Creating...");
	std::filesystem::create_directory(home_path + ".cliotp/");
	
}

print_debug("Working in " + home_path + ".cliotp/");
if (!file_exists(home_path + ".cliotp/secret.json"))
{

	print_debug(home_path + ".cliotp/secret.json does not exist. Creating...");
	
	std::ofstream secret_json((home_path + ".cliotp/secret.json"), std::ofstream::binary);	
	
	Json::Value vec(Json::arrayValue);
	//vec.append(Json::Value(1));
	//vec.append(Json::Value(2));  <- instead of integers put any value
	//vec.append(Json::Value(3));
	
	secret_json << vec << std::endl;

}

#endif

}


