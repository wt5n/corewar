/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:34:29 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 21:33:04 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void	write_value(t_cw *cw, int adrs, int value, int size)
{
	int	i;

	i = 0;
	while (--size >= 0)
	{
		cw->map[(adrs + size) % 4096] = (value >> i * 8) & 255;
		i++;
	}
}

int		is_reg(t_cw *cw, t_koretko *koretko)
{
	int	reg;

	reg = cw->map[get_adrs(koretko, 0, 0)];
	koretko->step++;
	return (koretko->regs[reg - 1]);
}

int		is_dir(t_cw *cw, t_koretko *koretko, int n, int pha)
{
	int	value;
	int	sign;
	int	i;

	i = 0;
	value = 0;
	sign = cw->map[get_adrs(koretko, 0, pha)] & 128;
	while (n)
	{
		if (sign)
			value += (cw->map[get_adrs(koretko, n - 1, pha)]
					^ 255) << (i++ * 8);
		else
			value += (cw->map[get_adrs(koretko, n - 1, pha)]) << (i++ * 8);
		n--;
	}
	if (pha == 0)
		koretko->step += i;
	if (sign)
		value = ~value;
	return (value);
}

int		is_indir(t_cw *cw, t_koretko *koretko)
{
	int	adrs;
	int	value;

	adrs = is_dir(cw, koretko, IND_SIZE, 0);
	if (koretko->op_code != 13)
		adrs %= IDX_MOD;
	koretko->ind_adrs = adrs;
	value = is_dir(cw, koretko, DIR_SIZE, 1);
	koretko->ind_adrs = 0;
	return (value);
}

int		get_value(t_cw *cw, t_koretko *koretko, int arg, int pha)
{
	if (arg == REG_CODE)
		return (is_reg(cw, koretko));
	else if (arg == DIR_CODE)
		return (is_dir(cw, koretko,
			g_op_tab[koretko->op_code - 1].tdir_size, pha));
	else if (arg == IND_CODE)
		return (is_indir(cw, koretko));
	else
		return (0);
}
