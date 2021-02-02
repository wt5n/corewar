#include "inc/vm.h"

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

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
                       TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}
int vis_init(t_cw *cw)
{
    if (!(cw->vis->font_path = "100.ttf")) {
        fprintf(stderr, "error: too many arguments\n");
        exit(EXIT_FAILURE);
    }
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, WIDTH, 0, &cw->vis->window, &cw->vis->renderer);
    TTF_Init();
    cw->vis->font = TTF_OpenFont(cw->vis->font_path, 10);
    if (cw->vis->font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}

//void vis_refresh(t_cw *cw)
    /* Deinit TTF. */
int vis_deinit(t_cw *cw)
{

        SDL_DestroyTexture(cw->vis->texture1);
        SDL_DestroyTexture(cw->vis->texture2);
        TTF_Quit();

        SDL_DestroyRenderer(cw->vis->renderer);
        SDL_DestroyWindow(cw->vis->window);
        SDL_Quit();
        return EXIT_SUCCESS;
}

void draw_map(t_cw *cw)
{
    int gnl;

    cw->vis->line = NULL;
    cw->vis->fd = open("mem_out", O_RDONLY);
    gnl = get_next_line(cw->vis->fd, &cw->vis->line);
    ft_printf("line = %s\n", cw->vis->line);

    get_text_and_rect(cw->vis->renderer, 0, 0, cw->vis->line, cw->vis->font, &cw->vis->texture1, &cw->vis->rect1);
    while (gnl ) {

        if (cw->vis->line)
            ft_strdel(&cw->vis->line);
        gnl = get_next_line(cw->vis->fd, &cw->vis->line);
        if (cw->vis->line)
            ft_printf("line = %s\n", cw->vis->line);
        //get_text_and_rect(cw->vis->renderer, 0, cw->vis->rect1.y + cw->vis->rect1.h, cw->vis->line, cw->vis->font, &cw->vis->texture2, &cw->vis->rect2);
    }
    if (cw->vis->line)
        ft_strdel(&cw->vis->line);
}

int   visualiser(t_cw *cw)
{
 /*       if (!(cw->vis->out = fopen("out.json", "w+"))) {
            ft_printf("Не удалось создать файл");
            return(0);
        }
        // открыть файл удалось
        ft_print_memory_to_file(cw, 4096, cw->vis->out);      // требуемые действия над данными
        fclose(cw->vis->out);
*/
        draw_map(cw);



            SDL_SetRenderDrawColor(cw->vis->renderer, 0, 0, 0, 0);
            SDL_RenderClear(cw->vis->renderer);

            /* Use TTF textures. */
            SDL_RenderCopy(cw->vis->renderer, cw->vis->texture1, NULL, &cw->vis->rect1);
            SDL_RenderCopy(cw->vis->renderer, cw->vis->texture2, NULL, &cw->vis->rect2);

            SDL_RenderPresent(cw->vis->renderer);
        }



