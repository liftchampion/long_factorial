/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 22:04:26 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/06 22:04:26 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <deque>
#include "big_int.h"

using namespace std;

BigInt::BigInt() : data(1, 0) {};

BigInt::BigInt(__uint128_t val) {
	while (val >= radix) {
		data.push_back(val % radix);
		val /= radix;
	}
	data.push_back(val);
}

size_t BigInt::len() const {
	return data.size();
}

bool BigInt::is_zero() const {
	return (len() == 1 && data[0] == 0);
}

size_t BigInt::operator[](size_t idx) const{
	return idx < len() ? data[idx] : 0;
}

size_t& BigInt::operator[](size_t idx){
	if (len() <= idx) {
		data.resize(idx + 1, 0);
	}
	return data[idx];
}

BigInt& BigInt::operator+=(const BigInt& other) {
	size_t carry = 0;
	size_t go_to = max(other.len(), this->len());
	size_t intermediate_res;

	for (size_t i = 0; i < go_to || carry; ++i) {
		intermediate_res = (*this)[i] + other[i] + carry;
		carry = intermediate_res / radix;
		intermediate_res %= radix;
		(*this)[i] = intermediate_res;
	}
	return *this;
}

BigInt& BigInt::operator+=(size_t other) {
	BigInt other_bigint(other);
	*this += other_bigint;
	return *this;
}

BigInt& BigInt::operator*=(size_t other) {
	if (this->is_zero()) { return *this; }
	if (!other) { *this = BigInt(0); return *this; }
	if (other == radix) { this->data.push_front(0); return *this; }

	BigInt res(0);

	for (int i = static_cast<int>(this->len()) - 1; i >= 0; --i) {
		res *= radix;
		res += BigInt(static_cast<__uint128_t>((*this)[i]) * other);
	}
	*this = res;
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
	if (this->is_zero()) { return *this; }
	if (other.is_zero()) { *this = BigInt(0); return *this; }

	BigInt res(0);
	BigInt tmp_res;

	for (int i = static_cast<int>(other.len()) - 1; i >= 0; --i) {
		res *= radix;
		tmp_res = *this;
		tmp_res *= other[i];
		res += tmp_res;
	}
	*this = res;
	return *this;
}

bool BigInt::operator==(const BigInt& other) const {
	if (this->len() != other.len()) { return false; }

	for (size_t i = 0; i < this->len(); ++i) {
		if ((*this)[i] != other[i]) {
			return false;
		}
	}
	return true;
}

bool BigInt::operator<(const BigInt& other) const {
	if (this->len() != other.len()) { return this->len() < other.len(); }

	for (int i = static_cast<int>(this->len()) - 1; i >= 0 ; --i) {
		if ((*this)[i] >= other[i]) {
			return false;
		}
	}
	return true;
}

bool BigInt::operator<=(size_t other) const {
	BigInt other_bi(other);
	if (this->len() != other_bi.len()) { return this->len() < other_bi.len(); }

	for (int i = static_cast<int>(this->len()) - 1; i >= 0 ; --i) {
		if ((*this)[i] >= other_bi[i]) {
			return false;
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const BigInt& bigint){
	bool is_first = true;
	for (int i = static_cast<int>(bigint.len()) - 1; i >= 0; --i) {
		if (is_first) {
			os << bigint[i];
			is_first = false;
		} else {
			os << setw(18) << setfill('0') << bigint[i];
		}
	}
	return os;
}
