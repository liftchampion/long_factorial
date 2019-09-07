/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_factorial.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 04:33:39 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 04:33:39 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <deque>
#include <iostream>

class BigInt {
public:
	BigInt();
	explicit BigInt(__uint128_t val);
	BigInt& operator=(const BigInt& other) = default;
	[[nodiscard]] size_t len() const;
	[[nodiscard]] bool is_zero() const;
	size_t operator[](size_t idx) const;
	size_t& operator[](size_t idx);
	BigInt& operator+=(const BigInt& other);
	BigInt& operator+=(size_t other);
	BigInt& operator*=(size_t other);
	BigInt& operator*=(const BigInt& other);
	bool operator==(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator<=(size_t other) const;
private:
	std::deque<size_t> data;
	static const size_t radix = 1'000'000'000'000'000'000lu;
};

std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
