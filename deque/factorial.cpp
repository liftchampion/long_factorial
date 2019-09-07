/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factorial.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 04:41:26 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 04:41:26 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"
#include "factorial.h"
#include <vector>

using namespace std;

BigInt factorial(int n) {
	if (n < 0) { throw invalid_argument("Negative factorial is not defined"); }
	if (n == 0) { return BigInt(1); }
	return (big_multiplies(small_multiplies(n)));
}

vector<BigInt> small_multiplies(int n) {
	vector<uint64_t> multipliers_small(n);
	vector<uint64_t> tmp;
	vector<BigInt>   multipliers_big;

	tmp.reserve(n / 2 + 1);
	multipliers_big.reserve(n / 4 + 1);
	for (int i = 0; i < n; ++i) {
		multipliers_small[i] = i + 1;
	}
	divide_and_conquer_multiply(multipliers_small, multipliers_big);
	return (multipliers_big);
}

BigInt	big_multiplies(vector<BigInt> multipliers)
{
	divide_and_conquer_multiply(multipliers);
	return multipliers[0];
}
