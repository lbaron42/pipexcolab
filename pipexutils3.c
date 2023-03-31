/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:46:09 by mrizakov          #+#    #+#             */
/*   Updated: 2023/03/31 19:47:20 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	unsigned int	str_len;
	unsigned int	correct_size;

	i = 0;
	str_len = ft_strlen((char *)s);
	correct_size = 1;
	if (start > str_len || len == 0)
		correct_size = 1;
	else if (len <= str_len - start)
		correct_size = len + 1;
	else if (len > str_len - start)
		correct_size = str_len - start + 1;
	substr = malloc(correct_size * sizeof(char));
	if (!substr)
		return ((void *) NULL);
	while (i != correct_size - 1)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	char			**array;
	int				word_count;
	int				i;
	unsigned int	len;
	int				y;

	word_count = ft_word_count(s, c);
	y = -1;
	i = 0;
	array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (++y < word_count)
	{
		while (s[i] == c)
			i++;
		len = ft_size_word(s, c, i);
		array[y] = ft_substr(s, i, len);
		if (!array[y])
			ft_free(array, y);
		i = i + len;
	}
	array[y] = 0;
	return (array);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0' || i == n)
		return (0);
	else
		return (-s2[i]);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*phaystack;
	size_t	needle_len;

	phaystack = (char *)haystack;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
	{
		return (phaystack);
	}
	while (*phaystack)
	{
		if (*phaystack == *needle)
		{
			if (ft_strncmp(needle, phaystack, needle_len) == 0)
			{
				return (phaystack);
			}
		}
		phaystack++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] != '\0' && big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
			{
				return ((char *)big + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}
