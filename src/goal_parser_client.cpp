/*
 * Author: Raul Peralta Lozada
 * e-mail: raulpl25@gmail.com
 * date: 22/01/2015
*/

#include <jsoncpp/json/json.h>
#include <cstdlib>
#include <string.h>
#include <ros/ros.h>
#include "json_msgs/JsonSrv.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "goal_parser_client");
    if (argc != 3) {
        ROS_INFO("usage: goal_parser_client command value");
        return 1;
    }
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<json_msgs::JsonSrv>("goal_parser_service");
    Json::Value request;
    request[argv[1]] = argv[2];

    Json::FastWriter writer;
    json_msgs::JsonSrv srv;
    srv.request.json = writer.write(request);

    std::cout << srv.request.json <<  std::endl;
    if (client.call(srv)) {
        ROS_INFO("Output => %s", srv.response.json.c_str());
    } else {
        ROS_ERROR("Failed to call service");
        return 1;
    }

    return 0;
}
