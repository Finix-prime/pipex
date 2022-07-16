/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:01:30 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/16 19:44:38 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*error(char **path, char **cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		i++;
	}
	perror(cmd[0]);
	return (0);
}

void	exec_env(t_pipe *pipex, int i)
{
	pipex->cmd = split(pipex->av[i], ' ');
	pipex->cmd_path = error(pipex->path, pipex->cmd);
}

int	piping(t_pipe *pipex, char **envp)
{
	int	id;

	pipex->index = 2;
	pipe(pipex->end);
	pipex->fd_in = open("infile", O_RDONLY);
	while (pipex->index < pipex->ac - 2)
	{
		id = fork();
		if (id == 0)
		{
			close(pipex->end[0]);
			dup2(pipex->fd_in, 0);
			dup2(pipex->end[1], 1);
			exec_env(pipex, pipex->index);
			execve(pipex->cmd_path, pipex->cmd, envp);
		}
		pipex->index++;
	}
	return (0);
}

void	forking(t_pipe *pipex, char **envp)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (pipex->index < pipex->ac - 2)
			piping(pipex, envp);
	}
	else
	{
		wait(0);
		close(pipex->end[1]);
		dup2(pipex->end[0], 0);
		pipex->fd_out = open("outfile", O_RDWR, 0644);
		dup2(pipex->fd_out, 1);
		exec_env(pipex, pipex->ac -2);
		execve(pipex->cmd_path, pipex->cmd, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;
	int		i;

	if (argc >= 5)
	{
		pipex = (t_pipe *)malloc(sizeof(t_pipe));
		if (!pipex)
			return (0);
		i = 0;
		while (ft_strncmp("PATH", envp[i], 4))
			i++;
		pipex->ac = argc;
		pipex->ev = envp[i] + 5;
		pipex->av = argv;
		pipex->path = split(pipex->ev, ':');
		forking(pipex, envp);
		free(pipex);
	}
	return (0);
}
