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

ostream& operator<<(ostream& os, __uint128_t gg) {

	uint64_t left = gg / 1'000'000'000'000'000'000lu;
	uint64_t right = gg % 1'000'000'000'000'000'000lu;

	if (!left && !right) { cout << '0'; }
	if (left) { cout << left; }
	if (right) { cout << right; }
	cout << endl;
	return os;
}

class BigInt {
public:
	BigInt() : data(1, 0) {};
	explicit BigInt(__uint128_t val) {
//		cout << "Got value: " << val << endl;
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
		if (other == radix) {
			this->data.push_front(0);
			return *this;
		}

		BigInt		res(0);

//		cout << "res0: " << res << endl;
		for (int i = static_cast<int>(this->len()) - 1; i >= 0; --i) {
			res *= radix;
//			cout << "res1: " << res << endl;


//			cout << "Going to create new from " << (*this)[i] << " and " << other << endl;
			BigInt tmp = BigInt(static_cast<__uint128_t>((*this)[i]) * other);
//			cout << "tmp:  " << tmp << endl;

			res += tmp;
//			cout << "res2: " << res << endl;
		}
		*this = res;
		return *this;
	}
	[[nodiscard]]
	const deque<size_t>& get_data() const{ // todo no need ?
		return this->data;
	}
private:
	deque<size_t> data;
	const size_t radix = 1'000'000'000'000'000'000lu;
};

ostream& operator<<(ostream& os, const BigInt& bigint){
//	if (bigint.is_zero()) {
//		cout << '0';
//		return os;
//	}
	bool is_first = true;
	for (int i = static_cast<int>(bigint.len()) - 1; i >= 0; --i) {
		if (is_first) {
			os << bigint[i];
			is_first = false;
		} else {
			os << setw(18) << setfill('0') << bigint[i];
		}
	}
//	cout << endl << bigint.len() << ": ";
//	for (const auto i : bigint.get_data()) {
//		cout << i << " ";
//	}
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
	BigInt num(0);
	BigInt other(10'000'000'000'000'000'000lu);

	num += 1;
	//size_t fact = atoi(av[1]);

	num = factorial(atoi(av[1]));
	//cout << endl << endl << endl << endl << endl;
	cout <<  num << endl;
//	num *= 29;
//	cout << "29: " << num << endl;
}