/*
 * Author: Raul Peralta Lozada
 * e-mail: raulpl25@gmail.com
 * date: 22/01/2015
*/

#ifndef GOAL_PARSER_H
#define GOAL_PARSER_H

#include <string>
#include "yaml-cpp/yaml.h"
#include "jsoncpp/json/json.h"

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "json_msgs/JsonSrv.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base/MoveBaseConfig.h>
#include <tf/transform_datatypes.h>


using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class GoalParser
{
public:
    //Methods
    GoalParser(string path);
    bool navigate(json_msgs::JsonSrv::Request& req, json_msgs::JsonSrv::Response& res);

private:
    // Attributes
    YAML::Node yaml_node;
    string robot_base_frame_, global_frame_;
    MoveBaseClient* ac;
};

#endif // GOAL_PARSER_H
