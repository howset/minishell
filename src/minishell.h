/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:08:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/27 18:08:01 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/src/ft_printf/ft_printf.h"
# include "./lib/src/get_next_line/get_next_line.h"
# include "./lib/src/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

# include "./structs.h"
# include "./lexer/lexer.h"
# include "./parser/parser.h"
# include "./utils/utils.h"

#endif