from SerialPort import SerialPort
from time import sleep


com = SerialPort('COM6', timeout=5)

com.sendMsg('12 01 01 FF')
sleep(3)
com.sendMsg('05 14 2B 37 39 32 31 38 36 37 31 39 39 37 00 00 00 00 00 00 00 00 FF')

# Wait UP batton
com.waitMsg()
com.sendMsg('1F 01 01 FF')
#sleep(3)
com.sendMsg('04 01 01 FF')
