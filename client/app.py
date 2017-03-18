from send_data import *
from notebook import notebook

import serial

from tkinter import *

root = Tk()
n = notebook(root, LEFT)

n_f1 = Frame(n())
n_f2 = Frame(n())

n.add_screen(n_f1, "House") #Screen 1
n.add_screen(n_f2, "Office") #Screen 2

## ---- n1 ----
n1 = notebook(n_f1, LEFT)
n1_f1 = Frame(n1())
n1_f2 = Frame(n1())


n1.add_screen(n1_f1, "Living Room") #Screen 1_1
n1.add_screen(n1_f2, "Kitchen") #Screen 1_2

#Buttons

##n1_f1_b1
n1_f1_b1 = Button(n1_f1, text="Button 1")
n1_f1_b1.pack(fill=BOTH, expand=1) 
n1_f1_b2 = Button(n1_f1, text="Button 2")
n1_f1_b2.pack(fill=BOTH, expand=1) 

##n1_f2_b1
n1_f2_b1 = Button(n1_f2, text="Make Popcorn!", command = make_popcorn)
n1_f2_b1.pack(fill=BOTH, expand=1) 
n1_f2_b2 = Button(n1_f2, text="Button 4")
n1_f2_b2.pack(fill=BOTH, expand=1) 


## ---- n2 ----
# Nested
n2 = notebook(n_f2, LEFT)
n2_f1 = Frame(n2())
n2_f2 = Frame(n2())


n2.add_screen(n2_f1, "Screen 2_1")
n2.add_screen(n2_f2, "Screen 2_2")

#Buttons

##n1_f1_b1
n1_f1_b1 = Button(n2_f1, text="Button 5")
n1_f1_b1.pack(fill=BOTH, expand=1) 
n1_f1_b2 = Button(n2_f1, text="Button 6")
n1_f1_b2.pack(fill=BOTH, expand=1) 

##n1_f2_b1
n1_f2_b1 = Button(n2_f2, text="Button 7")
n1_f2_b1.pack(fill=BOTH, expand=1) 
n1_f2_b2 = Button(n2_f2, text="Button 8")
n1_f2_b2.pack(fill=BOTH, expand=1) 



# def read_data():
# 	# read EMG data. If signal is a 1, send signal to make popcorn
# 	r = ss.readline().decode('ascii').strip()
# 	if r=='1':
# 		print(r)
# 		make_popcorn()
	
# 	root.after(100, read_data)

# ss = serial.Serial('/dev/cu.usbmodem1421', 115200) #(port='COM2', baudrate=115200)
# root.after(100, read_data) # This function runs 0s after mainloop runs and calls read_data after it executes


if __name__ == "__main__":
	root.mainloop()
