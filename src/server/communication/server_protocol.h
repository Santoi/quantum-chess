#ifndef QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H

#include "../../common/socket.h"
#include "../../common/packet.h"
#include "../../common/protocol.h"
#include "../quantum_chess/position.h"
#include "../quantum_chess/client_data.h"
#include <memory>
#include "../../common/protocol.h"
#include "../../common/client_data.h"
#include <map>
#include <list>

#define POSSIBLE_MOVES_PREFIX 'a'
#define CHAT_PREFIX 'c'
#define LOAD_BOARD_PREFIX 'l'
#define EXIT_PREFIX 'e'
#define EXCEPTION_PREFIX 'x'
#define POSSIBLE_SPLITS_PREFIX 'b'
#define POSSIBLE_MERGES_PREFIX 'd'
#define SAME_CHESSMAN_PREFIX 'f'
#define ENTANGLED_CHESSMEN_PREFIX 'g'
#define MERGE_PREFIX 'h'
#define SPLIT_PREFIX 's'
#define MOVE_PREFIX 'm'
#define SOUND_PREFIX 'i'
#define LOG_PREFIX 'j'

#define POSSIBLE_MOVES_PREFIX 'a'
#define CHAT_PREFIX 'c'
#define LOAD_BOARD_PREFIX 'l'
#define EXIT_PREFIX 'e'
#define EXCEPTION_PREFIX 'x'
#define POSSIBLE_SPLITS_PREFIX 'b'
#define POSSIBLE_MERGES_PREFIX 'd'
#define SAME_CHESSMAN_PREFIX 'f'
#define ENTANGLED_CHESSMEN_PREFIX 'g'
#define MERGE_PREFIX 'h'
#define SPLIT_PREFIX 's'
#define MOVE_PREFIX 'm'
#define SOUND_PREFIX 'i'
#define LOG_PREFIX 'j'

#define POSSIBLE_MOVES_PREFIX 'a'
#define CHAT_PREFIX 'c'
#define LOAD_BOARD_PREFIX 'l'
#define EXIT_PREFIX 'e'
#define EXCEPTION_PREFIX 'x'
#define POSSIBLE_SPLITS_PREFIX 'b'
#define POSSIBLE_MERGES_PREFIX 'd'
#define SAME_CHESSMAN_PREFIX 'f'
#define ENTANGLED_CHESSMEN_PREFIX 'g'
#define MERGE_PREFIX 'h'
#define SPLIT_PREFIX 's'
#define MOVE_PREFIX 'm'
#define SOUND_PREFIX 'i'
#define LOG_PREFIX 'j'
#define SURRENDER_PREFIX 'z'

class Instruction;

class Match;

class ServerProtocol : public Protocol {
public:

  ServerProtocol() = default;

  // Sends to socket info about running matches.
  void sendMatchesInfo(Socket &socket,
                       const std::map<uint16_t, std::vector<ClientData>>
                       &matches_data);

  // Returns number of match received from socket.
  uint16_t receiveChosenGame(Socket &socket);

  //Receives from socket the remote client's nick name,
  // storing it in the nick_name parameter.
  void getNickName(Socket &socket, std::string &nick_name);

  // Receives a instruction from socket, creates a new instruction according
  // to it and stores it in insttruct_ptr.
  void receiveAndFillInstruction(Socket &socket, const ClientData &client_data,
                                 std::shared_ptr<Instruction> &instruct_ptr);

  // Sends a packet filled with an instruction.
  void sendPacket(Socket &socket,
                  std::shared_ptr<Instruction> &instruct_ptr,
                  const ClientData &client_data);

  // Fills packet with a packet with a chat message.
  void fillPacketWithChatMessage(Packet &packet,
                                 const ClientData &client_data,
                                 const std::string &message,
                                 const std::string &timestamp);

  // Fills a packet with an exit instruction.
  void fillPacketWithExitMessage(Packet &packet, const std::string &nick_name);

