#ifndef COMMUNICATOR_LOOP_FUNCTIONS_H
#define COMMUNICATOR_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <controllers/alibot/alibot.h>
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/core/utility/math/vector2.h>

#include <list>

using namespace argos;

class CommunicatorLoopFunctions : public CLoopFunctions {

public:

   CommunicatorLoopFunctions();
   virtual ~CommunicatorLoopFunctions();

   virtual void Init(TConfigurationNode& t_tree);

   virtual void PreStep();

private:

   /* A list for all controllers */
   std::list<Alibot*> botControllers;

   /* Find and collects all foot-bot controllers.
    * (Only works with alibots) */
   void CollectBotControllers();
};

#endif