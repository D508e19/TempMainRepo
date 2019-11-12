#ifndef COMMUNICATOR_LOOP_FUNCTIONS_H
#define COMMUNICATOR_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <controllers/basicbot/basicbot.h>
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/core/utility/math/vector2.h>

#include <list>

using namespace argos;

class CommunicatorLoopFunctions : public CLoopFunctions {

public:

   /* A map used to convert a compass direction to a vector*/
   std::map<Basicbot::CompassDirection, CVector2> direction_vectors = {
      { Basicbot::CompassDirection::north, CVector2(0, 1) },
      { Basicbot::CompassDirection::east, CVector2(1, 0) },
      { Basicbot::CompassDirection::south, CVector2(0, -1) },
      { Basicbot::CompassDirection::west, CVector2(-1, 0) }
   };

   CommunicatorLoopFunctions();
   virtual ~CommunicatorLoopFunctions();

   virtual void Init(TConfigurationNode& t_tree);

   virtual void PreStep();

private:

   /* A list for all controllers */
   std::list<Basicbot*> botControllers;

   /* Returns the desired controller if it exits. */
   Basicbot* getController(int controllerNumber);

   /* Find and collects all foot-bot controllers.
    * (Only works with Basicbot) */
   void CollectBotControllers();

   /* temp variable to keep track of orders. */
   int commandCompletionCounter = 0;
};

#endif