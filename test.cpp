
#include "inc/User.hpp"
#include "inc/IRCServer.hpp"
#include "inc/Utils.hpp"
#include "inc/Operator.hpp"
#include "inc/Reply.hpp"
#include "inc/Error.hpp"
#include <iomanip>


uint16_t		port = 6667;
IRCServer		nserver(port);
int				fd1 = 4;

int main(){

	nserver.initOperators();
	return 0;
}

void IRCServer::initOperators(){

	std::ifstream operFile;

	operFile.open("config/ooperators.config");
	if (operFile.is_open() && !operFile.bad() && !operFile.peek() == 0)
	{
		std::cout << "Cannot set any operators" << std::endl;
		return ;
	}
	char line[256];
	std::vector<std::string> rawOper;
	operFile.getline(line, '\n');
	do {
		if (!line)
			break;
		rawOper = split(line, ' ');
		p_opers.push_back(Operator(rawOper[0], rawOper[1], rawOper[2]));
		operFile.getline(line, '\n');
	} while (line);
}
