#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>

class Instruction {

public:
    Instruction();
    ~Instruction();
};

class ChatInstruction: public Instruction {
    std::string message;
};

class MovementInstruction: public Instruction {

};
#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
