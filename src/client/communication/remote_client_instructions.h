#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H

#include <string>
#include <list>
#include <vector>
#include "../game/position.h"
#include "../../ascii_chess/ascii_board.h"
#include "../../common/packet.h"
#include "client_protocol.h"
#include "chessman_data.h"
#include "../game/game.h"

#define SPLIT_SOUND 0
#define MERGE_SOUND 1
#define CAPTURE_SOUND 2

// TODO diferenciar las que llegan de las que se van.

class Game;

class ClientProtocol;

class ChessmanData;

class Game;

class Chat;

class ChessLog;

class ErrorLog;

class TurnLog;

class RemoteClientInstruction {
public:
  RemoteClientInstruction() = default;

  virtual void
  fillPacketWithInstructionsToSend(Packet &packet,
                                   ClientProtocol &protocol);

  //A RemoteClientInstruction derived class needs to implement the virtual method makeAction.
  virtual void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log) = 0;

  virtual ~RemoteClientInstruction() = default;

};

class RemoteClientChatInstruction : public RemoteClientInstruction {
private:
  const uint16_t client_id;
  const std::string nickname;
  const std::string message;
  const std::string timestamp;

public:
  RemoteClientChatInstruction() = delete;

  //Creates a RemoteClientChatInstruction saving the nick_name and message passed as function
  //parameters.
  RemoteClientChatInstruction(uint16_t client_id,
                              std::string nick_name,
                              std::string message,
                              std::string timestamp);

  RemoteClientChatInstruction(std::string message_);

  //Prints to stdout "instructor_nick_name sends message"
  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log) override;

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientChatInstruction() = default;
};

class RemoteClientExitMessageInstruction : public RemoteClientInstruction {
  const std::string nickname;

public:
  RemoteClientExitMessageInstruction() = delete;

  //Creates a RemoteClientExitMessageInstruction saving the nick_name of the person leaving
  //passed as function parameters.
  RemoteClientExitMessageInstruction(const std::string &nick_name);

  //Prints to stdout "instructor_nick_name left the game"
  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

  ~RemoteClientExitMessageInstruction() = default;
};

class RemoteClientLoadBoardInstruction : public RemoteClientInstruction {
  std::vector<ChessmanData> chessman_data_vector;
  bool next_white;

public:
  RemoteClientLoadBoardInstruction() = delete;

  RemoteClientLoadBoardInstruction(
      std::vector<ChessmanData> &&chessman_data_vector_, bool next_white_);

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

  ~RemoteClientLoadBoardInstruction() = default;
};

class RemoteClientMoveInstruction : public RemoteClientInstruction {
  Position initial;
  Position final;

public:
  RemoteClientMoveInstruction() = delete;

  RemoteClientMoveInstruction(const Position &initial_, const Position &final_);

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientMoveInstruction() = default;
};

class RemoteClientExceptionInstruction : public RemoteClientInstruction {
  const std::string message;

public:
  RemoteClientExceptionInstruction() = delete;

  RemoteClientExceptionInstruction(const std::string &message);

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientExceptionInstruction() = default;
};

class RemoteClientPossibleMovesInstruction : public RemoteClientInstruction {
  std::list<Position> positions;

public:
  RemoteClientPossibleMovesInstruction() = delete;

  RemoteClientPossibleMovesInstruction(std::list<Position> &&positions_);

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

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

  void
  makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
             TurnLog &turn_log);

  void fillPacketWithInstructionsToSend(Packet &packet,
                                        ClientProtocol &protocol) override;

  ~RemoteClientLogInstruction() = default;
};

class RemoteClientSurrenderInstruction
        : public RemoteClientInstruction {
    const uint16_t client_id;
    const std::string nick_name;
    const std::string time_stamp;

public:
    RemoteClientSurrenderInstruction() = default;

    RemoteClientSurrenderInstruction(uint16_t client_id,
                                     const std::string &nick_name,
                                     const std::string &time_stamp);
    void
    makeAction(Game &game, Chat &chat, ChessLog &chess_log, ErrorLog &error_log,
               TurnLog &turn_log);

    void fillPacketWithInstructionsToSend(Packet &packet,
                                          ClientProtocol &protocol) override;

    ~RemoteClientSurrenderInstruction() = default;
};


#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
