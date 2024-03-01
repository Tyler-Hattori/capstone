; Auto-generated. Do not edit!


(cl:in-package pathing-msg)


;//! \htmlinclude seenPoints.msg.html

(cl:defclass <seenPoints> (roslisp-msg-protocol:ros-message)
  ((indices
    :reader indices
    :initarg :indices
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (confidences
    :reader confidences
    :initarg :confidences
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass seenPoints (<seenPoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <seenPoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'seenPoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pathing-msg:<seenPoints> is deprecated: use pathing-msg:seenPoints instead.")))

(cl:ensure-generic-function 'indices-val :lambda-list '(m))
(cl:defmethod indices-val ((m <seenPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pathing-msg:indices-val is deprecated.  Use pathing-msg:indices instead.")
  (indices m))

(cl:ensure-generic-function 'confidences-val :lambda-list '(m))
(cl:defmethod confidences-val ((m <seenPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pathing-msg:confidences-val is deprecated.  Use pathing-msg:confidences instead.")
  (confidences m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <seenPoints>) ostream)
  "Serializes a message object of type '<seenPoints>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'indices))))
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
   (cl:slot-value msg 'indices))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'confidences))))
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
   (cl:slot-value msg 'confidences))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <seenPoints>) istream)
  "Deserializes a message object of type '<seenPoints>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'indices) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'indices)))
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
  (cl:setf (cl:slot-value msg 'confidences) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'confidences)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<seenPoints>)))
  "Returns string type for a message object of type '<seenPoints>"
  "pathing/seenPoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'seenPoints)))
  "Returns string type for a message object of type 'seenPoints"
  "pathing/seenPoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<seenPoints>)))
  "Returns md5sum for a message object of type '<seenPoints>"
  "a1650ba81512ff9c6b2cf12c61879bc5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'seenPoints)))
  "Returns md5sum for a message object of type 'seenPoints"
  "a1650ba81512ff9c6b2cf12c61879bc5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<seenPoints>)))
  "Returns full string definition for message of type '<seenPoints>"
  (cl:format cl:nil "float64[] indices~%float64[] confidences~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'seenPoints)))
  "Returns full string definition for message of type 'seenPoints"
  (cl:format cl:nil "float64[] indices~%float64[] confidences~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <seenPoints>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'indices) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'confidences) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <seenPoints>))
  "Converts a ROS message object to a list"
  (cl:list 'seenPoints
    (cl:cons ':indices (indices msg))
    (cl:cons ':confidences (confidences msg))
))
