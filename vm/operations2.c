/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:31:55 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 19:32:10 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void	op_add(t_cw *cw, t_koretko *kor)
{
	int a;
	int value;

	kor->step += 2;
	value = is_reg(cw, kor) + is_reg(cw, kor);
	a = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[a - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void	op_sub(t_cw *cw, t_koretko *kor)
{
	int a;
	int value;

	kor->step += 2;
	value = is_reg(cw, kor) - is_reg(cw, kor);
	a = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[a - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void	op_and(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0], 0);
	b = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	value = a & b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void	op_or(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0], 0);
	b = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	value = a | b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void	op_xor(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0], 0);
	b = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	value = a ^ b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}
