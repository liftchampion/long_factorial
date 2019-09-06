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

using namespace std;

static inline bool sum_bits(bool b1, bool b2, bool& carry)
{
	bool sum = (b1 ^ b2) ^ carry;

	carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
	return sum;
}

template <size_t size>
static inline int find_active_block_begin(bitset<size> bs)
{
	static const bitset<size> mask(UINT64_MAX);

	for (size_t i = 1; i <= size / 64; ++i) {
		string str = ((bs >> (size - 64 * i)) & mask).to_string();
		cout << string(str.end() - 64, str.end()) << endl;
		//cout << ((bs >> (bits_count - 64 * i)) & mask).to_ullong() << endl;
	}
}

template <size_t size>
bitset<size>& operator+=(bitset<size>& lhs, const bitset<size>& rhs)
{
	uint64_t		left;
	uint64_t		right;
	uint64_t		carry = 0;
	uint64_t		intemediate_res;
	const int		chunks_count = size / 32;
	size_t			radix = static_cast<size_t>(UINT32_MAX) + 1;
	bitset<size>	mask(UINT32_MAX);
	bitset<size>	carry_bs;
	bitset<size>	inter_res_bs;

//	cout << "L " << lhs.to_string() << endl;
//	cout << "R " << rhs.to_string() << endl << endl;

	for (size_t i = 0; i < chunks_count; ++i) {
//		cout << "M " << mask.to_string() << endl;
//		cout << "M " << (~mask).to_string() << endl;
		left  = ((lhs & mask) >> (32 * i)).to_ulong();
		right = ((rhs & mask) >> (32 * i)).to_ulong();

//		cout << "L " << bitset<size>(left).to_string()  << " " << left << endl;
//		cout << "R " << bitset<size>(right).to_string() << " " << right << endl;
//		cout << "C " << bitset<size>(carry).to_string() << " " << carry << endl;

		intemediate_res = left + right + carry;

//		cout << "I " << bitset<size>(intemediate_res).to_string() << " " << intemediate_res << endl;

		carry = intemediate_res >> 32u;

		//carry_bs = carry;
		//carry_bs <<= 32 * (i + 1);
		intemediate_res &= radix - 1;

//		cout << "C " << bitset<size>(carry).to_string() << " " << carry << endl;
//		cout << "I " << bitset<size>(intemediate_res).to_string() << " " << intemediate_res << endl;

		lhs &= ~mask;
		inter_res_bs = intemediate_res;
		inter_res_bs <<= 32u * i;
		lhs |= inter_res_bs;
		mask <<= 32u;
		//radix += UINT32_MAX;

//		cout << "+ " << lhs.to_string() << endl << endl;
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
//				cout << lhs.to_ullong() << " + " << (tmp << i).to_ullong() << " = ";
				lhs += tmp << i;
//				cout << lhs.to_ullong() << endl;
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

bool test_one_mult(size_t left, size_t right)
{
	bitset<128> bs_l(left);
	bitset<128> bs_r(right);

	bs_l *= right;
	bs_r *= left;
	return (bs_l == left * right) && (bs_r == left * right);
}

bool test_one_sum(size_t left, size_t right)
{
	bitset<128> bs_l(left);
	bitset<128> bs_r(right);
	bitset<128> arg_l(left);
	bitset<128> arg_r(right);

	bs_l += arg_r;
	bs_r += arg_l;

	//cout << bs_l.to_string() << endl;
	//cout << arg_r.to_string() << endl;
	//cout << bs_l.to_string() << endl;

	return (bs_l == left + right) && (bs_r == left + right);
}

template <size_t size>
ostream& operator<<(ostream& os, bitset<size> bs)
{
	vector<size_t> res;
	static const bitset<size> radix(10'000'000'000'000'000'000u);
	//static const bitset<size> radix(1000u);
	static const bitset<size> zero(0);

	while (bs != zero)
	{
		res.push_back(bs % radix);
		bs = bs / radix;
	}
	reverse(res.begin(), res.end());
	for (const auto item : res) {
		cout << item;
	}
	return os;
}

template <size_t size>
bitset<size> long_factorial(int n, bitset<size> tmp)
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

void test()
{
	//2395008000 + 3832012800
	size_t left = 2395008000;
	size_t right = 3832012800;

	bitset<128> lhs(left);
	bitset<128> rhs(right);

	lhs += rhs;
	left += right;
	cout << lhs.to_ullong() << endl;
	cout << left << endl;
}

void print_factorial(int n)
{
	if (n < 0)  { cout << "Argument must be positive" << endl; return; }
	const int bits_count = 20032; // 2000! requires 19054 bits and 20032 % 64 == 0

	bitset<bits_count> tmp;
	bitset<bits_count> bs = long_factorial(n, tmp);

//	for (int i = 1; i <= n; ++i) {
//		bs *= i;
//	}

	//print(bs);

//	test();


	//bs = 100;
	//cout << bs % 32 << endl;


	//cout << bs.to_string() << endl;

//	for (int i = 1; i <= bits_count / 64; ++i) {
//		string str = ((bs >> (bits_count - 64 * i)) & mask).to_string();
//		cout << string(str.end() - 64, str.end()) << endl;
//		//cout << ((bs >> (bits_count - 64 * i)) & mask).to_ullong() << endl;
//	}

	//cout << mask.to_string() << endl;


//	cout << "Start test" << endl;
//	for (size_t i = 479001600; i < 479001600 + 1000; ++i) {
//		for (size_t j = 0; j < 1000; ++j) {
//			if (!test_one_mult(i, j)) {
//				cout << "Error: " << i << " " << j << endl;
//				return;
//			}
//			cout << i * 1000 + j << "\r";
//		}
//	}
//	cout << "End test" << endl;

//	bitset<100> bs(2);
//	bs *= 2147483645;
}

int main(int ac, char **av)
{
	if (ac != 2) {
		cout << "Please, give 1 numeric argument" << endl;
		return 0;
	}
	print_factorial(atoi(av[1]));
}