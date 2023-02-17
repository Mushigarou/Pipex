/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 08:38:10 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/15 19:29:47 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_sp(const char *fmt, va_list *args, unsigned int i)
{
	int	len;

	len = 0;
	if (fmt[i] == 's')
		len += printf_putstr_fd(va_arg(*args, char *), STDOUT);
	else if (fmt[i] == 'c')
		len += printf_putchar_fd(va_arg(*args, int), STDOUT);
	else if (fmt[i] == 'd' || fmt[i] == 'i')
		len += printf_putnbr_fd(va_arg(*args, int), STDOUT);
	else if (fmt[i] == 'x' || fmt[i] == 'X')
		conv_hex(va_arg(*args, unsigned int), &len, fmt[i]);
	else if (fmt[i] == 'p')
		len += wr_address(va_arg(*args, unsigned long));
	else if (fmt[i] == 'u')
		len += printf_putunbr_fd(va_arg(*args, unsigned int), STDOUT);
	else
		len += printf_putchar_fd(fmt[i], STDOUT);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list			args;
	unsigned int	i;
	int				len;

	va_start(args, fmt);
	len = 0;
	i = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			len += handle_sp(fmt, &args, i + 1);
			i++;
		}
		else
			len += printf_putchar_fd(fmt[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

// int main()
// {
//     // char    *pt = "Hey, below is an i.e of int";
//     // void    *ptr;
//     // unsigned int g = 4147483648;
//     // int          x = 2147483647;
//     // ft_printf("mine |\nchar %%c: %c\nstr  %%s: %s\n\nunsigned   
// %%u: %u\ninteger     %%d: %d\n\naddress of  %%X: %X\naddress of  
// %%x: %x\nAdress void %%p: %p",'A', pt, g, x, &x, &x, &ptr);
// //     printf("%-6d", 4);
// //     // char    p[] = "hel545lo";
// //     // printf("%s", address_toupper(p));

//     // ft_printf("mine :\n%p\n%p\n", INT_MIN, 16);
//     // printf("%+.b\n");
//    ft_printf(" %X \n", -1);
// //    return (ft_putnbr_fd(ft_printf("\001\002\007\v\010\f\r\n"), 1));
// //    printf( " %d \n", INT_MIN);
// }
