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

  //Plays music via mixer and booleans music_started and playing_music are set to
  //true.
  void playMusic();

  //Pauses music via mixer.
  void pauseMusic();

  void playSplitSound() const;

  void playMergeSound() const;

  void playCaptureSound() const;

  //If playing_music is true, pauseMusic method is called. Else if music_started is false,
  //playMusic method is called, or else resumeMusic method is called.
  //For all cases, playing_music is set to be !playing_music.
  void toggleMusic();

  //playing_sounds is set to be !playing_sounds.
  void toggleSounds();

  //Resumes music via mixer.
  void resumeMusic();

  //Stops music via mixer and booleans music_started and playing_music are set to
  //false.
  void stopMusic();
};


#endif //QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
