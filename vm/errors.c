#include "inc/vm.h"

void	output_error(int n)
{
	n == 1 ? write(2, "Wrong MAGIC number\n", 19) : 0;
	n == 2 ? write(2, "Wrong file name\n", 19) : 0;
	n == 3 ? write(2, "No NULL in .cor file\n", 22) : 0;
	n == 4 ? write(2, "Wrong champ size\n", 18) : 0;
}