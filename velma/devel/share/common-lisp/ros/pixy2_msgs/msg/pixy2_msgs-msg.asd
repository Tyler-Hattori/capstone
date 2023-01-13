
(cl:in-package :asdf)

(defsystem "pixy2_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "PixyBlock" :depends-on ("_package_PixyBlock"))
    (:file "_package_PixyBlock" :depends-on ("_package"))
    (:file "PixyData" :depends-on ("_package_PixyData"))
    (:file "_package_PixyData" :depends-on ("_package"))
    (:file "PixyResolution" :depends-on ("_package_PixyResolution"))
    (:file "_package_PixyResolution" :depends-on ("_package"))
    (:file "Servo" :depends-on ("_package_Servo"))
    (:file "_package_Servo" :depends-on ("_package"))
  ))