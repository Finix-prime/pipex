/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:33:50 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/16 19:40:45 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct pipex
{
	char	**path;
	char	*cmd_path;
	char	**cmd;
	char	**av;
	char	*ev;
	int		end[2];
	int		ac;
	int		index;
	int		fd_in;
	int		fd_out;
}	t_pipe;

int		execve(const char *pathname, char *const argv[], char *const envp[]);
int		access(const char *pathname, int mode);
int		wd_count(char const *s, char c);
int		al_count(char *str, char c);
void	word_add(char *str, char c, char *list);
void	reserve_word(char const *s, char c, char **list);
char	**split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
