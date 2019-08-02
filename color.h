#include<string>
#include<map>
#include<algorithm>

std::string get_color (std::string color)
{
	std::map<std::string, std::string> available_colors;
	
	// default bash colors
	available_colors["reset"]   = "\033[0m";
	available_colors["red"]     = "\033[31m";
	available_colors["green"]   = "\033[32m";
	available_colors["yellow"]  = "\033[33m";
	available_colors["blue"]    = "\033[34m";
	available_colors["magenta"] = "\033[35m";
	available_colors["cyan"]    = "\033[36m";
	
	// custom colors
	available_colors["debug"]   = "\033[1m\033[35m";
	available_colors["warning"] = "\033[1m\033[33m";
	available_colors["ok"]      = "\033[1m\033[32m";
	available_colors["error"]   = "\033[1m\033[31m";

	// check if 	chosen color is in available_colors
	if (available_colors.count(color) == 0)
	{
		// return empty string to not cause further problems.
		return "";
	}
	
	else 
	{
		return available_colors[color];
	}
	
}
