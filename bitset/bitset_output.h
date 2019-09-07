/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_output.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 05:09:04 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 05:09:04 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <vector>
#include "bitset_arithmetic.h"
#include "bitset_cmp.h"

template <size_t size>
std::ostream& operator<<(std::ostream& os, std::bitset<size> bs)
{
	std::vector<size_t>				res;
	static const std::bitset<size>	radix(10'000'000'000'000'000'000u);
	static const std::bitset<size>	zero(0);
	bool 							is_first = true;

	while (bs != zero) {
		auto division_result = divide(bs, radix);
		res.push_back(division_result.second);
		bs = division_result.first;
	}
	reverse(res.begin(), res.end());
	for (const auto item : res) {
		if (is_first) {
			std::cout << item;
			is_first = false;
		} else{
			std::cout  << std::setw(19) << std::setfill('0') << item;
		}
	}
	return os;
}
