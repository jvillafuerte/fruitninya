#include "GameHandler.h"


//Declaro punteros a todas las estructuras
MouseHandler * mh;
GameHandler * gm;
ObjectsLauncher * launcher;
Texto * tex;

c_sonido *choque;      // -- Sonidos --
c_sonido *explosion;


//Manda a dibujar el recorrido del mouse y se ejecuta la funcion principal "GameHandler"
void displayFn(){
    glClear(GL_COLOR_BUFFER_BIT);
    mh->dibujar();     
    gm->run();
    glutSwapBuffers();
   // glFlush();
}


void MiReshapeFunc(GLsizei w, GLsizei h){
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, WIN_ANCHO, 0, WIN_ALTO);

}


//Cuando se mueve el mouse sin hacer click
void passive_mouseFunc(int x, int y){
    mh->setDrawer(false);
}

//Cuando se mueve el mouse en la pantalla con el click presionado
void motion_mouseFunc(int x, int y){
    mh->addClick(x, y);
    mh->setDrawer(true);
}


void Init(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

static void idle(void)
{
    glutPostRedisplay();
}



int main(int argc, char ** argv){
    srand (time(NULL));

    //Se inicializa a los punteros y se agregan al controlador del Juego (gamehandler)    
    tex = new Texto();
    launcher = new ObjectsLauncher();
    mh = new MouseHandler();
    gm = new GameHandler();
    gm->set(mh, launcher, tex);
    ///////////////////7
    Inicia_SDL_mixer(); 
    //Mix_AllocateChannels(2);
    //choque    = new c_sonido( "Sonidos/DigitalStream.wav", 100, 128 );
    //explosion = new c_sonido( "Sonidos/Explosion.wav", 1, 128 );

    // Mix_Chunk *sound = Mix_LoadWAV("Sonidos/DigitalStream.wav");
//Mix_PlayChannel(-1, sound, 0);

    c_musica *musica = new c_musica( "Sonidos/fondo.wav");
    ///////////////////7
    //Llamada a las funciones de OpenGl

     ///////////////////////
    musica->reproduce();

    // for (int i = 0; i < 10000; ++i)
    // {
    //     if(i==5000)
    //         musica->para();
    // }
    //choque->reproduce();    delete choque;
    //explosion->para(); delete explosion;
    // musica->para();    delete musica;
    
    ///////////////////////////////7777
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_ANCHO, WIN_ALTO);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Fruit Ninja");
    glutDisplayFunc(displayFn);   
    glutReshapeFunc(MiReshapeFunc);
    glutIdleFunc(idle);
    glutMotionFunc(motion_mouseFunc);
    glutPassiveMotionFunc(passive_mouseFunc);
    Init();
    glutMainLoop();
    Cierra_SDL_mixer(); 
   
}