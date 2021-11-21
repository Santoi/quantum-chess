#ifndef QUANTUM_CHESS_PROJ_MATCH_H
#define QUANTUM_CHESS_PROJ_MATCH_H


#include <list>
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket.h"
#include "../../common/src/thread.h"
#include "quantum_chess/board.h"
#include "instructions/instruction.h"
#include "client_handler.h"

class ClientHandler;

class Instruction;

class Match: public Thread {
private:
    Board board;
    std::map<uint16_t, ClientHandler> clients;
    std::map<uint16_t, BlockingQueue<Instruction>> listening_queues;
    BlockingQueue<Instruction> match_updates_queue;

public:
    //Creates a match, creating the ClientDataRepository and the BlockingQueue<Instruction>. The client's vector
    //is also created and set with an initial capacity of BASE_CLIENTS.
    Match();

    //Moves the other match's thread, clients, listening queues and the thread safe queue to the new
    //match. The new match also copies the number of accepted clients of the other_match.
    Match(Match&& other_match);

    //Adds client to list of clients and nick names repository, and calls the client to start
    //single-threadedly
    void addSingleThreadedClientToMatchAndStart(Socket&& client_socket);

    //Adds client to list of clients and nick names repository, and calls the client to start with threads,
    //also sending the client the boolean threaded_match.
    void addClientToMatch(Socket &&client_socket, bool threaded_match,
                          uint16_t client_id);

    //Pops from updates_queue an instruction, and asks this instruction to makeActionAndNotifyAllListeningQueues.
    void checkAndNotifyUpdates();

    //Iterates over the list of clients, asking each one if the respective client is active. If either
    //of them is active, then a true is returned. If neither is active, a false is returned.
    bool hasActiveClients() const;

    //Creates an ExitInstruction with MATCH_ID, and pushes it to the match_updates_queue. This is ideal
    //for when one wants to end the game's execution.
    void pushExitInstructionToUpdatesQueue();

    ~Match() = default;

    void stop();

    std::vector<const ClientData *> getClientsData() const;

protected:
    //Calls checkAndNotifyUpdates until the match's ExitInstruction is popped and asked to
    //makeActionAndNotifyAllListeningQueues. This throws a running exception that is catched and
    //execution ends.
    void run() override;

private:
    //Creates a new ClientHandler and adds it to the client's vector (if the vector's capacity is not
    //enough, it is incremented by BASE_CLIENTS). The number of accepted clients is incremented by one.
    void addClientWithIdToListOfClients(Socket&& client_socket, ClientData &client_data);

    //Asks the new remote client for its nickname and saves it into the nick names repository,
    //associating it with the given client_id.
    void addClientsNickNameToRepository(uint16_t client_id);

    ClientData askClientData(Socket &socket, uint16_t client_id);
};



#endif //QUANTUM_CHESS_PROJ_MATCH_H
