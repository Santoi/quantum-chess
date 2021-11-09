#include "instructions.h"


ChatInstruction::ChatInstruction(std::string&& message)
                :message(std::move(message)){
}

