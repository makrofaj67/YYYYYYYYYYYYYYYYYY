/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:26:55 by rakman            #+#    #+#             */
/*   Updated: 2025/01/02 14:44:19 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
int		ft_handle_char(int character);
int		ft_handle_address(void *address);
int		ft_handle_string(char *str);
int		ft_handle_dec_int(int nb);
int		ft_handle_unsigned_int(unsigned int nb);
int		ft_handle_hexadecimal(unsigned int nb, char c);
char	*ft_itoa_base(unsigned long nb, int base);

#endif
