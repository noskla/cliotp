#include<fstream>
#include<json/json.h>
#include<json/writer.h>
#include<filesystem>
#include"working_directory.h"

bool file_exists(const std::string& file_path)
{
	return std::filesystem::exists(file_path);
}


bool create_json()
{

std::string home_path = get_working_directory();

#ifdef __linux__

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
	
	return true;

}
else
{
	print_debug(home_path + ".cliotp/secret.json exists. Skipping...");
	return false;
}

#elif _WIN32

// to be done

#endif

}


bool add_entry_to_json(std::string secret_key)
{

	#ifdef __linux__
	std::string home_path = get_working_directory();
	create_json();

	Json::Value secret_json;
	
	std::fstream secret_json_file ((home_path + ".cliotp/secret.json"), std::fstream::binary);
	secret_json_file >> secret_json;
	 
	secret_json.append(secret_key);
	secret_json_file << secret_json;

	return true;
	#endif

}


