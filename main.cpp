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

	// arguments	
	if (argc < 2)
	{
		printf("Not enough arguments, please refer to cliotp --help\n");	
		return -1;
	}

	std::string arg = std::string(argv[1]);
	if ((arg == "-a") || (arg == "--add"))
	{
	
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
		create_json();
	}
	else if ((arg == "-h") || (arg == "--help"))
	{
		
	}
	else
	{
		printf("Unknown argument, please refer to cliotp --help\n");
		return 1;	
	}	
	
	return 0;

}
