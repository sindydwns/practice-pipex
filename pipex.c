/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:43:33 by yonshin           #+#    #+#             */
/*   Updated: 2023/01/06 00:02:50 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);
	int fd1 = open(argv[1], O_RDONLY);
	dup2(fd1, 0);
	close(fd1);
	int fd2 = open(argv[4], O_WRONLY);
	dup2(fd2, 1);
	close(fd2);
	char b;
	while (read(0, &b, 1) > 0)
		write(1, &b, 1);
}
