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

void	vis_init(t_cw *cw)
{
	//INIT
	if (!(cw->vis->font_path = "100.ttf")) {
		fprintf(stderr, "error: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	SDL_Init(SDL_INIT_VIDEO); // init video
	TTF_Init();

	cw->vis->font = TTF_OpenFont(cw->vis->font_path, 10);
	if (cw->vis->font == NULL) {
		fprintf(stderr, "error: font not found\n");
		exit(EXIT_FAILURE);
	}
	// create the window like normal
	cw->vis->wind = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	// but instead of creating a renderer, we can draw directly to the screen
	cw->vis->scrn = SDL_GetWindowSurface(cw->vis->wind);
	/* Creating the surface. */
	cw->vis->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);	////////////////
	SDL_FillRect(cw->vis->sur, NULL, SDL_MapRGB(cw->vis->sur->format, 0, 0, 0));
	cw->vis->quit = 0;
}


/* Deinit TTF. */
/*int vis_deinit(t_cw *cw)
{
//	SDL_DestroyTexture(cw->vis->tex);
	SDL_DestroyRenderer(cw->vis->rend);
	SDL_DestroyWindow(cw->vis->wind);
	SDL_Quit();
	TTF_Quit();
	return EXIT_SUCCESS;
}*/


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

int DrawText(SDL_Surface* screen, TTF_Font* font, const char* text, int pos)
{
	SDL_Color color = {255,0,0, 1};
	SDL_Surface *text_surface;

	text_surface = TTF_RenderText_Solid(font, text, color);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = pos*12;
	if (text_surface != NULL)
	{
		SDL_BlitSurface(text_surface, NULL, screen, &rect);
		SDL_FreeSurface(text_surface);
		return 1;
	}
	else
	{
		// report error
		return 0;
	}
}

void 	read_and_draw(t_cw *cw)
{
	size_t i;
	size_t o;
	size_t tmp;
	o = 0;
	int y = 0;
	while (o < MEM_SIZE/* && id < 64*/) {

		tmp = 0;
		while (tmp < 191) {
			i = ft_print_hex_to_line(cw->map[o], cw, tmp);
			tmp = i;
			o++;
		}
		DrawText(cw->vis->scrn, cw->vis->font, cw->vis->line, y);
		y++;
		//	ft_printf("%s\n", cw->vis->line);
	}
	o = 0;
}

void   visualiser(t_cw *cw)
{
	////////////////
	SDL_Surface *image;
	////////////////
	//Event handler
//	EXAMPLE
/*	char sym[2];
	sym[0]=40;
	sym[1]=0;
*/
	while (!cw->vis->quit) {
		while (SDL_PollEvent(&cw->vis->eve) != 0) {
			//User requests quit
			if (cw->vis->eve.type == SDL_QUIT) {
				cw->vis->quit = 1;
			}
				//User presses a key
			else if (cw->vis->eve.type == SDL_KEYDOWN) {
				//Select surfaces based on key press
				switch (cw->vis->eve.key.keysym.sym) {
					case SDLK_DOWN:
						cw->vis->quit = 1;
						break;
				}
			}
		}
		////////////////
		read_and_draw(cw);
		////////////////
//	EXAMPLE
/*		for (int y=0; y < 64; y++)
		{
			DrawText(screen, cw->vis->font, cw->vis->line, y);
		}
		DrawText(screen, cw->vis->font, sym, 5);
*/

		SDL_UpdateWindowSurface(cw->vis->wind);
//	EXAMPLE
/*		sym[0]=sym[0]+1;
		if (sym[0] > 120)
			sym[0]=40;
*/
		SDL_BlitSurface(cw->vis->sur, NULL, cw->vis->scrn, NULL);
		SDL_Delay(500);
	}
//	vis_deinit(cw);
}





