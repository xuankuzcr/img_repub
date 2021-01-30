#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>

using namespace cv;
using namespace std;

double scale;
string camera_topic_in,camera_topic_out;
sensor_msgs::ImagePtr msg_output;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    //ROS_INFO("The image is subscribing.");
    cv::Mat src = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    cv::Mat dst;
    cv::resize(src,dst,Size(src.cols*scale,src.rows*scale),0,0,INTER_LINEAR);
    cv::imshow("Display",src);
    cv::imshow("Result",dst);
    if(cv::waitKey(10)==27)
       exit(0);
    msg_output = cv_bridge::CvImage(msg->header, "bgr8", dst).toImageMsg();
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "img_repub");

  ROS_INFO("The repub_node is open.");

  if(!ros::param::get("camera_topic_in", camera_topic_in)) {
    cout << "Can not get the value of camera_topic_in" << endl;
    exit(1);
  }
  if(!ros::param::get("camera_topic_out", camera_topic_out)) {
    cout << "Can not get the value of camera_topic_out" << endl;
    exit(1);
  }
  if(!ros::param::get("scale", scale)) {
    cout << "Can not get the value of scale" << endl;
    exit(1);
  }
  ros::NodeHandle n; 
  ros::Time::init();
  image_transport::ImageTransport it(n);
  image_transport::Subscriber sub = it.subscribe( camera_topic_in , 1, imageCallback);   
  image_transport::Publisher pub = it.advertise(camera_topic_out, 1);
  ros::Rate loop_rate(5);

  while(1)
  {   
    //ros::Time time = ros::Time::now();
    pub.publish(msg_output); 
    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}

