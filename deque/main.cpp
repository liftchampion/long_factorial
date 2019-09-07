/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 04:44:45 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/07 04:44:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "factorial.h"

using namespace std;

int main(int ac, char **av)
{
	if (ac != 2) {cout << "Please give 1 numeric argument" << endl; return (0); }

	BigInt num = factorial(atoi(av[1]));
	cout << num << endl;
	return 0;
}
