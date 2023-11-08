/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/08 12:57:48 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLY_HPP
# define REPLY_HPP

# include <string>

//void	sendRPL(int const user_fd, std::string user_buffer);

# define USER_ID(nickname, username, host) (nickname + "!" + username + "@" + host)

/*Registration*/

# define RPL_WELCOME(servername, nick, user, host)(":" + servername + " 001 " + nick + " Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n") //001
# define RPL_YOURHOST(servername, version)(":" + servername + " 002 * Your host is " + servername + ", running version " + version + "\r\n") //002
# define RPL_CREATED(servername, date)(":" + servername + " 003 " + servername + " :This server was created " + date + "\r\n") //003
# define RPL_MYINFO(servername, version, umodes, cmodes)(":" + servername + " 004 " + "* " + servername + " " + version + " " + umodes + " " + cmodes + "\r\n") //004
# define RPL_BOUNCE(servername, port)(":" + servername + " 005 Try server " + server name + ", port " + port + "\r\n") //005
# define RPL_TRACELINK(servername, version, debuglevel,  destination, next_server, protocolversion, linkuptime, bssendq, usbackq)\
("Link " + version + " & " debug level + " " + destination + " " + nextserver + " V" + protocolversion + linkuptime + " " + bssendq + " " +  ussendq + "\r\n") //200
# define RPL_TRACECONNECTING(servername, class, server)(":" + servername + " 201 Try. " + class + " " + server + "\r\n") //201
# define RPL_TRACEHANDSHAKE(servername, class, server)(":" + servername + " 202 H.S. " + class + " " + server + "\r\n") //202
# define RPL_TRACEUNKNOWN(servername, class, client_ip)(":" + servername + " 203 ???? " + class + " [" + client_ip + "]  \r\n") //203 client IP in dot form
# define RPL_TRACEOPERATOR(servername, class, nick)(":" + servername + " 204 Oper " + class + " " + nick + "\r\n") //204
# define RPL_TRACEUSER(servername, class, nick)(":" + servername + " 205 User " + class + " " + nick + "\r\n") //205
# define RPL_TRACESERVICE(servername, class, name, type, activetype)(":" + servername + " 207 Service " + class + " " + name + " " + type + " " + activetype + "\r\n") //207
# define RPL_TRACENEWTYPE(servername, newtype, client_name)(":" + servername + " 208 " + newtype + " 0 " + client_name + "\r\n") //208
# define RPL_TRACECLASS(servername, class, count)(":" + servername + " 209 Class " + class + " " + count + "\r\n") //209
# define RPL_STATSLINKINFO(servername, linkname, sendq, sentmsg, sentkbyte, recvmesg, recvkbyte, timme_open)\
(linkname + " " + sendq + " " + sentmsg + sentkbyte + " " + recvmesg + recvkbyte + " " + time_open + "\r\n") //211
# define RPL_STATSCOMMANDS(servername, command, count, b_byte, remote_count)(":" + servername + " 212 " + command + " " + count + " " + n_byte + " " + remote_count + "\r\n") //212
# define RPL_ENDOFSTATS(servername, stats_letter)(":" + servername + " 219 " + stats_letter + " :End of STATS report\r\n") //219
# define RPL_UMODEIS(servername, user, modestring)(":" + servername + " 221 " + user + " " + modestring + "\r\n") //221
# define RPL_SERVLIST(servername, name, server, mask, type, hopcount, info)(":" + servername + " 234 " + name + " " + server + " " + mask + " " + type + " " + hopcount + " " + info + "\r\n") //234
# define RPL_SERVLISTEND(servername, mask, type)(":" + servername + " 235 " + mask + " " + type + " :End of service listing\r\n") //235
# define RPL_STATSUPTIME(servername, serveruptime)(":" + servername + " 242 :Server Up serveruptime\r\n") //242 as %d days %d:%02d:%02d
# define RPL_STATSOLINE(servername)(":" + servername + " 243 " + + "\r\n") //243 ??????
# define RPL_LUSERCLIENT(servername, n_user, n_service, n_server)(":" + servername + " 251 " +  ":There are " + n_user + " users and " + n_service + " services on " + n_server + " servers\r\n") //251
# define RPL_LUSEROP(servername, n_ops)(":" + servername + " 252 " + n_ops + " :operator(s) online\r\n") //252
# define RPL_LUSERUNKNOWN(servername, n_unknown)(":" + servername + " 253 " + n_unkown + " :unknown connection(s)\r\n") //253
# define RPL_LUSERCHANNELS(servername, n_chan)(":" + servername + " 254 " + _n_chan + " :channels formed\r\n") //254
# define RPL_LUSERME(servername, n_client, n_server)(":" + servername + " 255 :I have " + n_client + " clients and " + n_server + " servers\r\n") //255
# define RPL_ADMINME(servername, server)(":" + servername + " 256 " + server + " :Administrative info\r\n") //256
# define RPL_ADMINLOC1(admin_info)(":" + servername + " 257 :" + admin_info + "\r\n") //257 server city, state, country)
# define RPL_ADMINLOC2(admin_info)(":" + servername + " 258 :" + admin_info + "\r\n") //258 institution)
# define RPL_ADMINEMAIL(servername, admin_info)(":" + servername + " 259 :" + admin info + "\r\n") //259 email address REQUIRED)
# define RPL_TRACELOG(servername, logfile, debuglevel)(":" + servername + " 261 File " + logfile + " " + debuglevel + "\r\n") //261
# define RPL_TRACEEND(servername, version, debuglevel)(":" + servername + " 262 " + servername +  + " " + version + "" & debuglevel + " :End of TRACE\r\n") //262
# define RPL_TRYAGAIN(servername, command)(":" + servername + " 263 " + command + " :Please wait a while and try again.\r\n") //263
# define RPL_AWAY(servername, nick, recipient, message)(":" + servername + " 301 " + nick + " " + recipient+ " :" + message + "\r\n") //301
# define RPL_USERHOST(servername)(":" + servername + " 302 \r\n") //302 ??????
# define RPL_ISON(servername)(":" + servername + " 303 \r\n") //303 ??????????
# define RPL_UNAWAY(servername)(":" + servername + " 305 :You are no longer marked as being away\r\n") //305
# define RPL_NOWAWAY(servername)(":" + servername + " 306 :You have been marked as being away\r\n") //306
# define RPL_WHOISUSER(servername, nick, user, host, realname)(":" + servername + " 311 " + nick + " " + user + " " + host + " * :" + realname + "\r\n") //311
# define RPL_WHOISSERVER(servername)(":" + servername + " 312 " + nick + " " + server + ":" + serverinfo + "\r\n") //312
# define RPL_WHOISOPERATOR(servername, nick)(":" + servername + " 313 " + nick + " :is an IRC operator\r\n") //313
# define RPL_WHOWASUSER(servername)(":" + servername + " 314 " +  nick +  + " " + user + " " + host + " * :" + realname + "\r\n") //314 ??????
# define RPL_ENDOFWHO(servername, nick, channel)(":" + servername + " 315 " + nick + " " + channel + " :End of /WHO list\r\n") //315
# define RPL_ENDOFWHO2(servername, nick)(":" + servername + " 315 " + nick + " :End of /WHO list\r\n") //315
# define RPL_WHOISIDLE(servername)(":" + servername + " 317 " + nick + " " + integer + " :seconds idle\r\n") //317
# define RPL_ENDOFWHOIS(servername, nick)(":" + servername + " 318 " + nick + " :End of /WHOIS list\r\n") //318
# define RPL_WHOISCHANNELS(servername)(":" + servername + " 319 \r\n") //319 ?????
# define RPL_LIST(servername, channel, n_visible, topic)(":" + servername + " 322 " + channel + " " + n_visible + " :" + topic + "\r\n") //322
# define RPL_LISTEND(servername)(":" + servername + " 323 :End of LIST\r\n") //323
# define RPL_CHANNELMODEIS(servername, user, channel, mode, mode_params)(":" + servername + " 324 " + user + " " + channel + " " + mode + " " + mode_params + "\r\n") //324
# define RPL_UNIQOPIS(servername, channel, nickname)(":" + servername + " 325 " + channel + " " + nickname + "\r\n") //325
# define RPL_NOTOPIC(servername, channel)(":" + servername + " 331 " + channel + " :No topic is set\r\n") //331
# define RPL_TOPIC(servername, nick, channel, topic)(":" + servername + " 332 " + nick + " " + channel + " :" + topic + "\r\n") //332
# define RPL_INVITING(servername, inviter, invited, channel)(":" + servername + " 341 " + inviter + " " + invited + " " + channel + "\r\n") //341
# define RPL_SUMMONING(servername, user)(":" + servername + " 342 " +  user + " :Summoning user to IRC\r\n") //342
# define RPL_INVITELIST(servername)(":" + servername + " 346 \r\n") //346 ???????
# define RPL_ENDOFINVITELIST(servername, channel)(":" + servername + " 347 " + channel + " :End of channel invite list\r\n") //347
# define RPL_EXCEPTLIST(servername)(":" + servername + " 348 \r\n") //348 ??????
# define RPL_ENDOFEXCEPTLIST(servername, channel)(":" + servername + " 349 " + channel + " :End of channel exception list\r\n") //349
# define RPL_VERSION(servername, version, debuglevel, server, comments)(":" + servername + " 351 " + version + "." + debuglevel + " " + server + " :" + comments + "\r\n") //351
# define RPL_WHOREPLY(servername)(":" + servername + " 352 " + nick + " " + channel + " " + username + " " + host + " " + servername + " " + nick + " " + status + " :0 " + realname + "\r\n")
# define RPL_NAMREPLY(servername, user, channel, userlist)(":" + servername + " 353 " + user + " @ " + channel + " :" + userlist + "\r\n") //353
# define RPL_LINKS(servername, mask, server, hopcount, serverinfo)(":" + servername + " 364 " + mask +  + " " + server + " :" + hopcount + " " + serverinfo + "\r\n") //364 ????? not sure we need it
# define RPL_ENDOFLINKS(servername, mask)(":" + servername + " 365 " +  mask + " :End of LINKS list\r\n") //365
# define RPL_ENDOFNAMES(servername, user, channel)(":" + servername + " 366 " + user + " " + channel + " :End of /NAMES list\r\n") //366
# define RPL_BANLIST(servername, channel, banmask)(":" + servername + " 367 " + channel +  + " " + banmask + "\r\n") //367
# define RPL_ENDOFBANLIST(servername, user, channel)(":" + servername + " 368 " + user + " " + channel + " :End of Channel Banlist\r\n") //368
# define RPL_ENDOFWHOWAS(servername)(":" + servername + " 369 " + nick + " :End of /WHOWAS\r\n") //369
# define RPL_INFO(servername, string)(":" + servername + " 371 :" + string + "\r\n") //371
# define RPL_MOTD(servername, text)(":" + servername + " 372 :- " + text + "\r\n") //372
# define RPL_ENDOFINFO(servername)(":" + servername + " 374 :End of INFO list\r\n") //374
# define RPL_MOTDSTART(servername)(":" + servername + " 375 :- " + servername + " Message of the day - \r\n") //375
# define RPL_ENDOFMOTD(servername)(":" + servername + " 376 :End of MOTD command\r\n") //376
# define RPL_YOUREOPER(servername, nick)(":" + servername + " 381 " + nick + " :You are now an IRC operator\r\n") //381
# define RPL_REHASHING(servername)(":" + servername + " 382 " + config + "file :Rehashing\r\n") //382
# define RPL_YOURESERVICE(servername, servicename)(":" + servername + " 383 You are service " + servicename + "\r\n") //383
# define RPL_MYPORTIS(servername)(":" + servername + " 384 \r\n") //384
# define RPL_TIME(servername, server, localtime)(":" + servername + " 391 " + server + " :" + localtime + "\r\n") //391
# define RPL_USERSSTART(servername)(":" + servername + " 392 :UserID Terminal  Host\r\n") //392
# define RPL_USERS(servername, userbame, ttyline, hostname)(":" + servername + " 393 :" + username + " " + ttyline + " " + hostname + "\r\n") //393
# define RPL_ENDOFUSERS(servername)(":" + servername + " 394 :End of users\r\n") //394
# define RPL_NOUSERS(servername)(":" + servername + " 395 :Nobody logged in\r\n") //395

# define RPL_NICK(ouser, uuser, host, user)(":" + ouser + "!" + uuser + "@" + host + " NICK " +  user + "\r\n")
# define RPL_CAP(servername, type, text)(":" + servername + " CAP * " + type + " :" + text + "\r\n")

#endif
