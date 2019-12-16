#ifndef WareHouse_bot_controller_CPP
#define WareHouse_bot_controller_CPP
#include "WareHouse_bot_controller.h"
#include <math.h>
#include <iomanip>
#include <sstream>

#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>
WareHouse_bot_controller::WareHouse_bot_controller() :
    m_pcWheels(NULL),
                                                       m_pcGroundSensor(NULL),
                                                       m_pcProximity(NULL),
                                                       m_cAlpha(10.0f),
                                                       m_fDelta(0.5f), // default: 0.5
                                                       m_fWheelVelocity(2.5f),
                                                       m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                                                                               ToRadians(m_cAlpha)),

                                                       m_turningSpeed(5.49778714378213f), //TODO calculate instead
                                                       movingSpeed(10.0f),                //TODO calculate instead

                                                       ticksToTurn(20),        //TODO calculate instead
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

{
}

void WareHouse_bot_controller::Init(TConfigurationNode &t_node)
{

    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
    m_pcPosSens = GetSensor<CCI_PositioningSensor>("positioning");
    m_pcGroundSensor = GetSensor<CCI_FootBotMotorGroundSensor>("footbot_motor_ground");

    GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
    m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
    GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
    GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);

    //ReadCellQR();
    //currentInstruction = idle;
}

void WareHouse_bot_controller::ControlStep()
{
    switch (currentInstruction)
    {
    case idle:
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
        //argos::LOGERR << "bot: " << robotID << " default in ControlStep switch. currentInstruction: " << currentInstruction << std::endl;
        break;
    }
}

void WareHouse_bot_controller::MoveForward()
{
    if (!isBusy)
    {
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
        //argos::LOG << "Arrived at: " << lastReadCellQR.x << " , " << lastReadCellQR.y << std::endl;
        ResetBot();
    }
}

void WareHouse_bot_controller::TurnRight()
{
    if (!isBusy)
    {
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
        if (facing == north)
        {
            facing = east;
        }
        else if (facing == south)
        {
            facing = west;
        }
        else if (facing == east)
        {
            facing = south;
        }
        else if (facing == west)
        {
            facing = north;
        }
        ResetBot();
    }
}

void WareHouse_bot_controller::TurnLeft()
{
    if (!isBusy)
    {
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
        if (facing == north)
        {
            facing = west;
        }
        else if (facing == south)
        {
            facing = east;
        }
        else if (facing == east)
        {
            facing = east;
        }
        else if (facing == west)
        {
            facing = south;
        }
        ResetBot();
    }
}

void WareHouse_bot_controller::Turn180()
{
    if (!isBusy)
    {
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
        if (facing == north)
        {
            facing = south;
        }
        else if (facing == south)
        {
            facing = north;
        }
        else if (facing == east)
        {
            facing = west;
        }
        else if (facing == west)
        {
            facing = east;
        }
        ResetBot();
    }
}

void WareHouse_bot_controller::PickUpPod()
{
    if (!isBusy)
    {
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

void WareHouse_bot_controller::PutDownPod()
{
    if (!isBusy)
    {
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

void WareHouse_bot_controller::BotWait()
{
    if (!isBusy)
    {
        isBusy = true;
        counter = ticksToWait;
    }

    if (counter > 0)
    {
        ticksWait++;
        counter--;
        if (counter == 0)
        {
            //argos::LOG << "waited: " << ticksToWait << " ticks." << std::endl;
            ResetBot();
        }
    }
}

void WareHouse_bot_controller::ResetBot()
{
    m_pcWheels->SetLinearVelocity(0, 0);
    cellsToMove = 1;
    ticksToWait = 1;
    currentInstruction = idle;
    isBusy = false;
}

void WareHouse_bot_controller::ReadCellQR()
{
    // TODO: BUGBUGBUG
    //argos::LOG << "read QR" << std::endl;
    CVector2 temp = GetPosition2D();
    double x = temp.GetX() * 5;
    double y = temp.GetY() * 5;
    x = std::round(x);
    y = std::round(y);
    lastReadCellQR = Coordinate((int)x, (int)y);
}

void WareHouse_bot_controller::LogReadablePosition()
{
    CVector2 temp = GetPosition2D();
    double x = temp.GetX();
    double y = temp.GetY();

    std::stringstream stream;
    stream << std::fixed << std::setprecision(5) << x << ", " << y;
    std::string s = stream.str();

    //argos::LOG << "Position: " << s << std::endl;
};

/* Returns the bots current postion as a 2D vector. */
CVector2 WareHouse_bot_controller::GetPosition2D()
{
    const CCI_PositioningSensor::SReading &tPosReads = m_pcPosSens->GetReading();
    return CVector2(tPosReads.Position.GetX(), tPosReads.Position.GetY());
}

bool WareHouse_bot_controller::IsHoldingPod()
{
    return isHoldingpod;
}


void WareHouse_bot_controller::SetLoopFunctions(WareHouse_loop_functions *lf)
{
    LoopFunctions = lf;
}



REGISTER_CONTROLLER(WareHouse_bot_controller, "WareHouse_bot_controller")
#endif // DEBUG
