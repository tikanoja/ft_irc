/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:23 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/27 17:16:54 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include "Uvector.hpp"

class User;

class Channel
{
	public:
		Channel(const std::string name);
		Channel(Channel const& src);
		~Channel();
		Channel &		operator=(Channel const& rhs);

		//getters
		std::string 	getName();
		std::string 	getTopic();
		Uvector*		getMembers();
		Uvector*		getInvitelist();

		//setters
		void			setTopic(std::string newTopic);
		void			toggleMode(); //??

		//utils
		void			broadcastToChannel(std::string message, User* sender);

	private:
		Channel();
		std::string	p_name;
		std::string p_topic;
		std::string p_key;
		int			p_maxusers;
		Uvector		p_invitelist;
		Uvector		p_members;
		Uvector		p_chops;

		//modes
		bool		p_inviteonly;
		bool		p_topicrestricted;
		bool		p_keyneeded;
		bool		p_userlimit;
};

#endif
