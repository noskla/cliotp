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

Json::Value get_all_entries ()
{

	std::string home_path = get_working_directory();

	#ifdef __linux__
	std::ifstream _input_entries_json ((home_path + ".cliotp/secret.json"), std::ifstream::binary);
	#endif
	
	Json::Value entries;
	_input_entries_json >> entries;
	
	return entries;

}


bool add_entry_to_json
(std::string entry_name, std::string secret_key, std::string digits, std::string timer)
{

	Json::Value entries = get_all_entries();
	std::string home_path = get_working_directory();

	entries[entry_name]["secret_key"] = secret_key;
	entries[entry_name]["digits"] = digits;
	entries[entry_name]["timer"] = timer;
	
	print_debug("Saving...");
	
	#ifdef __linux__
	std::ofstream _output_entries_json ((home_path + ".cliotp/secret.json"), std::ofstream::binary);
	_output_entries_json << entries << std::endl;
	#endif

	return true;

}

std::map<std::string, std::string> get_entry_from_json (std::string entry_name)
{
	
	Json::Value entries = get_all_entries();
	
	std::map<std::string, std::string> output_data;
	output_data["secret_key"] = entries[entry_name]["secret_key"].asString();	
	output_data["digits"]     = entries[entry_name]["digits"].asString();
	output_data["timer"]      = entries[entry_name]["timer"].asString();
	
	output_data["error"] = ((output_data["secret_key"] == "") ? "yes" : "no");
	
	return output_data;

}

void remove_entry (std::string entry_name)
{

	Json::Value entries = get_all_entries();
	std::string home_path = get_working_directory();
	
	if (!entries[entry_name].isNull())
	{
		entries[entry_name].clear();
	
		#ifdef __linux__
		std::ofstream _output_entries_json ((home_path + ".cliotp/secret.json"), std::ofstream::binary);
		_output_entries_json << entries << std::endl;
		#endif
	}
	
}
