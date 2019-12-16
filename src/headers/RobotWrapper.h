#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

class RobotWrapper
{
private:
    std::queue<instruction> instructionQueue;
    std::queue<int> instructionsValuesQueue;

    Basicbot* m_bot;
    Pathfinder* pfp; 

    direction lastFacing; // The direction of bot after last instruction.
    Coordinate lastCoordinate; // The coordination bot will be at after last instruction in queue.
 
    bool isCarrying = false;

public:
    RobotWrapper();
    RobotWrapper(Basicbot *bot, Pathfinder *pf); 
    ~RobotWrapper();

    void Tick();

    bool waitingForOrder;
    Order* currentOrder;

    void ProcessNewOrder();
    void TranslatePathToInstructions(Path p);
    void AddInstructionToQueue(instruction ins, int tiles);
    void SendNextInstruction();

    static direction GetFaceTowardsInstruction(Coordinate wantsToFace, Coordinate current, direction lastFacing);
};


#endif