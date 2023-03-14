#include "pipex.h"

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
    char *correct_path;

    i = 0;
    while(path[i])
    {
        correct_path = join_strings(path[i], "/", argv);
        if (access(correct_path, X_OK) == 0) {
            return (correct_path);
        }
        else {
            free(correct_path);
        }
        i++;
    }
    return (NULL);
}


int execute_program(char **arg_vec, char *path)
{
    if (execve(path, arg_vec, NULL) == -1) {
        perror("Could not execute");
    }
    return 0;
}


int pipe_function(data *pipex_data, char *argv1, char *argv4)
{
    pipex_data->pid1 = fork();
    if (pipex_data->pid1 < 0) {
        return 2;
    }

    if (pipex_data->pid1 == 0) {

        pipex_data->fd[1][0] = open(argv1, O_RDONLY, 0777);
        if (pipex_data->fd[1][0] == -1)
            printf("cant open file");

        dup2(pipex_data->fd[0][1], STDOUT_FILENO);
        dup2(pipex_data->fd[1][0], STDIN_FILENO);

        close(pipex_data->fd[0][1]);
        execute_program(pipex_data->arg_vec1, pipex_data->path1);
    } else {
        pipex_data->fd[1][1] = open(argv4, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (pipex_data->fd[1][1] == -1) {
            printf("cant open file");
        }
        dup2(pipex_data->fd[0][0], STDIN_FILENO);
        dup2(pipex_data->fd[1][1], STDOUT_FILENO);

        close(pipex_data->fd[0][1]);
        execute_program(pipex_data->arg_vec2, pipex_data->path2);
    }
    return 0;
}

int main(int argc, char *argv[], char **envp)
{
    data	pipex_data;

    if (argc != 5)
    {
        // write(1, "Usage : ./pipex infile cmd1 cmd2 outfile\n", 41);
        return (0);
    }
    pipex_data.arg_vec1 = ft_split(argv[2], ' ');
    pipex_data.arg_vec2 = ft_split(argv[3], ' ');


    pipex_data.path_to_validate = find_path(envp);


    pipex_data.path1 = valid_path(pipex_data.path_to_validate, pipex_data.arg_vec1[0]);
    pipex_data.path2 = valid_path(pipex_data.path_to_validate, pipex_data.arg_vec2[0]);

    if (pipe(pipex_data.fd[0]) == -1) {
        return 1;
    }
    pipex_data.pid1 = pipe_function(&pipex_data, argv[1], argv[4]);
//    if (pipe(pipex_data.fd2) == -1) {
//        return 1;
//    }
    //   printf("is this hapening?\n");



    close(pipex_data.fd[0][0]);
    close(pipex_data.fd[0][1]);
    close(pipex_data.fd[1][0]);
    close(pipex_data.fd[1][1]);
    waitpid(pipex_data.pid1, NULL, 0);
    clean_data(&pipex_data);

    return 0;
}
