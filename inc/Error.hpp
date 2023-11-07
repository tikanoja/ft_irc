/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:58:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 08:16:05 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ERROR_HPP
# define ERROR_HPP

# define ERR_NOSUCHNICK(servername, nickname, type)(":" + servername + " 401 " + nickname + " :No such " + type + "\r\n") //401
# define ERR_NOSUCHSERVER(servername)(":" + servername + " 402 " + servername + " :No such server" + "\r\n") //402
# define ERR_NOSUCHCHANNEL(servername, user, channelname)(":" + servername + " 403 " + user + " " + channelname + " :No such channel" + "\r\n") //403
# define ERR_CANNOTSENDTOCHAN(servername, channelname)(":" + servername + " 404 " + channelname + " :Cannot send to channel" + "\r\n") //404
# define ERR_TOOMANYCHANNELS(servername, channelname)(":" + servername + " 405 " + channelname + " :You have joined too many channels" + "\r\n") //405
# define ERR_WASNOSUCHNICK(servername, nickname)(":" + servername + " 406 " + nickname + " :There was no such nickname" + "\r\n") //406
# define ERR_TOOMANYTARGETS(servername, target, errorcode, abortmsg)(":" + servername + " 407 " + target + " :" + errorcode + "recipients." + abortmsg + "\r\n") //407
# define ERR_NOSUCHSERVICE(servername, servicename)(":" + servername + " 408 " + servicename + " :No such service" + "\r\n") //408
# define ERR_NOORIGIN(servername)(":" + servername + " 409 :No origin specified" + "\r\n") //409
# define ERR_NORECIPIENT(servername, command)(":" + servername + " 411 " +  ":No recipient given (" + command + ")" + "\r\n") //411
# define ERR_NOTEXTTOSEND(servername)(":" + servername + " 412 :No text to send" + "\r\n") //412
# define ERR_NOTOPLEVEL(servername, mask)(":" + servername + " 413 " + mask + " :No toplevel domain specified" + "\r\n") //413
# define ERR_WILDTOPLEVEL(servername, mask)(":" + servername + " 414 " + mask + " :Wildcard in toplevel domain" + "\r\n") //414
# define ERR_BADMASK(servername, mask)(":" + servername + " 415 " + mask + " :Bad Server/host mask" + "\r\n") //415
# define ERR_UNKNOWNCOMMAND(servername, command)(":" + servername + " 421 " + command + " :Unknown command" + "\r\n") //421
# define ERR_NOMOTD(servername, user)(":" + servername + " 422 " + user + " :MOTD File is missing" + "\r\n") //422
# define ERR_NOADMININFO(servername, server)(":" + servername + " 423 " + server + " :No administrative info available" + "\r\n") //423
# define ERR_FILEERROR(servername, fileop, file)(":" + servername + " 424 :File error doing " + fileop + " on " + file + "" + "\r\n") //424
# define ERR_NONICKNAMEGIVEN(servername)(":" + servername + " 431  :No nickname given" + "\r\n") //431
# define ERR_ERRONEUSNICKNAME(servername, nick)(":" + servername + " 432 " + nick + " :Erroneous nickname" + "\r\n") //432
# define ERR_NICKNAMEINUSE(servername, nick)(":" + servername + " 433 * " + nick + " :Nickname is already in use" + "\r\n") //433
# define ERR_NICKCOLLISION(servername, nick, user, host)(":" + servername + " 436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "" + "\r\n") //436
# define ERR_UNAVAILRESOURCE(servername, nick, label)(":" + servername + " 437 " +  nick + " :" + label + " is temporarily unavailable" + "\r\n") //437
# define ERR_USERNOTINCHANNEL(servername, nick, channel)(":" + servername + " 441 " + channel + " " + nick  + " :They aren't on that channel" + "\r\n") //441
# define ERR_NOTONCHANNEL(servername, channel)(":" + servername + " 442 " + channel + " :You're not on that channel" + "\r\n") //442
# define ERR_USERONCHANNEL(servername, user, channel)(":" + servername + " 443 " + channel + " " + user + " :is already on channel" + "\r\n") //443
# define ERR_NOLOGIN(servername, user)(":" + servername + " 444 " + user + " :User not logged in" + "\r\n") //444
# define ERR_SUMMONDISABLED(servername)(":" + servername + " 445 :SUMMON has been disabled" + "\r\n") //445
# define ERR_USERSDISABLED(servername)(":" + servername + " 446 :USERS has been disabled" + "\r\n") //446
# define ERR_NOTREGISTERED(servername,  command)(":" + servername + " 451 * " + command + " :You have not registered" + "\r\n") //451
# define ERR_NEEDMOREPARAMS(servername, command)(":" + servername + " 461 " + command + " :Not enough parameters" + "\r\n") //461
# define ERR_ALREADYREGISTRED(servername)(":" + servername + " 462 " +  ":Unauthorized command (already registered)" + "\r\n") //462
# define ERR_NOPERMFORHOST(servername)(":" + servername + " 463 :Your host isn't among the privileged" + "\r\n") //463
# define ERR_PASSWDMISMATCH(servername)(":" + servername + " 464 * :Password incorrect" + "\r\n") //464
# define ERR_KEYSET(servername, channel)(":" + servername + " 467 " + channel + " :Channel key already set" + "\r\n") //467
# define ERR_CHANNELISFULL(servername, user, channel)(":" + servername + " 471 " + user + " " + channel + " :Cannot join channel (+l)" + "\r\n") //471
# define ERR_UNKNOWNMODE(servername, user, char, channel)(":" + servername + " 472 " + user + " " + char + " :is unknown mode char to me for " + channel + "" + "\r\n") //472
# define ERR_INVITEONLYCHAN(servername, user, channel)(":" + servername + " 473 " + user + " " + channel + " :Cannot join channel (+i)" + "\r\n") //473
# define ERR_BADCHANNELKEY(servername, user, channel)(":" + servername + " 475 " + user + " " + channel + " :Cannot join channel (+k)" + "\r\n") //475
# define ERR_BADCHANMASK(servername, channel)(":" + servername + " 476 " +  channel + " :Bad Channel Mask" + "\r\n") //476
# define ERR_NOCHANMODES(servername, channel)(":" + servername + " 477 " + channel + " :Channel doesn't support modes" + "\r\n") //477
# define ERR_BANLISTFULL(servername, channel, char)(":" + servername + " 478 " + channel + "" + char + " :Channel list is full" + "\r\n") //478
# define ERR_NOPRIVILEGES(servername)(":" + servername + " 481 " +  ":Permission Denied- You're not an IRC operator" + "\r\n") //481
# define ERR_CHANOPRIVSNEEDED(servername, channel)(":" + servername + " 482 " + channel + " :You're not channel operator" + "\r\n") //482
# define ERR_CANTKILLSERVER(servername)(":" + servername + " 483 :You can't kill a server!" + "\r\n") //483
# define ERR_RESTRICTED(servername)(":" + servername + " 484 :Your connection is restricted!" + "\r\n") //484
# define ERR_UNIQOPPRIVSNEEDED(servername)(":" + servername + " 485 :You're not the original channel operator" + "\r\n") //485
# define ERR_NOOPERHOST(servername)(":" + servername + " 491 :No O-lines for your host" + "\r\n") //491
# define ERR_UMODEUNKNOWNFLAG(servername)(":" + servername + " 501 :Unknown MODE flag" + "\r\n") //501
# define ERR_USERSDONTMATCH(servername, user)(":" + servername + " 502 " + user + " :Cannot change mode for other users" + "\r\n") //502
# define ERR_INVALIDCAPCMD(servername, nick, type)(":" + servername + " 410 " + (nick == "" ? nick : "*") + " " + type + " :Invalid CAP command" + "\r\n")

#endif
