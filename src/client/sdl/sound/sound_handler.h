#ifndef QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
#define QUANTUM_CHESS_PROJ_SOUNDHANDLER_H

#include <SDL2pp/Mixer.hh>
#include <vector>
#include <SDL2pp/Chunk.hh>


class SoundHandler {
private:
    SDL2pp::Mixer& mixer;
    std::vector<SDL2pp::Chunk> chunks;

public:
    SoundHandler() = delete;

    explicit SoundHandler(SDL2pp::Mixer& mixer);

    void playSplitSound();

    void playMovementSound();

    void playTakenPieceSound();

    void playNewClientSound();

};



#endif //QUANTUM_CHESS_PROJ_SOUNDHANDLER_H
