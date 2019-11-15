/* Include the controller definition */
#include "basicbot.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
/* 3D vector definition */
#include <argos3/core/utility/math/vector3.h>
/* Quick maths */
#include <math.h> 
/* Enable logging */
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

Basicbot::Basicbot() : m_pcWheels(NULL),
                                         m_pcGroundSensor(NULL),
                                         m_pcProximity(NULL),
                                         m_cAlpha(10.0f),
                                         m_fDelta(0.5f),
                                         m_fWheelVelocity(2.5f),
                                         m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                                                                 ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void Basicbot::Init(TConfigurationNode &t_node)
{
   /*
    * Get sensor/actuator handles
    *
    * The passed string (ex. "differential_steering") corresponds to the
    * XML tag of the device whose handle we want to have. For a list of
    * allowed values, type at the command prompt:
    *
    * $ argos3 -q actuators
    *
    * to have a list of all the possible actuators, or
    *
    * $ argos3 -q sensors
    *
    * to have a list of all the possible sensors.
    *
    * NOTE: ARGoS creates and initializes actuators and sensors
    * internally, on the basis of the lists provided the configuration
    * file at the <controllers><footbot_diffusion><actuators> and
    * <controllers><footbot_diffusion><sensors> sections. If you forgot to
    * list a device in the XML and then you request it here, an error
    * occurs.
    */
   m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcProximity = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
   m_pcPosSens = GetSensor<CCI_PositioningSensor>("positioning");
   m_pcGroundSensor = GetSensor<CCI_FootBotMotorGroundSensor>("footbot_motor_ground");
   /*
    * Parse the configuration file
    *
    * The user defines this part. Here, the algorithm accepts three
    * parameters and it's nice to put them in the config file so we don't
    * have to recompile if we want to try other settings.
    */
   GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
   m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
   GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
   GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
}

/****************************************/
/****************************************/

void Basicbot::ControlStep()
{
   if(isBusy){
      if(isTurning){
         TurnToDesiredDirection();
      }else if(isMoving){
         MoveToNextQR();
      }
   }
}

/* ------------------------ PUBLIC METHODS ------------------- */

/* Makes the bot move the given number of cells forward. */
bool Basicbot::MoveForward(int numberOfCells){
   isBusy = true;
   isMoving = true;
   tilesLeftToMove = numberOfCells;
}

/* Makes the bot turn the given number of degrees. */
bool Basicbot::TurnDegrees(float degreesToTurn){
   isBusy = true;
   isTurning = true;

   /* Convert the given degrees into the desired target angle. */
   /* TODO optimize. Maybe not needed? */
   CRadians cZAngle, cYAngle, cXAngle;
   m_pcPosSens->GetReading().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
   double frontAngle = ToDegrees(cZAngle).GetValue();
   CVector2 frontVector = CVector2(cos(cZAngle.GetValue()), sin(cZAngle.GetValue()));
   double rotationRad = ToRadians(CDegrees(degreesToTurn)).GetValue();
   CVector2 desiredDirectionVector = CVector2(frontVector.GetX() * cos(rotationRad) - frontVector.GetY() * sin(rotationRad),
                                       frontVector.GetX() * sin(rotationRad) + frontVector.GetY() * cos(rotationRad));
   desiredTargetAngle = desiredDirectionVector.Angle().GetValue() * 57.2958;
}

/* Makes the bot pick up the pod on the current position. */
bool Basicbot::PickupPod(){
   return false; //TODO Not yet implemented
}

/* Makes the bot put down the pod on the current position. */
bool Basicbot::PutDownPod(){
   return false; //TODO Not yet implemented
}

/* Reads the pods QR code in the current cell. */
/* TODO the return parameter should be changed. */
bool Basicbot::ReadPodQR(){
   return false; //TODO Not yet implemented
}

/* Reads the QR code in the current cell and returns its coordinate. */
CVector2 ReadCellQR(){
   return CVector2(0,0); //TODO Not yet implemented
}

/* ------------------------ PRIVATE METHODS ------------------- */

