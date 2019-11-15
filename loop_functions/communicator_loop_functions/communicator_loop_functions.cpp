#include "communicator_loop_functions.h"

#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <controllers/basicbot/basicbot.h>
#include <argos3/core/utility/math/vector2.h>

#include <list>
#include <iterator>

//#include "src/pods/PodManager.h"

/****************************************/

CommunicatorLoopFunctions::CommunicatorLoopFunctions(){}

CommunicatorLoopFunctions::~CommunicatorLoopFunctions(){}

/****************************************/
/****************************************/

void CommunicatorLoopFunctions::Init(TConfigurationNode& t_tree){
   om = OrderManager(100);
   pm = PodManager(50);
   argos::LOG << "Pod count: " << pm.GetCount() << std::endl;
   CollectBotControllers();

}

void CommunicatorLoopFunctions::PreStep(){

   //printControllers();

   if(!getController(0)->isBusy){

      std::cout << "Giving robot next command. " << completedCommands << std::endl;

      switch (completedCommands)
      {
      case 0: getController(0)->MoveForward(2); break;
      case 1: getController(0)->TurnDegrees(90); break;
      case 2: getController(0)->MoveForward(1); break;
      case 3: getController(0)->TurnDegrees(-90); break;
      case 4: getController(0)->MoveForward(3); break;
      case 5: getController(0)->TurnDegrees(180); break;
      case 6: getController(0)->MoveForward(3); break;
      case 7: getController(0)->TurnDegrees(90); break;
      case 8: getController(0)->MoveForward(1); break;
      case 9: getController(0)->TurnDegrees(-90); break;
      case 10: getController(0)->MoveForward(2); break;
      
      default:
         break;
         }

      completedCommands++;
   }


   // --------------------- TODO: Remove ----------------
   Order temp = om.getNewOrder();
   argos::LOG << "OrderID: " << temp.getOrderID() << " PodID: "<< temp.getPodID() << std::endl;
   argos::LOG << "Pod count: " << pm.GetCount() << std::endl;
   // ------------------------------------------------
      
}

void CommunicatorLoopFunctions::printControllers(){
   
   std::map<int, Basicbot*>::iterator it;
   for(it = botControllers.begin(); it != botControllers.end(); it++){
      int robotID = it->first;
      std::cout << "Robot ID: " << robotID << std::endl;
   }
}

/* Returns the desired controller if it exits. */
Basicbot* CommunicatorLoopFunctions::getController(int robotID){
   return botControllers[robotID];
}

/* Find and collects all foot-bot controllers.
 * (Only works with Basicbot) */
void CommunicatorLoopFunctions::CollectBotControllers(){
   
   /* Get a map containing all active foot-bots */
   CSpace::TMapPerType& botMap = GetSpace().GetEntitiesByType("foot-bot");

   int robotIDCounter = 0;

   /* Iterate through all bots and collect their controller */
   for(CSpace::TMapPerType::iterator it = botMap.begin(); it != botMap.end(); it++){
      CFootBotEntity& cFootbot = *any_cast<CFootBotEntity*>(it->second); //Get the footbot
      Basicbot& controller = dynamic_cast<Basicbot&>(cFootbot.GetControllableEntity().GetController()); //Get the controller of the footbot
      Basicbot *pr = &controller;
      //int robotID = pr->robotID; //TODO This will be correct when a manager is made
      pr->robotID = robotIDCounter++;
      botControllers[pr->robotID] = pr;
   }
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CommunicatorLoopFunctions, "communicator_loop_functions");