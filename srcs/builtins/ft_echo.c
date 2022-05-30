/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:11:36 by aasli             #+#    #+#             */
/*   Updated: 2022/05/16 12:49:15 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static int	full_n(char *cmd)
{
	int	i;

	cmd += 2;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) != 0)
			return (n);
		if (ft_strncmp(cmd[i], "-n", 2) == 0
			&& full_n(cmd[i]))
			n++;
		i++;
	}
	return (n);
}

static void	print_echo(char **cmd, int n)
{
	int	i;

	i = 1;
	while (cmd[i + n])
	{
		if (i != 1)
			printf(" ");
		printf("%s", cmd[i + n]);
		i++;
	}
}

int	ft_echo(char **cmd, t_lenv **env)
{
	int		n;

	(void)env;
	n = check_echo(cmd);
	print_echo(cmd, n);
	if (n == 0)
		printf("\n");
	return (0);
}