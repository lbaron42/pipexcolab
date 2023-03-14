#include "pipex.h"


size_t	ft_strlen(const char *str)
{
    size_t	i;

    if (!str)
        return (0);
    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
    size_t	src_len;
    size_t	i;

    src_len = ft_strlen(src);
    if (destsize)
    {
        i = 0;
        while (src[i] != '\0' && i < (destsize - 1))
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    return (src_len);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    char		*d;
    const char	*s;

    if (!(dest || src))
        return (NULL);
    d = dest;
    s = src;
    while (n-- > 0)
        *d++ = *s++;
    return (dest);
}

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
	int	word_count;
	int	i;
	unsigned int	len;
    int	y;

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

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned int		i;

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
    size_t		needle_len;

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
        return ((char *) big);
    while (big[i] != '\0' && i < len)
    {
        j = 0;
        while (big[i + j] != '\0' && big[i + j] == little[j] && i + j < len)
        {
            if (little[j + 1] == '\0')
            {
                return ((char *) big + i);
            }
            j++;
        }
        i++;
    }
    return (0);
}

char *join_strings(const char *str1, const char *str2, const char *str3) {
    size_t len1 = ft_strlen(str1);
    size_t len2 = ft_strlen(str2);
    size_t len3 = ft_strlen(str3);
    char *result = malloc((len1 + len2 + len3 + 1) * sizeof(char)); // +1 for the terminating null character
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }
    ft_strlcpy(result, str1,len1 + len2 + len3 + 1);
    ft_strlcat(result, str2, len1 + len2 + len3 + 1);
    ft_strlcat(result, str3, len1 + len2 + len3 + 1);
    return result;
}

void clean_ptrs(char **double_ptr)
{
    char **tmp;

    tmp = double_ptr;
    while (*tmp)
    {
        free(*tmp);
        tmp++;
    }
    free(double_ptr);
}
void clean_data(data *pipex_data)
{
    close(pipex_data->fd1[0]);
    close(pipex_data->fd1[1]);

/*
    close(pipex_data->fd2);
*/

    clean_ptrs(pipex_data->arg_vec1);
    clean_ptrs(pipex_data->arg_vec2);
    free(pipex_data->path1);
    free(pipex_data->path2);
    clean_ptrs(pipex_data->path_to_validate);
}