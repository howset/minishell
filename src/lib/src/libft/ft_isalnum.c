/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:51:51 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/30 12:43:08 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i)
{
	if (('a' <= i && i <= 'z')
		|| ('A' <= i && i <= 'Z')
		|| ('0' <= i && i <= '9'))
		return (1);
	return (0);
}

/*checks for an alphanumeric character*/

/*
int	main(void)
{
	ft_isalnum('a'); //write(1,&i,1) under return(1)
	ft_isalnum('2');
	ft_isalnum('$');
}
*/
