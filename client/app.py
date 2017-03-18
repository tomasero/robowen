import requests
from send_data import *
from tkinter import *

#TODO: starting point for client app

top = Tk()

home_place = Frame(top, height=500, width=150, background='black')
where_home = Frame(top, height=500, width=300, background='blue')
b=Button(where_home, height=1, width=30, command=make_popcorn, text='Make Popcorn!')

home_place.pack(side = 'left')
where_home.pack(side='right')
b.pack()

#b=Button(top, height=32, width=32, command=make_popcorn)
#b.pack()


top.mainloop()