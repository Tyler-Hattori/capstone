// Generated by gencpp from file led_control/gpiowrite.msg
// DO NOT EDIT!


#ifndef LED_CONTROL_MESSAGE_GPIOWRITE_H
#define LED_CONTROL_MESSAGE_GPIOWRITE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace led_control
{
template <class ContainerAllocator>
struct gpiowrite_
{
  typedef gpiowrite_<ContainerAllocator> Type;

  gpiowrite_()
    : state(false)
    , duration(0)  {
    }
  gpiowrite_(const ContainerAllocator& _alloc)
    : state(false)
    , duration(0)  {
  (void)_alloc;
    }



   typedef uint8_t _state_type;
  _state_type state;

   typedef uint8_t _duration_type;
  _duration_type duration;





  typedef boost::shared_ptr< ::led_control::gpiowrite_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::led_control::gpiowrite_<ContainerAllocator> const> ConstPtr;

}; // struct gpiowrite_

typedef ::led_control::gpiowrite_<std::allocator<void> > gpiowrite;

typedef boost::shared_ptr< ::led_control::gpiowrite > gpiowritePtr;
typedef boost::shared_ptr< ::led_control::gpiowrite const> gpiowriteConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::led_control::gpiowrite_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::led_control::gpiowrite_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::led_control::gpiowrite_<ContainerAllocator1> & lhs, const ::led_control::gpiowrite_<ContainerAllocator2> & rhs)
{
  return lhs.state == rhs.state &&
    lhs.duration == rhs.duration;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::led_control::gpiowrite_<ContainerAllocator1> & lhs, const ::led_control::gpiowrite_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace led_control

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::led_control::gpiowrite_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::led_control::gpiowrite_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::led_control::gpiowrite_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::led_control::gpiowrite_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::led_control::gpiowrite_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::led_control::gpiowrite_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::led_control::gpiowrite_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e48107ec9af92b61adf575e5d66914d0";
  }

  static const char* value(const ::led_control::gpiowrite_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe48107ec9af92b61ULL;
  static const uint64_t static_value2 = 0xadf575e5d66914d0ULL;
};

template<class ContainerAllocator>
struct DataType< ::led_control::gpiowrite_<ContainerAllocator> >
{
  static const char* value()
  {
    return "led_control/gpiowrite";
  }

  static const char* value(const ::led_control::gpiowrite_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::led_control::gpiowrite_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# set the pin to high or low via true/false\n"
"bool state\n"
"\n"
"# Optionally, provide duration for state. <= 0 will leave in state indefinitely.\n"
"uint8 duration\n"
;
  }

  static const char* value(const ::led_control::gpiowrite_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::led_control::gpiowrite_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.state);
      stream.next(m.duration);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct gpiowrite_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::led_control::gpiowrite_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::led_control::gpiowrite_<ContainerAllocator>& v)
  {
    s << indent << "state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.state);
    s << indent << "duration: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.duration);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LED_CONTROL_MESSAGE_GPIOWRITE_H
