#ifndef WareHouse_loop_functions_H
#define WareHouse_loop_functions_H

#include <vector>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/datatypes/color.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include "src/argos/dev/WareHouse_bot_controller.h"

#include <list>
#include <iterator>

//#include "src/includefile.h"

using namespace argos;

class WareHouse_loop_functions : public CLoopFunctions
{
   friend class WareHouse_bot_controller;
   friend class WareHouse_qt_user_functions;
   friend class Warehouse;

public:
   //Warehouse wh;

   WareHouse_loop_functions();
   virtual ~WareHouse_loop_functions();

   virtual void Init(TConfigurationNode &t_tree);

   virtual void PreStep();

   virtual void Destroy();

protected:
   //size_t DrawDensityRate;
   size_t DrawIDs;
   size_t DrawTrails;
   size_t DrawTargetRays;

   /* physical robot & world variables */
   // Real PodRadius;
   // Real PodRadiusSquared;
   // Real PickingStationRadius;
   // Real PickingStationRadiusSquared;
   // Real PickingStationElevation;

   /* POD */
   std::vector<CVector2> PodList;
   CVector3 PodSize = CVector3(1, 1, 1);
   size_t PodItemCount;

private:
   /* A map for all controllers. */
   std::map<int, WareHouse_bot_controller *> botControllers;

   /* Returns the desired controller if it exits. */
   WareHouse_bot_controller *getController(int controllerNumber);

   /* Find and collects all foot-bot controllers.
    * (Only works with Basicbot) */
   void CollectBotControllers();

   /* private helper functions */
   void PodDistribution();

   /* Print robot ids for all collected controllers. */
   void printControllers();

   int completedCommands = 0;
};

#endif