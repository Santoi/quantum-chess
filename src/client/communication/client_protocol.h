#ifndef QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H

#include <string>
#include "../../common/socket.h"
#include "../../common/protocol.h"
#include "remote_client_instructions.h"
#include "../../common/client_data.h"
#include <memory>
#include <map>
#include <list>
#include <vector>

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

class RemoteClientInstruction;

class ClientProtocol : public Protocol {
public:
  ClientProtocol() = default;

  //Given the client socket, it returns the number of games running in server
  std::map<uint16_t, std::vector<ClientData>>
  receiveMatchesInfo(Socket &socket);

  //It sends to the client socket the game_number received as parameter
  void sendChosenGame(Socket &socket, uint16_t game_number);

  //It sends to the client socket the client's nick_name, following the protocol
  void sendClientsNickName(Socket &socket, std::string &nick_name);

  void fillPacketWithChatMessage(Packet &packet, const std::string &message);

  //Following the protocol, it receives from socket the information necessary
  // to create the appropriate RemoteClientInstruction.
  // After the function ends, the ptr_instruction points to a valid instruction
  // that can be executed calling the makeAction instruction
  void receiveInstruction(Socket &socket,
                          std::shared_ptr<RemoteClientInstruction>
                          &ptr_instruction);

  void sendInstruction(Socket &socket,
                       std::shared_ptr<RemoteClientInstruction> &instruction);

  ~ClientProtocol() = default;

  void
  fillPacketWithMoveMessage(Packet &packet, BoardPosition &initial,
                            BoardPosition &final);

  void fillPacketWithPossibleMovesMessage(Packet &packet,
                                          const BoardPosition &position);

  void getAvailableRoles(Socket &socket, std::list<ClientData::Role> &roles);

  void sendChosenRole(Socket &socket, ClientData::Role role);

  void
  fillPacketWithPossibleSplitsMessage(Packet &packet, const BoardPosition &position);

  void fillPacketWithSplitMessage(Packet &packet, BoardPosition &from, BoardPosition &to1,
                                  BoardPosition &to2);

  void
  fillPacketWithPossibleMergesMessage(Packet &packet, const BoardPosition &position);

  void
  fillPacketWithPossibleMergesMessage(Packet &packet, const BoardPosition &position1,
                                      const BoardPosition &position2);

  void
  fillPacketWithSameChessmanInstruction(Packet &packet, BoardPosition &position);

  void
  fillPacketWithEntangledChessmanInstruction(Packet &packet,
                                             BoardPosition &position);

  void fillPacketWithMergeMessage(Packet &packet, const BoardPosition &from1,
                                  const BoardPosition &from2, const BoardPosition &to);

private:
  // Gets necessary information to create the RemoteClientChatInstruction
  // (the instructor's nickname and the corresponding message)
  // After the function ends, the ptr_instruction points to this
  // new ChatInstruction
  void fillChatInstruction(Socket &socket,
                           std::shared_ptr<RemoteClientInstruction> &
                           ptr_instruction);

  // Gets necessary information to create the RemoteClientExitMessageInstruction
  // (the instructor's nickname, this is, the person that left the match)
  // After the function ends, the ptr_instruction points to this
  // new ExitInstruction
  void fillExitInstruction(Socket &socket,
                           std::shared_ptr<RemoteClientInstruction> &
                           ptr_instruction);

  void fillLoadBoardInstruction(Socket &socket,
                                std::shared_ptr<RemoteClientInstruction>
                                &ptr_instruction);

  void fillShortLogInstruction(Socket &socket,
                               std::shared_ptr<RemoteClientInstruction>
                               &instruction);

  void fillPossibleMovesInstruction(Socket &socket,
                                    std::shared_ptr<RemoteClientInstruction>
                                    &ptr_instruction);

  void fillPossibleSplitsInstruction(Socket &socket,
                                     std::shared_ptr<RemoteClientInstruction>
                                     &ptr_instruction);

  void fillPossibleMergesInstruction(Socket &socket,
                                     std::shared_ptr<RemoteClientInstruction>
                                     &ptr_instruction);

  void fillSameChessmanInstruction(Socket &socket,
                                   std::shared_ptr<RemoteClientInstruction>
                                   &ptr_instruction);

  void fillEntangledChessmanInstruction(Socket &socket,
                                        std::shared_ptr<RemoteClientInstruction>
                                        &ptr_instruction);

  void fillSoundInstruction(Socket &socket,
                            std::shared_ptr<RemoteClientInstruction>
                            &ptr_instruction);

  void fillLogInstruction(Socket &socket,
                          std::shared_ptr<RemoteClientInstruction> &ptr);
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
