#ifndef QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
#define QUANTUM_CHESS_PROJ_SOUNDHANDLER_H

#include <SDL2pp/Mixer.hh>
#include <vector>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Music.hh>
#include <mutex>

class SoundHandler {
private:
  SDL2pp::Mixer &mixer;
  SDL2pp::Music music;
  std::vector<SDL2pp::Chunk> chunks;
  std::mutex mutex;
  bool playing_music;
  bool playing_sounds;
  bool music_started;

public:
  SoundHandler() = delete;

  explicit SoundHandler(SDL2pp::Mixer &mixer);

  void playMusic();

  void pauseMusic();

  void playSplitSound() const;

  void playMergeSound() const;

  void playCaptureSound() const;

  void toggleMusic();

  void toggleSounds();

  void resumeMusic();

  void stopMusic();
};


#endif //QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
