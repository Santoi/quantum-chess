#include "sound_handler.h"
#include <mutex>
#include <utility>

#define NUMBER_OF_DIFFERENT_CHUNKS 5

SoundHandler::SoundHandler(SDL2pp::Mixer &mixer)
        : mixer(mixer), music("sound/music.mp3"), mutex(),
          playing_music(false), playing_sounds(true) {
  chunks.reserve(NUMBER_OF_DIFFERENT_CHUNKS);
  chunks.push_back(SDL2pp::Chunk("sound/split.wav"));
  chunks.push_back(SDL2pp::Chunk("sound/merge.wav"));
  chunks.push_back(SDL2pp::Chunk("sound/capture.wav"));
}

void SoundHandler::toggleMusic() {
  if (playing_music)
    stopMusic();
  else
    playMusic();
  playing_music = !playing_music;
}

void SoundHandler::playMusic() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  mixer.PlayMusic(music);
}

void SoundHandler::stopMusic() {
  mixer.PauseMusic();
}

void SoundHandler::toggleSounds() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  playing_sounds = !playing_sounds;
}

void SoundHandler::playSplitSound() const {
  if (playing_sounds)
    mixer.PlayChannel(-1, chunks[0]);
}

void SoundHandler::playMergeSound() const {
  if (playing_sounds)
    mixer.PlayChannel(-1, chunks[1]);
}

void SoundHandler::playCaptureSound() const {
  if (playing_sounds)
    mixer.PlayChannel(-1, chunks[2]);
}


