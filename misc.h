#include<iostream>
#include"color.h"

void print_debug (std::string message)
{
	if (debug) {
		std::string debug_color_prefix = get_color("debug");
		std::string reset = get_color("reset");
		
		std::cout << debug_color_prefix << "[DEBUG] " << reset << message << std::endl;
	}
}
