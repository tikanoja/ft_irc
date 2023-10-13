
#include "inc/IRCServer.hpp"
#include "inc/User.hpp"
#include "inc/Message.hpp"
#include "inc/CircularBuffer.hpp"
#include "inc/Reply.hpp"
#include "inc/Error.hpp"

# define ALL_MODES "+-awiroOs"
# define SETTABLE_MODES "iwroO"

uint16_t	port = 6667;
IRCServer	nserver(port);
int			fd1 = 4;
User		nuser(fd1, "127.0.0.1");
Message		nmessage1(":djagusch MODE DudeMcDud\r\n");
Message		nmessage2(":djagusch MODE DudeMcDod\r\n");
Message		nmessage3(":djagusch MODE\r\n");
Message		nmessage4(":djagusch MODE DudeMcDud +i\r\n");
Message		nmessage5(":djagusch MODE DudeMcDud -i\r\n");
Message		nmessage6(":djagusch MODE DudeMcDud +i\r\n");
Message		nmessage7(":djagusch MODE DudeMcDud +i\r\n");

int cmd_mode(IRCServer& server, User& user, Message& message);


int main(){

	nuser.setNick("DudeMcDud");
	nuser.setUserName("See above");
	nuser.setRealName("See above");
	nuser.setMode(static_cast<IRCServer::e_uperm>(0x0080));

	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage1);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage2);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage3);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage4);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage5);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage6);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage7);
	std::cout << "Mode:" << nuser.getMode() << std::endl;
	cmd_mode(nserver, nuser, nmessage8);
	std::cout << "Mode:" << nuser.getMode() << std::endl;

	return 0;
}


int cmd_mode(IRCServer& server, User& user, Message& message){

	std::vector<std::string>const & params = message.getParams();

	if (params.size() < 1){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	std::cout << "param check passed" << std::endl;
	std::cout << user.getNick() << "\n" << params[0] << std::endl;
	if (user.getNick() != params[0]){
		user.getSendBuffer().addToBuffer(ERR_USERSDONTMATCH(server.getName()).c_str());
		std::cout << "Users don't match" << std::endl;
		return 1;
	}
	std::cout << "nick check passed" << std::endl;

	if (params.size() == 2){
		user.getSendBuffer().addToBuffer(RPL_UMODEIS(server.getName(),
			server.printModeStr(user)).c_str());
		std::cout << "mode is " << server.printModeStr(user) << std::endl;
	}
	std::cout << "modes given" << std::endl;

	size_t forbidden;
	for (size_t i = 0; i < params.size(); i++){
		forbidden = params[i].find_first_not_of(ALL_MODES);
		if (forbidden != std::string::npos)
			user.getSendBuffer().addToBuffer(ERR_UMODEUNKNOWNFLAG(server.getName()).c_str());
		std::cout << "Unknown MODE flag" << std::endl;
	}
	std::cout << "Unknown mode flags checked" << std::endl;

	std::string additions;
	std::string removals;
	for (size_t i = 1; i < params.size(); i++){
		size_t pos = 0;
		while (pos < params[i].size())
		{
			additions += server.setBatchMode(user, params[i], &pos);
			removals += server.unsetBatchMode(user, params[i], &pos);
			pos++;
		}
	}
	std::cout << "YAAAAAAS" << std::endl;

	std::string reply = ":" + user.getNick() + " MODE " +  user.getNick() + " :+" + additions + "-" + removals;
	user.getSendBuffer().addToBuffer(reply.c_str());
	std::cout << "BYYYYYYEEEEE GUUUUURRRRLL" << std::endl;

	return 0;
}

