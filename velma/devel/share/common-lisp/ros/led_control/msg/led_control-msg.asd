
(cl:in-package :asdf)

(defsystem "led_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "gpiowrite" :depends-on ("_package_gpiowrite"))
    (:file "_package_gpiowrite" :depends-on ("_package"))
  ))