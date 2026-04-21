#!/usr/bin/env python3
import pygame

print("H3110, C4P7A1N!")

print("W3LC0M3 70 TH3 H7ML P07YG0N BU1LD3R")

pygame.init()

window = pygame.display.set_mode((768, 960))
X1 = pygame.time.Clock()

pygame.display.set_caption("HTML Polygon Builder")

run=True


x=0
y=0
while run:
    pygame.time.delay(60)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False

        elif event.type == pygame.MOUSEBUTTONUP:
            x, y=event.pos
            print("{"+str(x//6)+","+str(y//6)+"}, ",end='')
            pygame.draw.rect(window, (255,255,255), (x, y, 6, 6))

    pygame.display.update()
    X1.tick(60)

pygame.quit()

print("533 U L8R, 4L1G470R")
