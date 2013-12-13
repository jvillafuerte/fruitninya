#include <iostream>
using namespace std;

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"


#define SDL_USE_NIB_FILE 1

void Inicia_SDL_mixer();

void Cierra_SDL_mixer();

class c_sonido {
  public:
    c_sonido( const char *nombre_archivo, int canal, Uint8 volumen );
    ~c_sonido( void ) { Mix_FreeChunk( tmp_chunk ); };
    void reproduce( void ) { Mix_HaltChannel( tmp_canal ); Mix_PlayChannel( tmp_canal, tmp_chunk, 0 ); };
    void para( void )    { Mix_HaltChannel( tmp_canal ); };
    void pausa( void )   { if( Mix_Playing( tmp_canal ) == 1 ) Mix_Pause(  tmp_canal ); };
    void reanuda( void ) { if( Mix_Paused(  tmp_canal ) == 1 ) Mix_Resume( tmp_canal ); };
    void volumen( Uint8 volumen ) { Mix_VolumeChunk( tmp_chunk, volumen ); };
  private:
    int tmp_canal;
    Mix_Chunk *tmp_chunk;
};

class c_musica {
  public:
    Mix_Chunk *sound;
    c_musica( const char *nombre_archivo );
    c_musica(const c_musica * wa){
        sound = wa->sound;
    }
    ~c_musica( void ) {   Mix_FreeChunk( sound ); };
    void reproduce() { 
        Mix_PlayChannel(-1, sound, 0); 
    };
    void para( void ) { Mix_HaltMusic(); };
    void pausa( void )   { if( Mix_PlayingMusic() == 1 ) Mix_PauseMusic();  };
    void reanuda( void ) { if( Mix_PausedMusic()  == 1 ) Mix_ResumeMusic(); };
    void inico( void )   { Mix_RewindMusic(); };
    void volumen( Uint8 volumen ) { Mix_VolumeMusic( volumen ); };
 
};

