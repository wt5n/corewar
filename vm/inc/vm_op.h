/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:20:32 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 21:33:19 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_OP_H
# define VM_OP_H

# include "vm.h"

typedef struct	s_op
{
	char		*name;
	int			op_code;
	int			num_of_args;
	int			args[3];
	int			delay;
	int			inf_carry;
	int			code_args;
	int			tdir_size;

}				t_op;

static	t_op	g_op_tab[16] =
{
	{
		.name = "live",
		.num_of_args = 1,
		.args = {T_DIR, 0, 0},
		.op_code = 1,
		.delay = 10,
		.inf_carry = 0,
		.code_args = 0,
		.tdir_size = 4
	},
	{
		.name = "ld",
		.num_of_args = 2,
		.args = {T_DIR | T_IND, T_REG, 0},
		.op_code = 2,
		.delay = 5,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "st",
		.num_of_args = 2,
		.args = {T_REG, T_IND | T_REG, 0},
		.op_code = 3,
		.delay = 5,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "add",
		.num_of_args = 3,
		.args = {T_REG, T_REG, T_REG},
		.op_code = 4,
		.delay = 10,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "sub",
		.num_of_args = 3,
		.args = {T_REG, T_REG, T_REG},
		.op_code = 5,
		.delay = 10,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "and",
		.num_of_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.op_code = 6,
		.delay = 6,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "or",
		.num_of_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.op_code = 7,
		.delay = 6,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "xor",
		.num_of_args = 3,
		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.op_code = 8,
		.delay = 6,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "zjmp",
		.num_of_args = 1,
		.args = {T_DIR, 0, 0},
		.op_code = 9,
		.delay = 20,
		.inf_carry = 0,
		.code_args = 0,
		.tdir_size = 2
	},
	{
		.name = "ldi",
		.num_of_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.op_code = 10,
		.delay = 25,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 2
	},
	{
		.name = "sti",
		.num_of_args = 3,
		.args = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.op_code = 11,
		.delay = 25,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 2
	},
	{
		.name = "fork",
		.num_of_args = 1,
		.args = {T_DIR, 0, 0},
		.op_code = 12,
		.delay = 800,
		.inf_carry = 0,
		.code_args = 0,
		.tdir_size = 2
	},
	{
		.name = "lld",
		.num_of_args = 2,
		.args = {T_DIR | T_IND, T_REG, 0},
		.op_code = 13,
		.delay = 10,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
	{
		.name = "lldi",
		.num_of_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.op_code = 14,
		.delay = 50,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 2
	},
	{
		.name = "lfork",
		.num_of_args = 1,
		.args = {T_DIR, 0, 0},
		.op_code = 15,
		.delay = 1000,
		.inf_carry = 0,
		.code_args = 0,
		.tdir_size = 2
	},
	{
		.name = "aff",
		.num_of_args = 1,
		.args = {T_REG, 0, 0},
		.op_code = 16,
		.delay = 2,
		.inf_carry = 1,
		.code_args = 1,
		.tdir_size = 4
	},
};

#endif
