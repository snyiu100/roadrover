from SerialPort import SerialPort


com = SerialPort('COM6', timeout=1)

com.waitMsg()
com.sendMsg('01 02 00 01 FF')
com.waitMsg()
com.sendMsg('01 02 00 01 FF')
com.waitMsg()
com.sendMsg('22 22 07 30 30 32 34 30 34 31 39 66 66 63 64 00 45 37 31 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF')

while True:
    com.waitMsg()
