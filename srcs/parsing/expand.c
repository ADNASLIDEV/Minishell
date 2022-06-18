/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:13:02 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/18 19:31:49 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_iden(char c)
{
	if (c == ' ' || c == '\'' || c == '"' || c == '$'
		|| c == ':' || c == ';' || c == '-' || c == '?')
		return (0);
	return (1);
}

static char	*replace_expand(char *str, int n, char *rep)
{
	int		i;
	int		j;
	char	*n_str;

	n_str = malloc((ft_strlen(str) - (n + 1)
				+ ft_strlen(rep) + 1) * sizeof(char));
	if (!n_str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && is_valid_iden(str[i + 1]))
			break;
		n_str[i] = str[i];
	}
	j = -1;
	while (rep[++j])
		n_str[i + j] = rep[j];
	i += n;
	while (str[++i])
		n_str[i + j - (n + 1)] = str[i];
	n_str[i + j - (n + 1)] = '\0';
	return (n_str);
}

char	*make_expand(char *str, int n, t_lenv *lenv)
{
	int	size;
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && is_valid_iden(str[i + 1]))
			break ;
	while (lenv)
	{
		size = ft_strlen(lenv->k) - 1;
		if (size < n)
			size = n;
		if (ft_strncmp(&str[i + 1], lenv->k, size) == 0)
			break ;
		lenv = lenv->next;
	}
	if (!lenv)
		return (replace_expand(str, n, ""));
	return (replace_expand(str, n, lenv->v));
}

static int	there_are_expand(char *av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (av[i] == '$' && av[i + 1] && is_valid_iden(av[i + 1]))
			return (1);
	return (0);
}

static void	prepare_expand(char	**av, t_lenv *lenv)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if ((*av)[0] == '\'')
		return ;
	j = 0;
	while (there_are_expand(&(*av)[j]))
	{
		i = -1;
		k = 0;
		while ((*av)[++i])
		{
			if (((*av)[i] == '$' && (*av)[i + 1] && is_valid_iden((*av)[i + 1]) && k == 0) || k > 0)
			{
				if ((!(*av)[i] || !is_valid_iden((*av)[i])) && k > 0)
					break ;
				k++;
			}
		}
		k--;
		if (k > 0)
		{
			str = make_expand(*av, k, lenv);
			free(*av);
			*av = str;
		}
		j = i;
	}
}

t_cmd	*get_expands(t_cmd *cmd, t_lenv *lenv)
{
	int		i;
	t_cmd	*rt;

	rt = cmd;
	while (cmd)
	{
		i = -1;
		if (cmd->cmd)
			while (cmd->cmd[++i])
				prepare_expand(&cmd->cmd[i], lenv);
		cmd = cmd->next;
	}
	return (rt);
}
