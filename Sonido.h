//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programación) www.scenebeta.com          --
//-- FECHA ÚLTIMA MODIFICACIÓN: 07/04/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  código  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en él. Sin el  más --
//-- mínimo ánimo de lucro, siempre por la satisfacción del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  daño  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  ánimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este código que colabore en su mejora--
//-- y perfeccionamiento poniéndomelo en conocimiento por correo electrónico. --
//------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -- Sonido -------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
// #include "../Includes/Sonido.h" 
//
// Inicia_SDL_mixer();
//
// Mix_AllocateChannels(1);
// c_sonido *sonido_1 = new c_sonido( "Sonido_1.wav", 0, 64 );
// c_sonido *sonido_2 = new c_sonido( "Sonido_2.wav", 1, 64 );
// sonido_1->reproduce();
// sonido_2->reproduce();
//
// c_musica *musica = new c_musica( "Musica.mid", 64 );
// musica->reproduce();
//
// delete sonido_1;
// delete sonido_2;
// delete musica;
//
// Cierra_SDL_mixer();
//
// -----------------------------------------------------------------------------



#include <iostream>
using namespace std;

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

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

