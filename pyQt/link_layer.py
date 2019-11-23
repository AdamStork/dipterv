#   @author   Adam Golya
#   @brief    Python source file for Link Layer implementation
from enum import Enum
import queue

class link_layer:
    BYTE_START = 0x5A
    BYTE_END = 0xA5
    BYTE_ESC = 0x7E
    BYTES_TO_ESCAPE = [BYTE_START, BYTE_END, BYTE_ESC]

    def __init__(self):
        self.rx_buffer = []
        self.tx_buffer = []
        self.escape_happened = False
        self.frame_ready = False
        self.received_frames = queue.Queue()

    """ Unframe data using start, end, escape bytes """
    def link_receive_data(self, data):
        for i in data:
            if i == self.BYTE_START:
                self.rx_buffer.clear()
            elif i == self.BYTE_END:
                self.received_frames.put(self.rx_buffer)
            elif i == self.BYTE_ESC:
                self.escape_happened = True
            elif self.escape_happened:
                self.rx_buffer.append(i)
                self.escape_happened = False
            else:
                self.rx_buffer.append(i)
    """ Frame data with start, end, escape bytes """
    def link_send_data(self, pb_data):
        self.tx_buffer.clear()
        self.tx_buffer = [self.BYTE_START]
        for i in bytes(pb_data):
            if i in self.BYTES_TO_ESCAPE:
                self.tx_buffer.append(self.BYTE_ESC)
            self.tx_buffer.append(i)    
        self.tx_buffer.append(self.BYTE_END)

##LL = link_layer()
##LL.escape_happened
##data = "Z0~0"
##data = data.encode()
##LL.link_send_data(data)
##print(LL.tx_buffer)
