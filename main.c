/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:01:30 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/15 14:01:37 by pmethira         ###   ########.fr       */
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

void	forking(char *cmd_path, char **envp, char **cmd, char **path, int fdin, char **av)
{
	pid_t	id;
	int	fd[2];
	int	x;
	char **cmd1, **cmd2;
	char *cmd_path1, *cmd_path2;


	if (pipe(fd) == -1)
		return ;
	id = fork();
	cmd1 = split(av[2], ' ');
	cmd2 = split(av[3], ' ');
	cmd_path1 = error(path, cmd1);
	cmd_path2 = error(path, cmd2);
	if (id != 0)
	{
		close(fd[1]);
		wait(0);
		dup2(fd[0], 0);
		x = open("outfile", O_RDWR, 0644);
		dup2(x, 1);
		// cmd_path = error(path, cmd);
		printf("id 0 print");
		execve(cmd_path2, cmd2, envp);
	}
	else
	{
		close(fd[0]);
		dup2(fdin, 0);
		dup2(fd[1], 1);
		printf("id 1 print");
		execve(cmd_path1, cmd1, envp);
	}

}

void	piping(int ac, char **av, char **path, char **envp, int fd)
{
	char	**cmd;
	char	*cmd_path;
	int		i;

	i = 2;
	// while (i < ac - 1)
	// {
	// 	forking(cmd_path, envp, cmd, path, fd);
	// 	i++;
	// }
	cmd = split(av[i], ' ');
	cmd_path = error(path, cmd);
	forking(cmd_path, envp, cmd, path, fd, av);
}

int main(int argc, char **argv, char **envp)
{
	char	*cmd_path;
	char	**path;
	char	**cmd;
	char	*ev;
	int		i;
	int	fd;

	(void)argc;
	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	fd = open("infile", O_RDONLY);
	ev = envp[i] + 5;
	path = split(ev, ':');
	cmd = split(argv[2], ' ');
	cmd_path = error(path, cmd);
	piping(argc, argv, path, envp, fd);
	// execve(cmd_path, cmd, envp);
	freeall(cmd_path, path, cmd);
	return(0);
}
