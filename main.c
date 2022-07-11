/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:01:30 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/10 10:20:59 by pmethira         ###   ########.fr       */
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

void	freeall(char *cmd_path, char **path, char **cmd)
{
	free(cmd_path);
	free(path);
	free(cmd);
	printf("come in free\n");
	return ;
}

void	forking(char *cmd_path, char **envp, char **cmd, char **path)
{
	pid_t	id;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	id = fork();
	if (id != 0)
	{
		close(fd[1]);
		cmd_path = error(path, cmd);
		printf("id 0 print");
		execve(cmd_path, cmd, envp);
	}
	else
	{
		close(fd[0]);
		printf("id 1 print");
		execve(cmd_path, cmd, envp);
	}

}

void	piping(int ac, char **av, char **path, char **envp)
{
	char	**cmd;
	char	*cmd_path;
	int		i;

	i = 2;
	while (i < ac)
	{
		cmd = split(av[i], ' ');
		cmd_path = error(path, cmd);
		forking(cmd_path, envp, cmd, path);
		i++;
	}

}

int main(int argc, char **argv, char **envp)
{
	char	*cmd_path;
	char	**path;
	char	**cmd;
	char	*ev;
	int		i;

	(void)argc;
	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	ev = envp[i] + 5;
	path = split(ev, ':');
	cmd = split(argv[2], ' ');
	cmd_path = error(path, cmd);
	piping(argc, argv, path, envp);
	// execve(cmd_path, cmd, envp);
	freeall(cmd_path, path, cmd);
	printf("%s\n", cmd_path);
	// free(cmd_path);
	// free(path);
	// free(cmd);
	return(0);
}
