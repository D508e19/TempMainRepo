#ifndef WareHouse_loop_functions_CPP
#define WareHouse_loop_functions_CPP

#include "WareHouse_loop_functions.h"

WareHouse_loop_functions::WareHouse_loop_functions() {}
WareHouse_loop_functions::~WareHouse_loop_functions() {}
void WareHouse_loop_functions::Init(TConfigurationNode &t_tree)
{

   CollectBotControllers();

   //wh.SetupWarehouse(botControllers);

   // Send a pointer to this loop functions object to each controller.
   argos::CSpace::TMapPerType &footbots_ = GetSpace().GetEntitiesByType("foot-bot");
   argos::CSpace::TMapPerType::iterator it;

   for (it = footbots_.begin(); it != footbots_.end(); it++)
   {
      argos::CFootBotEntity &footBot = *argos::any_cast<argos::CFootBotEntity *>(it->second);
      WareHouse_bot_controller &c = dynamic_cast<WareHouse_bot_controller &>(footBot.GetControllableEntity().GetController());

      c.SetLoopFunctions(this);
   }
}

void WareHouse_loop_functions::PreStep()
{
   //wh.Tick();
}

/* Returns the desired controller if it exits. */
WareHouse_bot_controller *WareHouse_loop_functions::getController(int robotID)
{
   return botControllers[robotID];
}

/* Find and collects all foot-bot controllers.
 * (Only works with Basicbot) */
void WareHouse_loop_functions::CollectBotControllers()
{

   /* Get a map containing all active foot-bots */
   CSpace::TMapPerType &botMap = GetSpace().GetEntitiesByType("foot-bot");

   int robotIDCounter = 0;

   /* Iterate through all bots and collect their controller */
   for (CSpace::TMapPerType::iterator it = botMap.begin(); it != botMap.end(); it++)
   {
      CFootBotEntity &cFootbot = *any_cast<CFootBotEntity *>(it->second);                                                                //Get the footbot
      WareHouse_bot_controller &controller = dynamic_cast<WareHouse_bot_controller &>(cFootbot.GetControllableEntity().GetController()); //Get the controller of the footbot
      WareHouse_bot_controller *pr = &controller;
      //int robotID = pr->robotID; //TODO This will be correct when a manager is made
      pr->robotID = robotIDCounter++;
      botControllers[pr->robotID] = pr;
   }
}

void WareHouse_loop_functions::Destroy()
{
   //wh.CollectData();
}

REGISTER_LOOP_FUNCTIONS(WareHouse_loop_functions, "wareHouse_loop_functions");

#endif // !WareHouse_loop_functions
