import smbus
import time

address = 0x70

bus = smbus.SMBus(1)

bus.write_byte(address, 0x21)
bus.write_byte(address, 0xEF)
bus.write_byte(address, 0x81)

digit =[[0b00000000, 0b00111111],
        [0b00000000, 0b00000110],
        [0b00000000, 0b01011011],
        [0b00000000, 0b01001111],
        [0b00000000, 0b01100110],
        [0b00000000, 0b01101101],
        [0b00000000, 0b01111101],
        [0b00000000, 0b00000111],
        [0b00000000, 0b01111111],
        [0b00000000, 0b01101111],
        [0b00000000, 0b00000000],
        ]
    
def write(a,b,c,d):
    bus.write_i2c_block_data(address, 0x00, [
        digit[a][1], digit[a][0] ,
        digit[b][1], digit[b][0] ,
        digit[10][1], digit[10][0] ,
        digit[c][1], digit[c][0] ,
        digit[d][1], digit[d][0]] )

total_seconds = 3600*4 + 1800 + 7*60 

while total_seconds >= 0:
    minute, second = divmod(total_seconds%3600, 60) 
    write(minute/10, minute%10, second/10, second%10)
    total_seconds -= 1
    time.sleep(1)

