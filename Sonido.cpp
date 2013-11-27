//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programaci�n) www.scenebeta.com          --
//-- FECHA �LTIMA MODIFICACI�N: 31/03/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  c�digo  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en �l. Sin el  m�s --
//-- m�nimo �nimo de lucro, siempre por la satisfacci�n del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  da�o  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  �nimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este c�digo que colabore en su mejora--
//-- y perfeccionamiento poni�ndomelo en conocimiento por correo electr�nico. --
//------------------------------------------------------------------------------

#include "Sonido.h"

// ---------------------------------------------------------------------------
// Inicializamos SDL_mixer ---------------------------------------------------
// ---------------------------------------------------------------------------
// int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
//
// freq: La frecuencia (en Hertzios) de reproducci�n del sample. Valores habituales son:
//       11025 (calidad telef�nica), 22050 (calidad radiof�nica) o 44100 (calidad CD).   
// format:  
//   AUDIO_U8 Sample de 8 bits sin signo
//   AUDIO_S8 Sample de 8 bits con signo
//   AUDIO_U16 o AUDIO_U16LSB Sample de 16 bits sin signo en formato little-endian.
//   AUDIO_S16 o AUDIO_S16LSB Sample de 16 bits con signo en formato little-endian.
//   AUDIO_U16MSB Sample de 16 bits sin signo en formato big-endian.
//   AUDIO_S16MSB Sample de 16 bits con signo en formato big-endian.
//   AUDIO_U16SYS AUDIO_U16LSB o
//   AUDIO_U16MSB dependiendo del peso de tu sistema (big o little end�an)
//   AUDIO_S16SYS AUDIO_S16LSB o
//   AUDIO_S16MSB dependiendo del peso de tu sistema (big o little end�an)
// channels:  N�mero de canales de audio. Pueden ser 1 para mono y 2 para estereo.   
// chunksize: El valor habitual es 4096 seg�n la documentaci�n oficial de SDL.
// Ejemplo:   Mix_OpenAudio( 22050, AUDIO_S16, 2, 4096)
// int Mix_AllocateChannels(int numchannels)
//   Lo normal es que le pasemos tantos canales como sonidos simult�neos queramos
//   poder reproducir. Te aconsejo que no te quedes corto. Por otro lado, mientras m�s
//   canales, m�s recursos requer�ra el audio.
// --------------------------------------------------------------------------- 
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

//------------------------------------------------------------------------------
//-- CERRAR MIX_AUDIO ----------------------------------------------------------
//------------------------------------------------------------------------------
void Cierra_SDL_mixer() {
  Mix_CloseAudio();   // Cerrar Mix_Audio
}

// -----------------------------------------------------------------------------
// -- Carga un Sonido  ---------------------------------------------------------
// -----------------------------------------------------------------------------
// Mix_Chunk *Mix_LoadWAV(char *file)                     // Carga un Sonido
// void Mix_FreeChunk( Mix_Chunk *chunk)                  // Borra un Sonido
// int Mix_VolumeChunk( Mix_Chunk *chunk, int volume )    // Volumen rango de 0 a 128.
//     int loop -> Reproduce una vez loops = 0; Reproduce infinito loops = -1
//     int channel -> -1 Asigna canal autom�ticamente.
// int Mix_PlayChannel( int channel, Mix_Chunk *chunk, int loops )
// int Mix_PlayChannelTimed( int channel, Mix_Chunk *chunk, int loops, int ticks)
// int Mix_FadeInChannel( int channel, Mix_Chunk *chunk, int loops, int ms)
// int Mix_FadeInChannelTimed( int channel, Mix_Chunk *chunk, int loops, int ms, int ticks)
// void Mix_Pause( int channel )
// void Mix_Resume( int channel )
// int Mix_HaltChannel( int channel )
// int Mix_FadeOutChannel( int channel, int ms ) 
// int Mix_Playing( int channel )  // Si est� sonando 1, 0 si no.
// int Mix_Paused( int channel )   // Si est� pausada 0, 1 si est� sonando.
// -----------------------------------------------------------------------------
c_sonido::c_sonido(  const char *nombre_archivo, int canal, Uint8 volumen  ) {
  tmp_canal = canal;
  tmp_chunk = Mix_LoadWAV( nombre_archivo );
  if ( tmp_chunk == NULL ) {
    cerr << "No pude cargar sonido: " << nombre_archivo << " -> " << Mix_GetError() << endl;
    exit(1);
  }
  Mix_VolumeChunk( tmp_chunk, volumen ); // De 0 a 128
}

// -----------------------------------------------------------------------------
// Carga una M�sica ------------------------------------------------------------
// -----------------------------------------------------------------------------
// Mix_Music *Mix_LoadMUS( const char *file )
// void Mix_FreeMusic( Mix_Music )
// int Mix_PlayMusic( Mix_Music *music, int loops )
// int Mix_FadeInMusic( Mix_Music *music, int loops, int ms )
// int Mix_VolumeMusic( int volume )
// void Mix_PauseMusic()
// void Mix_ResumeMusic()
// int Mix_HaltMusic()
// int Mix_FadeOutMusic(int ms)
// Int Mix_PlayingMusic()
// Int Mix_PausedMusic()
// void Mix_RewindMusic() // Su misis�n es volver la reproducci�n de la m�sica al principio.
// int Mix_SetMusicPosition( double position )  
//     La funci�n nos permite situar la posici�n de reproducci�n en el lugar
//     deseado. La posici�n depender� directamente del formato del archivo de m�sica,
//     pudiendo ser el tiempo en milisegundo para archivos de m�sica digitalizada o la posici�n
//     del patr�n o el comp�s si es un archivo MOD o MIDI.
// Mix_MusicType Mix_GetMusicType(const Mix_Music *music)
//     Mix_MusicType puede tomar los siguientes valores: 
//       MUS_WAV,
//       MUS_MOD
//       MUS_MID 
//       MUS_OGG 
//       MUS_MP3  Si el valor devuelto es 
//       MUS_NONE significa que no hay ninguna m�sica en reproducci�n. 
//       MUS_CMD  significa que la reproducci�n la est� llevando un reproductor externo.   
// -----------------------------------------------------------------------------
c_musica::c_musica( const char *nombre_archivo ) {       
  sound = Mix_LoadWAV(nombre_archivo);
  
}   
