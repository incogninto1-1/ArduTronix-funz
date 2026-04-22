#!/usr/bin/env python3

class pixel:
    def __init__(self, x, y):
        self.x= x
        self.y= y
        self.Next= None



import pygame

print("H3110, C4P7A1N!")

print("W3LC0M3 70 TH3 4RDU1N0 P07YG0N BU1LD3R (V3R510N 0.1)")

pygame.init()                                           #Start pygame

window = pygame.display.set_mode((768, 960))            #Make the pygame window
X1 = pygame.time.Clock()                                #Main pygame timer

pygame.display.set_caption("Arduino Polygon Builder")   #Set the title

run=True                                                            #flag to tell that the program is running


x=0                                                                 #Cursor location variables
y=0

stack = []                                                          #This is the stack where we are going to store our nodes

while run:                                                          #while the program is running
    pygame.time.delay(60)

    for event in pygame.event.get():                                #read events that pygame recognises
        if event.type == pygame.QUIT:                               #If we press the X button
            run=False                                               #The program is no longer running

        elif event.type == pygame.MOUSEBUTTONUP:                    #If the user clicks the mouse
            x, y=event.pos                                          #Get the coordinates of the cursor
            #print("{"+str(x//6)+","+str(y//6)+"}, ",end='')         #TODO: Implement a stack and add each node to the stack
            stack.append(pixel((x//6), (y//6)))                     #Push the pixel to the stack
            pygame.draw.rect(window, (255,255,255), (x, y, 6, 6))   #Place a size accurate pixel
                                                                    #TODO: place the pixels in the same way as the LCD for a WYSIWYG experience

        elif event.type == pygame.KEYUP:                            #If the user presses a key
            if event.key == pygame.K_s:                             #If that key is the 's' key on the keyboard (Save)
                print("{", end='')
                for element in stack:
                    print("{" + str(element.x) + ", " + str(element.y) + "},", end='')
                print("}")
                print(str(len(stack)) + " N0D35 L0NG")
                                                                    #TODO(maybe): Save the final structure to a TXT file
            elif event.key == pygame.K_c:                           #If the key presses is 'c' (Compile)
                print("WIP")                                        #TODO: Make a basic compiler that draws a preview 

    pygame.display.update()                                         #Refresh the screen
    X1.tick(60)                                                     #Wait for the timer

pygame.quit()                                                       #Quit the editor

print("533 U L8R, 4L1G470R")
