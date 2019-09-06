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

using namespace std;

class BigInt {
public:
	BigInt() = default;
	explicit BigInt(size_t num) {
		while (num >= radix) {
			this->data.push_back(num % radix);
			num /= radix;
		}
		this->data.push_back(num);
	}
	size_t len() const {
		return this->data.size();
	}
	size_t operator[](size_t idx) const{
		return idx < this->len() ? this->data[idx] : 0;
	}
	size_t& operator[](size_t idx){
		if (this->len() <= idx) {
			this->data.resize(idx + 1, 0);
		}
		return this->data[idx];
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
		size_t		carry = 0;
		size_t		go_to = this->len();
		__uint128_t	intermediate_res;

		for (size_t i = 0; i < go_to || carry; ++i) {
			intermediate_res = static_cast<__uint128_t>((*this)[i]) * other;
			carry = intermediate_res
		}
		return *this;
	}
	const vector<size_t>& get_data() const{ // todo no need ?
		return this->data;
	}
private:
	vector<size_t> data;
	const size_t radix = 1'000'000'000'000'000'000lu;
};

ostream& operator<<(ostream& os, const BigInt& bigint){
	if (!bigint.len()) {
		os << '0';
	}
	else {
		bool is_first = true;
		for (int i = static_cast<int>(bigint.len()) - 1; i >= 0; --i) {
			if (i == is_first) {
				os << bigint[i];
			} else {
				os << setw(18) << setfill('0') << bigint[i];
			}
		}
	}
//	cout << bigint.len() << ": ";
//	for (const auto i : bigint.get_data()) {
//		cout << i << " ";
//	}
	return os;
}

int main()
{
	BigInt num;
	BigInt other(10'000'000'000'000'000'000lu);

	cout << num << endl;
	cout << other << endl;
	for (size_t i = 0; i < 20000; ++i) {
		num += 500'000'000'000'000'000lu;
		//cout << num << endl;
	}
	cout << num << endl;
}