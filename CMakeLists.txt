cmake_minimum_required(VERSION 2.8.3)
project(img_repub)
add_compile_options(-std=c++11)
 
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
)
 
find_package(OpenCV 3.2.0 REQUIRED)
 
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_image_transport
  CATKIN_DEPENDS cv_bridge
#  DEPENDS system_lib
)
 
 
 
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)
 
 
 
#build my_publisher and my_subscriber
add_executable(img_repub src/img_repub.cpp)
target_link_libraries(img_repub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
 

