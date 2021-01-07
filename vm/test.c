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

t_koretko	*create_koretko(int id)
{
	t_koretko *kor;

	if (!(kor = (t_koretko*)ft_memalloc(sizeof(t_koretko))))
		return NULL;
	if (!(kor->regs = (t_reg*)ft_memalloc(sizeof(t_reg))))
		return NULL;
	kor->next = NULL;
	kor->id = id;
	return kor;
}

int main()
{
	t_koretko *k1;
	t_koretko *k2;
	t_koretko	*k3;

	k1 = create_koretko(1);
	k2 = create_koretko(2);
	k3 = create_koretko(3);

	chain_kor(&k1, k2);
//	chain_kor(&k1, k3);
	printf("%d\n", k1->id);
	printf("%d\n", k1->next->id);
//	printf("%d\n", k2->id);
//	printf("%d\n", k3->id);

}
