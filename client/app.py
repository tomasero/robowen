from send_data import *
from notebook import notebook

import serial

from tkinter import *

class FullScreenApp(object):
    def __init__(self, master, **kwargs):
        self.master=master
        pad=3
        self._geom='200x200+0+0'
        master.geometry("{0}x{1}+0+0".format(
            master.winfo_screenwidth()//2-pad, master.winfo_screenheight()-pad))
        #master.bind('<Escape>',self.toggle_geom)            
    def toggle_geom(self,event):
        geom=self.master.winfo_geometry()
        print(geom,self._geom)
        self.master.geometry(self._geom)
        self._geom=geometry

def writeToLog(msg):
    numlines = log.index('end - 1 line').split('.')[0]
    log['state'] = 'normal'
    if numlines==24:
        log.delete(1.0, 2.0)
    if log.index('end-1c')!='1.0':
        log.insert('end', '\n')
    log.insert('end', msg)
    log.see(END)
    log['state'] = 'disabled'

SECTION_BACKGROUND="#9DE7A0"
SUBSECTION_BACKGROUND="#DAE2C1"

root = Tk()
app=FullScreenApp(root)
root.wm_title("HAH - House Automation Hub")
n = notebook(root, LEFT, select_bg=SECTION_BACKGROUND)

n_f1 = Frame(n())
n_f2 = Frame(n())

n.add_screen(n_f1, "House") #Screen 1
n.add_screen(n_f2, "Office") #Screen 2


######## START HOUSE ########

house = notebook(n_f1, LEFT, select_bg=SUBSECTION_BACKGROUND)
house_f1 = Frame(house())
house_f2 = Frame(house())
house_f3 = Frame(house())
house_f4 = Frame(house())

door_radio_button = house.add_screen(house_f1, "Door") #Screen 1_1
kitchen_appliances_radio_button = house.add_screen(house_f2, "Kitchen\nAppliances") #Screen 1_2
# heater_radio_button = house.add_screen(house_f3, "Heater") #Screen 1_3
lightsradio_button = house.add_screen(house_f4, "Lights") #Screen 1_4


## HOUSE > f1 (Door)
house_f1_b1 = Button(house_f1, text="Open Door",  command = lambda: writeToLog(open_door()), pady=30)
house_f1_b1.pack(fill=BOTH, expand=1) 
# house_f1_b2 = Button(house_f1, text="Prop Open Door",  command = lambda: writeToLog("Prop Open Door"))
# house_f1_b2.pack(fill=BOTH, expand=1) 


## HOUSE > f2 (Kitchen Appliances)
make_popcorn_btn = Button(house_f2, text="Make Popcorn!", command = lambda: writeToLog(make_popcorn()), pady=30)
make_popcorn_btn.pack(fill=BOTH, expand=1) 

## HOUSE > f4 (Lights)
lights_btn = Button(house_f4, text="Turn Lights on!", command = lambda: writeToLog(light_on()), pady=30)
lights_btn.pack(fill=BOTH, expand=1) 

## HOUSE > f3 (Heater)
status_lbl = Label(house_f4, text="Light\nintensity", padx=30, pady=30)
status_lbl.pack(side = LEFT)
heater_scale = Scale(house_f4, from_=0, to=100, orient=HORIZONTAL, length=300)#, command = lambda: writeToLog("Temperature adjusted to X"))
heater_scale.pack(side=LEFT)



## HOUSE > f4
#TODO

######## END HOUSE ########


######## START OFFICE ########
#TODO: the following is just a placeholder
## ---- n2 ----
# Nested
n2 = notebook(n_f2, LEFT, select_bg=SUBSECTION_BACKGROUND)
n2_f1 = Frame(n2())
n2_f2 = Frame(n2())


n2.add_screen(n2_f1, "Screen 2_1")
n2.add_screen(n2_f2, "Screen 2_2")

#Buttons

##house_f1_b1
house_f1_b1 = Button(n2_f1, text="Button 5")
house_f1_b1.pack(fill=BOTH, expand=1) 
house_f1_b2 = Button(n2_f1, text="Button 6")
house_f1_b2.pack(fill=BOTH, expand=1) 

##house_f2_b1
house_f2_b1 = Button(n2_f2, text="Button 7")
house_f2_b1.pack(fill=BOTH, expand=1) 
house_f2_b2 = Button(n2_f2, text="Button 8")
house_f2_b2.pack() 


status_label = Label(root, text="Log:")
status_label.pack()

S = Scrollbar(root)
log = Text(root, state='disabled', width=80, height=24, wrap='none', relief=GROOVE, borderwidth=2)
log.config(font=("Courier", 14))
S.pack(side=RIGHT, fill=Y)
log.pack(side=LEFT, expand=1, fill=Y)
S.config(command=log.yview)
log.config(yscrollcommand=S.set)

# S = Scrollbar(root)
# T = Text(root, height=4, width=50)
# S.pack(side=RIGHT, fill=Y)
# T.pack(side=LEFT, fill=Y)
# S.config(command=T.yview)
# T.config(yscrollcommand=S.set)

######## END OFFICE ########


# def read_data():
#   # read EMG data. If signal is a 1, send signal to make popcorn
#   r = ss.readline().decode('ascii').strip()
#   if r=='1':
#       print(r)
#       make_popcorn()
    
#   root.after(100, read_data)

# ss = serial.Serial('/dev/cu.usbmodem1421', 115200) #(port='COM2', baudrate=115200)
# root.after(100, read_data) # This function runs 0s after mainloop runs and calls read_data after it executes


if __name__ == "__main__":
    root.mainloop()
