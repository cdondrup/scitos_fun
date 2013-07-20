#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <ros/console.h>

#include <string>
#include <signal.h>

#include "scitos_apps_msgs/action_buttons.h"

ros::Publisher pub_cmd_vel;
double l_scale_, a_scale_;

std::string file_name;

bool execute;
int pid = -1;

geometry_msgs::Twist t;
float last_msg[2] = {0.0, 0.0};

bool konami_code[10] = {false,false,false,false,false,false,false,false,false,false};

void controlCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  /*t.linear.x = 0.9*t.linear.x + 0.1*l_scale_ * msg->axes[1];
  t.angular.z = 0.5*t.angular.z + 0.5*a_scale_ * msg->axes[0];
	if(msg->header.frame_id == "stop") {
		t.linear.x = 0.0;
		t.angular.z = 0.0;
	}
	pub_cmd_vel.publish(t);*/

	//msg->axes[7]
	//msg->axes[6]

	if(konami_code[0]) {
		if(konami_code[1]) {
			if(konami_code[2]) {
				if(konami_code[3]) {
					if(konami_code[4]) {
						if(konami_code[5]) {
							if(konami_code[6]) {
								if(konami_code[7]) {
									
								} else if(msg->axes[6] == 0.0 && last_msg[0] == -1.0) {
									konami_code[7] = true;
									printf("Up, Up, Down, Down, Left, Right, Left, Right\n");
								} //else	{}
							} else if(msg->axes[6] == 0.0 && last_msg[0] == 1.0) {
								konami_code[6] = true;
								printf("Up, Up, Down, Down, Left, Right, Left\n");
							} //else	{}
						} else if(msg->axes[6] == 0.0 && last_msg[0] == -1.0) {
							konami_code[5] = true;
							printf("Up, Up, Down, Down, Left, Right\n");
						} //else	{}
					} else if(msg->axes[6] == 0.0 && last_msg[0] == 1.0) {
						konami_code[4] = true;
						printf("Up, Up, Down, Down, Left\n");
					} //else	{}
				} else if(msg->axes[7] == 0.0 && last_msg[1] == -1.0) {
					konami_code[3] = true;
					printf("Up, Up, Down, Down\n");
				} //else	{}
			} else if(msg->axes[7] == 0.0 && last_msg[1] == -1.0) {
				konami_code[2] = true;
				printf("Up, Up, Down\n");
			} //else	{}
		} else if(msg->axes[7] == 0.0 && last_msg[1] == 1.0) {
			konami_code[1] = true;
			printf("Up, Up\n");
		}	//else {}
	} else if(msg->axes[7] == 0.0 && last_msg[1] == 1.0) {
		konami_code[0] = true;
		printf("Up\n");
	}

	last_msg[0] = msg->axes[6];
	last_msg[1] = msg->axes[7];
}

void exterminate() {
	execute = true;
	std::string command("xterm -e mplayer -loop 2 ");
	command += file_name;
	pid = system(command.c_str());
}

void buttonCallback(const scitos_apps_msgs::action_buttons::ConstPtr& msg) {
	if(konami_code[7]) {
		if(konami_code[8]) {
	
		} else if(msg->A) {
			konami_code[9] = true;
			printf("Up, Up, Down, Down, Left, Right, Left, Right, B, A!\n");
			exterminate();
			for(int i = 0; i < 10; i++)
				konami_code[i] = false;
		}
	} else if(msg->B) {
		konami_code[8] = true;
		printf("Up, Up, Down, Down, Left, Right, Left, Right, B\n");
	}
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "konami");

  ros::NodeHandle n("konami");

  ros::Subscriber sub = n.subscribe("/teleop_joystick/joy", 1000, controlCallback);
	ros::Subscriber sub2 = n.subscribe("/teleop_joystick/action_buttons", 1000, buttonCallback);
  //pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

	n.getParam("exterminate", file_name);
  
  ros::spin();

  return 0;
}
