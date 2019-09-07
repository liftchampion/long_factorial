/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_arithmetic.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 05:03:03 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 05:03:03 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <bitset>
#include <vector>
#include "bitset_cmp.h"

static inline bool sum_bits(bool b1, bool b2, bool& carry)
{
	bool sum = (b1 ^ b2) ^ carry;

	carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
	return sum;
}

template <size_t size>
std::bitset<size>& operator+=(std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	bool carry = false;

	for (size_t i = 0; i < size; ++i) {
		lhs[i] = sum_bits(lhs[i], rhs[i], carry);
	}
	return lhs;
}

template <size_t size>
std::bitset<size>& operator*=(std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	std::bitset<size> tmp = lhs;

	lhs.reset();
	if (tmp.count() < rhs.count()) {
		for (size_t i = 0; i < size; ++i) {
			if (tmp[i]) {
				lhs += rhs << i;
			}
		}
	}
	else {
		for (size_t i = 0; i < size; ++i) {
			if (rhs[i]) {
				lhs += tmp << i;
			}
		}
	}
	return lhs;
}

template <size_t size>
std::bitset<size>& operator*=(std::bitset<size>& lhs, int rhs)
{
	std::bitset<size> right(rhs);

	return lhs *= right;
}

template <size_t size>
std::bitset<size>& operator-=(std::bitset<size>& lhs, const std::bitset<size>& rhs)
{
	bool borrow = false;

	for (size_t i = 0; i < size; i++) {
		if (borrow) {
			if (lhs[i]) {
				lhs[i] = rhs[i];
				borrow = rhs[i];
			} else {
				lhs[i] = !rhs[i];
				borrow = true;
			}
		} else {
			if (lhs[i]) {
				lhs[i] = !rhs[i];
				borrow = false;
			} else {
				lhs[i] = rhs[i];
				borrow = rhs[i];
			}
		}
	}
	return lhs;
}

template <size_t size>
int operator/(std::bitset<size> lhs, const std::bitset<size>& rhs)
{
	if (!rhs.count()){
		throw std::domain_error("division by zero undefined");
	}
	int res = 0;
	while (lhs >= rhs) {
		++res;
		lhs -= rhs;
	}
	return (res);
}

template <size_t size>
size_t operator%(std::bitset<size> lhs, std::bitset<size> rhs)
{
	std::bitset<size> without_mod = rhs;
	without_mod *= lhs / rhs;

	lhs -= without_mod;
	return (lhs.to_ullong());
}

template <size_t size>
std::pair<std::bitset<size>, size_t>
        divide(std::bitset<size> dividend, std::bitset<size> divisor)
{
	std::bitset<size>	quotient(0);
	std::bitset<size>	curr_quotient(0);
	std::bitset<size>	original_divisor(divisor);
	size_t			reminder;

	while (dividend > divisor) {
		curr_quotient = 1;
		while (divisor <= dividend) {
			divisor <<= 1u;
			curr_quotient <<= 1u;
		}
		if (dividend < divisor) {
			divisor >>= 1u;
			curr_quotient >>= 1u;
		}
		dividend -= divisor;
		quotient += curr_quotient;
		divisor = original_divisor;
	}
	if (dividend == divisor) {
		reminder = 0;
		quotient += std::bitset<size>(1);
	} else {
		reminder = dividend.to_ullong();
	}
	return make_pair(quotient, reminder);
}
