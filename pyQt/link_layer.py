#   @author   Adam Golya
#   @brief    Python source file for Link Layer implementation
from enum import Enum

# MSG_LENGTH_MAX = 255
BYTE_START = 0x5A
BYTE_END = 0xA5
BYTE_ESC = 0x7E

class UnEscapingState(Enum):
    WAIT_HEADER = 0
    IN_MSG = 1
    AFTER_ESC = 2

class link_layer:
    def __init__(self):
        self.receive_buffer = []
        self.receive_buffer_index = 0
        self.tx_buffer = []
        self.escape_next = false
        self.frame_ready = false
        self.state = UnEscapingState()

    def buffer_reset(self):
        self.frame_ready = 0
        self.receive_buffer_index = 0
        self.escape_next = false

    def buffer_write(self, byte):
        self.receive_buffer.append(byte)
        self.receive_buffer_index++

    def link_parse_byte(self, byte):
#        If we are in between two frames
        if self.state == UnEscapingState.WAIT_HEADER:
            if byte == BYTE_START:
                self.state = UnEscapingState.IN_MSG
                self.buffer_reset(self)
#                If we are in a frame
        elif self.state == UnEscapingState.IN_MSG:
            if byte == BYTE_START:
                self.buffer_reset(self)
            elif byte == BYTE_ESC:
                self.state = AFTER_ESC
            elif byte == BYTE_END:
                self.frame_ready = true
                self.state = UnEscapingState.WAIT_HEADER
            else:
                self.buffer_write(self, byte)
#                If the previous byte was an ESC
        elif self.state == UnEscapingState.AFTER_ESC:
            self.buffer_write(self, byte)
            self.state = UnEscapingState.IN_MSG

    def link_get_valid_frame(self):
        is_frame_ready = self.frame_ready
        if is_frame_ready:
            is_frame_ready = false
            length = self.receive_buffer_index
            list = self.receive_buffer
            return length, list

    def link_write(self, pb_data):
        tx_buffer_i = 0
        i = 0
        self.tx_buffer.append = BYTE_START
        tx_buffer_i++

        for i in pb_data:
            if pb_data[i] == BYTE_START or pb_data[i] == BYTE_END or pb_data[i] == BYTE_ESC:
                self.tx_buffer[tx_buffer_i] = BYTE_ESC
                tx_buffer_i++
            self.tx_buffer[tx_buffer_i] = pb_data[i]
            tx_buffer_i++
        self.tx_buffer[tx_buffer_i] = BYTE_END
        tx_buffer_i++


