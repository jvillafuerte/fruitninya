#include "Sonido.h"

void Inicia_SDL_mixer() {
 if( SDL_Init(SDL_INIT_AUDIO) < 0) {
   cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
   exit(1);
 }
 atexit(SDL_Quit);

 if ( Mix_OpenAudio( 22050, AUDIO_S16, 2, 4096) < 0 ) {
   cerr << "No se puede inicializar SDL_mixer: " << Mix_GetError() << endl;
   exit(1);
 }
 atexit( Mix_CloseAudio );  
 Mix_Volume( -1,  64 ); // De 0 a 128.
 Mix_VolumeMusic( 64 ); // De 0 a 128.
}

void Cierra_SDL_mixer() {
  Mix_CloseAudio();   // Cerrar Mix_Audio
}

c_sonido::c_sonido(  const char *nombre_archivo, int canal, Uint8 volumen  ) {
  tmp_canal = canal;
  tmp_chunk = Mix_LoadWAV( nombre_archivo );
  if ( tmp_chunk == NULL ) {
    cerr << "No pude cargar sonido: " << nombre_archivo << " -> " << Mix_GetError() << endl;
    exit(1);
  }
  Mix_VolumeChunk( tmp_chunk, volumen ); // De 0 a 128
}

c_musica::c_musica( const char *nombre_archivo ) {       
  sound = Mix_LoadWAV(nombre_archivo);
  
}   
