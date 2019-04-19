#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <iostream>
 
using namespace std;
using namespace cv;

Video::Video(ros::NodeHandle& nh_) : _nh(nh_){
  _img_msg="";//QUI COME FUNZIONA?
}

Video::~Video(){
//COSA CI VA?
}

cv::Mat Video::setFilter1(sensor_msgs::ImagePtr img){
  cv::Mat src_img = img->image;
  scr_img.convertTo( src_img_f,cv::DataType<float>::type );
  cv::normalize(src_img_f, src_img_f, 0, 1.0, cv::NORM_MINMAX, cv::DataType<float>::type);
  cv::Mat gaussian_blurred_img, box_blurred_img;
  float gaussian_stddev = 1.0;
  cv::GaussianBlur( src_img_f, gaussian_blurred_img,cv::Size(0,0), gaussian_stddev );
  // Compute the image derivatives along x and y using Sobel
  cv::Mat dx_img, dy_img;
  cv::Sobel(src_img_f, dx_img, cv::DataType<float>::type, 1, 0, 3);
  cv::Sobel(src_img_f, dy_img, cv::DataType<float>::type, 0, 1, 3);
  cv::Mat gradient_mag_img, abs_dx_img, abs_dy_img, binary_img;
  // Compute the gradient magnitude image
  abs_dx_img = cv::abs(dx_img);
  abs_dy_img = cv::abs(dy_img);
  gradient_mag_img = 0.5*(abs_dx_img + abs_dy_img);
  // Binarize the image
  cv::threshold (gradient_mag_img, binary_img, 0.4,1.0,cv::THRESH_BINARY);
  return binary_image;

}
