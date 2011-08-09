import serial


def str2bin(s):
    return ''.join( map(lambda x: chr(int(x,16)), s.split()) )

def bin2str(b):
    return ' '.join( map(lambda x: hex(ord(x))[2:], b) )


class SerialPort(serial.Serial):
    def __init__(self, *args, **kwargs):
        super(SerialPort, self).__init__(*args, **kwargs)
        self.flushInput()
        self.flushOutput()

    def sendMsg(self, msg):
        if len(msg):
            print '>', msg
            self.write( str2bin(msg) )

    def recvMsg(self):
        data = self.read(128)
        if len(data):
            print '<', bin2str(data)
            return True
        return False

    def waitMsg(self):
        while not self.recvMsg():
            pass
