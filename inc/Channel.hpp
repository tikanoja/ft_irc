/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:23 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/31 08:42:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <sstream>
# include <cstdlib>
# include "Uvector.hpp"

class User;

class Channel
{
	public:

		enum chanModes {
			invite = 0x01, 		// Set/remove Invite-only channel;
			topic_rest = 0x02, 		// Set/remove the restrictions of the TOPIC command to chanops
			key = 0x04, 			// Set/remove the channel key (password)
			secret = 0x08, 			// Set/remove the channel key (password)
			ops = 0x10, 			// Give/take channel operator privilege
			limit = 0x20 			// Set/remove the user limit to channel
		};

		Channel(const std::string name);
		Channel(Channel const& src);
		~Channel();
		Channel &		operator=(Channel const& rhs);

		//getters
		std::string 	getName();
		std::string 	getTopic();
		Uvector*		getMembers();
		Uvector*		getChops();
		Uvector*		getInvitelist();
		bool			getUserlimit();
		std::string		getKey();
		chanModes		getMode();
		std::string		getChanModes();
		std::string		getChanStr();

		//setters
		void			setTopic(std::string newTopic);
		void 			setUserlimit(std::string limitstr);
		void			setKey(std::string key);
		void			setChop(std::string target, Channel* chan);
		void			unsetChop(std::string target, Channel* chan);
		bool			setMode(chanModes mode);
		bool			unsetMode(chanModes mode);
		
		std::string		setBatchMode(std::string const & modes, size_t *index);
		std::string		unsetBatchMode(std::string const & modes, size_t *index);
		
		//utils
		void			broadcastToChannel(std::string message, User* sender);
		bool			isChop(User& user);
		void			removeFromChops(User& user);
		void			removeFromInvlist(User& user);
		void			removeFromMembers(User& user);

	private:
		Channel();
		std::string		p_name;
		std::string 	p_topic;
		std::string 	p_key;
		unsigned int	p_maxusers;
		Uvector			p_invitelist;
		Uvector			p_members;
		Uvector			p_chops;
		chanModes		p_mode;
};

#endif
