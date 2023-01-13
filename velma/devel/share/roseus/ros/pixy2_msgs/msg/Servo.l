;; Auto-generated. Do not edit!


(when (boundp 'pixy2_msgs::Servo)
  (if (not (find-package "PIXY2_MSGS"))
    (make-package "PIXY2_MSGS"))
  (shadow 'Servo (find-package "PIXY2_MSGS")))
(unless (find-package "PIXY2_MSGS::SERVO")
  (make-package "PIXY2_MSGS::SERVO"))

(in-package "ROS")
;;//! \htmlinclude Servo.msg.html


(defclass pixy2_msgs::Servo
  :super ros::object
  :slots (_channel _position ))

(defmethod pixy2_msgs::Servo
  (:init
   (&key
    ((:channel __channel) 0)
    ((:position __position) 0)
    )
   (send-super :init)
   (setq _channel (round __channel))
   (setq _position (round __position))
   self)
  (:channel
   (&optional __channel)
   (if __channel (setq _channel __channel)) _channel)
  (:position
   (&optional __position)
   (if __position (setq _position __position)) _position)
  (:serialization-length
   ()
   (+
    ;; uint8 _channel
    1
    ;; uint16 _position
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _channel
       (write-byte _channel s)
     ;; uint16 _position
       (write-word _position s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _channel
     (setq _channel (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _position
     (setq _position (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get pixy2_msgs::Servo :md5sum-) "37c8ea878d139a8b80638ae8ed0a3ac3")
(setf (get pixy2_msgs::Servo :datatype-) "pixy2_msgs/Servo")
(setf (get pixy2_msgs::Servo :definition-)
      "uint8 channel
uint16 position

")



(provide :pixy2_msgs/Servo "37c8ea878d139a8b80638ae8ed0a3ac3")


