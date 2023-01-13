# signiture types
uint16 NORMAL_SIGNATURE=0
uint16 COLOR_CODE=1

# the message.  if type==0, then angle should be ignored.
uint16 type
uint16 signature
sensor_msgs/RegionOfInterest roi
float32 angle # in radians
uint8 index # Block index
uint8 age # Number of frames that this block has existed for