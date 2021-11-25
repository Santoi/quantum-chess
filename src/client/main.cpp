#include "client.h"
#include "main_drawer.h"
#include "sdl/chat/text_entry.h"
#include "sdl/chat/font.h"
#include "sdl/event_handler.h"
#include <iostream>

#define SUCCESS 0
#define FONT_SIZE 240

int main(int argc, char *argv[]) {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);
  SDL2pp::SDLTTF ttf;
  Window window;
  Renderer renderer(window);
  Font font("fonts/font.ttf", FONT_SIZE);
  TextEntry text(renderer, font);
  EventHandler event_handler;
  while (event_handler.writeMessage(renderer, text)) {}
  return 0;
//  return main_drawer();
  bool single_threaded_client = false;
  if (argc == 4)
    single_threaded_client = true;
  try {
    Client client;
    client.execute(argv[1], argv[2], single_threaded_client);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return SUCCESS;
}