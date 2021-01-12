#include "inc/vm.h"

void	chain_kor(t_koretko **kors, t_koretko *kor)
{
	// t_koretko	*current;

	// current = kors;
	// while(current->next != NULL)
	// 	current = current->next;
	// curent->next = kor;
	kor->next = *kors;
	*kors = kor;
}
void	delete_koretko(int id, t_koretko **kors)
{
	t_koretko *current;
	t_koretko *prev;

	current = *kors;
	if (current->id == id)
		*kors = current->next;
	else
	{
		while (id != current->id)
		{
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
	}
	free(current);
}


t_koretko	*create_koretko(int id)
{
	t_koretko *kor;

	if (!(kor = (t_koretko*)ft_memalloc(sizeof(t_koretko))))
		return NULL;
	kor->next = NULL;
	kor->id = id;
	return kor;
}

int		ft_pow(int a, int pow)
{
	int res;

	res = a;
	if (pow == 0)
		return (1);
	while (--pow)
	{
		res *= a;
	}
	return (res);
}

int main()
{
	int x = -2;

	printf("%d", ~x);

//	printf("%d\n", x);
//	t_koretko *k1;
//	t_koretko *k2;
//	t_koretko	*k3;
//	int r[3];
//
//	k1 = create_koretko(1);
//	k2 = create_koretko(2);
//	k3 = create_koretko(3);
//
//	chain_kor(&k1, k2);
//	chain_kor(&k1, k3);
//
//	delete_koretko(3, &k1);
//	t_koretko *res = k1;
//	while (res)
//	{
//		printf("%d\n", res->id);
//		res = res->next;
//	}
//	delete_koretko(1, &k1);
//	while (k1)
//	{
//		printf("%d\n", k1->id);
//		k1 = k1->next;
//	}
//	printf("1 - %d 2 - %d 3 - %d", r[0], r[1], r[2]);

//	printf("%d", ft_pow(5, 0));
//	printf("%d\n", k1->id);
//	printf("%d\n", k1->next->id);
//	printf("%d\n", k2->id);
//	printf("%d\n", k3->id);
}
