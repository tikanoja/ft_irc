/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/09/28 09:47:27 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLY_HPP
# define REPLY_HPP

# include <string>

void	sendRPjL(int const client_fd, std::string client_buffer);

# define USER_ID (nickname, username, host) (":" + nickname + "!" + username + "@" + host)

// Registration

# define RPL_WELCOME(nick, user, host)("Welcome to the Internet Relay Network" + nick"!" + user + "@" + host + "\r\n") //001
# define RPL_YOURHOST(servername, version)("Your host is " + servername + ", running version " + version + "\r\n") //002
# define RPL_CREATED(date)("This server was created" + date + "\r\n") //003
# define RPL_MYINFO(servername, version, umodes, cmodes)(servername + " " + version + " " + umodes + " " + cmodes + "\r\n") //004
# define RPL_BOUNCE(servername, port)("Try server " + server name + ", port " + port + "\r\n") //005
# define RPL_TRACELINK(version, debuglevel,  destination, next_server, protocolversion, linkuptime, bssendq, usbackq)\
("Link " + version + " & " debug level + " " + destination + " " + nextserver + " V" + protocolversion + linkuptime + " " + bssendq + " " +  ussendq + "\r\n") //200
# define RPL_TRACECONNECTING(class, server)("Try. " + class + " " + server + "\r\n") //201
# define RPL_TRACEHANDSHAKE(class, server)("H.S. " + class + " " + server + "\r\n") //202
# define RPL_TRACEUNKNOWN(class, client_ip)("???? " + class + " [" + client_ip + "]  \r\n") //203 client IP in dot form
# define RPL_TRACEOPERATOR(class, nick)("Oper " + class + " " + nick + "\r\n") //204
# define RPL_TRACEUSER(class, nick)("User " + class + " " + nick + "\r\n") //205
//# define RPL_TRACESERVER(class, n_services, n_users, server, )("Serv " + class + " " + n_services + "S " + n_users + "C " + server + nick!user|*!* + "@" + host|server + " V" + protocolversion + "\r\n") //206 incorrect!!!!!!
# define RPL_TRACESERVICE(class, name, type, activetype)("Service " + class + " " + name + " " + type + " " + activetype + "\r\n") //207
# define RPL_TRACENEWTYPE(newtype, client_name)(newtype + " 0 " + client_name + "\r\n") //208
# define RPL_TRACECLASS(class, count)("Class " + class + " " + count + "\r\n") //209
# define RPL_STATSLINKINFO(linkname, sendq, sentmsg, sentkbyte, recvmsg, recvkbyte, timme_open)\
(linkname + " " + sendq + " " + sentmsg + sentkbyte + " " + recvmsg + recvkbyte + " " + time_open + "\r\n") //211
# define RPL_STATSCOMMANDS(command, count, b_byte, remote_count)(command + " " + count + " " + n_byte + " " + remote_count + "\r\n") //212
# define RPL_ENDOFSTATS(stats_letter)(stats_letter + " :End of STATS report\r\n") //219
# define RPL_UMODEIS(usermodestring)(usermodestring + "\r\n") //221
# define RPL_SERVLIST(name, server, mask, type, hopcount, info)(name + " " + server + " " + mask + " " + type + " " + hopcount + " " + info + "\r\n") //234
# define RPL_SERVLISTEND(mask, type)(mask + " " + type + " :End of service listing\r\n") //235
# define RPL_STATSUPTIME(serveruptime)(":Server Up serveruptime\r\n") //242 as %d days %d:%02d:%02d
# define RPL_STATSOLINE()(+ "\r\n") //243 ??????
# define RPL_LUSERCLIENT(n_user, n_service, n_server)( ":There are " + n_user + " users and " + n_service + " services on " + n_server + " servers\r\n") //251
# define RPL_LUSEROP(n_ops)(n_ops + " :operator(s) online\r\n") //252
# define RPL_LUSERUNKNOWN(n_unknown)(n_unkown + " :unknown connection(s)\r\n") //253
# define RPL_LUSERCHANNELS(n_chan)(_n_chan + " :channels formed\r\n") //254
# define RPL_LUSERME(n_client, n_server)(":I have " + n_client + " clients and " + n_server + " servers\r\n") //255
# define RPL_ADMINME(server)(server + " :Administrative info\r\n") //256
# define RPL_ADMINLOC1(admin_info)(":" + admin_info + "\r\n") //257 (server city, state, country)
# define RPL_ADMINLOC2(admin_info)(":" + admin_info + "\r\n") //258 (institution)
# define RPL_ADMINEMAIL(admin_info)(":" + admin info + "\r\n") //259 (email address REQUIRED)
# define RPL_TRACELOG(logfile, debuglevel)("File " + logfile + " " + debuglevel + "\r\n") //261
# define RPL_TRACEEND(servername, version, debuglevel)(servername +  + " " + version + "" & debuglevel + " :End of TRACE\r\n") //262
# define RPL_TRYAGAIN(command)(command + " :Please wait a while and try again.\r\n") //263
# define RPL_AWAY(nick, message)(nick + ": " + message + "\r\n") //301
# define RPL_USERHOST()("\r\n") //302 ??????
# define RPL_ISON()("\r\n") //303 ??????????
# define RPL_UNAWAY()(":You are no longer marked as being away\r\n") //305
# define RPL_NOWAWAY()(":You have been marked as being away\r\n") //306
# define RPL_WHOISUSER(nick, user, host, realname)(nick + " " + user + " " + host + " * :" + realname + "\r\n") //311
# define RPL_WHOISSERVER()(nick + " " + server + ":" + serverinfo + "\r\n") //312
# define RPL_WHOISOPERATOR(nick)(nick + " :is an IRC operator\r\n") //313
# define RPL_WHOWASUSER()( nick +  + " " + user + " " + host + " * :" + realname + "\r\n") //314 ??????
# define RPL_ENDOFWHO(name)(name + " :End of WHO list\r\n") //315
# define RPL_WHOISIDLE()(nick + " " + integer + " :seconds idle\r\n") //317
# define RPL_ENDOFWHOIS()(nick + " :End of WHOIS list\r\n") //318
# define RPL_WHOISCHANNELS()("\r\n") //319 ?????
# define RPL_LIST(channel, n_visible, topic)(channel + " " + n_visible + " :" + topic + "\r\n") //322
# define RPL_LISTEND()(":End of LIST\r\n") //323
# define RPL_CHANNELMODEIS(cannel, mode, mode_params)(channel +  + " " + mode + " " + mode_params + "\r\n") //324
# define RPL_UNIQOPIS(channel, nickname)(channel + " " + nickname + "\r\n") //325
# define RPL_NOTOPIC(channel)(channel + " :No topic is set\r\n") //331
# define RPL_TOPIC(channel, topic)(channel + " :" + topic + "\r\n") //332
# define RPL_INVITING(channel, nick)(channel + " " + nick + "\r\n") //341
# define RPL_SUMMONING(user)( user + " :Summoning user to IRC\r\n") //342
# define RPL_INVITELIST()("\r\n") //346 ???????
# define RPL_ENDOFINVITELIST(channel)(channel + " :End of channel invite list\r\n") //347
# define RPL_EXCEPTLIST()("\r\n") //348 ??????
# define RPL_ENDOFEXCEPTLIST(channel)(channel + " :End of channel exception list\r\n") //349
# define RPL_VERSION(version, debuglevel, server, comments)(version + "." + debuglevel + " " + server + " :" + comments + "\r\n") //351
# define RPL_WHOREPLY()("\r\n") //352 ??????
# define RPL_NAMREPLY()("\r\n") //353 ???????
# define RPL_LINKS(mask, server, hopcount, serverinfo)(mask +  + " " + server + " :" + hopcount + " " + serverinfo + "\r\n") //364 ????? not sure we need it
# define RPL_ENDOFLINKS(mask)( mask + " :End of LINKS list\r\n") //365
# define RPL_ENDOFNAMES(channel)(channel + " :End of NAMES list\r\n") //366
# define RPL_BANLIST(channel, banmask)(channel +  + " " + banmask + "\r\n") //367
# define RPL_ENDOFBANLIST()("\r\n") //368
# define RPL_ENDOFWHOWAS()(nick + " :End of WHOWAS\r\n") //369
# define RPL_INFO(string)(":" + string + "\r\n") //371
# define RPL_MOTD()(":- " + text + "\r\n") //372
# define RPL_ENDOFINFO()(":End of INFO list\r\n") //374
# define RPL_MOTDSTART()(":- " + server + " Message of the day - \r\n") //375
# define RPL_ENDOFMOTD()(":End of MOTD command\r\n") //376
# define RPL_YOUREOPER()(":You are now an IRC operator\r\n") //381
# define RPL_REHASHING()(config + "file :Rehashing\r\n") //382
# define RPL_YOURESERVICE(servicename)("You are service " + servicename + "\r\n") //383
# define RPL_MYPORTIS()("\r\n") //384
# define RPL_TIME(server, localtime)(server + " :" + localtime + "\r\n") //391
# define RPL_USERSSTART()(":UserID Terminal  Host\r\n") //392
# define RPL_USERS(userbame, ttyline, hostname)(":" + username + " " + ttyline + " " + hostname + "\r\n") //393
# define RPL_ENDOFUSERS()(":End of users\r\n") //394
# define RPL_NOUSERS()(":Nobody logged in\r\n") //395

#endif