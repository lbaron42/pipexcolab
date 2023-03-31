#include    "pipex.h"

char	*join_strings(const char *str1, const char *str2, const char *str3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	result = malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str1, len1 + len2 + len3 + 1);
	ft_strlcat(result, str2, len1 + len2 + len3 + 1);
	ft_strlcat(result, str3, len1 + len2 + len3 + 1);
	return (result);
}

void	clean_ptrs(char **double_ptr)
{
	char	**tmp;

	tmp = double_ptr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(double_ptr);
}

void	clean_data(data *pipex_data)
{
	close(pipex_data->fd[0][0]);
	close(pipex_data->fd[0][1]);
	close(pipex_data->fd[1][0]);
	close(pipex_data->fd[1][1]);
	clean_ptrs(pipex_data->arg_vec1);
	clean_ptrs(pipex_data->arg_vec2);
	free(pipex_data->path1);
	free(pipex_data->path2);
	clean_ptrs(pipex_data->path_to_check);
}
