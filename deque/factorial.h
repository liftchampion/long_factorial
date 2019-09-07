/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factorial.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 04:42:20 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 04:42:20 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "big_int.h"

BigInt factorial(int n);

std::vector<BigInt> small_multiplies(int n);

BigInt	big_multiplies(std::vector<BigInt> multipliers);

static std::vector<BigInt> default_vector;
template <typename T>
void	divide_and_conquer_multiply(std::vector<T>& multipliers,
									std::vector<BigInt>& big_multipliers = default_vector)
{
	size_t			size;
	std::vector<T>	tmp;

	tmp.reserve(multipliers.size() + 1);
	while (multipliers.size() > 1) {
		size = multipliers.size();
		for (size_t i = 0; i < size - 1; i += 2) {
			multipliers[i] *= multipliers[i + 1];
			if (typeid(T) == typeid(BigInt) ||
				multipliers[i] <= UINT32_MAX)
			{
				tmp.emplace_back(std::move(multipliers[i]));
			}
			else {
				big_multipliers.emplace_back(BigInt(multipliers[i]));
			}
		}
		if (size % 2) {
			tmp.push_back(multipliers[size - 1]);
		}
		multipliers.swap(tmp);
		tmp.clear();
	}
	if (!multipliers.empty() && typeid(T) != typeid(BigInt)) {
		big_multipliers.emplace_back(BigInt(multipliers[0]));
	}
}
