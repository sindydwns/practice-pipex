/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:43:33 by yonshin           #+#    #+#             */
/*   Updated: 2023/01/06 13:46:58 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define PIPE_READ pipefd[0]
#define PIPE_WRITE pipefd[1]
#define FILE1 argv[1]
#define CMD1 "/bin/cat"
#define CMD2 "/bin/cat"
#define FILE2 argv[4]

char **str_split(char const *s, char c);
void connect(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int main(int argc, char *argv[], char *envp[])
{
	int pipefd[2];
	int pid;
	int state;
	
	if (argc < 4)
		return (0);

	pipe(pipefd);
	
	for (int i = 2; i < argc - 1; i++) {
		pid = fork();
		if (pid == 0) {
			if (i == 2)
				connect(open(FILE1, O_RDONLY), STDIN_FILENO);
			close(PIPE_READ);
			connect(PIPE_WRITE, STDOUT_FILENO);
			execve(argv[i], str_split(argv[i], ' '), envp);
		}
		close(PIPE_WRITE);
		connect(PIPE_READ, STDIN_FILENO);
		if (i < argc - 2)
			pipe(pipefd);
		waitpid(pid, &state, 0);
	}
	
	char c;
	int fileout = open(FILE2, O_WRONLY | O_CREAT, 0644);
	while (read(STDIN_FILENO, &c, 1))
		write(fileout, &c, 1);
	close(fileout);
	close(STDIN_FILENO);
	waitpid(pid, &state, 0);
}

/*
int main(int argc, char *argv[], char *envp[])
{
	int pipefd[2];
	int pid;
	int state;
	
	if (argc < 4)
		return (0);

	if (pipe(pipefd) < 0)
		perror("pipe");

	pid = fork();
	if (pid == 0) { // 첫번째 자식 프로세스
	
		// int filein = open(FILE1, O_RDONLY);
		// connect(filein, STDIN_FILENO);

		close(PIPE_READ);
		connect(PIPE_WRITE, STDOUT_FILENO);
		
		execve(CMD1, NULL, envp);
		perror("execve");
		
	} else { // 부모 프로세스
		
		close(PIPE_WRITE);
		connect(PIPE_READ, STDIN_FILENO);
		
		if (pipe(pipefd) < 0)
			perror("pipe");
		
		pid = fork();
		if (pid == 0) { // 두번째 자식 프로세스

			close(PIPE_READ);
			connect(PIPE_WRITE, STDOUT_FILENO);

			execve(CMD2, NULL, envp);
			perror("execve");
			
		} else { // 부모 프로세스

			// int fileout = open(FILE2, O_WRONLY | O_CREAT);
			// connect(fileout, STDOUT_FILENO);

			close(PIPE_WRITE);
			connect(PIPE_READ, STDOUT_FILENO);

			waitpid(pid, &state, 0);
		}
	}
}
*/


/*

		if (pipe(pipefd) < 0)
			exit(1);
		if (i == 2) {
			
			close(IN);
			IN = open(argv[1], O_RDONLY);
			connect(IN, IN);
			
			connect(OUT, OUT);
			
		} else if (i < argc - 2) {
			connect(OUT, pipefd)
			OUT = open(argv[argc - 1], O_WRONLY | O_CREAT);
			connect(OUT, OUT);
		}
		
*/