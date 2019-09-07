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
	BigInt& operator=(const BigInt& other) = default;
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
	BigInt& operator*=(const BigInt& other) {
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
	bool operator==(const BigInt& other) {
		if (this->len() != other.len()) { return false; }

		for (size_t i = 0; i < this->len(); ++i) {
			if ((*this)[i] != other[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator<(const BigInt& other) {
		if (this->len() != other.len()) { return this->len() < other.len(); }

		for (int i = static_cast<int>(this->len()) - 1; i >= 0 ; --i) {
			if ((*this)[i] >= other[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator<=(const size_t other) {
		BigInt other_bi(other);
		if (this->len() != other_bi.len()) { return this->len() < other_bi.len(); }

		for (int i = static_cast<int>(this->len()) - 1; i >= 0 ; --i) {
			if ((*this)[i] >= other_bi[i]) {
				return false;
			}
		}
		return true;
	}
private:
	deque<size_t> data;
	static const size_t radix = 1'000'000'000'000'000'000lu;
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

static vector<BigInt> default_vector;

template <typename T>
void	divide_and_conquer_multiply(vector<T>& multipliers,
									vector<BigInt>& big_multipliers = default_vector)
{
	size_t		size;
	vector<T>	tmp;

	tmp.reserve(multipliers.size() + 1);
	while (multipliers.size() > 1) {
		size = multipliers.size();
		for (size_t i = 0; i < size - 1; i += 2) {
			multipliers[i] *= multipliers[i + 1];
			if (typeid(T) == typeid(BigInt) ||
				multipliers[i] <= UINT32_MAX)
			{
				tmp.emplace_back(move(multipliers[i]));
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

BigInt my_factorial(int n) {
	if (n < 0) { throw invalid_argument("Negative factorial is not defined"); }
	if (n == 0) { return BigInt(1); }
	return (big_multiplies(small_multiplies(n)));
}

int main(int ac, char **av)
{
	if (ac != 2) {cout << "Please give 1 numeric argument" << endl; return (0); }
	BigInt num = my_factorial(atoi(av[1]));
	cout << num << endl;
	return 0;
}
