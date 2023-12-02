/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 09:42:43 by afidalgo          #+#    #+#             */
/*   Updated: 2023/11/11 11:38:13 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

static void	handle_signal(int signum, siginfo_t *info, void *context);
static void	terminate(char *msg);

int	main(void)
{
	struct sigaction	sigusr_action;

	ft_printf("PID: %d\n", getpid());
	sigemptyset(&sigusr_action.sa_mask);
	sigusr_action.sa_flags = SA_SIGINFO;
	sigusr_action.sa_sigaction = &handle_signal;
	if (sigaction(SIGUSR1, &sigusr_action, NULL) == -1)
		terminate("Unable to set signal handler for signal SIGUSR1.");
	if (sigaction(SIGUSR2, &sigusr_action, NULL) == -1)
		terminate("Unable to set signal handler for signal SIGUSR2.");
	while (1)
	{
	}
	return (0);
}

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static char	c;
	static int	bit_count;
	static int	client_pid;

	(void)context;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		c = 0;
		bit_count = 0;
	}
	if (info->si_pid)
		client_pid = info->si_pid;
	if (!client_pid)
		terminate("Unable to send signal. Client PID is NULL.");
	if (kill(client_pid, SIGUSR1) == -1)
		terminate("Unable to send signal. Kill function failed.");
}

static void	terminate(char *msg)
{
	ft_printf("\n\n%s\n", msg);
	exit(EXIT_FAILURE);
}
