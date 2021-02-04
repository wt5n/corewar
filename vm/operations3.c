/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:32:57 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 19:33:08 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void	op_ld(t_cw *cw, t_koretko *kor)
{
	int value;
	int reg;

	kor->step += 2;
	value = get_value(cw, kor, kor->args[0], 0);
	kor->carry = value == 0 ? 1 : 0;
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[reg - 1] = value;
	kor->step++;
}

void	op_ldi(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int reg;

	kor->step += 2;
	first_arg = get_value(cw, kor, kor->args[0], 0);
	second_arg = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->ind_adrs = (first_arg + second_arg) % IDX_MOD;
	kor->regs[reg - 1] = is_dir(cw, kor, DIR_SIZE, 1);
	kor->ind_adrs = 0;
	kor->step++;
}

void	op_lld(t_cw *cw, t_koretko *kor)
{
	int value;
	int reg;

	kor->step += 2;
	value = get_value(cw, kor, kor->args[0], 0);
	kor->carry = value == 0 ? 1 : 0;
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[reg - 1] = value;
	kor->step++;
}

void	op_lldi(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int reg;

	kor->step += 2;
	first_arg = get_value(cw, kor, kor->args[0], 0);
	second_arg = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->ind_adrs = first_arg + second_arg;
	kor->carry = kor->ind_adrs == 0 ? 1 : 0;
	kor->regs[reg - 1] = is_dir(cw, kor, DIR_SIZE, 1);
	kor->ind_adrs = 0;
	kor->step++;
}

void	op_aff(t_cw *cw, t_koretko *kor)
{
	kor->step += 2;
	ft_printf("Aff: %c\n", is_reg(cw, kor));
}
