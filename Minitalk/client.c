/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:58:59 by nachab            #+#    #+#             */
/*   Updated: 2022/11/26 19:46:50 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libserv.h"

int	send_bin(int pid, char *string)
{
	int	bits;

	while (*string)
	{
		bits = 6;
		while (bits >= 0)
		{
			if ((*string >> bits) & 1)
			{
				if (kill(pid, SIGUSR1) == -1)
					return (-1);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					return (-1);
			}
			usleep(50);
			bits--;
		}
		string++;
	}
	return (0);
}

void	my_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr("The signal was received by the server!\n");
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa;

	sa.sa_handler = my_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
	{
		ft_putstr("There was an error, please enter a valid process ID and a valid string!\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr("Please enter a valid PID as the first argument.\n");
		return (0);
	}
	if (send_bin(pid, argv[2]) == -1)
		ft_putstr("unsuccessful, nothing was sent.");
	return (0);
}
