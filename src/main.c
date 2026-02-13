/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:03:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 10:35:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernel.h"

void	main(void)
{
	terminal_initialize();

	terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
	terminal_writestring("42");
	while (1)
	{
		;
	}
}
