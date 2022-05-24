#!/usr/bin/env python3
 
"""
CronTab:        https://www.makeuseof.com/how-to-run-a-raspberry-pi-program-script-at-startup/
Make HC06 work: https://dev.to/ivanmoreno/how-to-connect-raspberry-pi-with-hc-05-bluetooth-module-arduino-programm-3h7a
"""
 
import pygame
import time
import serial
import random
 
#List of selected sounds
hums = ["/home/pi/Desktop/Jedi/hum/HUM1.mp3", "/home/pi/Desktop/Jedi/hum/HUM7.mp3", "/home/pi/Desktop/Jedi/hum/HUM13.mp3", "/home/pi/Desktop/Jedi/hum/HUM17.mp3","/home/pi/Desktop/Jedi/hum/HUM23.mp3"]
screams = ["/home/pi/Desktop/Jedi/scream/SCREAM1.mp3", "/home/pi/Desktop/Jedi/scream/SCREAM2.mp3", "/home/pi/Desktop/Jedi/scream/SCREAM3.mp3", "/home/pi/Desktop/Jedi/scream/SCREAM4.mp3"]
sents = ["/home/pi/Desktop/Jedi/sent/SENT2.mp3", "/home/pi/Desktop/Jedi/sent/SENT4.mp3", "/home/pi/Desktop/Jedi/sent/SENT5.mp3", "/home/pi/Desktop/Jedi/sent/SENT17.mp3", "/home/pi/Desktop/Jedi/sent/SENT20.mp3"]
procs = ["/home/pi/Desktop/Jedi/proc/PROC2.mp3", "/home/pi/Desktop/Jedi/proc/PROC3.mp3", "/home/pi/Desktop/Jedi/proc/PROC5.mp3", "/home/pi/Desktop/Jedi/proc/PROC13.mp3", "/home/pi/Desktop/Jedi/proc/PROC15.mp3"]
 
pygame.init()
screen = pygame.display.set_mode((400,400))
 
try:
    arduinoBody = serial.Serial('/dev/ttyACM0', 9600)
    print("Connected to Arduino Body through /dev/ttyACM0")
except:
    print("Could not connect to Arduino Body")
    
try:
    arduinoHead = serial.Serial('/dev/rfcomm0', 9600)
    print("Connected to Arduino Head through /dev/rfcomm0")
except:
    print("Could not connect to Arduino Head")
    
        
time.sleep(1)
 
while True:
    for event in pygame.event.get():
        #Should be a switch-case but no python 3.10 on pi
        if event.type == pygame.KEYDOWN:
            
            if event.key == pygame.K_i:
                print("pygame.K_i | HUM")
                pygame.mixer.init()
                soundChoice = random.randint(0, 4)
                pygame.mixer.music.load(hums[soundChoice])
                pygame.mixer.music.play()
                
            elif event.key == pygame.K_u:
                print("pygame.K_u | PROC")
                pygame.mixer.init()
                soundChoice = random.randint(0, 4)
                pygame.mixer.music.load(procs[soundChoice])
                pygame.mixer.music.play()
            
            elif event.key == pygame.K_p:
                print("pygame.K_p | SENT")
                pygame.mixer.init()
                soundChoice = random.randint(0, 4)
                pygame.mixer.music.load(sents[soundChoice])
                pygame.mixer.music.play()
                
            elif event.key == pygame.K_o:
                print("pygame.K_o | SCREAM")
                pygame.mixer.init()
                soundChoice = random.randint(0, 3)
                pygame.mixer.music.load(screams[soundChoice])
                pygame.mixer.music.play()
                
            elif event.key == pygame.K_1:
                print("pygame.K_1 | D-PAD UP")
                arduinoHead.write('$'.encode())
            
            elif event.key == pygame.K_2:
                print("pygame.K_2 | D-PAD LEFT")
                arduinoHead.write('#'.encode())
            
            elif event.key == pygame.K_3:
                print("UNUSED INPUT | pygame.K_3 | D-PAD DOWN")
                
            elif event.key == pygame.K_4:
                print("UNUSED INPUT | pygame.K_4 | D-PAD RIGHT")
                
            elif event.key == pygame.K_5:
                print("pygame.K_5 | CANTINA")
                pygame.mixer.init()
                pygame.mixer.music.load("/home/pi/Desktop/Jedi/mix/CANTINA.mp3")
                pygame.mixer.music.play()
            
            elif event.key == pygame.K_6:
                print("pygame.K_6 | ANNOYED")
                pygame.mixer.init()
                pygame.mixer.music.load("/home/pi/Desktop/Jedi/mix/ANNOYED.mp3")
                pygame.mixer.music.play()
                
            elif event.key == pygame.K_7:
                print("pygame.K_7 | SHORT CIRCUIT")
                pygame.mixer.init()
                pygame.mixer.music.load("/home/pi/Desktop/Jedi/mix/SHORTCKT.mp3")
                pygame.mixer.music.play()
                
            elif event.key == pygame.K_8:
                print("pygame.K_8 | SPEED BOOST + SCREAM")
                pygame.mixer.init()
                pygame.mixer.music.load("/home/pi/Desktop/Jedi/scream/SCREAM1.mp3")
                pygame.mixer.music.play()
                #RUN FAST HERE
                
            #The idea here was to have 2 states based on the start/select button so you could use more types of sounds but never got implemented
            #but I just like using copyrighted music so I set it to that for now
            elif event.key == pygame.K_9:
                print("pygame.K_9 | Audio Set 1")
                pygame.mixer.init()
                pygame.mixer.music.load("/home/pi/Desktop/Sunshine.ogg")
                pygame.mixer.music.play()
                
            elif event.key == pygame.K_0:
                print("pygame.K_0 | Audio Set 2")
                pygame.mixer.init()
                pygame.mixer.music.load("/home/pi/Desktop/Someday.ogg")
                pygame.mixer.music.play()
            
            elif event.key == pygame.K_w:
                print("pygame.K_w")
                arduinoBody.write('w'.encode())
                
            elif event.key == pygame.K_a:
                print("pygame.K_a")
                arduinoBody.write('a'.encode())
            
            elif event.key == pygame.K_s:
                print("pygame.K_s")
                arduinoBody.write('s'.encode())
                
            elif event.key == pygame.K_d:
                print("pygame.K_d")
                arduinoBody.write('d'.encode())
                
            elif event.key == pygame.K_RIGHT:
                print("pygame.K_RIGHT")
                arduinoBody.write('6'.encode())
                
            elif event.key == pygame.K_LEFT:
                print("pygame.K_LEFT")
                arduinoBody.write('7'.encode())
            
            #The original plan here was to be able to tilt a camera up and down using one of the 'eyes' in the R2D2 head
            elif event.key == pygame.K_UP:
                print("pygame.K_UP")
                #Tilt head up
                
            elif event.key == pygame.K_DOWN:
                print("pygame.K_DOWN")
                #Tilt head up
                
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_w or event.key == pygame.K_s:
                arduinoBody.write('y'.encode())
            elif event.key == pygame.K_a or event.key == pygame.K_d:
                arduinoBody.write('z'.encode())
            elif event.key == pygame.K_RIGHT or event.key == pygame.K_LEFT:
                arduinoBody.write('8'.encode())
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()