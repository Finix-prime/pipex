/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:01:30 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/08 00:57:47 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *error(char *av, char **path)
{
    char    **cmd;
    char    *cmd_path;
    int     i;

    i = 0;
    cmd = split(av, ' ');
    i = 0;
    while (path[i])
    {
        cmd_path = ft_strjoin(path[i], "/");
        cmd_path = ft_strjoin(cmd_path, cmd[0]);
        if (access(cmd_path, F_OK) == 0)
            return (cmd_path);
        i++;
    }
        perror(cmd_path);
    return (cmd_path);
}

int main(int argc, char **argv, char **envp)
{
	char *cmd_path;
	char **path;
    char *ev;
    char *options[3] = {"ls", "-la", NULL};
    int i;
    int fd;

    (void)argc;
    i = 0;
    while(ft_strncmp("PATH",envp[i], 4))
        i++;
    ev = envp[i] + 5;
    path = split(ev, ':');
    fd = open(argv[1], O_RDONLY);
    cmd_path = error(argv[2], path);
    execve(cmd_path, options, envp);
    free(cmd_path);
    free(path);
    close(fd);
    return(0);
}
