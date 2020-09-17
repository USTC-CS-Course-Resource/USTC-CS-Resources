#pragma once

#include <iostream>
#include <string>

void Print_Title(std::string s) {
	static const std::string cut_off_rule = "/-------------------------------\\\n";
	static const std::string cut_off_rule_middle = " ------------------------------- \n";
	std::cout << cut_off_rule << '\t' << s << std::endl << cut_off_rule_middle;
}
void Print_End() {
	static const std::string cut_off_rule = "\\_______________________________/\n";
	std::cout << std::endl << cut_off_rule << std::endl << std::endl << std::endl;
}