; Auto-generated. Do not edit!


(cl:in-package gpio_control-msg)


;//! \htmlinclude OutputState.msg.html

(cl:defclass <OutputState> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:boolean
    :initform cl:nil)
   (duration
    :reader duration
    :initarg :duration
    :type cl:fixnum
    :initform 0))
)

(cl:defclass OutputState (<OutputState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OutputState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OutputState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gpio_control-msg:<OutputState> is deprecated: use gpio_control-msg:OutputState instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <OutputState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpio_control-msg:state-val is deprecated.  Use gpio_control-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'duration-val :lambda-list '(m))
(cl:defmethod duration-val ((m <OutputState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpio_control-msg:duration-val is deprecated.  Use gpio_control-msg:duration instead.")
  (duration m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OutputState>) ostream)
  "Serializes a message object of type '<OutputState>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'state) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'duration)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OutputState>) istream)
  "Deserializes a message object of type '<OutputState>"
    (cl:setf (cl:slot-value msg 'state) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'duration)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OutputState>)))
  "Returns string type for a message object of type '<OutputState>"
  "gpio_control/OutputState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OutputState)))
  "Returns string type for a message object of type 'OutputState"
  "gpio_control/OutputState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OutputState>)))
  "Returns md5sum for a message object of type '<OutputState>"
  "e48107ec9af92b61adf575e5d66914d0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OutputState)))
  "Returns md5sum for a message object of type 'OutputState"
  "e48107ec9af92b61adf575e5d66914d0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OutputState>)))
  "Returns full string definition for message of type '<OutputState>"
  (cl:format cl:nil "# set the pin to high or low via true/false~%bool state~%~%# Optionally, provide duration for state. <= 0 will leave in state indefinitely.~%uint8 duration~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OutputState)))
  "Returns full string definition for message of type 'OutputState"
  (cl:format cl:nil "# set the pin to high or low via true/false~%bool state~%~%# Optionally, provide duration for state. <= 0 will leave in state indefinitely.~%uint8 duration~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OutputState>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OutputState>))
  "Converts a ROS message object to a list"
  (cl:list 'OutputState
    (cl:cons ':state (state msg))
    (cl:cons ':duration (duration msg))
))
