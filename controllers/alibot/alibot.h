#ifndef FOOTBOT_DIFFUSION_H
#define FOOTBOT_DIFFUSION_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the differential steering actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
/* Definition of the foot-bot proximity sensor */
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
/* Definition of the positioning sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>
/**/
//#include <loop_functions/communicator_loop_functions/communicator_loop_functions.h> //This gives an error, be aware!

/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;

/*
 * A controller is simply an implementation of the CCI_Controller class.
 */
class Alibot : public CCI_Controller {

public:

   /* An enum for compass directions */
   enum class CompassDirection {
      north, 
      east, 
      south, 
      west
   };
   
   /* A map used to convert a compass direction to a vector*/
   std::map<Alibot::CompassDirection, CVector2> direction_vectors = {
      { CompassDirection::north, CVector2(0, 1) },
      { CompassDirection::east, CVector2(1, 0) },
      { CompassDirection::south, CVector2(0, -1) },
      { CompassDirection::west, CVector2(-1, 0) }
   };

   /* Class constructor. */
   Alibot();

   /* Class destructor. */
   virtual ~Alibot() {}

   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><footbot_diffusion_controller> section.
    */
   virtual void Init(TConfigurationNode& t_node);

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();

   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    * In this example controller there is no need for resetting anything,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Reset() {}

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Destroy() {}

   /* Returns the state of the bot. */
   bool getIsBusy();

   /* Points the bot towards the given direction. */
   void pointTowards(Alibot::CompassDirection desiredCompassDirection);

   /* Call this and the bot will move to the next cell infront of it. 
   (until QR-code is scanned. */
   void moveOneCellForward();

private:

   /* Pointer to the differential steering actuator */
   CCI_DifferentialSteeringActuator* m_pcWheels;
   /* Pointer to the foot-bot proximity sensor */
   CCI_FootBotProximitySensor* m_pcProximity;
   /* Pointer to the positioning sensor */
   CCI_PositioningSensor* m_pcPosSens;
   /* Pointer to the ground sensor */
   CCI_FootBotMotorGroundSensor* m_pcGroundSensor;

   /*
    * The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><footbot_diffusion_controller> section.
    */

   /* Maximum tolerance for the angle between
    * the robot heading direction and
    * the closest obstacle detected. */
   CDegrees m_cAlpha;
   /* Maximum tolerance for the proximity reading between
    * the robot and the closest obstacle.
    * The proximity reading is 0 when nothing is detected
    * and grows exponentially to 1 when the obstacle is
    * touching the robot.
    */
   Real m_fDelta;
   /* Wheel speed. */
   Real m_fWheelVelocity;
   /* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
   CRange<CRadians> m_cGoStraightAngleRange;

   /* Reads and prints the bots current position if it is over a dot. */
   void GetAndPrintGroundReadings();

   /* Returns true if the bot is currently placed on a QR-code. */
   bool isBotOnQRCode();

   /* Returns the value from ground sensor number 2. */
   Real getGroundSensorReading();

   /* Returns the value of the sensor matching the given number. (param: 1-4) */
   Real getSensorReading(int sensorNumber);

   /* Returns the bots current postion as a 2D vector. */
   CVector2 GetPosition2D();

   /* Is the bot ready busy and not ready for a new action? */
   bool isBusy = false;

   bool isTurning = false;
   bool isMoving = false;

   /* These booleans is used when the bot is moving from one QR to the next. */
   bool hasLeftStartQR = false;
   bool hasSensor1LeftQR = false;
   bool hasSensor2LeftQR = false;
   bool hasSensor3LeftQR = false;
   bool hasSensor4LeftQR = false;

   /* The direction the bot should be facing. */
   CVector2 desiredDirection;

   /* Turns the bot to point in the direction of the field: desiredDirection. */
   void checkAndTurn();

   /* Moves the bot forward until all sensors has left the start QR 
   and all sensors has reached the next QR. */
   void checkAndMove();
};

#endif