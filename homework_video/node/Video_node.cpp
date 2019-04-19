#include "ros/ros.h"
#include "publisher.h"
#include <std_msgs/UInt8.h>
#include <sstream>

using namespace std;
using namespace utils;


int main(int argc, char **argv)
{
 
 
int main(int argc, char** argv)
{
  // Check if video source has been passed as a parameter
  if(argv[1] == NULL) return 1;

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
  cv::VideoCapture cap(0);
 
  if(!cap.isOpened()) return 1;
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    if(!frame.empty()) {
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      Video video(nh);
      video.setFilter1(&msg);
      //video.setFilter2(&msg);
      //video.setFilter3(&msg);

      pub.publish(msg);
      cv::waitKey(1);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

