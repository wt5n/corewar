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

//void vis_refresh(SDL_Renderer **renderer, SDL_Texture **texture1, SDL_Texture **texture2)
    /* Deinit TTF. */
//int vis_deinit(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture **texture1, SDL_Texture **texture2)


int   visualiser(t_cw *cw)
{
    FILE *out;
    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Renderer *renderer;
    SDL_Texture *texture1, *texture2;
    SDL_Window *window;
    char *font_path;
    int quit;


        if (!(font_path = "100.ttf")) {
            fprintf(stderr, "error: too many arguments\n");
            exit(EXIT_FAILURE);
        }
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(WIDTH, WIDTH, 0, &window, &renderer);
        TTF_Init();
        TTF_Font *font = TTF_OpenFont(font_path, 24);
        if (font == NULL) {
            fprintf(stderr, "error: font not found\n");
            exit(EXIT_FAILURE);
        }

        if (!(out = fopen("out.json", "w+"))) {
            ft_printf("Не удалось создать файл");
            return(0);
        }
        // открыть файл удалось
        ft_print_memory_to_file(cw, 4096, out);      // требуемые действия над данными
        fclose(out);

        get_text_and_rect(renderer, 0, 0, "hello", font, &texture1, &rect1);
        get_text_and_rect(renderer, 0, rect1.y + rect1.h, "world", font, &texture2, &rect2);

        quit = 0;
        while (!quit) {
            while (SDL_PollEvent(&event) == 1) {
                if (event.type == SDL_QUIT) {
                    quit = 1;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            /* Use TTF textures. */
            SDL_RenderCopy(renderer, texture1, NULL, &rect1);
            SDL_RenderCopy(renderer, texture2, NULL, &rect2);

            SDL_RenderPresent(renderer);
        }


        SDL_DestroyTexture(texture1);
        SDL_DestroyTexture(texture2);
        TTF_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_SUCCESS;

}


