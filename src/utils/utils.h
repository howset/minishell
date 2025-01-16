/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:57:40 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 15:58:25 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

// malloc_perex.c
void	*malloc_perex(size_t bytes, char *msg);

// ft_fprintf.c
int		ft_fprintf(int fd, const char *fmt, ...);

// debug_print_tkn_commtab.c
void	print_tkn(t_token *tokens);
void	print_commargs(char **args);
void	print_commredirs(t_redirection *redir);
void	print_commdetails(t_command *cmd);
void	print_command_table(t_cmdtable *table);

// debug_print_ast.c
void	print_indentation(int level, int spaces);
void	print_redirection_info(t_ast *node, int level);
void	print_node_info(t_ast *node, int level);
void	print_ast(t_ast *node, int level);

#endif
