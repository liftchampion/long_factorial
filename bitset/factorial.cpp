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
#include <iomanip>
#include "bitset_arithmetic.h"
#include "bitset_output.h"

using namespace std;

void print_factorial(int n)
{
	if (n < 0)  { cout << "Argument must be positive" << endl; return; }
	const int bits_count = 20032; // 2000! requires 19054 bits and 20032 % 64 == 0

	bitset<bits_count> bs(1);
	for (int i = 1; i <= n; ++i) {
		bs *= i;
	}
	cout << bs << endl;
}
