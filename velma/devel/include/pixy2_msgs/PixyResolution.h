// Generated by gencpp from file pixy2_msgs/PixyResolution.msg
// DO NOT EDIT!


#ifndef PIXY2_MSGS_MESSAGE_PIXYRESOLUTION_H
#define PIXY2_MSGS_MESSAGE_PIXYRESOLUTION_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace pixy2_msgs
{
template <class ContainerAllocator>
struct PixyResolution_
{
  typedef PixyResolution_<ContainerAllocator> Type;

  PixyResolution_()
    : width(0)
    , height(0)  {
    }
  PixyResolution_(const ContainerAllocator& _alloc)
    : width(0)
    , height(0)  {
  (void)_alloc;
    }



   typedef uint16_t _width_type;
  _width_type width;

   typedef uint16_t _height_type;
  _height_type height;





  typedef boost::shared_ptr< ::pixy2_msgs::PixyResolution_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pixy2_msgs::PixyResolution_<ContainerAllocator> const> ConstPtr;

}; // struct PixyResolution_

typedef ::pixy2_msgs::PixyResolution_<std::allocator<void> > PixyResolution;

typedef boost::shared_ptr< ::pixy2_msgs::PixyResolution > PixyResolutionPtr;
typedef boost::shared_ptr< ::pixy2_msgs::PixyResolution const> PixyResolutionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::pixy2_msgs::PixyResolution_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::pixy2_msgs::PixyResolution_<ContainerAllocator1> & lhs, const ::pixy2_msgs::PixyResolution_<ContainerAllocator2> & rhs)
{
  return lhs.width == rhs.width &&
    lhs.height == rhs.height;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::pixy2_msgs::PixyResolution_<ContainerAllocator1> & lhs, const ::pixy2_msgs::PixyResolution_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace pixy2_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pixy2_msgs::PixyResolution_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pixy2_msgs::PixyResolution_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pixy2_msgs::PixyResolution_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
{
  static const char* value()
  {
    return "20cde1cc3b01e7f015e45dc31f8ca17d";
  }

  static const char* value(const ::pixy2_msgs::PixyResolution_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x20cde1cc3b01e7f0ULL;
  static const uint64_t static_value2 = 0x15e45dc31f8ca17dULL;
};

template<class ContainerAllocator>
struct DataType< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
{
  static const char* value()
  {
    return "pixy2_msgs/PixyResolution";
  }

  static const char* value(const ::pixy2_msgs::PixyResolution_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint16 width\n"
"uint16 height\n"
;
  }

  static const char* value(const ::pixy2_msgs::PixyResolution_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.width);
      stream.next(m.height);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PixyResolution_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pixy2_msgs::PixyResolution_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::pixy2_msgs::PixyResolution_<ContainerAllocator>& v)
  {
    s << indent << "width: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.width);
    s << indent << "height: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.height);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PIXY2_MSGS_MESSAGE_PIXYRESOLUTION_H
