#ifndef QUANTUM_CHESS_PROJ_ENTANGLEMENT_LOG_H
#define QUANTUM_CHESS_PROJ_ENTANGLEMENT_LOG_H

#include "../quantum_position.h"

class EntanglementLog {
  class Entanglement {
  private:
    QuantumPosition &first;
    QuantumPosition &second;

    friend EntanglementLog;

  public:
    Entanglement(QuantumPosition &pos1_, QuantumPosition &pos2_);

    bool operator==(const QuantumPosition &pos);

    QuantumPosition &getOther(const QuantumPosition &pos);
  };

  std::list<Entanglement> log;

public:
  EntanglementLog() = default;

  void
  add(QuantumPosition &pos1, QuantumPosition &pos2);


  void addEntanglementsOfTo(const QuantumPosition &search,
                            QuantumPosition &add);

  std::list<EntanglementLog::Entanglement>::iterator
  find(const QuantumPosition &pos1, const QuantumPosition &pos2);

  void deleteEntanglementsWhichAreNotSharedBy(const QuantumPosition &pos1,
                                              const QuantumPosition &pos2);

  bool chessmanIsEntangledMoreThanOnceWithPosition(const Chessman &chessman,
                                                   const QuantumPosition &position);

  void
  measureEntanglements(const Chessman &chessman,
                       const QuantumPosition &position);

  void measureIfEntangledWithAllPositionsInList(
          std::list<QuantumPosition *> &list);

  void deleteEntanglementsOf(const QuantumPosition &position);

  void
  deleteEntanglementsOfWith(std::list<Entanglement>::iterator from,
                            const Chessman &chessman1,
                            const Chessman &chessman2);

  bool areEntangled(const Chessman &chessman1, const Chessman &chessman2);

  void getEntangledOf(const Chessman &chessman,
                      std::list<const Chessman *> &positions);
};


#endif //QUANTUM_CHESS_PROJ_ENTANGLEMENT_LOG_H
