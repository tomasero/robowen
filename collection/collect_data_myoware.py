#!/usr/bin/env python2

import serial
import csv
from datetime import datetime
import time
import sys

s = serial.Serial('/dev/cu.usbmodem1421',baudrate=115200)

N_sensors = 1

# tag = 'none'

# header = ['timestamp', 'x', 'y', 'z', 'x_gyro', 'y_gyro', 'z_gyro', 'pressure']
header = ['timestamp', 'emg']

date = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
fname = sys.argv[1]

print(fname)

f_writer = open(fname, 'w')
writer = csv.writer(f_writer)

writer.writerow(header)

def collect(length, tag=0):
    ts = time.time()
    while time.time() - ts < length:
        td = time.time() - ts
        if abs(td % 1) < 0.02:
            print(td)
        
        try:
            line = s.readline().decode('ascii').strip().split(',')
            line = [float(x) for x in line]
            # print(line)
        except ValueError:
            continue

        if len(line) < N_sensors:
            continue
        
        # row = line + [tag]
        tstamp = str(time.time())
        row = [tstamp] + line
        writer.writerow(row)
        f_writer.flush()


print('starting in 3 seconds...')
time.sleep(3)
print('COLLECTING DATA')

collect(30)

f_writer.close()
