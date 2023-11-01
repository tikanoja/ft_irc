/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:25:37 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 12:53:38 by djagusch         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
#endif
