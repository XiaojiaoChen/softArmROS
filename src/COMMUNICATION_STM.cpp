#include "ros/ros.h"
#include "extensa/Sensor.h"
#include "extensa/Command_Pre_Open.h"

using namespace std;

class COMMUNICATION_STM
{
  public:
    COMMUNICATION_STM()
    {
      sub1_ = n_.subscribe("Command_Pre_Open", 300, &COMMUNICATION_STM::encoder, this);
      sub2_ = n_.subscribe("Carmera", 300, &COMMUNICATION_STM::encoder, this);
      pub_ = n_.advertise<extensa::Sensor>("Sensor", 300);
    }

    void encoder(const extensa::Command_Pre_Open& msg)
    {
      ;
    }

    void pub()
    {
      pub_.publish(sensor_);
    }

  private:
    ros::NodeHandle n_;
    ros::Subscriber sub1_;
    ros::Subscriber sub2_;
    ros::Publisher pub_;

    extensa::Sensor sensor_;
};

int main(int argc, char **argv)
{

  ros::init(argc, argv, "COMMUNICATION_STM_Node");

  COMMUNICATION_STM COMMUNICATION_STM_Node;

  ros::AsyncSpinner s(3);
  s.start();

  ros::Rate loop_rate(100); 

  ROS_INFO("Ready for COMMUNICATION_STM_Node");

  while(ros::ok())
  {
    COMMUNICATION_STM_Node.pub();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
