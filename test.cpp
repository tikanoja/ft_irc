
#include "inc/User.hpp"
#include "inc/CircularBuffer.hpp"
#include "inc/IRCServer.hpp"
#include "inc/Message.hpp"
#include "inc/Reply.hpp"
#include "inc/Error.hpp"
#include <iomanip>

# define ALL_MODES "+-awiroOs"

uint16_t		port = 6667;

int cmd_mode(IRCServer& server, User& user, Message& message);


int main(){

IRCServer		nserver(port);


	return 0;
}
