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
	
	Json::Value root;
	root = Json::objectValue;
	//vec.append(Json::Value(1));
	//vec.append(Json::Value(2));  <- instead of integers put any value
	//vec.append(Json::Value(3));
	
	secret_json << root;
	
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


bool add_entry_to_json
(std::string entry_name, std::string secret_key, std::string digits, std::string timer)
{

	#ifdef __linux__
	std::string home_path = get_working_directory();
	print_debug(home_path);

	Json::Value entries;
	print_debug("Initialized variables entries.");
	
	std::ifstream _input_entries_json ((home_path + ".cliotp/secret.json"), std::ifstream::binary);
	print_debug("Opened file.");
	_input_entries_json >> entries;
	print_debug("Moved contents to variable.");

	print_debug("Contents: " + secret_key + " " + digits + " " + timer);
	entries[entry_name]["secret_key"] = secret_key;
	entries[entry_name]["digits"] = digits;
	entries[entry_name]["timer"] = timer;
	
	print_debug("Saving...");
	std::ofstream _output_entries_json ((home_path + ".cliotp/secret.json"), std::ofstream::binary);
	_output_entries_json << entries << std::endl;

	return true;
	#endif

}


