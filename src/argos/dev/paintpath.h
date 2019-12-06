#ifndef  PAINT_PATH_LOOP_FUNCTIONS_H
#define PAINT_PATH_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>

using namespace argos;

class PaintPath_LoopFunctios : public CLoopFunctions
{
    public:
        typedef std::map<CFootBotEntity *, std::vector<CVector3>> TWaypointMap;
        TWaypointMap m_tWaypoints;
};


#endif // !PAINT_PATH_LOOP_FUNCTIONS_H
