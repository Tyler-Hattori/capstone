;; Auto-generated. Do not edit!


(when (boundp 'pixy2_msgs::PixyData)
  (if (not (find-package "PIXY2_MSGS"))
    (make-package "PIXY2_MSGS"))
  (shadow 'PixyData (find-package "PIXY2_MSGS")))
(unless (find-package "PIXY2_MSGS::PIXYDATA")
  (make-package "PIXY2_MSGS::PIXYDATA"))

(in-package "ROS")
;;//! \htmlinclude PixyData.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass pixy2_msgs::PixyData
  :super ros::object
  :slots (_header _blocks ))

(defmethod pixy2_msgs::PixyData
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:blocks __blocks) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _blocks __blocks)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:blocks
   (&rest __blocks)
   (if (keywordp (car __blocks))
       (send* _blocks __blocks)
     (progn
       (if __blocks (setq _blocks (car __blocks)))
       _blocks)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; pixy2_msgs/PixyBlock[] _blocks
    (apply #'+ (send-all _blocks :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; pixy2_msgs/PixyBlock[] _blocks
     (write-long (length _blocks) s)
     (dolist (elem _blocks)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; pixy2_msgs/PixyBlock[] _blocks
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _blocks (let (r) (dotimes (i n) (push (instance pixy2_msgs::PixyBlock :init) r)) r))
     (dolist (elem- _blocks)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get pixy2_msgs::PixyData :md5sum-) "d7b5179bbac08dbbbf116047daeca32b")
(setf (get pixy2_msgs::PixyData :datatype-) "pixy2_msgs/PixyData")
(setf (get pixy2_msgs::PixyData :definition-)
      "std_msgs/Header header
PixyBlock[] blocks
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: pixy2_msgs/PixyBlock
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
================================================================================
MSG: sensor_msgs/RegionOfInterest
# This message is used to specify a region of interest within an image.
#
# When used to specify the ROI setting of the camera when the image was
# taken, the height and width fields should either match the height and
# width fields for the associated image; or height = width = 0
# indicates that the full resolution image was captured.

uint32 x_offset  # Leftmost pixel of the ROI
                 # (0 if the ROI includes the left edge of the image)
uint32 y_offset  # Topmost pixel of the ROI
                 # (0 if the ROI includes the top edge of the image)
uint32 height    # Height of ROI
uint32 width     # Width of ROI

# True if a distinct rectified ROI should be calculated from the \"raw\"
# ROI in this message. Typically this should be False if the full image
# is captured (ROI not used), and True if a subwindow is captured (ROI
# used).
bool do_rectify

")



(provide :pixy2_msgs/PixyData "d7b5179bbac08dbbbf116047daeca32b")


