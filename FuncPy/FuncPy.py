import simple_pb2
import frame_pb2
import serial

# Initialize message
SimpleMsg = simple_pb2.SimpleMessage()
SimpleMsg.startChar = "##"
SimpleMsg.data = "Hello"
SimpleMsg.endChar = "\n\n"
pb = SimpleMsg.SerializeToString()

# # Initialize frame
# FrameMsg = frame_pb2.Frame()
# FrameMsg.startFrame = "#"
# FrameMsg.length = len(SimpleMsg.data)
# FrameMsg.pb = pb
# FrameMsg.endFrame = "/n"
# FrameMsg.escaping = "~"
# frm = FrameMsg.SerializeToString()

# # Initialize & open serial port
ser = serial.Serial(port='COM9', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=0)
ser.is_open
# # ser.open()
ser.write(pb)
# ser.write(frm)
#
# # close serial port
# ser.close()