int		ft_pow(int a, int pow)
{
	int res;

	res = a;
	if (pow == 0)
		return (1);
	while (--pow)
		res *= a;
	return (res);
}