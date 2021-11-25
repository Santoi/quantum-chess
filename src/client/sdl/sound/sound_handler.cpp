#include "sound_handler.h"

#define NUMBER_OF_DIFFERENT_CHUNKS 5

SoundHandler::SoundHandler(SDL2pp::Mixer& mixer)
            :mixer(mixer), music("21_sound_effects_and_music/music.wav") {
    chunks.reserve(NUMBER_OF_DIFFERENT_CHUNKS);
    chunks.push_back(std::move(SDL2pp::Chunk("21_sound_effects_and_music/low.wav")));
    chunks.push_back(std::move(SDL2pp::Chunk("21_sound_effects_and_music/high.wav")));
    chunks.push_back(std::move(SDL2pp::Chunk("21_sound_effects_and_music/medium.wav")));
    chunks.push_back(std::move(SDL2pp::Chunk("21_sound_effects_and_music/beat.wav")));
}

void SoundHandler::playMusic() {
    mixer.PlayMusic(music);
}

void SoundHandler::stopMusic() {
    mixer.PauseMusic();
}

void SoundHandler::playSplitSound() {
    mixer.PlayChannel(-1, chunks[0]);
}

void SoundHandler::playMovementSound() {
    mixer.PlayChannel(-1, chunks[1]);
}

void SoundHandler::playTakenPieceSound() {
    mixer.PlayChannel(-1, chunks[2]);
}

void SoundHandler::playNewClientSound() {

}


