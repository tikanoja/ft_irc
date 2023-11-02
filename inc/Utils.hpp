/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:25:37 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 10:10:02 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string>	split(const std::string& str, char c);
bool						matchWildcard(const std::string& pattern, const std::string& str);
int							isValidWildchard(const std::string& pattern);

#endif
