#include "sound_handler.h"
#include <mutex>
#include <utility>

#define NUMBER_OF_DIFFERENT_CHUNKS 5

#define PATH "resources/sounds/"

SoundHandler::SoundHandler(SDL2pp::Mixer &mixer)
    : mixer(mixer), music(PATH "music.mp3"), mutex(),
      playing_music(false), playing_sounds(true), music_started(false) {
  chunks.reserve(NUMBER_OF_DIFFERENT_CHUNKS);
  chunks.emplace_back(SDL2pp::Chunk(PATH "split.wav"));
  chunks.emplace_back(SDL2pp::Chunk(PATH "merge.wav"));
  chunks.emplace_back(SDL2pp::Chunk(PATH "capture.wav"));
}

void SoundHandler::toggleMusic() {
  if (playing_music)
    pauseMusic();
  else if (!music_started)
    playMusic();
  else
    resumeMusic();
  playing_music = !playing_music;
}

void SoundHandler::playMusic() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  mixer.PlayMusic(music);
  music_started = true;
  playing_music = true;
}

void SoundHandler::stopMusic() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  mixer.PauseMusic();
  music_started = false;
  playing_music = false;
}

void SoundHandler::resumeMusic() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  mixer.ResumeMusic();
}

void SoundHandler::pauseMusic() {
  std::lock_guard<std::mutex> lock_guard(mutex);
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


