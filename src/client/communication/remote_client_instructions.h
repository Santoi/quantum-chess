#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H

#include <string>
#include <list>
#include <vector>
#include "../position.h"
#include "../ascii/ascii_board.h"
#include "../../common/src/packet.h"
#include "client_protocol.h"
#include "chessman_data.h"
#include "../game/game.h"

#define SPLIT_SOUND 0
#define MERGE_SOUND 1
#define CAPTURE_SOUND 2

// TODO diferenciar las que llegan de las que se van.

class ClientProtocol;

class ChessmanData;

class RemoteClientInstruction {
protected:
  const std::string instructor_nick_name;

public:
  RemoteClientInstruction() = default;

  //A RemoteClientInstruction is created, saving the instructor's nick name received in the
  //function parameter.
  RemoteClientInstruction(const std::string &instructor_nick_name);

  virtual void
  fillPacketWithInstructionsToSend(Packet &packet, ClientProtocol &protocol);

  //A RemoteClientInstruction derived class needs to implement the virtual method makeAction.
  virtual void makeAction(Game &game) = 0;

  virtual ~RemoteClientInstruction() = default;

};

class RemoteClientChatInstruction : public RemoteClientInstruction {
private:
  const std::string message;

public:
  RemoteClientChatInstruction() = delete;

  //Creates a RemoteClientChatInstruction saving the nick_name and message passed as function
  //parameters.
  RemoteClientChatInstruction(const std::string &nick_name,
                              const std::string &message);

  //Prints to stdout "instructor_nick_name sends message"
  void makeAction(Game &game) override;

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientChatInstruction() = default;
};

class RemoteClientExitMessageInstruction : public RemoteClientInstruction {
public:
  RemoteClientExitMessageInstruction() = delete;

  //Creates a RemoteClientExitMessageInstruction saving the nick_name of the person leaving
  //passed as function parameters.
  RemoteClientExitMessageInstruction(const std::string &nick_name);

  //Prints to stdout "instructor_nick_name left the game"
  void makeAction(Game &game);

  ~RemoteClientExitMessageInstruction() = default;
};

class RemoteClientLoadBoardInstruction : public RemoteClientInstruction {
  std::vector<ChessmanData> chessman_data_vector;

public:
  RemoteClientLoadBoardInstruction() = delete;

  RemoteClientLoadBoardInstruction(
          std::vector<ChessmanData> &&chessman_data_vector_);

  void makeAction(Game &game);

  ~RemoteClientLoadBoardInstruction() = default;
};

class RemoteClientMoveInstruction : public RemoteClientInstruction {
  Position initial;
  Position final;

public:
  RemoteClientMoveInstruction() = delete;

  RemoteClientMoveInstruction(const Position &initial_, const Position &final_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientMoveInstruction() = default;
};

class RemoteClientExceptionInstruction : public RemoteClientInstruction {
  const std::string message;

public:
  RemoteClientExceptionInstruction() = delete;

  RemoteClientExceptionInstruction(const std::string &message);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientExceptionInstruction() = default;
};

class RemoteClientPossibleMovesInstruction : public RemoteClientInstruction {
  std::list<Position> positions;

public:
  RemoteClientPossibleMovesInstruction() = delete;

  RemoteClientPossibleMovesInstruction(std::list<Position> &&positions_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientPossibleMovesInstruction() = default;
};

class RemoteClientPossibleSplitsInstruction : public RemoteClientInstruction {
  std::list<Position> positions;

public:
  RemoteClientPossibleSplitsInstruction() = delete;

  RemoteClientPossibleSplitsInstruction(std::list<Position>
                                        &&positions_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientPossibleSplitsInstruction() = default;
};

class RemoteClientPossibleMergesInstruction : public RemoteClientInstruction {
  std::list<Position> positions;

public:
  RemoteClientPossibleMergesInstruction() = delete;

  RemoteClientPossibleMergesInstruction(std::list<Position>
                                        &&positions_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientPossibleMergesInstruction() = default;
};

class RemoteClientSplitInstruction : public RemoteClientInstruction {
  Position from;
  Position to1;
  Position to2;

public:
  RemoteClientSplitInstruction() = delete;

  RemoteClientSplitInstruction(
          const Position &from, const Position &to1, const Position &to2);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientSplitInstruction() = default;
};

class RemoteClientMergeInstruction : public RemoteClientInstruction {
  Position from1;
  Position from2;
  Position to;

public:
  RemoteClientMergeInstruction() = delete;

  RemoteClientMergeInstruction(
          const Position &from1_, const Position &from2_, const Position &to_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientMergeInstruction() = default;
};

class RemoteClientSameChessmanInstruction : public RemoteClientInstruction {
  std::list<Position> positions;

public:
  RemoteClientSameChessmanInstruction() = delete;

  RemoteClientSameChessmanInstruction(std::list<Position>
                                      &&positions_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientSameChessmanInstruction() = default;
};

class RemoteClientEntangledChessmanInstruction
        : public RemoteClientInstruction {
  std::list<Position> positions;

public:
  RemoteClientEntangledChessmanInstruction() = delete;

  RemoteClientEntangledChessmanInstruction(std::list<Position>
                                           &&positions_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientEntangledChessmanInstruction() = default;
};

class RemoteClientSoundInstruction
        : public RemoteClientInstruction {
  uint8_t sound;

public:
  RemoteClientSoundInstruction() = delete;

  RemoteClientSoundInstruction(uint8_t sound_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientSoundInstruction() = default;
};

class RemoteClientLogInstruction
        : public RemoteClientInstruction {
  std::list<std::string> log;

public:
  RemoteClientLogInstruction() = delete;

  RemoteClientLogInstruction(std::list<std::string> &&log_);

  void makeAction(Game &game);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientLogInstruction() = default;
};

#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
