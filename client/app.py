import requests
from send_data import *
from tkinter import *

import serial


#TODO: starting point for client app

top = Tk()

URL = Frame(top, height=500, width=150, background='black')
channel = Frame(top, height=500, width=300, background='blue')
b=Button(channel, height=3, width=30, command=make_popcorn, text='Make Popcorn!')
c=Button(channel, height=3, width=30, background='red')


URL.pack(side = 'left')
channel.pack(side='top')
b.pack(padx=30, pady=30, side='top')
c.pack(side='top', padx=30, pady=30)


def read_data():
	# read EMG data. If signal is a 1, send signal to make popcorn
	r = ss.readline()
	if r=='1':
		make_popcorn()
	print(r)


# Establish a connection with the Arduino
ss = serial.Serial('/dev/cu.usbmodem1421', 115200) #(port='COM2', baudrate=115200)
top.after(0, read_data) # This function runs 0s after mainloop runs and calls read_data after it executes

top.mainloop()