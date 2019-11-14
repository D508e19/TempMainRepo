#ifndef COMMUNICATOR_LOOP_FUNCTIONS_H
#define COMMUNICATOR_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <controllers/alibot/alibot.h>
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/core/utility/math/vector2.h>

#include <list>

#include <source/pods/PodManager.h>
#include <source/orders/OrderManager.h>

using namespace argos;

class CommunicatorLoopFunctions : public CLoopFunctions {

public:
   OrderManager om;
   PodManager pm;

   /* A map used to convert a compass direction to a vector*/
   std::map<Alibot::CompassDirection, CVector2> direction_vectors = {
      { Alibot::CompassDirection::north, CVector2(0, 1) },
      { Alibot::CompassDirection::east, CVector2(1, 0) },
      { Alibot::CompassDirection::south, CVector2(0, -1) },
      { Alibot::CompassDirection::west, CVector2(-1, 0) }
   };

   CommunicatorLoopFunctions();
   virtual ~CommunicatorLoopFunctions();

   virtual void Init(TConfigurationNode& t_tree);

   virtual void PreStep();

private:

   /* A list for all controllers */
   std::list<Alibot*> botControllers;

   /* Returns the desired controller if it exits. */
   Alibot* getController(int controllerNumber);

   /* Find and collects all foot-bot controllers.
    * (Only works with alibots) */
   void CollectBotControllers();

   /* temp variable to keep track of orders. */
   int commandCompletionCounter = 0;
};

#endif