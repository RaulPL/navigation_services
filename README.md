# navigation_services

The services for the GOLEM-III robot provide information in json messages. Currently, there are four services: battery_inspector_service, door_checker_service, goal_parser_service and pose_sender_service.

battery_inspector_service
------------------
This service returns the current voltage of the patrolbot in a json message.

```json
{
    "battery_voltage" : 25.30
}
```

door_checker_service
------------------
This service checks if there is an obstacle in front of the robot (usually a door in a Robocup setting). It returns a json message with the status of the door.

```json
{
    "door_status" : "closed"
}
```

goal_parser_service
------------------
This service is in charge of parsing the goals sent by Sitlog to the move_base node. This package requieres yaml-cpp, json-cpp, and the json_msgs package.

Example of the commands and values the service understands:
```json
{
    "navigate" : "hall"
}
```
```json
{
    "navigate" : "{x:0.0, y:0.0, angle:0.0}"
}
```
```json
{
    "advance" : 1.0
}
```
```json
{
    "turn" : 45.0
}
```
And the service returns the status of the navigation task when it is over, which can be "ok" or "navigation_error", according to the status sent by the move_base node.
```json
{
  "status": "ok"
}
```

pose_sender_service
------------------
This service returns the pose of the robot in the map in a json message.

```json
{
  "robot_pose": [x, y, yaw]
}
```
