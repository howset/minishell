/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:19:32 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 16:36:20 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z' )
		return (c + 32);
	return (c);
}

/*make lowercase*/

/*
int     main(void)
{
        int     test;

        test = ft_tolower('H');
        write(1,&test,1);

        test = ft_tolower('b');
        write(1,&test,1);
	return (0);
}
*/
