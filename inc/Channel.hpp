/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:23 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/04 13:38:52 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <sstream>
# include <cstdlib>
# include "Error.hpp"
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
			limit = 0x10 			// Set/remove the user limit to channel
		};

		Channel(const std::string name);
		~Channel();

		//getters
		std::string const & 	getName()const;
		std::string const & 	getTopic()const;
		Uvector*				getChops();
		Uvector*				getMembers();
		Uvector*				getInvitelist();
		bool					getUserlimit()const;
		std::string const &	 	getKey() const;
		unsigned int			getMode() const;
		std::string				getChanModes()const;
		std::string				getChanStr()const;
		size_t					getMaxusers() const;
		std::string				getNicks() const;

		//setters
		void			setTopic(std::string newTopic);
		void			setKey(std::string key);
		int				setChop(std::string target);
		int				unsetChop(std::string target);
		bool 			setUserlimit(std::string limitstr);
		bool			setMode(chanModes mode);
		bool			unsetMode(chanModes mode);
		
		std::string		setBatchMode(User & user, std::vector<std::string> const & modes, size_t & word,
										size_t & character, std::vector<size_t> & indeces);
		std::string		unsetBatchMode(User & user, std::vector<std::string> const & modes, size_t & word,
										size_t &character, std::vector<size_t> & indeces);

		//utils
		void			broadcastToChannel(std::string message, User* sender);
		bool			isChop(User& user);
		void			removeFromChops(User& user);
		void			removeFromInvlist(User& user);
		void			removeFromMembers(User& user);
		void			reopChannel(std::string const & servername);

	private:
		Channel();
		std::string		p_name;
		std::string 	p_topic;
		std::string 	p_key;
		unsigned int	p_maxusers;
		unsigned int	p_curusers;
		Uvector			p_invitelist;
		Uvector			p_members;
		Uvector			p_chops;
		unsigned int	p_mode;
};

#endif
