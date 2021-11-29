#ifndef QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
#define QUANTUM_CHESS_PROJ_SOUNDHANDLER_H

#include <SDL2pp/Mixer.hh>
#include <vector>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Music.hh>

class SoundHandler {
private:
  SDL2pp::Mixer &mixer;
  SDL2pp::Music music;
  std::vector<SDL2pp::Chunk> chunks;

public:
  SoundHandler() = delete;

  explicit SoundHandler(SDL2pp::Mixer &mixer);

  void playMusic() const;

  void stopMusic() const;

  void playSplitSound() const;

  void playMergeSound() const;

  void playCaptureSound() const;

  void playNewClientSound() const;

};


#endif //QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
