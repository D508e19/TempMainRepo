#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

class RobotWrapper
{
private:
    std::queue<instruction> instructionQueue;
    std::queue<int> instructionsValuesQueue;

    Basicbot* m_bot;
    Pathfinder pf = Pathfinder();

    direction lastFacing;
    Coordinate lastCoordinate;

public:
    RobotWrapper();
    RobotWrapper(Basicbot *bot); 
    ~RobotWrapper();

    void Tick();

    void TranslatePathToInstructions(Path p);
    void AddInstructionToQueue(instruction ins, int tiles);
    void SendNextInstruction();

    direction GetFaceTowardsInstruction(Coordinate wantsToFace, Coordinate current, direction lastFacing);
};


#endif