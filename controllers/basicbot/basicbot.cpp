#include "basicbot.h"

#include <math.h> 
#include <iomanip>
#include <sstream>

#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>

Basicbot::Basicbot() : 
   m_pcWheels(NULL),
   m_pcGroundSensor(NULL),
   m_pcProximity(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f), // default: 0.5
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
   ToRadians(m_cAlpha)),

   m_turningSpeed(5.49778714378213f), //TODO calculate instead 
   movingSpeed(10.0f), //TODO calculate instead 

   ticksToTurn(20), //TODO calculate instead 
   ticksToMoveOneCell(20), //TODO calculate instead 

   // data collection
   ticksIdle(0),
   ticksMoveforward(0),
   ticksTurnleft(0),
   ticksTurnright(0),
   ticksTurn180(0),
   ticksPickuppod(0), 
   ticksPutdownpod(0),
   ticksIgnore(0),
   ticksWait(0)

   {}


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


   // TODO: check if these does anything. 
   ReadCellQR();
   currentInstruction = idle;
}

void Basicbot::ControlStep()
{
   switch (currentInstruction)
   {
      case idle:
         argos::LOG << "Bip bop i am Idle." << std::endl;
         ticksIdle++;
         break;
      case moveforward:
         MoveForward();
         break;
      case turnleft:
         TurnLeft();
         break;
      case turnright:
         TurnRight();
         break;
      case turn180:
         Turn180();
         break;
      case pickuppod:
         PickUpPod();
         break;
      case putdownpod:
         PutDownPod();
         break;   
      case _wait:
         BotWait();
         break;
      default:
      argos::LOGERR << "bot: " << robotID << " default in ControlStep switch. currentInstruction: " << currentInstruction << std::endl;
         break;
   }
}

void Basicbot::MoveForward()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToMoveOneCell * cellsToMove;
   }
   
   if (counter > 0)
   {
      m_pcWheels->SetLinearVelocity(movingSpeed, movingSpeed);
      ticksMoveforward++;
      counter--;
   }
   else
   {
      ReadCellQR();
      argos::LOG << "Arrived at: " << lastReadCellQR.x << " , " << lastReadCellQR.y << std::endl;
      ResetBot();
   }
}

void Basicbot::TurnRight()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToTurn;
   }
   if (counter > 0)
   {
      m_pcWheels->SetLinearVelocity(m_turningSpeed, -m_turningSpeed);
      ticksTurnright++;
      counter--;
   }
   else
   {
      if(facing == north){facing=east;}
      else if(facing == south){facing=west;}
      else if(facing == east){facing=south;}
      else if(facing == west){facing=north;}
      ResetBot();
   }
}

void Basicbot::TurnLeft()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToTurn;
   }
   if (counter > 0)
   {
      m_pcWheels->SetLinearVelocity(-m_turningSpeed, m_turningSpeed);
      ticksTurnleft++;
      counter--;
   }
   else
   {
      if(facing == north){facing=west;}
      else if(facing == south){facing=east;}
      else if(facing == east){facing=east;}
      else if(facing == west){facing=south;}
      ResetBot();
   }
}

void Basicbot::Turn180()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToTurn * 2;
   }
   if (counter > 0)
   {
      m_pcWheels->SetLinearVelocity(m_turningSpeed, -m_turningSpeed);
      ticksTurn180++;
      counter--;
   }
   else
   {
      if(facing == north){facing=south;}
      else if(facing == south){facing=north;}
      else if(facing == east){facing=west;}
      else if(facing == west){facing=east;}
      ResetBot();
   }
}

void Basicbot::PickUpPod()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToPickUpPod;
   }
   
   if (counter > 0)
   {
      ticksPickuppod++;
      counter--;
   }
   else
   {
      ResetBot();
   }
}

void Basicbot::PutDownPod()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToPutDownPod;
   }
   
   if (counter > 0)
   {
      ticksPutdownpod++;
      counter--;
   }
   else
   {
      ResetBot();
   }
}

void Basicbot::BotWait()
{
   if (!isBusy){
      isBusy = true;
      counter = ticksToWait;
   }
   
   if (counter > 0)
   {
      ticksWait++;
      counter--;
      if (counter == 0)
      {
         argos::LOG << "Waited: " << ticksToWait << " ticks." << std::endl;
         ResetBot();
      }
   }
}

void Basicbot::ResetBot()
{
   m_pcWheels->SetLinearVelocity(0, 0);
   cellsToMove = 1;
   ticksToWait = 1;
   currentInstruction = idle;
   isBusy = false;

}

void Basicbot::ReadCellQR(){
   // TODO: BUGBUGBUG
   //argos::LOG << "read QR" << std::endl;
   CVector2 temp = GetPosition2D();
   double x = temp.GetX() * 5;
   double y = temp.GetY() * 5;
   x = std::round(x);
   y = std::round(y);
   lastReadCellQR = Coordinate((int)x, (int)y);
}

void Basicbot::LogReadablePosition(){
   CVector2 temp = GetPosition2D();
   double x = temp.GetX();
   double y = temp.GetY();

   std::stringstream stream;
   stream << std::fixed << std::setprecision(5) << x << ", " << y;
   std::string s = stream.str();
   
   argos::LOG << "Position: " << s << std::endl;
};

/* Returns the bots current postion as a 2D vector. */
CVector2 Basicbot::GetPosition2D(){
    const CCI_PositioningSensor::SReading &tPosReads = m_pcPosSens->GetReading();
    return CVector2(tPosReads.Position.GetX(), tPosReads.Position.GetY());
}

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