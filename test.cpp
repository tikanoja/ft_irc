#include <string>
#include <algorithm>
#include <iostream>

int main(void)
{
	std::string string = "wri;rifagjdbfv klsiusdkvkherng4vow49thwiurvherg89vvnriervl,";

	sort(string.begin(), string.end());
	std::cout << string << std::endl;
	return 0;
}