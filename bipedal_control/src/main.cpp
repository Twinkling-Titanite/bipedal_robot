#include "ros/ros.h"
#include "unitree_legged_msgs/MotorCmd.h"
#include "unitree_legged_msgs/MotorState.h"

int main(int argc,char *argv[])
{
    unitree_legged_msgs::MotorCmd msg_L[5];
    unitree_legged_msgs::MotorCmd msg_R[5];
    float toe=-1;
    float calf=1;
    float thigh=-1.5;
    for(int i=0;i<5;i++)
    {
        msg_L[i].mode=10;
        msg_L[i].tau=0;
        msg_L[i].dq=0;
        msg_L[i].Kd=0.5;
        msg_L[i].Kp=200;
        if(i==0||i==1) msg_L[i].q=0;
        if(i==2) msg_L[i].q=thigh;
        if(i==3) msg_L[i].q=calf;
        if(i==4) msg_L[i].q=toe;
    }
    for(int i=0;i<5;i++)
    {
        msg_R[i].mode=10;
        msg_R[i].tau=0;
        msg_R[i].dq=0;
        msg_R[i].Kd=0.5;
        msg_R[i].Kp=200;
        if(i==0||i==1) msg_R[i].q=0;
        if(i==2) msg_R[i].q=-thigh;
        if(i==3) msg_R[i].q=-calf;
        if(i==4) msg_R[i].q=-toe;
    }
    ros::init(argc,argv,"bipedal_control");
    ros::NodeHandle nh;
    ros::Publisher pub_L[5];
    ros::Publisher pub_R[5];
    pub_L[0]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/L_hip_controller/command",1);
    pub_L[1]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/L_hip2_controller/command",1);
    pub_L[2]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/L_thigh_controller/command",1);
    pub_L[3]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/L_calf_controller/command",1);
    pub_L[4]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/L_toe_controller/command",1);
    pub_R[0]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/R_hip_controller/command",1);
    pub_R[1]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/R_hip2_controller/command",1);
    pub_R[2]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/R_thigh_controller/command",1);
    pub_R[3]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/R_calf_controller/command",1);
    pub_R[4]=nh.advertise<unitree_legged_msgs::MotorCmd>("/bipedal_gazebo/R_toe_controller/command",1);
    ros::Rate loop_rate(100);
    while (ros::ok())
    {
        for(int i=0;i<5;i++)
        {
            pub_L[i].publish(msg_L[i]);
            pub_R[i].publish(msg_R[i]);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }
}