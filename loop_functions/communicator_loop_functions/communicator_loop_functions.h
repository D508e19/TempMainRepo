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

   CommunicatorLoopFunctions();
   virtual ~CommunicatorLoopFunctions();

   virtual void Init(TConfigurationNode& t_tree);

   virtual void PreStep();

private:

   /* A list for all controllers */
   //std::list<Basicbot*> botControllers;

   /* A map for all controllers. */
   std::map<int, Basicbot*> botControllers;

   /* Returns the desired controller if it exits. */
   Basicbot* getController(int controllerNumber);

   /* Find and collects all foot-bot controllers.
    * (Only works with Basicbot) */
   void CollectBotControllers();

   /* Print robot ids for all collected controllers. */
   void printControllers();

   int completedCommands = 0;
};

#endif