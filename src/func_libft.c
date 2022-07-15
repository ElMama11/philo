/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:27:14 by mverger           #+#    #+#             */
/*   Updated: 2022/07/15 16:52:57 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	neg;

	neg = 0;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		nb *= -1;
	return (nb);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return ((str1[i] - str2[i]));
		i++;
	}
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (char)c;
		i++;
	}
	return (b);
}