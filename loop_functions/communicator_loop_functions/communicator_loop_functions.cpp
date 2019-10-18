#include "communicator_loop_functions.h"

#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <controllers/alibot/alibot.h>
#include <argos3/core/utility/math/vector2.h>

#include <list>
#include <iterator>

/****************************************/

CommunicatorLoopFunctions::CommunicatorLoopFunctions() {
}

CommunicatorLoopFunctions::~CommunicatorLoopFunctions(){

}

/****************************************/
/****************************************/

void CommunicatorLoopFunctions::Init(TConfigurationNode& t_tree){
   
   CollectBotControllers();
}

void CommunicatorLoopFunctions::PreStep(){

   if(botControllers.size() > 0){ // Have we collected any controllers?
      Alibot* firstControllerPtr = getController(0);

      if(!firstControllerPtr->getIsBusy()){ //Is controller ready for a command?

         switch (commandCompletionCounter)
         {
         case 0:  firstControllerPtr->pointTowards(Alibot::CompassDirection::east); break;
         case 1:  firstControllerPtr->moveOneCellForward(); break;
         case 2:  firstControllerPtr->moveOneCellForward(); break;
         case 3:  firstControllerPtr->pointTowards(Alibot::CompassDirection::south); break;
         case 4:  firstControllerPtr->moveOneCellForward(); break;
         case 5:  firstControllerPtr->moveOneCellForward(); break;
         
         default: argos::LOG << "All commands has been executed!" << std::endl;
            break;
         }

         commandCompletionCounter++;
      }
   }
}

/* Returns the desired controller if it exits. */
Alibot* CommunicatorLoopFunctions::getController(int controllerNumber){

   std::list<Alibot*>::iterator it = botControllers.begin();
   std::advance(it, controllerNumber);

   return *it;
}

/* Find and collects all foot-bot controllers.
 * (Only works with alibots) */
void CommunicatorLoopFunctions::CollectBotControllers(){
   
   /* Get a map containing all active foot-bots */
   CSpace::TMapPerType& botMap = GetSpace().GetEntitiesByType("foot-bot");

   /* Iterate through all bots and collect their controller */
   for(CSpace::TMapPerType::iterator it = botMap.begin(); it != botMap.end(); it++){
      CFootBotEntity& cFootbot = *any_cast<CFootBotEntity*>(it->second); //Get the footbot
      Alibot& controller = dynamic_cast<Alibot&>(cFootbot.GetControllableEntity().GetController()); //Get the controller of the footbot
      Alibot *pr = &controller;
      botControllers.push_back(pr); //Put it a the end of the list
   }
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CommunicatorLoopFunctions, "communicator_loop_functions");