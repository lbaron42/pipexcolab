#include "pipexlib.h"
//adding useful comments



void	free_sheet(char **str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        if (str[i] != NULL)
        {
            free(str[i]);
            i++;
        }
        *str = NULL;
    }
    free (str);

}

char **find_path(char **envp)
{
    int i;
    char *path;
    char **path_buf;

    i = 0;
    while(ft_strnstr(envp[i], "PATH=", 5) == NULL)
    {
        i++;
    }
    path = ft_strstr(envp[i], "/");
    path_buf = ft_split(path, ':');
    return (path_buf);
}

char *valid_path(char **path, char *argv)
{
    int i;

    i = 0;
    while(path[i])
    {
        path[i] = join_strings(path[i], "/", argv);
        if (access(path[i], X_OK) == 0)
            return (path[i]);
        free(path[i]);
        i++;
    }
    return (NULL);
}

void pipex()
{
    int fd[2];
    int pid_parent;
    pipe(fd);
    pid_parent = fork();
}



int main(int argc, char *argv[], char **envp)
{
	//for(int i = 0;i < 100;i++)
	   //     printf("%s\n", envp[i]);
    char **path_to_validate = find_path(envp);
    char *path = valid_path(path_to_validate, argv[1]);
    char *cmd = argv[1];
    char *arguments = argv[2];
    char *argVec[] = {cmd, arguments, NULL};
    if (execve(path, argVec, NULL) == -1) {
        perror("Could not execute");
    }
    return 0;
}
