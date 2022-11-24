/*
 * Copyright 1996-2020 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef Robot_H
#define Robot_H

/*
   Modular robot implementation for Webots simulator
*/

#include <webots/robot.h>
#include <webots/supervisor.h>

// number of DOFs of the robot
#define MAX_MOTORS 16
#define POSITION_ARRAY_SIZE 7

#define SIMULATION_STEP_DURATION 5

#define EXPERIMENT_NUMBER 1

#define PELVIS 0
#define FRONT_LEFT_1 1
#define FRONT_RIGHT_1 2
#define FRONT_LEFT_2 3
#define FRONT_RIGHT_2 4
#define FRONT_LEFT_3 5
#define FRONT_RIGHT_3 6
#define BACK_LEFT_1 7
#define BACK_RIGHT_1 8
#define BACK_LEFT_2 9
#define BACK_RIGHT_2 10
#define BACK_LEFT_3 11
#define BACK_RIGHT_3 12
#define NECK_1 13
#define NECK_2 14
#define HEAD 15


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ax12_2_deg(X) ((X * 150 / 512) - 150)
#define deg_2_ax12(X) ((int)((X + 150) * 512) / 150)

#define rad_2_deg(X) (X / M_PI * 180.0)
#define deg_2_rad(X) (X / 180.0 * M_PI)

#define L1 9    // UPPER_LEG_LENGTH [cm]
#define L2 8.5  // LOWER_LEG_LENGTH [cm]

class Robot {
public:
  // constructor: create robot according to specification
  explicit Robot(const char *name);

  // destructor
  virtual ~Robot(){};

  const char *getName() const { return _name; }

  void enableMotorPosition(int motorId);
  void setMotorPosition(int motorId, double value);
  double getMotorPosition(int motorId);
  
  
  void getTouchSensorValue();
  void standing();
  void walking(int gait_type, double DC, double ztd, double time);

  // Compute the position of shoulder and knee motors according to the time
  static void computeAnglePosition(double *motorsPosition, double x, double y);
  // Comute X and Y values
  void computeTrajectory(double *status, int mat_ind, double DC, float ztd, double t, int counter);

  void wait(double x);

  static const char *MOTOR_NAMES[MAX_MOTORS + 1];
  static const double coupling_matrix[2][4][4];
  static const int gait_setup[4][2];

private:
  const char *_name;    // robot name
  double _controlStep;  // simulation step size in milliseconds
  int _stepCount;       // number of simulation steps so far
  WbDeviceTag motors[MAX_MOTORS];
  WbDeviceTag position_sensor[MAX_MOTORS];
  WbDeviceTag touch_sensor_FRONT_LEFT;
  WbDeviceTag touch_sensor_FRONT_RIGHT;
  WbDeviceTag touch_sensor_BACK_LEFT;
  WbDeviceTag touch_sensor_BACK_RIGHT;
};

#endif
