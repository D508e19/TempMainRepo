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

Basicbot::Basicbot() :   m_pcWheels(NULL),
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

}

/* PUBLIC METHODS */

/* Makes the bot move the given number of cells forward. */
bool Basicbot::MoveForward(int numberOfCells) {}

/* Makes the bot turn the given number of degrees. */
/* TODO the decription should reflect more details about the argument. */
bool Basicbot::TurnDegrees(float degreesToTurn) {}

/* Makes the bot pick up the pod on the current position. */
bool Basicbot::PickupPod() {}

/* Makes the bot put down the pod on the current position. */
bool Basicbot::PutDownPod() {}

/* Returns the bots current postion as a 2D vector. */
CVector2 Basicbot::GetPosition2D() {}

/* Reads the pods QR code in the current cell. */
/* TODO the return parameter should be changed. */
bool Basicbot::ReadPodQR() {}

/* PRIVATE METHODS */

/* Reads the QR code in the current cell and returns its coordinate. */
CVector2 Basicbot::ReadCellQR() {}

/* Returns true if the bot is currently placed on a QR-code. */
bool Basicbot::isBotOnQRCode() {}

/* Returns the value from ground sensor number 2. */
Real Basicbot::getGroundSensorReading() {}

/* Returns the value of the sensor matching the given number. (param: 1-4) */
Real Basicbot::getSensorReading(int sensorNumber) {}

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