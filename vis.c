#include "inc/vm.h"
/*
void	ft_fprint_hex(unsigned char c, FILE *out)
{
    char *base = "0123456789abcdef";
    fprintf(out, "%c", base[c / 16]);
    fprintf(out, "%c", base[c % 16]);
}
void	ft_print_memory_to_file(const void *addr, size_t size, FILE *out)
{
    size_t i;
    size_t j;
    unsigned  char *p;
    i = 0;
    p = (unsigned char*)addr;
    while (i < size)
    {
        j = 0;
        while (j < 64 && i + j < size)
        {
            ft_fprint_hex(p[i + j], out);
            fprintf(out, " ");
            j++;
        }
        fprintf(out, "\n");
        i += 64;
    }
}
int create_file(t_cw *cw)
{
    if (!(cw->vis->out = fopen("mem_out", "w+"))) {
        ft_printf("Не удалось создать файл");
        exit(0);
    }
    // открыть файл удалось
    ft_print_memory_to_file(cw, 4096, cw->vis->out);      // требуемые действия над данными
    fclose(cw->vis->out);
    return(0);
}
*/

int vis_init(t_cw *cw)
{
	if (!(cw->vis->font_path = "100.ttf")) {
		fprintf(stderr, "error: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIDTH, WIDTH, 0, &cw->vis->wind, &cw->vis->rend);
	TTF_Init();
	cw->vis->font = TTF_OpenFont(cw->vis->font_path, 10);
	if (cw->vis->font == NULL) {
		fprintf(stderr, "error: font not found\n");
		exit(EXIT_FAILURE);
	}
	SDL_RenderClear(cw->vis->rend);

	return(0);
}


/* Deinit TTF. */
int vis_deinit(t_cw *cw)
{

	SDL_DestroyTexture(cw->vis->tex);
	TTF_Quit();

	SDL_DestroyRenderer(cw->vis->rend);
	SDL_DestroyWindow(cw->vis->wind);
	SDL_Quit();
	return EXIT_SUCCESS;
}


/*
1. почистил карту (фон черный выставить)
2. задал начальные параметры x и y
3. в главном цикле рисуешь карту изменяя x и y
4. делаешь render release
5. возвращаешься в п.1
*/


void tex_and_rect(int x, int y, t_cw *cw) {
	int txt_w;
	int txt_h;
	SDL_Surface *surface;


	SDL_RenderPresent(cw->vis->rend);
	SDL_SetRenderDrawColor(cw->vis->rend, 0, 0, 0, 255);
	SDL_Color textColor = {111, 255, 255, 255};

	surface = TTF_RenderText_Blended(cw->vis->font, cw->vis->line, textColor);
	cw->vis->tex = SDL_CreateTextureFromSurface(cw->vis->rend, surface);
	txt_w = surface->w;
	txt_h = surface->h;
	SDL_FreeSurface(surface);
	cw->vis->rect.x = x;
	cw->vis->rect.y = y;
	cw->vis->rect.w = txt_w;
	cw->vis->rect.h = txt_h;
	/* Use TTF textures. */
	SDL_RenderCopy(cw->vis->rend, cw->vis->tex, NULL, &cw->vis->rect);
}

int 	ft_print_hex_to_line(unsigned char c, t_cw *cw, size_t tmp)
{
	size_t id;

	id = tmp;
	char *base = "0123456789abcdef";
	while (id < tmp+2) {

		cw->vis->line[id] = base[c / 16];
		id++;
		cw->vis->line[id] = base[c % 16];
		id++;
		if (id != 191) {
			cw->vis->line[id] = ' ';
			id++;
		}
	}
	return(id);
}

void	ft_print_memory_to_line(t_cw *cw, size_t o)
{
	size_t i;
	size_t tmp;
	size_t y = 50;

	tmp = 0;
	while (o < MEM_SIZE)
	{
		i = 0;
		tmp = 0;
		while (tmp < 191) {
			i = ft_print_hex_to_line(cw->map[o], cw, tmp);
			tmp = i;
			o++;
//			ft_printf("\ni = %d\n", i);

//			ft_printf("\no = %d\n", o);
		}
		tex_and_rect(20, y, cw);

		y+=12;
	}
}

void draw_map(t_cw *cw)
{
	size_t o = 0;
	ft_print_memory_to_line(cw, o);
	ft_printf("\n%s\n", cw->vis->line);
}

void   visualiser(t_cw *cw)
{
	cw->map[MEM_SIZE - 2] = 0xFE;
	draw_map(cw);


	while (!cw->vis->quit) {
		while (SDL_PollEvent(&cw->vis->event) == 1) {
			if (cw->vis->event.type == SDL_QUIT) {
				cw->vis->quit = 1;
			}
			if (cw->vis->event.type == SDL_KEYDOWN)
			{
				cw->vis->quit = 1;
			}

		}
	}
	vis_deinit(cw);

}





