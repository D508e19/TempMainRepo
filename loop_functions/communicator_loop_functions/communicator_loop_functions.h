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

   /* An enum for compass directions */
   enum class CompassDirection {
      north, 
      east, 
      south, 
      west
   };
   
   /* A map used to convert a compass direction to a vector*/
   std::map<CommunicatorLoopFunctions::CompassDirection, CVector2> direction_vectors = {
      { CompassDirection::north, CVector2(0, 1) },
      { CompassDirection::east, CVector2(1, 0) },
      { CompassDirection::south, CVector2(0, -1) },
      { CompassDirection::west, CVector2(-1, 0) }
   };

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