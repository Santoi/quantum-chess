#include "entanglement_log.h"
#include <algorithm>
#include <map>


void EntanglementLog::add(QuantumPosition &pos1,
                          QuantumPosition &pos2) {
  log.emplace_back(pos1, pos2);
}

void EntanglementLog::addEntanglementsOfTo(const QuantumPosition &search,
                                           QuantumPosition &add) {
  for (auto &entanglement: log) {
    if (entanglement.first == search)
      log.emplace_back(add, entanglement.second);
    else if (entanglement.second == search)
      log.emplace_back(entanglement.first, add);
  }
}

void
EntanglementLog::deleteEntanglementsOf(const QuantumPosition &position) {
  for (auto it = log.begin(); it != log.end();) {
    if (*it == position)
      it = log.erase(it);
    else
      ++it;
  }
}

void
EntanglementLog::deleteEntanglementsOfWith(
        std::list<Entanglement>::iterator from, const Chessman &chessman1,
        const Chessman &chessman2) {
  for (auto it = from; it != log.end();) {
    if ((it->first.isMyChessman(chessman1) &&
         it->second.isMyChessman(chessman2)) ||
        (it->second.isMyChessman(chessman1) &&
         it->first.isMyChessman(chessman2))) {
      it = log.erase(it);
    } else
      ++it;
  }
}

bool EntanglementLog::areEntangled(const Chessman &chessman1,
                                   const Chessman &chessman2) {
  for (auto it = log.begin(); it != log.end(); ++it) {
    if ((it->first.isMyChessman(chessman1) &&
         it->second.isMyChessman(chessman2)) ||
        (it->second.isMyChessman(chessman1) &&
         it->first.isMyChessman(chessman2)))
      return true;
  }
  return false;
}

void EntanglementLog::getEntangledOf(const Chessman &chessman,
                                     std::list<const Chessman *> &positions) {
  for (auto &entangled: log) {
    if (entangled.first.isMyChessman(chessman))
      positions.push_back(&entangled.second.getChessman());
    else if (entangled.second.isMyChessman(chessman))
      positions.push_back(&entangled.first.getChessman());
  }
}

void
EntanglementLog::deleteEntanglementsWhichAreNotSharedBy(
        const QuantumPosition &pos1,
        const QuantumPosition &pos2) {
  // First for position 1
  for (auto it = log.begin(); it != log.end();) {
    if (*it == pos1) {
      // Find entanglement of pos2 with the other position entangled in *it.
      if (find(pos2, it->getOther(pos1)) == log.end()) {
        it = log.erase(it);
        continue;
      }
    }
    ++it;
  }
  // For position 2
  for (auto it = log.begin(); it != log.end();) {
    if (*it == pos2) {
      // Find entanglement of pos1 with the other position entangled in *it.
      if (find(pos1, it->getOther(pos2)) == log.end()) {
        it = log.erase(it);
        continue;
      }
    }
    ++it;
  }
}

void EntanglementLog::measureIfEntangledWithAllPositionsInList(
        std::list<QuantumPosition *> &list) {
  size_t list_size = list.size();
  std::map<QuantumPosition *, size_t> counters;
  for (auto &entanglement: log) {
    // If first of entanglement is in list. Then increment the counter to
    // the second. If not, then check for the second.
    if (std::find(list.begin(), list.end(), &entanglement.first) !=
        list.end()) {
      if (counters.count(&entanglement.second))
        counters[&entanglement.second]++;
      else
        counters[&entanglement.second] = 1;
    } else if (std::find(list.begin(), list.end(), &entanglement.second) !=
               list.end()) {
      if (counters.count(&entanglement.second))
        counters[&entanglement.first]++;
      else
        counters[&entanglement.first] = 1;
    }
  }

  // Iterate all the find positions entangled with any position of the list.
  // Then if the counter is equal to the list size, it means that is entangled
  // with all of them, so measure it.
  for (auto it = counters.begin(); it != counters.end(); ++it) {
    if (it->second == list_size) {
      deleteEntanglementsOfWith(log.begin(), (*list.begin())->getChessman(),
                                it->first->getChessman());
      it->first->measure();
    }
  }
}

void EntanglementLog::measureEntanglements(const Chessman &chessman,
                                           const QuantumPosition &position) {
  std::list<QuantumPosition *> to_measure;
  for (auto it = log.begin(); it != log.end();) {
    if (*it == position) {
      if (!chessmanIsEntangledMoreThanOnceWithPosition(chessman, it->getOther(
              position))) {
        QuantumPosition &other = it->getOther(position);
        it = log.erase(it);
        to_measure.push_back(&other);
      } else
        it = log.erase(it);
    } else
      ++it;
  }

  // Measure at the end to not corrupt the log iterator.
  for (auto &to_meas: to_measure)
    to_meas->measure();
}

bool EntanglementLog::chessmanIsEntangledMoreThanOnceWithPosition(
        const Chessman &chessman, const QuantumPosition &position) {
  size_t counter = 0;
  for (auto entangled: log) {
    if (entangled == position &&
        entangled.getOther(position).isMyChessman(chessman))
      counter++;
    if (counter > 1)
      return true;
  }
  return false;
}

std::list<EntanglementLog::Entanglement>::iterator
EntanglementLog::find(const QuantumPosition &pos1,
                      const QuantumPosition &pos2) {
  for (auto it = log.begin(); it != log.end(); ++it) {
    if (*it == pos1 && *it == pos2)
      return it;
  }
  return log.end();
}

EntanglementLog::Entanglement::Entanglement(
        QuantumPosition &pos1_,
        QuantumPosition &pos2_) :
        first(pos1_), second(pos2_) {}

bool EntanglementLog::Entanglement::operator==(const QuantumPosition &pos) {
  return first == pos || second == pos;
}


QuantumPosition &
EntanglementLog::Entanglement::getOther(const QuantumPosition &pos) {
  if (pos == first)
    return second;
  if (pos == second)
    return first;
  throw std::runtime_error("position is not in this entanglement");
}

