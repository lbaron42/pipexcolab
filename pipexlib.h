 #ifndef PIPEX_PIPEXLIB_H
#define PIPEX_PIPEXLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_pipex {
    int pid1;
    int pid2;
    int fd1[2];
    int fd2[2];
    char **arg_vec1;
    char **arg_vec2;
/*    char *cmd_pin;
    char *arg_in;
    char *cmd_pout;
    char *arg_out;*/
    char *path1;
    char *path2;
    char *outfile;
    char *infile;
}   data;

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_free(char **strs, int j);
int     ft_word_count(const char *str, char c);
int     ft_size_word(const char *s, char c, int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);
char *join_strings(const char *str1, const char *str2, const char *str3);
 char	*ft_strnstr(const char *big, const char *little, size_t len);


#endif //PIPEX_PIPEXLIB_H