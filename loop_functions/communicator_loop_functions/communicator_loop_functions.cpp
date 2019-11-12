#include "communicator_loop_functions.h"

#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <controllers/basicbot/basicbot.h>
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
      Basicbot* firstControllerPtr = getController(0);

      if(!firstControllerPtr->getIsBusy()){ //Is controller ready for a command?

         switch (commandCompletionCounter)
         {
         case 0:  firstControllerPtr->pointTowards(Basicbot::CompassDirection::east); break;
         case 1:  firstControllerPtr->moveOneCellForward(); break;
         case 2:  firstControllerPtr->pointTowards(Basicbot::CompassDirection::north); break;
         case 3:  firstControllerPtr->moveOneCellForward(); break;
         case 4:  firstControllerPtr->pointTowards(Basicbot::CompassDirection::east); break;
         case 5:  firstControllerPtr->moveOneCellForward(); break;
         case 6:  firstControllerPtr->pointTowards(Basicbot::CompassDirection::west); break;
         case 7:  firstControllerPtr->moveOneCellForward(); break;
         
         default: argos::LOG << "All commands has been executed!" << std::endl;
            break;
         }

         commandCompletionCounter++;
      }
   }
}

/* Returns the desired controller if it exits. */
Basicbot* CommunicatorLoopFunctions::getController(int controllerNumber){

   std::list<Basicbot*>::iterator it = botControllers.begin();
   std::advance(it, controllerNumber);

   return *it;
}

/* Find and collects all foot-bot controllers.
 * (Only works with Basicbot) */
void CommunicatorLoopFunctions::CollectBotControllers(){
   
   /* Get a map containing all active foot-bots */
   CSpace::TMapPerType& botMap = GetSpace().GetEntitiesByType("foot-bot");

   /* Iterate through all bots and collect their controller */
   for(CSpace::TMapPerType::iterator it = botMap.begin(); it != botMap.end(); it++){
      CFootBotEntity& cFootbot = *any_cast<CFootBotEntity*>(it->second); //Get the footbot
      Basicbot& controller = dynamic_cast<Basicbot&>(cFootbot.GetControllableEntity().GetController()); //Get the controller of the footbot
      Basicbot *pr = &controller;
      botControllers.push_back(pr); //Put it a the end of the list
   }
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CommunicatorLoopFunctions, "communicator_loop_functions");