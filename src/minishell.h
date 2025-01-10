/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:08:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/10 18:49:18 by hsetyamu         ###   ########.fr       */
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
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include "./structs.h"
# include "./lexer/lexer.h"
# include "./parser/parser.h"
# include "./exec/exec.h"
# include "./envs/envs.h"
# include "./builtins/builtins.h"
# include "./command_table/command_table.h"
# include "./utils/utils.h"
# include "./signals/signals.h"

//# define RES			"\033[0m"
# define RES			"\x1b[0m"
# define RED			"\033[31m"
# define GRE			"\033[32m"
# define BLU			"\033[34m"
# define CYA			"\033[36m"
# define MAG			"\033[35m"
# define YEL			"\033[33m"
# define BOLD			"\x1b[1m"

#endif
