import serial
import time
portx = '/dev/tty.usbmodem2101'
bps = 115200
qtpy = serial.Serial(portx, bps)
print(qtpy.name)
record = ['']*100
condition = 0

while True:
    mode = input("Please enter the mode: R , W or G\n")
    # read mode: send command to rp2040
    if (mode == 'R' or mode == 'r'):

        path = './test.txt'
        recording = open(path, 'wb+')

        print('Read mode.')
        qtpy.write('r'.encode('utf-8'))
        print('Sent read command to rp2040.\n')
        i = 0
        while i < 100:
            record[i] = qtpy.readline().decode('utf-8')
            recording.write(record[i])
            print(record[i])
            i += 1
        recording.close()
        qtpy.write('s'.encode('utf-8'))
        print('Recording finished!')

    # write mode: send command to rp2040 and toggle the led
    elif (mode == 'W' or mode == 'w'):
        print('Write mode.')
        qtpy.write('w'.encode('utf-8'))
        print('Sent write command to rp2040.\n')
        for i in range(100):
            qtpy.write(record[i].encode('utf-8'))
        qtpy.write('s'.encode('utf-8'))
        print('Writing finished!')

    # modify register mode: write or read the value of specific register address
    elif (mode == 'G' or mode == 'g'):
        print('Modify register mode.')
        qtpy.write('g'.encode('utf-8'))
        print('Sent modify register command to rp2040.')
        rORw = input('Please choose the mode: "R" or "r" for read mode and "W" or "w" for write mode.\n')

        if (rORw == 'R' or rORw == 'r'):
            qtpy.write('r'.encode('utf-8'))
            print('Input the target address:')
            for i in range(8):
                tmp = input('The ' + str(i) + ' th inex of the address.\n')
                qtpy.write(tmp.encode('utf-8'))
            print('Enter finished!')
            time.sleep(4)
            print(qtpy.readline().decode('utf-8'))


        elif (rORw == 'W' or rORw == 'w'):
            qtpy.write('w'.encode('utf-8'))
            print('Input the target address:')
            for i in range(8):
                tmp = input('The ' + str(i) + ' th inex of the address.\n')
                qtpy.write(tmp.encode('utf-8'))
            print('Enter finished!')
            print('Input the changed address:')
            for i in range(8):
                tmp = input('The ' + i + ' th inex of the address.\n')
                qtpy.write(tmp.encode('utf-8'))
            print('Enter finished!')
            time.sleep(4)
            print(qtpy.readline().decode('utf-8'))

    # invalid input
    else: print('Invalid input, try again.\n')


