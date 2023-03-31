/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:46:26 by mrizakov          #+#    #+#             */
/*   Updated: 2023/03/31 19:47:25 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (!size || len_d >= size)
		return (size + len_s);
	if (len_s < size - len_d)
		ft_memcpy(dst + len_d, src, len_s + 1);
	else
	{
		ft_memcpy(dst + len_d, src, size - len_d - 1);
		dst[size - 1] = '\0';
	}
	return (len_d + len_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	buf_len;

	ret = 0;
	if (s1 && s2)
	{
		buf_len = ft_strlen(s1) + ft_strlen(s2) + 1;
		ret = malloc(buf_len);
		if (!ret)
			return (ret);
		ret[0] = 0;
		ft_strlcpy(ret, s1, buf_len);
		ft_strlcat(ret, s2, buf_len);
	}
	return (ret);
}

char	**ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
	strs = NULL;
	return (NULL);
}

int	ft_word_count(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int	ft_size_word(const char *s, char c, int i)
{
	int	word_size;

	word_size = 0;
	while (s[i] != c && s[i])
	{
		word_size++;
		i++;
	}
	return (word_size);
}
