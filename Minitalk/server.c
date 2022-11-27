/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:24:06 by nachab            #+#    #+#             */
/*   Updated: 2022/11/26 19:44:52 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libserv.h"

void	my_handler(int signum, siginfo_t *sa, void *context)
{
	static int				bits;
	static int				init;
	static unsigned char	byte;

	if (init == 0)
	{
		init = 1;
		bits = 6;
		byte = 0b00000000;
	}
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		if (signum == SIGUSR1)
			byte |= (1 << bits);
	}
	bits--;
	if (bits == -1)
	{
		kill(sa->si_pid, SIGUSR1);
		ft_putchar(byte);
		bits = 6;
		byte = 0b00000000;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	printf("The process ID is == %d\n", pid);
	sa.sa_sigaction = my_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
