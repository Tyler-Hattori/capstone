
(cl:in-package :asdf)

(defsystem "pathing-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "gpio" :depends-on ("_package_gpio"))
    (:file "_package_gpio" :depends-on ("_package"))
  ))