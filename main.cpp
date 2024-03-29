#include<iostream>
#include<stdio.h>
#include<string>
#include<cotp.h>

#include"conf.h"
#include"misc.h"
#include"io_keys.h"


char* generate_code (const char* secret)
{

	cotp_error_t* err;
	char* code = get_totp (secret, 6, 30, SHA1, err);
	printf(code + '\n');
	return code;
	
}

int main (int argc, char** argv)
{

	print_debug("Running version " + version_str);
	create_json();

	// arguments	
	if (argc < 2)
	{
		printf("Not enough arguments, please refer to cliotp --help\n");	
		return -1;
	}

	std::string arg = std::string(argv[1]);
	
	
	if ((arg == "-a") || (arg == "--add"))
	{
		
		// declare variables in this scope
		std::string entry_name;
		std::string secret_key;
		std::string digits = "6";
		std::string timer = "30";
		
		if (argc >= 3)
		{
			// Get values
			entry_name = argv[2];
			secret_key = argv[3];
			
			if (argc > 4)
			{
				digits = argv[4];
				if (argc > 5) { timer = argv[5]; }
			}
			
			print_debug(
				entry_name + " - found arguments:" +
				"\n   secret => " + secret_key + 
				"\n   digits => " + digits +
				"\n   timer  => " + timer
			);
		
			bool result = add_entry_to_json (entry_name, secret_key, digits, timer);
			
			if (result)
				std::cout << (get_color("ok") + "Ok!" + get_color("reset")) << std::endl;
			else
				std::cout << (get_color("error") + "An error occurred." + get_color("reset")) << std::endl;				
			
		}
		else
		{
			std::cout << "Not enough arguments. Please check \"cliotp --help\"." << std::endl;
			return -1;
		}
		
	}
	
	else if ((arg == "-g") || (arg == "--generate"))
	{
		
		if (argc < 2)
		{
			std::cout << "Not enough arguments. Please check \"cliotp --help\"." << std::endl;
			return -1;
		}
		
		std::string entry_name = argv[2];
		std::map entry_data    = get_entry_from_json(entry_name);
		
		if (entry_data["error"] == "yes")
		{
			std::cout << "This entry does not exist." << std::endl;
			return -1;		
		}
		
		const char* secret_key = entry_data["secret_key"].c_str();
		std::string totp = std::string(generate_code(secret_key));

		totp.insert(3, " ");
		
		std::cout << get_color("cyan") << entry_name <<  get_color("reset")
		          << " => " << get_color("ok") << totp << get_color("reset")
		          << std::endl << "This code will be invalidated in less than "
		          << entry_data["timer"] << " seconds" << std::endl;
		
	}
	
	else if ((arg == "-l") || (arg == "--list"))
	{
		Json::Value entries = get_all_entries();
		// loop through entries
		int i = 1;
		for ( Json::Value::const_iterator entry = entries.begin();
			   entry != entries.end(); entry++ )
		{

			if (i != 1)
				std::cout << " --- --- --- --- --- --- ---" << std::endl;

			std::string key = entry.key().asString();

			std::cout << get_color("ok") << key << get_color("reset") << ":" << std::endl;
			std::cout << "Secret Key => " << entries[key]["secret_key"] << std::endl;
			std::cout << "Digits     => " << entries[key]["digits"] << std::endl;
			std::cout << "Timer      => " << entries[key]["timer"] << std::endl;
	
			i++;
		
		}
	}
	
	else if ((arg == "-r") || (arg == "--remove"))
	{
		if (argc < 3)
		{
			std::cout << "Not enough arguments. Please check \"cliotp --help\"." << std::endl;
			return -1;
		}
		
		std::string entry_name = argv[2];
		remove_entry(entry_name);
		std::cout << get_color("ok") << "Ok." << get_color("reset") << std::endl;
	}
	
	else if ((arg == "-h") || (arg == "--help"))
	{
		std::cout << std::endl << "cliotp " << version_str << std::endl << std::endl;
		
		std::cout << "   -a/--add <name> <secret-key> <digits> <timer>" << std::endl;
		std::cout << "    ^ Add new entry. <digits> and <timer> are optional (default to 6, 30)" << std::endl << std::endl;
		
		std::cout << "   -g/--generate <name>" << std::endl;
		std::cout << "    ^ Generate the code for specified entry." << std::endl << std::endl;
		
		std::cout << "   -l/--list" << std::endl;
		std::cout << "    ^ List all entries." << std::endl << std::endl;
		
		std::cout << "   -r/--remove <name>" << std::endl;
		std::cout << "    ^ Remove specified entry permanently." << std::endl << std::endl;
		
		std::cout << "   -h/--help" << std::endl;
		std::cout << "    ^ Display this message." << std::endl << std::endl;
	}
	
	else
	{
		printf("Unknown argument, please refer to cliotp --help\n");
		return 1;	
	}	
	
	return 0;

}
