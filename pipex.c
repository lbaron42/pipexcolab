/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:55:02 by lbaron            #+#    #+#             */
/*   Updated: 2023/03/31 19:55:06 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	int		i;
	char	*path;
	char	**path_buf;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	path = ft_strstr(envp[i], "/");
	path_buf = ft_split(path, ':');
	return (path_buf);
}

char	*valid_path(char **path, char *argv)
{
	int		i;
	char	*correct_path;

	i = 0;
	while (path[i])
	{
		correct_path = join_strings(path[i], "/", argv);
		if (access(correct_path, X_OK) == 0)
			return (correct_path);
		else
		{
			free(correct_path);
		}
		i++;
	}
	return (NULL);
}

int	execute_program(char **arg_vec, char *path)
{
	if (execve(path, arg_vec, NULL) == -1)
	{
		perror("Could not execute");
		return (1);
	}
	return (0);
}

int	pipe_function(t_data *pipex, char *argv1, char *argv4)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		print_error();
	if (pipex->pid1 == 0)
	{
		pipex->fd[1][0] = open(argv1, O_RDONLY, 0777);
		if (dup2(pipex->fd[0][1], STDOUT_FILENO) == -1
		|| dup2(pipex->fd[1][0], STDIN_FILENO) == -1 || pipex->fd[1][0] == -1)
			print_error();
		close_3fds(pipex->fd[0][0], pipex->fd[0][1], pipex->fd[1][0]);
		execute_program(pipex->arg_vec1, pipex->path1);
	}
	else
	{
		pipex->fd[1][1] = open(argv4, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (dup2(pipex->fd[0][0], STDIN_FILENO) == -1
		|| dup2(pipex->fd[1][1], STDOUT_FILENO) == -1 || pipex->fd[1][1] == -1)
			print_error();
		close_3fds(pipex->fd[0][0], pipex->fd[0][1], pipex->fd[1][1]);
		execute_program(pipex->arg_vec2, pipex->path2);
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	pipex;

	if (argc != 5)
	{
		write(1, "Usage : ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (1);
	}
	if (access(argv[1], F_OK | R_OK) == -1)
		print_error();
	pipex.arg_vec1 = ft_split(argv[2], ' ');
	pipex.arg_vec2 = ft_split(argv[3], ' ');
	pipex.path_to_check = find_path(envp);
	pipex.path1 = valid_path(pipex.path_to_check, pipex.arg_vec1[0]);
	pipex.path2 = valid_path(pipex.path_to_check, pipex.arg_vec2[0]);
	if (pipe(pipex.fd[0]) == -1)
		return (1);
	pipex.pid1 = pipe_function(&pipex, argv[1], argv[4]);
	if (pipex.pid1 == 1)
		return (1);
	if (pipe(pipex.fd[1]) == -1)
		return (1);
	waitpid(pipex.pid1, NULL, 0);
	clean_data(&pipex);
	return (0);
}
