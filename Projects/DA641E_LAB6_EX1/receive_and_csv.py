import serial
import os

dir_name = 'data'

if not os.path.exists(dir_name):
    os.makedirs(dir_name)

ser = serial.Serial('/dev/ttyACM1', 115200, timeout=1)

try:
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(line)
            if line == 'Done!':
                ser.close()
                break
            with open(f'{dir_name}/data.csv', 'a') as f:
                f.write(line + '\n')
except KeyboardInterrupt:
    ser.close()
    print('Serial closed.')