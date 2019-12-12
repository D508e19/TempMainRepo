#include "communicator_loop_functions_dev.h"

#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/simulator/entities/cylinder_entity.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

#include <list>
#include <iterator>

CommunicatorLoopFunctions::CommunicatorLoopFunctions(){}
CommunicatorLoopFunctions::~CommunicatorLoopFunctions(){}

void CommunicatorLoopFunctions::Init(TConfigurationNode& t_tree){
   CollectBotControllers();

   wh.SetupWarehouse(botControllers);

}

void CommunicatorLoopFunctions::PreStep()
{
   wh.Tick();
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

void CommunicatorLoopFunctions::DrawPod()
{
   uint32_t unPlacedPods = 0;
   CBoxEntity *_pod;

   _pod = new CBoxEntity();

}

void CommunicatorLoopFunctions::Destroy()
{
   wh.CollectData();
}

REGISTER_LOOP_FUNCTIONS(CommunicatorLoopFunctions, "communicator_loop_functions");