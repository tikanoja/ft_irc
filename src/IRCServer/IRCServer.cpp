/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:21:45 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/14 10:49:50 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IRCServer.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Utils.hpp"

std::string const & IRCServer::getName() const{

	return p_serverName;
}

std::string const & IRCServer::getPassword() const{

	return p_password;
}

Uvector const &	IRCServer::getUsers() const{
	
	return p_users;
}

Cvector & IRCServer::getChannels(){

	return p_channels;
}

std::vector<Operator> const & IRCServer::getOpers() const{

	return p_opers;
}

std::string const & IRCServer::getDate(void) const{
	return p_creationDate;
}

std::string const & IRCServer::getVersion(void) const{
	return p_version;
}

std::string const & IRCServer::getUmodes(void) const{
	return p_modes;
}

std::string const & IRCServer::getCmodes(void) const{
	return p_chanModes;
}


void signalHandler(int signum) {
	
	if (signum == SIGINT) {
		std::cout << std::endl << "Server quit." << BRIGHT_COLOR_RED << " <3" << COLOR_END << std::endl;
		exit(0);
	}
}

IRCServer::IRCServer(uint16_t port, std::string password) : p_port(port), p_password(password){

	p_pfds.reserve(MAXCLIENTS + 1);
	p_users.reserve(MAXCLIENTS + 1);
	p_logger = new Logger("./config/log");
	p_logger->log("IRCserv started", __FILE__, __LINE__);
	try{
		initServer();
	} catch (std::exception &e){
		exit(1);
	}
	return ;
}

IRCServer::~IRCServer(void) {
	
	p_logger->log("IRCserv shutdown", __FILE__, __LINE__);
	delete p_logger;
	return ;
}

void IRCServer::initServer() {
	
	if (getListenerSocket()){
		p_logger->log("Could not create listener socket", __FILE__, __LINE__);
		throw std::runtime_error("Failed to create listener socket");
	}
	setGlobals() ;
	initCommands();
	initOperators();
	std::cout << BRIGHT_COLOR_GREEN << "PawsitiveIRC server is starting"<< std::endl;
	std::cout << "   _______________                       _______________" << "\n"
	<< "  |  ___________  |     .-.     .-.     |  ___________  |" << "\n"
	<< "  | |           | |    .****. .****.    | |           | |" << "\n"
	<< "  | |   0   0   | |    .*****.*****.    | |   0   0   | |" << "\n"
	<< "  | |     -     | |     .*********.     | |     -     | |" << "\n"
	<< "  | |   \\___/   | |      .*******.      | |   \\___/   | |" << "\n"
	<< "  | |___     ___| |       .*****.       | |___     ___| |" << "\n"
	<< "  |_____|\\_/|_____|        .***.        |_____|\\_/|_____|" << "\n"
	<< "    _|__|/ \\|_|_.............*........... _|__|/ \\|_|_" << "\n"
	<< "   / ********** \\                         / ********** \\" << "\n"
	<< " /  ************  \\                     /  ************  \\" << "\n"
	<< "--------------------                   -------------------- " << COLOR_END << std::endl;
	std::cout << "Running..."<< std::endl;
	std::cout << "Connect with Irssi:\t/connect 127.0.0.1 " << p_port << " " << p_password << std::endl;
	std::cout << "or with Netcat:\t\tnc 127.0.0.1 " << p_port << std::endl;
	return ;
}

void IRCServer::setGlobals() {
	std::time_t p_cur_time = std::time(0);
	std::tm* now = std::localtime(&p_cur_time);

	p_serverName = "PawsitiveIRC";
	p_creationDate = std::asctime(now); 
	p_version = "0.0.1";
	p_modes = "awiroOs";
	p_chanModes = "itkol";
}

void IRCServer::initCommands() {

	std::pair<std::string, commandFunction> cmdPairs[] = {
		std::make_pair("cap", cmd_cap),
		std::make_pair("pass", cmd_pass),
		std::make_pair("nick", cmd_nick),
		std::make_pair("user", cmd_user),
		std::make_pair("mode", cmd_mode),
		std::make_pair("motd", cmd_motd),
		std::make_pair("oper", cmd_oper),
		std::make_pair("away", cmd_away),
		std::make_pair("quit", cmd_quit),
		std::make_pair("ping", cmd_ping),
		std::make_pair("pong", cmd_pong),
		std::make_pair("privmsg", cmd_privmsg),
		std::make_pair("notice", cmd_notice),
		std::make_pair("kill", cmd_kill),
		std::make_pair("who", cmd_who),
		std::make_pair("whois", cmd_whois),
		std::make_pair("join", chan_cmd_join),
		std::make_pair("part", chan_cmd_part),
		std::make_pair("topic", chan_cmd_topic),
		std::make_pair("invite", chan_cmd_invite),
		std::make_pair("kick", chan_cmd_kick)
	};
	p_commandMap.insert(cmdPairs, cmdPairs + sizeof(cmdPairs) / sizeof(cmdPairs[0]));
}

void IRCServer::initOperators(){

	std::ifstream operFile;

	operFile.open("config/operators.config", std::fstream::in);
	if (!operFile.good() || !operFile.is_open() || operFile.peek() < 0){
		p_logger->log("Cannot set any operators", __FILE__, __LINE__);
		if (operFile.is_open())
			operFile.close();
		return ;
	}
	char line[256];
	std::vector<std::string> rawOper;
	while (operFile.getline(line, 256)){
		std::string string = line;
		rawOper = split(string, ' ');
		p_opers.push_back(Operator(rawOper[0], rawOper[1], rawOper[2]));
	}
	operFile.close();
}

void IRCServer::log(std::string string, std::string file, int line){
	
	p_logger->log(string, file, line);
}

int IRCServer::pollingRoutine() {
	
	int poll_count;
	p_fd_count = static_cast<nfds_t>(p_pfds.size());
	signal(SIGINT, signalHandler);
	while (1) {
		if ((poll_count = poll(&(p_pfds[0]), p_fd_count, 0)) == -1)
			return (-1);
		for (nfds_t i = 0; i < p_fd_count; i++) {
			if (p_pfds[i].revents & (POLLIN | POLLOUT | POLLNVAL | POLLERR | POLLHUP)) {
				if (p_pfds[i].revents & POLLIN) {
					if (i == 0) {
						acceptClient();
					} else {
						receiveMsg(p_users.findUserBySocket(p_pfds[i].fd), i);
					}
				} else if (p_pfds[i].revents & POLLOUT) {
					checkSendBuffer(p_users.findUserBySocket(p_pfds[i].fd));
					checkRecvBuffer(p_users.findUserBySocket(p_pfds[i].fd), i);
				} else if (p_pfds[i].revents & (POLLNVAL | POLLERR | POLLHUP) && i != 0) {
					dropConnection(0, i);
					p_logger->log("Connection dropped", __FILE__, __LINE__);
				}
			}
		}
	}
	for (nfds_t i = 0; i < p_fd_count; i++) {
		close(p_pfds[i].fd);
	}
	return (0);
}
