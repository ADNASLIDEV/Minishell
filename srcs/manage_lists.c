/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:17:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/22 17:05:38 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexing	*ft_create_elem_lex(char letter, enum e_type type)
{
	t_lexing	*elem;

	elem = malloc(sizeof(t_lexing));
	if (!elem)
		return (0);
	elem->letter = letter;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_lex(t_lexing **begin_list,
		char letter, enum e_type type)
{
	t_lexing	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_lex(letter, type);
	}
	else
		*begin_list = ft_create_elem_lex(letter, type);
}

t_regroup	*ft_create_elem_reg(char *str)
{
	t_regroup	*elem;

	elem = malloc(sizeof(t_regroup));
	if (!elem)
		return (0);
	elem->str = str;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_reg(t_regroup **begin_list, char *str)
{
	t_regroup	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_reg(str);
	}
	else
		*begin_list = ft_create_elem_reg(str);
}

void	ft_list_clear_lex(t_lexing *begin_list)
{
	t_lexing	*tmp;

	tmp = begin_list;
	while (tmp)
	{
		tmp = begin_list->next;
		free(begin_list);
	}
}

void	ft_list_clear_reg(t_regroup *begin_list)
{
	t_regroup	*tmp;

	tmp = begin_list;
	while (tmp)
	{
		tmp = begin_list->next;
		free(begin_list->str);
		free(begin_list);
	}
}
