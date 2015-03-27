/*
 * Author: Raul Peralta Lozada
 * e-mail: raulpl25@gmail.com
 * date: 22/01/2015
*/

#include <ros/ros.h>
#include <math.h>
#include <geometry_msgs/PoseStamped.h>
#include "navigation_services/goal_parser.h"

using namespace std;

GoalParser::GoalParser(string path)
{
    robot_base_frame_ = "base_link";
    global_frame_ = "map";
    yaml_node = YAML::LoadFile(path);
    ac = new MoveBaseClient("move_base", true);
    while (!ac->waitForServer(ros::Duration(5.0))) {
        ROS_INFO("Waiting for the move_base action server to come up");
    }
}

bool GoalParser::navigate(json_msgs::JsonSrv::Request& req, json_msgs::JsonSrv::Response& res)
{
    // Parsing message
    Json::Reader reader;
    Json::Value parsed_req;
    bool parsingSuccessful = reader.parse(req.json, parsed_req);
    bool error = false;
    string ref_frame = "odom";
    vector<double> goal_pose(7, 0.0);

    if (parsingSuccessful) {
        for (Json::ValueIterator itr = parsed_req.begin(); itr != parsed_req.end(); itr++) {
            string command = itr.key().asString();
            cout << "command: " << command << endl;
            //Execute command
            if (command.compare("navigate") == 0) {
                ref_frame = global_frame_;
                if (parsed_req["navigate"].isString()) { //label
                    //Read YAML file
                    string place_name = parsed_req["navigate"].asString();
                    goal_pose = yaml_node[place_name].as<vector<double> >();
                } else {
                    const Json::Value coord = parsed_req["navigate"];
                    double angle = coord["angle"].asDouble();
                    double theta = (angle * M_PI) / 180.0; // radians
                    tf::Quaternion q = tf::createQuaternionFromRPY(0.0, 0.0, theta);
                    goal_pose[0] = coord["x"].asDouble();
                    goal_pose[1] = coord["y"].asDouble();
                    goal_pose[3] = q.x();
                    goal_pose[4] = q.y();
                    goal_pose[5] = q.z();
                    goal_pose[6] = q.w();
                }
            } else if (command.compare("advance") == 0) {
                ref_frame = robot_base_frame_;
                double distance = 0.0;
                if (parsed_req["advance"].isString()) {
                    string distance_str = parsed_req["advance"].asString();
                    string::size_type sz;
                    distance = stod(distance_str, &sz);
                } else {
                    distance = parsed_req["advance"].asDouble();
                }
                goal_pose[0] = distance;
                goal_pose[6] = 1.0;
            } else if (command.compare("turn") == 0) {
                ref_frame = robot_base_frame_;
                double angle = 0.0;
                if (parsed_req["turn"].isString()) {
                    string angle_str = parsed_req["turn"].asString();
                    string::size_type sz;
                    angle = stod(angle_str, &sz);
                } else {
                    angle = parsed_req["turn"].asDouble();
                }
                double theta = -1.0 * (angle * M_PI) / 180.0; // radians
                tf::Quaternion q = tf::createQuaternionFromRPY(0.0, 0.0, theta);
                goal_pose[3] = q.x();
                goal_pose[4] = q.y();
                goal_pose[5] = q.z();
                goal_pose[6] = q.w();
            } else {
                error = true;
                ROS_ERROR("Invalid command.");
            }
        }
    } else {
        error = true;
        ROS_ERROR("Problem while parsing the message. Maybe due to an invalid json.");
    }

    Json::FastWriter writer;
    Json::Value response;

    if (!error) {
        //Goal configuration
        ROS_INFO("Sending goal: ");
        for (vector<double>::const_iterator it = goal_pose.begin(); it != goal_pose.end(); it++)
            cout << *it << ", ";
        cout << endl;
        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = ref_frame;
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = goal_pose[0];
        goal.target_pose.pose.position.y = goal_pose[1];
        goal.target_pose.pose.position.z = goal_pose[2];
        goal.target_pose.pose.orientation.x = goal_pose[3];
        goal.target_pose.pose.orientation.y = goal_pose[4];
        goal.target_pose.pose.orientation.z = goal_pose[5];
        goal.target_pose.pose.orientation.w = goal_pose[6];

        ac->sendGoal(goal);
        ac->waitForResult();

        if (ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("Success");
            response["status"] = "ok";
            res.json = writer.write(response);
        } else {
            ROS_INFO("The robot failed to get to the goal");
            response["status"] = "navigation_error";
            res.json = writer.write(response);
        }
    } else {
        ROS_ERROR("Error flag. Robot not moving.");
        response["status"] = "navigation_error";
        res.json = writer.write(response);
    }
    return true;
}


