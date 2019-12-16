#ifndef WAREHOUSE_QT_USER_FUNCTIONS_H
#define WAREHOUSE_QT_USER_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <src/argos/dev/WareHouse_loop_functions.h>

using namespace argos;
using namespace std;

class WareHouse_bot_controller;
class WareHouse_loop_functions;

class WareHouse_qt_user_functions : public CQTOpenGLUserFunctions
{

public:
    WareHouse_qt_user_functions();

    /* interface functions between QT and ARGoS */
    void DrawOnRobot(CFootBotEntity &entity);
    void DrawOnArena(CFloorEntity &entity);
    //void DrawOnBox(CBoxEntity &entity);

private:
    /* private helper drawing functions */
    void DrawPod();
    void DrawQr();
    void DrawPath();
    void DrawPickingStation();

    WareHouse_loop_functions &loopFunctions;
};

#endif /* WAREHOUSE__QT_USER_FUNCTIONS_H */