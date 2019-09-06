/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_factorial_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 22:04:26 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/06 22:04:26 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <iomanip>
#include <deque>

using namespace std;

class BigInt;
ostream& operator<<(ostream& os, const BigInt& bigint);

class BigInt {
public:
	BigInt() : data(1, 0) {};
	explicit BigInt(__uint128_t val) {
		while (val >= radix) {
			data.push_back(val % radix);
			val /= radix;
		}
		data.push_back(val);
	}
	BigInt& operator=(const BigInt& other) {
		this->data = other.data;
		return *this;
	}
	[[nodiscard]]
	size_t len() const {
		return data.size();
	}
	[[nodiscard]]
	bool is_zero() const {
		return (len() == 1 && data[0] == 0);
	}
	size_t operator[](size_t idx) const{
		return idx < len() ? data[idx] : 0;
	}
	size_t& operator[](size_t idx){
		if (len() <= idx) {
			data.resize(idx + 1, 0);
		}
		return data[idx];
	}
	BigInt& operator+=(const BigInt& other) {
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
	BigInt& operator+=(size_t other) {
		BigInt other_bigint(other);
		*this += other_bigint;
		return *this;
	}
	BigInt& operator*=(size_t other) {
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
private:
	deque<size_t> data;
	const size_t radix = 1'000'000'000'000'000'000lu;
};

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

BigInt factorial(int n) {
	BigInt res(1);

	for (int i = 1; i <= n; ++i) {
		res *= i;
	}
	return res;
}

int main(int ac, char **av)
{
	BigInt num;

	num = factorial(atoi(av[1]));
	cout <<  num << endl;
}