/* Used to move the bot to the next QR-code. */
void Basicbot::MoveToNextQR(){
   if(hasLeftStartQR){
      //Check sensor one: reached next QR?
      if(hasSensor1LeftQR){
         if((getSensorReading(1) < 0.9))
            hasSensor1LeftQR = false;
      }

      //Check sensor two: reached next QR?
      if(hasSensor2LeftQR){
         if((getSensorReading(2) < 0.9))
            hasSensor2LeftQR = false;
      }

      //Check sensor three: reached next QR?
      if(hasSensor3LeftQR){
         if((getSensorReading(3) < 0.9))
            hasSensor3LeftQR = false;
      }

      //Check sensor four: reached next QR?
      if(hasSensor4LeftQR){
         if((getSensorReading(4) < 0.9))
            hasSensor4LeftQR = false;
      }
      
      //Has all sensors reached the next QR?
      if(!hasSensor1LeftQR && !hasSensor2LeftQR && !hasSensor3LeftQR && !hasSensor4LeftQR){
         if(tilesLeftToMove == 1){
            m_pcWheels->SetLinearVelocity(0, 0);
            isMoving = false;
            isBusy = false;
         }

         tilesLeftToMove--;
         hasLeftStartQR = false;
      }

   }else{
      m_pcWheels->SetLinearVelocity(m_fWheelVelocity, m_fWheelVelocity);

      //Check sensor one: has left start QR?
      if(!hasSensor1LeftQR){
         if(!(getSensorReading(1) < 0.9))
            hasSensor1LeftQR = true;
      }

      //Check sensor two: has left start QR?
      if(!hasSensor2LeftQR){
         if(!(getSensorReading(2) < 0.9))
            hasSensor2LeftQR = true;
      }

      //Check sensor three: has left start QR?
      if(!hasSensor3LeftQR){
         if(!(getSensorReading(3) < 0.9))
            hasSensor3LeftQR = true;
      }

      //Check sensor four: has left start QR?
      if(!hasSensor4LeftQR){
         if(!(getSensorReading(4) < 0.9))
            hasSensor4LeftQR = true;
      }
      
      //Has all sensors left the start QR?
      if(hasSensor1LeftQR && hasSensor2LeftQR && hasSensor3LeftQR && hasSensor4LeftQR){
         hasLeftStartQR = true;
      }
   }
}

/* Turns the bot to point in the direction of the field: desiredDirection. */
void Basicbot::TurnToDesiredDirection(){
   CRadians cZAngle, cYAngle, cXAngle;
   m_pcPosSens->GetReading().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
   double frontAngle = ToDegrees(cZAngle).GetValue();

   if(abs(desiredTargetAngle - frontAngle) < 0.11){ //0.11
      isBusy = false;
      isTurning = false;
      m_pcWheels->SetLinearVelocity(0, 0); //Stop the wheels from turning
   }else{

      /* Is the shortest turning to the right or left? */
      bool shouldTurnRight;
      int frontAngleShifted = frontAngle + 179;
      int targetAngleShifted = desiredTargetAngle + 179;
      shouldTurnRight = (targetAngleShifted - frontAngleShifted) < 0;

      /* Calculate turn modifier. The smaller the angle the slower it turns. */
      int turnSpeedModifier = getTurnSpeedModifier(abs(desiredTargetAngle - frontAngle));

      if(shouldTurnRight)
         m_pcWheels->SetLinearVelocity(m_fWheelVelocity /turnSpeedModifier, -m_fWheelVelocity /turnSpeedModifier);
      else
         m_pcWheels->SetLinearVelocity(-m_fWheelVelocity /turnSpeedModifier, m_fWheelVelocity /turnSpeedModifier);
   }
}

/* Returns the turn speed modifier based on the absolute angle difference.*/
int Basicbot::getTurnSpeedModifier(double angleDiffAbs){

   if(angleDiffAbs > 2)
      return 4;

   //Currently based on points: (0.11, 60) , (1, 25) , (2, 4)
   return (23300 / 2403) * pow(angleDiffAbs, 2) - (40121 / 801) * angleDiffAbs + (157138 / 2403);
}

/* Returns the value of the sensor matching the given number. (param: 1-4) */
Real Basicbot::getSensorReading(int sensorNumber){
   const CCI_FootBotMotorGroundSensor::TReadings& tGroundReads = m_pcGroundSensor->GetReadings();

   switch (sensorNumber)
   {
      case 1: return tGroundReads[0].Value;
      case 2: return tGroundReads[1].Value;
      case 3: return tGroundReads[2].Value;
      case 4: return tGroundReads[3].Value;
   
      default: throw "Basicbot::getSonsorReading: Input number was not between 1 and 4!";
   }
}

/****************************************/
/****************************************/

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the configuration file to refer to this
 * controller.
 * When ARGoS reads that string in the configuration file, it knows which
 * controller class to instantiate.
 * See also the configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(Basicbot, "Basicbot_controller")