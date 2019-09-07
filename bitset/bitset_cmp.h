/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_cmp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 05:07:30 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 05:07:30 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <bitset>

template <size_t size>
bool operator<(const std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return rhs[i];
		}
	}
	return false;
}

template <size_t size>
bool operator<=(const std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return rhs[i];
		}
	}
	return true;
}

template <size_t size>
bool operator>(const std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return lhs[i];
		}
	}
	return false;
}

template <size_t size>
bool operator>=(const std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return lhs[i];
		}
	}
	return true;
}

template <size_t size>
bool operator==(const std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template <size_t size>
bool operator!=(const std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return true;
		}
	}
	return false;
}
