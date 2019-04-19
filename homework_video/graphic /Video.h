#pragma once
#include "ros/ros.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
class Video{
public:
  Video(ros::NodeHandle& nh_);
  ~Video();
  
protected:
  ros::NodeHandle& _nh;
  ros::publisher _pub_topic;
};
