/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itprime_1.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:59:24 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/05 16:59:24 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bitset>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

static inline bool sum_bits(bool b1, bool b2, bool& carry)
{
	bool sum = (b1 ^ b2) ^ carry;

	carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
	return sum;
}

template <size_t size>
bitset<size>& operator+=(bitset<size>& lhs, const bitset<size>& rhs)
{
	bool carry = false;

	for (size_t i = 0; i < size; ++i) {
		lhs[i] = sum_bits(lhs[i], rhs[i], carry);
	}
	return lhs;
}

template <size_t size>
bitset<size>& operator*=(bitset<size>& lhs, const bitset<size>& rhs)
{
	bitset<size> tmp = lhs;

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
bitset<size>& operator*=(bitset<size>& lhs, int rhs)
{
	bitset<size> right(rhs);

	return lhs *= right;
}

template <size_t size>
bitset<size>& operator-=(bitset<size>& lhs, const bitset<size>& rhs)
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
bool operator<(const bitset<size>& lhs, const bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return rhs[i];
		}
	}
	return false;
}

template <size_t size>
bool operator<=(const bitset<size>& lhs, const bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return rhs[i];
		}
	}
	return true;
}

template <size_t size>
bool operator>(const bitset<size>& lhs, const bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return lhs[i];
		}
	}
	return false;
}

template <size_t size>
bool operator>=(const bitset<size>& lhs, const bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return lhs[i];
		}
	}
	return true;
}

template <size_t size>
bool operator==(const bitset<size>& lhs, const bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template <size_t size>
bool operator!=(const bitset<size>& lhs, const bitset<size>& rhs)
{
	for (int i = size; i >= 0; --i) {
		if (lhs[i] != rhs[i]) {
			return true;
		}
	}
	return false;
}

template <size_t size>
int operator/(bitset<size> lhs, const bitset<size>& rhs)
{
	if (!rhs.count()){
		throw std::domain_error("division by zero undefined"); // todo check exc type
	}
	int res = 0;
	while (lhs >= rhs) {
		++res;
		lhs -= rhs;
	}
	return (res);
}

template <size_t size>
size_t operator%(bitset<size> lhs, bitset<size> rhs)
{
	bitset<size> without_mod = rhs;
	without_mod *= lhs / rhs;

	lhs -= without_mod;
	return (lhs.to_ullong());
}

template <size_t size>
pair<bitset<size>, size_t> divide(bitset<size> dividend, bitset<size> divisor)
{
	bitset<size>	quotient(0);
	bitset<size>	curr_quotient(0);
	bitset<size>	original_divisor(divisor);
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
		quotient += bitset<size>(1);
	} else {
		reminder = dividend.to_ullong();
	}
	return make_pair(quotient, reminder);
}

template <size_t size>
ostream& operator<<(ostream& os, bitset<size> bs)
{
	vector<size_t>				res;
	static const bitset<size>	radix(10'000'000'000'000'000'000u);
	static const bitset<size>	zero(0);
	bool 						is_first = true;

	while (bs != zero) {
		auto division_result = divide(bs, radix);
		res.push_back(division_result.second);
		bs = division_result.first;
	}
	reverse(res.begin(), res.end());
	for (const auto item : res) {
		if (is_first) {
			cout << item;
			is_first = false;
		} else{
			cout  << setw(19) << setfill('0') << item;
		}
	}
	return os;
}

template <size_t size>
bitset<size> long_factorial(int n, bitset<size> tmp) // todo rm tmp
{
	bitset<size> bs(1);
	for (int i = 1; i <= n; ++i) {
		bs *= i;
	}
	return bs;
}

template <size_t size>
void print(bitset<size> tmp)
{
	cout << tmp << endl;
}

template <size_t size>
void print_bin(bitset<size> tmp)
{
	string str = tmp.to_string();
	string to_print(find(str.begin(), str.end(), '1'), str.end());

	cout << to_print << endl;
}

void print_factorial(int n)
{
	if (n < 0)  { cout << "Argument must be positive" << endl; return; }
	const int bits_count = 20032; // 2000! requires 19054 bits and 20032 % 64 == 0

	bitset<bits_count> tmp;
	bitset<bits_count> bs = long_factorial(n, tmp);
	print(bs);
}

int main(int ac, char **av)
{
	if (ac != 2) {
		cout << "Please, give 1 numeric argument" << endl;
		return 0;
	}
	print_factorial(atoi(av[1]));
}