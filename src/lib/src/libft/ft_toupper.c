/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:58:20 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 16:33:44 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z' )
		return (c - 32);
	return (c);
}

/*make uppercase*/

/*
int	main(void)
{
	int	test;

	test = ft_toupper('H');
	write(1,&test,1);

	test = ft_toupper('b');
	write(1,&test,1);
	return (0);	
}
*/
