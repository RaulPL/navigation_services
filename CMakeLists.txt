cmake_minimum_required(VERSION 2.8.3)
project(navigation_services)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(catkin REQUIRED COMPONENTS
  actionlib
  move_base_msgs
  move_base
  roscpp
  roslib
  std_msgs
  json_msgs
  tf
)

find_library(JSONCPP_LIBRARY jsoncpp /usr/lib/x86_64-linux-gnu)

catkin_package(
  CATKIN_DEPENDS actionlib move_base_msgs roscpp json_msgs message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

########################

add_library(goal_parser
  src/goal_parser.cpp
)

add_library(pose_sender
  src/pose_sender.cpp
)

add_library(battery_inspector
  src/battery_inspector.cpp
)

add_library(door_checker
  src/door_checker.cpp
)

########################

target_link_libraries(goal_parser
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

target_link_libraries(pose_sender
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

target_link_libraries(battery_inspector
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

target_link_libraries(door_checker
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

########################

add_executable(goal_parser_node src/goal_parser_node.cpp)
add_executable(goal_parser_client src/goal_parser_client.cpp)

add_executable(pose_sender_node src/pose_sender_node.cpp)
add_executable(pose_sender_client src/pose_sender_client.cpp)

add_executable(battery_inspector_node src/battery_inspector_node.cpp)
add_executable(battery_inspector_client src/battery_inspector_client.cpp)

add_executable(door_checker_node src/door_checker_node.cpp)
add_executable(door_checker_client src/door_checker_client.cpp)

########################

target_link_libraries(goal_parser_node
   goal_parser
   yaml-cpp
   ${catkin_LIBRARIES}
)

target_link_libraries(goal_parser_client
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

#######

target_link_libraries(pose_sender_node
  pose_sender
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

target_link_libraries(pose_sender_client
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

#######

target_link_libraries(battery_inspector_node
   battery_inspector
   ${catkin_LIBRARIES}
)

target_link_libraries(battery_inspector_client
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)

#######

target_link_libraries(door_checker_node
   door_checker
   yaml-cpp
   ${catkin_LIBRARIES}
)

target_link_libraries(door_checker_client
  ${catkin_LIBRARIES}
  ${JSONCPP_LIBRARY}
)
