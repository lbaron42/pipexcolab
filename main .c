#include "pipexlib.h"
//adding useful comments

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


int execute_program(char **arg_vec, char *path)
{
    if (execve(path, arg_vec, NULL) == -1) {
        perror("Could not execute");
    }
    printf("ops, something went wrong");
    return 0;
}


int pipe_function(data *pipex_data)
{
    pipex_data->pid1 = fork();
    if (pipex_data->pid1 < 0) {
        return 2;
    }

    if (pipex_data->pid1 == 0) {
        dup2(pipex_data->fd1[1], STDOUT_FILENO);
        // dup2(fd_read, STDIN_FILENO);
        printf("STDOUT is %d\n", STDOUT_FILENO);
        printf("is this working?\n");

        close(pipex_data->fd1[0]);
        close(pipex_data->fd1[1]);
        execute_program(pipex_data->arg_vec1, pipex_data->path1); //<--
    }
    pipex_data->pid2 = fork();
    if (pipex_data->pid2 < 0) {
        return 3;
    }
    if (pipex_data->pid2 == 0) {
        dup2(pipex_data->fd1[0], STDIN_FILENO);
        // dup2(fd_write, STDOUT_FILENO);

        printf("STDIN is %d\n", STDIN_FILENO);
        close(pipex_data->fd1[0]);
        close(pipex_data->fd1[1]);
        execute_program(pipex_data->arg_vec2, pipex_data->path2);
    }
    return 0;
}


/*
//OLD backup of pipe_function
int pipe_function(char *cmd, char **argv, int fd_read, int fd_write)
{
    int pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }

    if (pid1 == 0) {
        dup2(fd_write, STDOUT_FILENO);
        // dup2(fd_read, STDIN_FILENO);
        printf("STDOUT is %d\n", STDOUT_FILENO);
        printf("is this working?\n");

        close(fd_read);
        close(fd_write);
        execute_program("cat", argv[1]);
    }
    int pid2 = fork();
    if (pid2 < 0) {
        return 3;
    }
    if (pid2 == 0) {
        dup2(fd_read, STDIN_FILENO);
        // dup2(fd_write, STDOUT_FILENO);

        printf("STDIN is %d\n", STDIN_FILENO);
        close(fd_read);
        close(fd_write);
        execute_program("grep", "in");
    }
}
*/

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
}



int main(int argc, char *argv[], char **envp)
{
    data	pipex_data;


    pipex_data.arg_vec1 = malloc(sizeof(char*) * 2);
    pipex_data.arg_vec1[0] = strdup("cat");
    pipex_data.arg_vec1[1] = strdup(argv[1]);

    pipex_data.arg_vec2 = ft_split(argv[2], ' '); // have to free cmd_pin and give a pointer to result [1] of ft_split
/*    char cmd_pout[] = ft_split(argv[3])[0];
    char arg_out[] = ft_split(argv[3])[1];*/

    char **path_to_validate = find_path(envp);



    //char *arg_vec[] = {cmd_pin, arg_in, NULL};
    pipex_data.path1 = valid_path(path_to_validate, "cat"); //potential issue
    pipex_data.path2 = valid_path(path_to_validate,  pipex_data.arg_vec2[0]);

    /*
    if (execve(path, argVec, NULL) == -1) {
        perror("Could not execute");
    }
*/

    if (pipe(pipex_data.fd1) == -1) {
        return 1;
    }
    pipex_data.pid1 = pipe_function(&pipex_data);
    if (pipe(pipex_data.fd2) == -1) {
        return 1;
    }

   /* close(pipex_data.fd1[0]);
    close(pipex_data.fd1[1]);
    close(pipex_data.fd2[0]);
    close(pipex_data.fd2[1]);*/

    waitpid(pipex_data.pid1, NULL, 0);
    waitpid(pipex_data.pid2, NULL, 0);
    //clean_ptrs(path_to_validate);
    clean_data(&pipex_data);

    return 0;
}
