; Auto-generated. Do not edit!


(cl:in-package pathing-msg)


;//! \htmlinclude waypoints.msg.html

(cl:defclass <waypoints> (roslisp-msg-protocol:ros-message)
  ((xs
    :reader xs
    :initarg :xs
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (ys
    :reader ys
    :initarg :ys
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass waypoints (<waypoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <waypoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'waypoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pathing-msg:<waypoints> is deprecated: use pathing-msg:waypoints instead.")))

(cl:ensure-generic-function 'xs-val :lambda-list '(m))
(cl:defmethod xs-val ((m <waypoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pathing-msg:xs-val is deprecated.  Use pathing-msg:xs instead.")
  (xs m))

(cl:ensure-generic-function 'ys-val :lambda-list '(m))
(cl:defmethod ys-val ((m <waypoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pathing-msg:ys-val is deprecated.  Use pathing-msg:ys instead.")
  (ys m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <waypoints>) ostream)
  "Serializes a message object of type '<waypoints>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'xs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'xs))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ys))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'ys))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <waypoints>) istream)
  "Deserializes a message object of type '<waypoints>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'xs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'xs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ys) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ys)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<waypoints>)))
  "Returns string type for a message object of type '<waypoints>"
  "pathing/waypoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'waypoints)))
  "Returns string type for a message object of type 'waypoints"
  "pathing/waypoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<waypoints>)))
  "Returns md5sum for a message object of type '<waypoints>"
  "86ce9604e58ca9c772c5cdb0f6a5a8ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'waypoints)))
  "Returns md5sum for a message object of type 'waypoints"
  "86ce9604e58ca9c772c5cdb0f6a5a8ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<waypoints>)))
  "Returns full string definition for message of type '<waypoints>"
  (cl:format cl:nil "float64[] xs~%float64[] ys~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'waypoints)))
  "Returns full string definition for message of type 'waypoints"
  (cl:format cl:nil "float64[] xs~%float64[] ys~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <waypoints>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'xs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ys) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <waypoints>))
  "Converts a ROS message object to a list"
  (cl:list 'waypoints
    (cl:cons ':xs (xs msg))
    (cl:cons ':ys (ys msg))
))
