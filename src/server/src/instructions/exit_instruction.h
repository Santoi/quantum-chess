#ifndef QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H

#include <string>
#include <list>
#include "../../../common/src/packet.h"
#include "../server_protocol.h"
#include <vector>

class ExitInstruction : public Instruction {
private:
  // It is copied because client is destroyed
  ClientData instructor_data;

public:
  ExitInstruction() = delete;

  //Creates a new ExitInstruction, saving the client_id (that is the instrcuctor's id).
  explicit ExitInstruction(const ClientData &instructor_data_);

  //It creates a new ExitInstruction and sends it to all the listening queues (even to the leaving
  //client queue), and joins the ClientHandler that corresponds to the object's instructor_id.
  //If the instructor's id is the MATCH_ID, a runtime_error exception is thrown. This is useful
  //to stop the match's execution.
  void makeActionAndNotifyAllListeningQueues(
          std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
          Match &match,
          BlockingQueue<Instruction> &match_updates_queue) override;

  //Gets the leaving instructor's nickname from the ClientDataRepository using the object's instructor_id
  //attribute, and calls the protocol method fillPacketWithExitInfo to fill the given packet. If the
  //client_receiver_id (this is, the id of the corresponding remote client) ìs the same as the object's
  //instructor_id (the id of the person that left), it means that the remote client is disconnected and
  //a runtime_error exception is thrown.
  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;

  ~ExitInstruction() = default;
};


#endif //QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H
