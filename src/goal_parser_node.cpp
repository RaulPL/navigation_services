/*
 * Author: Raul Peralta Lozada
 * e-mail: raulpl25@gmail.com
 * date: 22/01/2015
*/

#include <iostream>
#include <string>
#include <ros/ros.h>
#include <ros/package.h>
#include <navigation_services/goal_parser.h>

using namespace std;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "goal_parser_node");

    string places_path = ros::package::getPath("navigation_services");
    places_path = places_path + "/resource/arturo_test.yaml";  //configuration file created with rqt_map_topo
    GoalParser gp(places_path);

    ros::NodeHandle n;
    ros::ServiceServer ss = n.advertiseService("goal_parser_service", &GoalParser::navigate, &gp);
    ROS_INFO("READY: Providing the navigation_service");
    ros::spin();
    return 0;
}

