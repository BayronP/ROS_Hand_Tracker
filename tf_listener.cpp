#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  ros::Publisher cmd_vel =
       node.advertise<geometry_msgs::Twist>("cmd_vel", 10);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform;
    try{
      listener.lookupTransform("/skeleton/openni_depth_frame", "/skeleton/right_hand_1",
                               ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
    }

    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = transform.getOrigin().y();
    vel_msg.angular.z = transform.getOrigin().x();

    cmd_vel.publish(vel_msg);

    rate.sleep();
  }
  return 0;
};

