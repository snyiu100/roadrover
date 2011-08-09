import serial

answers = [
'01 02 00 01 FF',
'01 02 00 01 FF',
#'22 22 00 66 38 64 62 37 66 35 63 30 35 31 34 00 62 69 6F 68 74 63 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF '
#'22 22 01 65 34 65 63 31 30 66 30 35 63 34 32 00 4E 6F 6B 69 61 20 36 33 30 33 69 20 63 6C 61 73 73 69 63 00 FF '
#'22 22 02 65 63 39 62 35 62 33 61 61 39 34 33 00 51 41 2E 41 32 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF '
#'22 22 03 65 63 39 62 35 62 33 61 38 34 36 38 00 EF BF A1 E2 80 9C E9 A6 99 E9 A3 98 EF BD 9E EF BC A0 E2 80 FF '
#'22 22 04 30 30 31 33 65 66 30 30 30 30 30 64 00 43 53 52 20 41 75 64 69 6F 20 41 64 61 70 74 6F 72 00 00 00 FF '
#'22 22 05 30 30 31 38 65 34 30 63 31 64 33 66 00 4C 45 4E 4F 56 4F 2D 44 37 34 46 34 45 34 37 00 00 00 00 00 FF '
#'22 22 06 30 30 32 32 66 63 36 35 65 38 38 36 00 4E 6F 6B 69 61 20 37 32 31 30 63 00 00 00 00 00 00 00 00 00 FF '
'22 22 07 30 30 32 34 30 34 31 39 66 66 63 64 00 45 37 31 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF ',
]

def str2bin(s):
    return ''.join( map(lambda x: chr(int(x,16)), s.split()) )

def bin2str(b):
    return ' '.join( map(lambda x: hex(ord(x))[2:], b) )


it = iter(answers)

com = serial.Serial('COM6', timeout=1)
while True:
    data = com.read(128)
    #print '.',
    if len(data):
        #print
        print '<', bin2str(data)
        answ = it.next()
        if len(answ):
            print '>', answ
            com.write( str2bin(answ) )
