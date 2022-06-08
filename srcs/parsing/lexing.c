/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:38:43 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/07 15:01:43 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static enum e_type	get_type(char c)
{
	if (c == ' ')
		return (SPACE_);
	else if (c == '>')
		return (OUTREDIR);
	else if (c == '<')
		return (INREDIR);
	else if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (SIMPLEQUOTE);
	else if (c == '"')
		return (DOUBLEQUOTE);
	else
		return (LITERAL);
}

t_lexing	*get_lexing(char *line)
{
	int			i;
	t_lexing	*lexing;

	if (!is_quotes_close(line) || !has_no_double_pipe(line)
		|| !has_no_multiple_redir(line))
		return (0);
	lexing = ft_create_elem_lex(line[0], get_type(line[0]));
	if (!lexing)
		return (0);
	i = 0;
	while (line[++i])
		ft_list_push_back_lex(&lexing, line[i], get_type(line[i]));
	return (lexing);
}