  // Fills a packet with an exception message.
  void
  fillPacketWithExceptionMessage(Packet &packet, const std::string &message);

  // Fills a packet with a load board message.
  void
  fillPacketWithLoadBoardMessage(Packet &packet,
                                 const std::vector<SquareData> &data,
                                 bool white);

  // Fills a packet with a message with possible moves.
  void
  fillPacketWithPossibleMoves(Packet &packet,
                              const std::list<Position> &positions);

  // Fills a packet with a message with possible merges.
  void fillPacketWithPossibleMerges(Packet &packet,
                                    const std::list<Position> &positions);

  // Fills a packet with a message with possible splits.
  void fillPacketWithPossibleSplits(Packet &packet,
                                    const std::list<Position> &positions);

  // Sends a message with available roles in list.
  void
  sendAvailableRoles(Socket &socket, const std::list<ClientData::Role> &roles);

  // Receives a player selected role.
  ClientData::Role receivePlayerRole(Socket &socket,
                                     const std::list<ClientData::Role> &roles);

  // Fill packet with a message with positions that are the same chessman_.
  void fillPacketWithSameChessmanInstruction(Packet &packet,
                                             const std::list<Position> &positions);

  // Fills a packet with message with entangled chessmen positions.
  void fillPacketWithEntangledChessmanInstruction(Packet &packet,
                                                  const std::list<Position> &positions);

  // Fills packet with a request to play a sound.
  void fillPacketWithSoundMessage(Packet &packet, uint8_t sound);

  // Fills a packet with a log message.
  void fillPacketLogMessage(Packet &packet,
                            std::list<std::string> &log);

  ~ServerProtocol() = default;

    void
    fillPacketWithSurrenderMessage(Packet &packet, const ClientData &data, std::string time_stamp);

private:
  // Creates a chat instruction receiving the incoming message.
  void fillChatInstruction(Socket &socket, const ClientData &client_data,
                           std::shared_ptr<Instruction> &instruct_ptr);

  // Creates a movement instruction receiving the incoming message.
  void fillMovementInstruction(Socket &socket, const ClientData &client_data,
                               std::shared_ptr<Instruction> &instruct_ptr);

  // Creates a possible moves instruction receiving the incoming message.
  void fillPossibleMovesInstruction(Socket &socket, const ClientData &data,
                                    std::shared_ptr<Instruction> &sharedPtr);

  // Creates a split instruction receiving the incoming message.
  void fillSplitInstruction(Socket &socket,
                            const ClientData &client_data,
                            std::shared_ptr<Instruction> &instruct_ptr);

  // Creates a merge instruction receiving the incoming message.
  void fillMergeInstruction(Socket &socket,
                            const ClientData &client_data,
                            std::shared_ptr<Instruction> &instruct_ptr);

  // Creates a possible splits instruction receiving the incoming message.
  void
  fillPossibleSplitsInstruction(Socket &socket, const ClientData &client_data,
                                std::shared_ptr<Instruction> &instruct_ptr);

  // Creates a possible merges instruction receiving the incoming message.
  void
  fillPossibleMergesInstruction(Socket &socket, const ClientData &client_data,
                                std::shared_ptr<Instruction> &instruct_ptr);

  // Creates a same chessman_ instruction receiving the incoming message.
  void
  fillSameChessmanInstruction(Socket &socket, const ClientData &client_data,
                              std::shared_ptr<Instruction> &instruct_ptr);

  // Creates an entangled chessmen instruction receiving the incoming message.
  void fillEntangledChessmenInstruction(Socket &socket,
                                        const ClientData &client_data,
                                        std::shared_ptr<Instruction>
                                        &instruct_ptr);

    void fillSurrenderInstruction(Socket &socket, const ClientData &data,
                                  std::shared_ptr<Instruction> &instruc_ptr);
};


#endif //QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
