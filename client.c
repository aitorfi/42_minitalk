/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 09:42:40 by afidalgo          #+#    #+#             */
/*   Updated: 2023/11/11 11:35:46 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	g_wait = 0;

static void	handle_server_response(int signum);
static void	send_str(int pid, char *str);
static void	send_signal(int pid, int signal);
static void	terminate(char *msg);

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sigusr_action;
	int					i;

	if (argc != 3 || ft_strlen(argv[2]) == 0)
		terminate("Invalid input.");
	i = 0;
	while (argv[1][i] != '\0')
	{
		if (!ft_isdigit(argv[1][i]))
			terminate("Invalid input.");
		i++;
	}
	sigusr_action.sa_handler = handle_server_response;
	sigemptyset(&sigusr_action.sa_mask);
	sigusr_action.sa_flags = 0;
	if (sigaction(SIGUSR1, &sigusr_action, NULL) == -1)
		terminate("Unable to set signal handler.");
	server_pid = ft_atoi(argv[1]);
	send_str(server_pid, argv[2]);
	return (0);
}

static void	handle_server_response(int signum)
{
	if (signum == SIGUSR1)
		g_wait = 0;
}

static void	send_str(int pid, char *str)
{
	int		i;
	int		bit_count;

	i = 0;
	while (str[i] != '\0')
	{
		bit_count = 7;
		while (bit_count >= 0)
		{
			g_wait = 1;
			if (str[i] & 1 << bit_count)
				send_signal(pid, SIGUSR2);
			else
				send_signal(pid, SIGUSR1);
			bit_count--;
			while (g_wait)
			{
			}
		}
		i++;
	}
}

static void	send_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		terminate("Unable to send signal. Kill function failed.");
}

static void	terminate(char *msg)
{
	ft_printf("\n\n%s\n", msg);
	exit(EXIT_FAILURE);
}
