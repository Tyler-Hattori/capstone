
(cl:in-package :asdf)

(defsystem "gpio_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "InputState" :depends-on ("_package_InputState"))
    (:file "_package_InputState" :depends-on ("_package"))
    (:file "OutputState" :depends-on ("_package_OutputState"))
    (:file "_package_OutputState" :depends-on ("_package"))
  ))