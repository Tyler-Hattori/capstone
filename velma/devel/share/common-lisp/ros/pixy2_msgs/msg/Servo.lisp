; Auto-generated. Do not edit!


(cl:in-package pixy2_msgs-msg)


;//! \htmlinclude Servo.msg.html

(cl:defclass <Servo> (roslisp-msg-protocol:ros-message)
  ((channel
    :reader channel
    :initarg :channel
    :type cl:fixnum
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Servo (<Servo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Servo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Servo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pixy2_msgs-msg:<Servo> is deprecated: use pixy2_msgs-msg:Servo instead.")))

(cl:ensure-generic-function 'channel-val :lambda-list '(m))
(cl:defmethod channel-val ((m <Servo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pixy2_msgs-msg:channel-val is deprecated.  Use pixy2_msgs-msg:channel instead.")
  (channel m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <Servo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pixy2_msgs-msg:position-val is deprecated.  Use pixy2_msgs-msg:position instead.")
  (position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Servo>) ostream)
  "Serializes a message object of type '<Servo>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'channel)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'position)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Servo>) istream)
  "Deserializes a message object of type '<Servo>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'channel)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'position)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Servo>)))
  "Returns string type for a message object of type '<Servo>"
  "pixy2_msgs/Servo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Servo)))
  "Returns string type for a message object of type 'Servo"
  "pixy2_msgs/Servo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Servo>)))
  "Returns md5sum for a message object of type '<Servo>"
  "37c8ea878d139a8b80638ae8ed0a3ac3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Servo)))
  "Returns md5sum for a message object of type 'Servo"
  "37c8ea878d139a8b80638ae8ed0a3ac3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Servo>)))
  "Returns full string definition for message of type '<Servo>"
  (cl:format cl:nil "uint8 channel~%uint16 position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Servo)))
  "Returns full string definition for message of type 'Servo"
  (cl:format cl:nil "uint8 channel~%uint16 position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Servo>))
  (cl:+ 0
     1
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Servo>))
  "Converts a ROS message object to a list"
  (cl:list 'Servo
    (cl:cons ':channel (channel msg))
    (cl:cons ':position (position msg))
))
