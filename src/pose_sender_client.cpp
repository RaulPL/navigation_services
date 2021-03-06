#include <jsoncpp/json/json.h>
#include <cstdlib>
#include <string.h>
#include <ros/ros.h>
#include "json_msgs/JsonSrv.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pose_sender_client");
  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<json_msgs::JsonSrv>("pose_sender_service");
  Json::Value request;
  request["Empty"] = 0;

  Json::FastWriter writer;
  json_msgs::JsonSrv srv;
  srv.request.json = writer.write(request);

  std::cout << "Retrieving the pose of the robot" <<  std::endl;
  if (client.call(srv)) {
      ROS_INFO("Output => %s", srv.response.json.c_str());
  } else {
      ROS_ERROR("Failed to call pose_sender_service");
      return 1;
  }

  return 0;
}
