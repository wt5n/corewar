import pygame
import sys
pygame.init()

screenSizeX = 1080
screenSizeY = 720
screenSize = (screenSizeX,screenSizeY)

screen = pygame.display.set_mode(screenSize,0)
pygame.display.set_caption("Display Text")

WHITE = (255,255,255)
GREEN = (0,255,0)
BLUE = (0,0,255)
RED = (255,0,0)
YELLOW = (255,255,0)
BLACK = (0,0,0)
x = 100
y = 100


data = open("out.txt", "r")

def textOutput(line):
    fontTitle = pygame.font.SysFont("Arial", 72)
    textTitle = fontTitle.render(line, True, GREEN)
    screen.blit(textTitle, (x,y))

pygame.display.update()
print (data)

go = True
while go:
    for event in pygame.event.get():
        if event.type ==pygame.QUIT:
            go = False
        screen.fill(WHITE)
        fontTitle = pygame.font.SysFont("Arial", 72)
        textTitle = fontTitle.render(text, True, GREEN)
        screen.blit(textTitle, (x,y))

        pygame.display.update()

data.close()

pygame.quit()
sys.exit()