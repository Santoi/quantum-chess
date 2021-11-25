#include "sound_handler.h"

#define NUMBER_OF_DIFFERENT_CHUNKS 5

SoundHandler::SoundHandler(SDL2pp::Mixer &mixer)
    : mixer(mixer), music("sound/music.wav") {
  chunks.reserve(NUMBER_OF_DIFFERENT_CHUNKS);
  chunks.push_back(std::move(SDL2pp::Chunk("sound/low.wav")));
  chunks.push_back(std::move(SDL2pp::Chunk("sound/high.wav")));
  chunks.push_back(std::move(SDL2pp::Chunk("sound/medium.wav")));
  chunks.push_back(std::move(SDL2pp::Chunk("sound/beat.wav")));
}

void SoundHandler::playMusic() const {
  mixer.PlayMusic(music);
}

void SoundHandler::stopMusic() const {
  mixer.PauseMusic();
}

void SoundHandler::playSplitSound() const {
  mixer.PlayChannel(-1, chunks[0]);
}

void SoundHandler::playMovementSound() const {
  mixer.PlayChannel(-1, chunks[1]);
}

void SoundHandler::playTakenPieceSound() const {
  mixer.PlayChannel(-1, chunks[2]);
}

void SoundHandler::playNewClientSound() const {

}


