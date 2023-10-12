
#include "inc/IRCServer.hpp"
#include "inc/User.hpp"
#include "inc/Message.hpp"
#include "inc/CircularBuffer.hpp"
#include "inc/Reply.hpp"
#include "inc/Error.hpp"


# define ALL_MODES "+-awiroOs"
# define SETTABLE_MODES "iwroO"


int cmd_mode(IRCServer& server, User& user, Message& message){
	
	std::vector<std::string>const & params = message.getParams();

	if (params.size() < 1){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	if (message.getSender()->getNick() != params[0]){
		user.getSendBuffer().addToBuffer(ERR_USERSDONTMATCH(server.getName()).c_str());
		return 1;
	}

	if (params.size() == 2){
		user.getSendBuffer().addToBuffer(RPL_UMODEIS(server.getName(),
			server.printModeStr(user)).c_str());
	}

	size_t forbidden;
	for (size_t i = 0; i < params.size(); i++){
		forbidden = params[i].find_first_not_of(ALL_MODES);
		if (forbidden != std::string::npos)
			user.getSendBuffer().addToBuffer(ERR_UMODEUNKNOWNFLAG(server.getName().c_str()));
	}

	std::string additions;
	std::string removals;
	for (size_t i = 0; i < params.size(); i++){
		size_t pos = 0;
		while (pos < params[i].size())
		{
			additions += server.setBatchMode(user, params[i], &pos);
			removals += server.unsetBatchMode(user, params[i], &pos);
		}
	}
	std::string reply = ":" + user.getNick() + " MODE " +  user.getNick() + " :+" + additions + "-" + removals;
	user.getSendBuffer().addToBuffer(reply.c_str());

	return 0;
}