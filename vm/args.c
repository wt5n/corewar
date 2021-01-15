#include "inc/vm.h"

int		get_adrs(t_koretko *koretko, int modif)
{
	int	adrs;

	if (koretko->ind_adrs > 0)
		adrs = koretko->position + koretko->ind_adrs + modif;
	else
		adrs = koretko->position + koretko->step + modif;
	adrs %= MEM_SIZE;
	if (adrs < 0)
		adrs += MEM_SIZE;
	return (adrs);
}

int		is_reg(t_cw *cw, t_koretko *koretko)
{
	int	reg;

	reg = cw->map[get_adrs(koretko, 0)];
	koretko->step++;
	return (koretko->regs[reg - 1]);
}

int		is_dir(t_cw *cw, t_koretko *koretko, int n)
{
	int	value;
	int	sign;
	int	i;

	i = 0;
	value = 0;
	sign = cw->map[get_adrs(koretko, 0)] & 128;
	koretko->step += n;
	while (n)
	{
		if (sign)
			value += (cw->map[get_adrs(koretko, n)] ^ 255) << (i++ * 8);
		else
			value += (cw->map[get_adrs(koretko, n)]) << (i++ * 8);
		n--;
	}
	if (sign)
		value = ~value;
	return (value);
}

int		is_indir(t_cw *cw, t_koretko *koretko, int n)
{
	int	adrs;
	int	value;

	adrs = is_dir(cw, koretko, T_IND);
	if (koretko->op_code != 13)
		adrs %= IDX_MOD;
	koretko->ind_adrs = adrs;
	value = is_dir(cw, koretko, n);
	koretko->ind_adrs = 0;
	return (value);
}

int		get_value(t_cw *cw, t_koretko *koretko, int arg)
{
	if (arg == T_REG)
		return (is_reg(cw, koretko));
	else if (arg == T_DIR)
		return (is_dir(cw, koretko, op_tab[koretko->op_code - 1].tdir_size));
	else if (arg == T_IND)
		return (is_indir(cw, koretko, arg));
	else
		return (0);
}