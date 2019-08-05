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
			
		}
		
		print_debug(
			entry_name + " - found arguments:" +
			"\n   secret => " + secret_key + 
			"\n   digits => " + digits +
			"\n   timer  => " + timer
		);
		
		bool result = add_entry_to_json (entry_name, secret_key, digits, timer);
		
	}
	
	else if ((arg == "-g") || (arg == "--generate"))
	{
		//const char* secret = "";
		//char* totp = generate_code(secret);
		//std::cout << totp << std::endl;
	}
	
	else if ((arg == "-l") || (arg == "--list"))
	{
	
	}
	
	else if ((arg == "-d") || (arg == "--delete"))
	{
		
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
		
		std::cout << "   -d/--delete <name>" << std::endl;
		std::cout << "    ^ Remove permanently specified entry." << std::endl << std::endl;
		
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
