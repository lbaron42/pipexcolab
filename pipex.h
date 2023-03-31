/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:46:16 by mrizakov          #+#    #+#             */
/*   Updated: 2023/03/31 19:47:13 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipex {
	int		pid1;
	int		pid2;
	int		fd[2][2];
	char	**arg_vec1;
	char	**arg_vec2;
	char	**path_to_check;
	char	*path1;
	char	*path2;
	char	*outfile;
	char	*infile;
}	t_data;

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
void	clean_data(data *pipex_data);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_free(char **strs, int j);
int		ft_word_count(const char *str, char c);
int		ft_size_word(const char *s, char c, int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);
char	*join_strings(const char *str1, const char *str2, const char *str3);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	clean_ptrs(char **double_ptr);
void	close_3fds(int a, int b, int c);
int		print_error(void);

#endif //PIPEX_PIPEXLIB_H
