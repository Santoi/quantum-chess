#ifndef QUANTUM_CHESS_PROJ_ENTANGLEMENT_LOG_H
#define QUANTUM_CHESS_PROJ_ENTANGLEMENT_LOG_H

#include "../quantum_position.h"

// Represents a list where entanglements are noted.
class EntanglementLog {
  // Represents an entanglement.
  class Entanglement {
  private:
    QuantumPosition &first;
    QuantumPosition &second;

    friend EntanglementLog;

  public:
    Entanglement(QuantumPosition &pos1_, QuantumPosition &pos2_);

    bool operator==(const QuantumPosition &pos);

    // Returns a reference to the QuantumPosition which is not passed.
    QuantumPosition &getOther(const QuantumPosition &pos);
  };

  std::list<Entanglement> log;

  // Returns an iterator to log where entanglement note involving two positions
  // is.
  std::list<EntanglementLog::Entanglement>::iterator
  find(const QuantumPosition &pos1, const QuantumPosition &pos2);

public:
  EntanglementLog() = default;

  // Add an entanglement involving the two Quantum Positions.
  void
  add(QuantumPosition &pos1, QuantumPosition &pos2);

  // Updates all notes involving Quantum Position 'search' replacing it with
  // 'add'.
  void addEntanglementsOfTo(const QuantumPosition &search,
                            QuantumPosition &add);

  // Deletes all entanglements which involve one of two positions and delete
  // them if the other is not entangled with it.
  void deleteEntanglementsWhichAreNotSharedBy(const QuantumPosition &pos1,
                                              const QuantumPosition &pos2);

  // Returns true if a chessman is entangled more than once with a position.
  bool chessmanIsEntangledMoreThanOnceWithPosition(const Chessman &chessman,
                                                   const QuantumPosition &position);

  // Measures entanglements of a position of a chessman.
  void
  measureEntanglements(const Chessman &chessman,
                       const QuantumPosition &position);

  // Measures positions that are entangled with all positions in list.
  void
  measureIfEntangledWithAllPositionsInList(std::list<QuantumPosition *> &list);

  // Deletes all entanglements of position.
  void deleteEntanglementsOf(const QuantumPosition &position);

  // Deletes all entanglements between two chessman, starting from iterator
  // from.
  void
  deleteEntanglementsOfWith(std::list<Entanglement>::iterator from,
                            const Chessman &chessman1,
                            const Chessman &chessman2);

  // Returns true if chessmen are entangled.
  bool areEntangled(const Chessman &chessman1, const Chessman &chessman2);

  // Loads positions list with all chessmen entangled with chessman.
  void getEntangledOf(const Chessman &chessman,
                      std::list<const Chessman *> &positions);
};


#endif //QUANTUM_CHESS_PROJ_ENTANGLEMENT_LOG_H
