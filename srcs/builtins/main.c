/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/06/13 13:07:52 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	g_status = 0;

void	ctrl_c_exec(int signum)
{
	(void)signum;
	printf("\n");
	g_status = signum + 28;
}

void	handle_signals_exec(void)
{
	signal(SIGINT, ctrl_c_exec);
	signal(SIGQUIT, SIG_IGN);
}


void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	g_status = signum + 28;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals_main(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	free_split(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

int	print_cmd(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		printf("%s ", cmd[i++]);
	printf("\n");
	return (0);
}

char	**get_c_nv(t_lenv **lenv)
{
	t_lenv	*tmp;
	char	**env;
	int i;
	
	env = malloc(1000 * sizeof(char *));
	if (!env)
	{
		printf("Allocation error");
		return (NULL);
	}
	tmp = *lenv;
	i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->k, tmp->v);
		i++;
		tmp = tmp->next;
	}
	env[i] = 0;
	return (env);
}

t_lenv	*get_min_env(void)
{
	t_lenv	*lbegin;
	char	*pwd;
	char	*tmp;
	char	*tmp2;

	lbegin = NULL;
	tmp = ft_calloc(2049, sizeof(char));
	if (!tmp)
	{
		printf("Allocation error");
		return (0);
	}
	pwd = ft_strjoin("PWD=", getcwd(tmp, 2048));
	ft_addback_lenv(&lbegin, ft_new_lenv(pwd));
	free (pwd);
	ft_addback_lenv(&lbegin, ft_new_lenv("SHLVL=1"));
	tmp2 = ft_strjoin("_=", getcwd(tmp, 2048));
	free(tmp);
	tmp = ft_strjoin(tmp2, "/Minishell");
	ft_addback_lenv(&lbegin, ft_new_lenv(tmp));
	free(tmp);
	free(tmp2);
	return (lbegin);
}

int	minishell(t_lenv **env)
{
	t_data	data;
	t_lenv	**lenv;
	t_cmd 	*cmd;
	t_cmd	*tmp;

	lenv = env;
	data.run = 1;
	while (data.run)
	{
		handle_signals_main();
		data.line = readline("Rovidshell $>");
		if (!data.line)
		{
			data.run = 0;
			printf("exit\n");
			return (0);
		}
		if (data.line[0])
			add_history(data.line);
		handle_signals_exec();
		cmd = parsing(get_regroup(get_lexing(data.line)), *lenv);
		if (!cmd->cmd)
		{
			free(cmd);
			continue;
		}
		tmp = cmd;
		/*while (cmd)
		{
			int i = -1;
			while (cmd->cmd[++i])
				printf("\t%s\n", cmd->cmd[i]);
			printf("fd_in: %i\nfd_out: %i\n", cmd->fd_in, cmd->fd_out);
			cmd = cmd->next;
		}*/
		ft_loop_cmds(tmp, lenv);
		ft_list_clear_cmd(tmp);
		free(data.line);
	}	
	return (0);
}

void	data_init(t_data *data, char **envp, t_glist *glist)
{
	data->glist = glist;
	data->unset_path = 0;
	if (!*envp)
	{
		data->env = get_min_env();
		data->min_env = 1;
	}
	else
	{
		data->env = get_env(envp);
		data->min_env = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_glist	*glist;
	t_data	*data;

	(void)ac;
	(void)av;
	glist = malloc(sizeof(t_glist) * 1);
	if (!glist)
		return (0);
	//data = ft_malloc(sizeof(t_data), 1, &glist);
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (0);
	data_init(data, envp, glist);
	minishell(&data->env);
	free_lenv(&data->env);
	free(glist);
	free(data);
	return (0);
}
