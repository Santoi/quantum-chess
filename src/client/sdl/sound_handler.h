#ifndef QUANTUM_CHESS_PROJ_SOUND_HANDLER_H
#define QUANTUM_CHESS_PROJ_SOUND_HANDLER_H

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

  // Start music player
  void playMusic();

  // Pause music player
  void pauseMusic();

  //Resumes music via mixer.
  void resumeMusic();

  void toggleMusic();

  void playSplitSound() const;

  void playMergeSound() const;

  void playCaptureSound() const;

  void toggleSounds();
};


#endif //QUANTUM_CHESS_PROJ_SOUND_HANDLER_H
