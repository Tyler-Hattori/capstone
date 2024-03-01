;; Auto-generated. Do not edit!


(when (boundp 'pathing::waypoints)
  (if (not (find-package "PATHING"))
    (make-package "PATHING"))
  (shadow 'waypoints (find-package "PATHING")))
(unless (find-package "PATHING::WAYPOINTS")
  (make-package "PATHING::WAYPOINTS"))

(in-package "ROS")
;;//! \htmlinclude waypoints.msg.html


(defclass pathing::waypoints
  :super ros::object
  :slots (_xs _ys ))

(defmethod pathing::waypoints
  (:init
   (&key
    ((:xs __xs) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:ys __ys) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _xs __xs)
   (setq _ys __ys)
   self)
  (:xs
   (&optional __xs)
   (if __xs (setq _xs __xs)) _xs)
  (:ys
   (&optional __ys)
   (if __ys (setq _ys __ys)) _ys)
  (:serialization-length
   ()
   (+
    ;; float64[] _xs
    (* 8    (length _xs)) 4
    ;; float64[] _ys
    (* 8    (length _ys)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _xs
     (write-long (length _xs) s)
     (dotimes (i (length _xs))
       (sys::poke (elt _xs i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _ys
     (write-long (length _ys) s)
     (dotimes (i (length _ys))
       (sys::poke (elt _ys i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _xs
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _xs (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _xs i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _ys
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ys (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _ys i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get pathing::waypoints :md5sum-) "86ce9604e58ca9c772c5cdb0f6a5a8ac")
(setf (get pathing::waypoints :datatype-) "pathing/waypoints")
(setf (get pathing::waypoints :definition-)
      "float64[] xs
float64[] ys

")



(provide :pathing/waypoints "86ce9604e58ca9c772c5cdb0f6a5a8ac")


