#ifndef WAREHOUSE_USER_FUNCTION_CPP
#define WAREHOUSE_USER_FUNCTION_CPP

#include "WareHouse_qt_user_functions.h"

/*****
 * Constructor: In order for drawing functions in this class to be used by
 * ARGoS it must be registered using the RegisterUserFunction function.
 *****/
WareHouse_qt_user_functions::WareHouse_qt_user_functions() : loopFunctions(dynamic_cast<WareHouse_loop_functions &>(CSimulator::GetInstance().GetLoopFunctions()))
{
    RegisterUserFunction<WareHouse_qt_user_functions, CFootBotEntity>(&WareHouse_qt_user_functions::DrawOnRobot);
    RegisterUserFunction<WareHouse_qt_user_functions, CFloorEntity>(&WareHouse_qt_user_functions::DrawOnArena);
}

/*****
 *
 *****/
void WareHouse_qt_user_functions::DrawOnRobot(CFootBotEntity &entity)
{
}

/*****
 *
 *****/
void WareHouse_qt_user_functions::DrawOnArena(CFloorEntity &entity)
{
    DrawPickingStation();
}

/*****
 *
 *****/
void WareHouse_qt_user_functions::DrawPod()
{

    Real x, y;
    for (size_t i = 0; i < loopFunctions.PodList.size(); i++)
    {
        x = loopFunctions.PodList[i].GetX();
        y = loopFunctions.PodList[i].GetY();
        DrawBox(CVector3(x, y, 0.1), CQuaternion(), loopFunctions.PodSize);
    }
}

/*****
 * This function is called by the DrawOnArena(...) function.
 *****/
void WareHouse_qt_user_functions::DrawPickingStation()
{
    /* 2d cartesian coordinates of the nest */
    Real x_coordinate = 1.0;
    Real y_coordinate = 1.0;

    /* required: leaving this 0.0 will draw the nest inside of the floor */
    Real elevation = 0.0;

    /* 3d cartesian coordinates of the nest */
    CVector3 nest_3d(x_coordinate, y_coordinate, elevation);

    /* Draw the nest on the arena. */
    DrawCircle(nest_3d, CQuaternion(), 0.5, CColor::GRAY50);
}
/*****
 *
 *****/
void WareHouse_qt_user_functions::DrawPath()
{
}
/*****
 *
 *****/
void WareHouse_qt_user_functions::DrawQr()
{
}

REGISTER_QTOPENGL_USER_FUNCTIONS(WareHouse_qt_user_functions, "WareHouse_qt_user_functions")

#endif // !WAREHOUSE_USER_FUNCTION_CPP
