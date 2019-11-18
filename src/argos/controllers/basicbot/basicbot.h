#ifndef BASICBOT_H
#define BASICBOT_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>

#include <src/qrcodes/QRCode.h>

#include "src/datatypes/ds_instruction.h"

using namespace argos;

class Basicbot : public CCI_Controller {

public:
   Basicbot();
   virtual ~Basicbot() {}

   /* This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><footbot_diffusion_controller> section. */
   virtual void Init(TConfigurationNode& t_node);

   /* This function is called once every time step.
    * The length of the time step is set in the XML file. */
   virtual void ControlStep();

   /* This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    * In this example controller there is no need for resetting anything,
    * so the function could have been omitted. It's here just for
    * completeness. */
   virtual void Reset(){ResetBot();}; //TODO: rykkes til cpp-filen?

   /* Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness. */
   virtual void Destroy() {}

   int robotID;
   bool isBusy = false;
   instruction currentInstruction = idle;
   // last read pod QR
   // last read cell QR

   void MoveForward();
   void TurnLeft();
   void TurnRight();
   void Turn180();

   int counter = 0;
   int cellsToMove = 1;

   void LogReadablePosition();
   void ResetBot();


private:

   /* Pointer to the differential steering actuator */
   CCI_DifferentialSteeringActuator* m_pcWheels;
   /* Pointer to the foot-bot proximity sensor */
   CCI_FootBotProximitySensor* m_pcProximity;
   /* Pointer to the positioning sensor */
   CCI_PositioningSensor* m_pcPosSens;
   /* Pointer to the ground sensor */
   CCI_FootBotMotorGroundSensor* m_pcGroundSensor;

   /* The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><footbot_diffusion_controller> section. */

   /* Maximum tolerance for the angle between
    * the robot heading direction and
    * the closest obstacle detected. */
   CDegrees m_cAlpha;
   /* Maximum tolerance for the proximity reading between
    * the robot and the closest obstacle.
    * The proximity reading is 0 when nothing is detected
    * and grows exponentially to 1 when the obstacle is
    * touching the robot. */
   Real m_fDelta;
   /* Wheel speed. */
   Real m_fWheelVelocity;
   /* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
   CRange<CRadians> m_cGoStraightAngleRange;

   Real m_turningSpeed;
   int m_ticksToTurn;
   int m_ticksToMoveOneCell;

   CVector2 GetPosition2D();
};


#endif