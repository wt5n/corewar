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
	cw->vis->wind = SDL_CreateWindow("Corewar", 100, 100, (WIDTH), (HEIGHT), SDL_WINDOW_SHOWN);
	cw->vis->rend = SDL_CreateRenderer(cw->vis->wind, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	cw->vis->font = TTF_OpenFont(cw->vis->font_path, 12);
	if (cw->vis->font == NULL) {
		fprintf(stderr, "error: font not found\n");
		exit(EXIT_FAILURE);
	}
	return(0);
}


/* Deinit TTF. */
int vis_deinit(t_cw *cw)
{
//	SDL_DestroyTexture(cw->vis->tex);
	SDL_DestroyRenderer(cw->vis->rend);
	SDL_DestroyWindow(cw->vis->wind);
	SDL_Quit();
	TTF_Quit();
	return EXIT_SUCCESS;
}


/*
1. почистил карту (фон черный выставить)
2. задал начальные параметры x и y
3. в главном цикле рисуешь карту изменяя x и y
4. делаешь render release
5. возвращаешься в п.1
*/

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

void tex_and_rect(int x, int y, t_cw *cw, SDL_Rect *rect, SDL_Texture **tex)
{
	int txt_w;
	int txt_h;

	cw->vis->txt_col.r = 111;
	cw->vis->txt_col.g = 255;
	cw->vis->txt_col.b = 255;
	cw->vis->txt_col.a = 255;

	cw->vis->surface = TTF_RenderText_Solid(cw->vis->font, cw->vis->line, cw->vis->txt_col);
	*tex = SDL_CreateTextureFromSurface(cw->vis->rend, cw->vis->surface);
	txt_w = cw->vis->surface->w;
	txt_h = cw->vis->surface->h;
	SDL_FreeSurface(cw->vis->surface);
	/* Use TTF textures. */
//	SDL_SetRenderDrawColor(cw->vis->rend, 0, 0, 0, 255);
//	SDL_RenderDrawRect(cw->vis->rend, &rect);
	rect->x = x;
	rect->y = y;
	rect->w = txt_w;
	rect->h = txt_h;
	ft_printf("00000");
}

void draw_map(t_cw *cw, SDL_Rect	*rect, SDL_Texture **tex_arr)
{
	size_t i;
	size_t o;
	size_t tmp;
	size_t id = 0;


	o = 0;

	while (o < MEM_SIZE && id < 64) {

		tmp = 0;
		while (tmp < 191) {
			i = ft_print_hex_to_line(cw->map[o], cw, tmp);
			tmp = i;
			o++;
		}
		ft_printf("\n%s\n", cw->vis->line);
		if(id == 0) {
			ft_printf("11111");
			tex_and_rect(25, 0, cw, &rect[id], &*(tex_arr + id));
		}
		else {
			ft_printf("33333");
			tex_and_rect(25, rect[id].y + 14, cw, &rect[id], &*(tex_arr + id));
		}//SDL_Delay(100);
		ft_printf("22222");


			id++;
			ft_printf("   id = %d\n", id);
		}

}


void   visualiser(t_cw *cw) {
	SDL_Rect rect[64];
	SDL_Texture *tex_arr[64];
	int id =0;
	int quit = 0;

	cw->map[MEM_SIZE - 2] = 0xFE;
	memset((cw->map + (MEM_SIZE - 64)), 0xaa, 64);
	memset((cw->map + 64), 0xAA, 64);
	memset((cw->map + 128), 0xBB, 64);
	memset((cw->map + 192), 0xCC, 64);
	memset((cw->map + 192 + 64), 0xDD, 64);
	memset((cw->map + 192 + 128), 0xee, 64);
	memset((cw->map + 192 + 128 + 64), 0xFF, 64);
//	memset((cw->map ), 0xee, 64);

	SDL_SetRenderDrawColor(cw->vis->rend, 0, 0, 0, 0);
	SDL_RenderClear(cw->vis->rend);
	draw_map(cw, rect, &tex_arr);
	ft_printf("55555");

	while (!cw->vis->quit) {
		while (SDL_PollEvent(&cw->vis->event) == 1) {
			if (cw->vis->event.type == SDL_QUIT) {
				cw->vis->quit = 1;
			}
			if (cw->vis->event.type == SDL_KEYDOWN) {
				cw->vis->quit = 1;
			}
		}
		while (id < 64) {
			SDL_RenderCopy(cw->vis->rend, tex_arr[id], NULL, &rect[id]);
			SDL_RenderPresent(cw->vis->rend);
			id++;
		}
	}
	vis_deinit(cw);

}





