#include "mapper.h" 
#include <math.h>
#include <iostream>

LaserMapper::LaserMapper(ros::NodeHandle &nh_) : _nh(nh_)
{
  _listener = new tf::TransformListener;
  _odom_frame_id = "";
  _laser_topic = "";
}

LaserMapper::~LaserMapper()
{
  delete _listener;
}

void LaserMapper::laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg_)
{
  tf::StampedTransform transform;
  // Get laser transform in odom frame using the tf listener
  if (_listener->canTransform(_odom_frame_id, msg_->header.frame_id, msg_->header.stamp, NULL))
      _listener->lookupTransform(_odom_frame_id, msg_->header.frame_id, msg_->header.stamp, transform);

 
  Eigen::Isometry2f T = convertPose2D(transform);

  // Extract points from raw laser scan and paint them on canvas

  for (int i = 0; i < msg_->ranges.size(); i++)
  {
    Eigen::Vector2f p;
     float angle = msg_->angle_min + msg_->angle_increment * i;
    p[0] = msg_->ranges[i] * cos(angle);
    p[1] = msg_->ranges[i] * sin(angle);
      
   Eigen::Vector2f transformed_point = T * p;

    _canvas->colorPoint(transformed_point);
  }
  _canvas->show();
}

void LaserMapper::subscribe()
{ 
  _laser_sub = _nh.subscribe(_laser_topic, 10, &LaserMapper::laserCallback, this);
  _odom_sub = _nh.subscribe(_odom_frame_id, 10, &LaserMapper::odomCallback,this);
}
void LaserMapper::odomCallback(const nav_msgs::Odometry::ConstPtr &msg_){
   const cv::Vec3b & color = cv::Vec3b(0,0,255);
   
   Eigen::Vector2f p;
    p[0]= msg_->pose.pose.position.x;
    p[1] = msg_->pose.pose.position.y;
  _canvas->colorPoint(p,color);


}
