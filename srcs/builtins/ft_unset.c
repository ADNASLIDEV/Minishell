/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:16:35 by aasli             #+#    #+#             */
/*   Updated: 2022/05/14 12:13:19 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	is_bad_identifier(char c)
{
	if (isalpha(c) || c == '_')
		return (0);
	return (1);
}

int	ft_unset(char **cmd, t_lenv **env)
{
	int		i;

	i = 1;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			printf("Rovidshell: unset: %s: options are not handled\n", cmd[1]);
			return (1);
		}
		while (cmd[i])
		{
			if (is_bad_identifier(cmd[i][0]) == 1)
			{
				printf("Rovidshell: unset: %s: not a valid identifier\n",
					cmd[i]);
			}
			else if (check_env_var(env, cmd[i]) == 1)
				unset_var_env(env, cmd[i], ft_strlen(cmd[i]));
			i++;
		}
		return (0);
	}
	return (2);
}