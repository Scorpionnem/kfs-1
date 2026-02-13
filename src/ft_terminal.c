/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:15:18 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 15:57:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_terminal.h"
#include "ft_libc.h"
#include "ft_io.h"

size_t		terminal_row;
size_t		terminal_column;
uint8_t		terminal_color;
uint16_t*	terminal_buffer = (uint16_t*)VGA_MEMORY;

uint8_t	vga_entry_color(vga_color fg, vga_color bg)
{
	return fg | bg << 4;
}

uint16_t	vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

/*
	Initializes terminal with spaces to clear the screen.
*/
void	terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;

			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void	terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;

	terminal_buffer[index] = vga_entry(c, color);

	update_cursor(x + 1, y); // Set cursor on last written char
}

void	terminal_scroll_up()
{
	ft_memmove(terminal_buffer, terminal_buffer + VGA_WIDTH, (VGA_HEIGHT * (VGA_WIDTH - 1)) * sizeof(uint16_t));
	terminal_column = 0;
	terminal_row--;
	for (int i = 0; i < VGA_WIDTH; i++)
	{
		const size_t index = terminal_row * VGA_WIDTH + i;

		terminal_buffer[index] = vga_entry(' ', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));
	}
}

int	terminal_putchar(char c)
{
	if (c == '\n')
	{
		terminal_row++;
		terminal_column = 0;
		update_cursor(terminal_column, terminal_row);
		return (1);
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	terminal_column++;
	if (terminal_column == VGA_WIDTH)
	{
		terminal_row++;
		if (terminal_row == VGA_HEIGHT && terminal_column == VGA_WIDTH)
		{
			terminal_scroll_up();
			return (1);
		}
		if (terminal_row == VGA_HEIGHT)
			terminal_row = 0;
		terminal_column = 0;
	}
	return (1);
}

int	terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
	return (size);
}

int	terminal_putstr(const char* data)
{
	return (terminal_write(data, ft_strlen(data)));
}
