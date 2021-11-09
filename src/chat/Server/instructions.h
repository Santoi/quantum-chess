#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>

class Instruction {

public:
    Instruction() = default;
    ~Instruction() = default;
};

class ChatInstruction: public Instruction {
private:
    std::string message;

public:
    ChatInstruction() = delete;
    ChatInstruction(std::string&& message);
    ~ChatInstruction() = default;
};

class MovementInstruction: public Instruction {

};
#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
