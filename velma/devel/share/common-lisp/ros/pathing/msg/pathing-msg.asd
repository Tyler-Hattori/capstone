
(cl:in-package :asdf)

(defsystem "pathing-msg"
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
    (:file "gpioread" :depends-on ("_package_gpioread"))
    (:file "_package_gpioread" :depends-on ("_package"))
    (:file "gpiowrite" :depends-on ("_package_gpiowrite"))
    (:file "_package_gpiowrite" :depends-on ("_package"))
  ))