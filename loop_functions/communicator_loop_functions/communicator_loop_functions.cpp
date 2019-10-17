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

}

/* Delegates destinations to controllers that is available. /
void CommunicatorLoopFunctions::DelegateDestinations(){

   /* Iterate through all controllers and check if bot is ready for directions /
   std::list<Alibot*>::iterator it = this->botControllers.begin(); 
   std::list<Alibot*>::iterator end = this->botControllers.end();
    
   for(it; it != end; it++){

      /* Is this bot ready for directions? /
      if((*it)->IsReadyForDestination()){

         /* Is there any directions left to give? /
         if(destinations.size() != 0){
            std::list<CVector2>::iterator itDest = destinations.begin();

            CVector2 dest = *itDest;
            destinations.pop_front();
            (*it)->SetDestination(dest);
         }
      }
   }
}/*

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