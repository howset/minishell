/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:22:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/07 16:16:25 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int i)
{
	if (('0' <= i && i <= '9'))
		return (1);
	return (0);
}

/*checks for adigit*/

/*
int	main(void)
{
	ft_isdigit('a'); //write(1,&i,1) under return(1)
}
*/
