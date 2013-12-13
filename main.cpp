
#include "Texture.h"


// GLMmodel* pmodel = NULL;

//#include "SOIL.h"

//Declaro punteros a todas las estructuras
MouseHandler * mh;
GameHandler * gm;
ObjectsLauncher * launcher;
Texto * tex;
texture * textu;

int ANGULO = 10;

//Manda a dibujar el recorrido del mouse y se ejecuta la funcion principal "GameHandler"
void displayFn(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_pos[] = { WIN_ANCHO/2, WIN_ALTO/2, 0.0, 1.0 };
    //GLfloat light_pos_top[] = { WIN_ANCHO/2, WIN_ALTO, 10.0, 1.0 };
    GLfloat color[] = {1.0f, 1.0f, 1.0f, 0.5f};
    //GLfloat color2[] = {1.0f, 1.0f, 1.0f, 0.5f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    //lLightfv(GL_LIGHT1, GL_POSITION, light_pos_top);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

    //glLightfv(GL_LIGHT1, GL_AMBIENT, color2);


    

    //glColor3f(0.5,0.5,0.5);

    mh->dibujar();
    gm->run();
    textu->run();

    // glPushMatrix();

    // if (!pmodel) {
    //     pmodel = glmReadOBJ("models/apple/apples.obj");
    //     if (!pmodel) exit(0);
    //     glmUnitize(pmodel);
    //     glmFacetNormals(pmodel);
    //     glmVertexNormals(pmodel, 90.0);
    //     glmScale(pmodel, 50);
    // }
    

 // glRotatef( ((ANGULO / 3.14) * 180.0f),0.0,0.0,1.0); // inclinagira a los lados 
 // // glTranslatef(centro_->x_,centro_->y_, centro_->z_); 
 // // glTranslatef( -centro_->x_, -centro_->y_, -centro_->z_); 
 // glEnable(GL_TEXTURE_2D); 
 // // glmDraw(modelo_,GLM_SMOOTH | GLM_TEXTURE); 
 // glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL); 
 // glDisable(GL_TEXTURE_2D); 
 // glLoadIdentity(); 
 // glPopMatrix();



 //    glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);

    glutSwapBuffers();
    // glFlush();
}

void MiReshapeFunc(GLsizei w, GLsizei h){
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D (0, WIN_ANCHO, 0, WIN_ALTO);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // if (mode == PERSPECTIVE)
    //     gluPerspective(perspective[0].value, perspective[1].value, 
    //     perspective[2].value, perspective[3].value);
    // else if (mode == ORTHO)
    // glOrtho(-100.0, WIN_ANCHO, -100.0, WIN_ALTO, -10.0, 10.0);

    glOrtho(0, WIN_ANCHO, 0, WIN_ALTO, -500.0, 500.0);


    // else if (mode == FRUSTUM)
    //     glFrustum(frustum[0].value, frustum[1].value, frustum[2].value,
    //     frustum[3].value, frustum[4].value, frustum[5].value);
    // glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    // glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    // glClearColor(0.2, 0.2, 0.2, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


}

//Cuando se mueve el mouse sin hacer click
void passive_mouseFunc(int x, int y){
    mh->setDrawer(false);
}

//Cuando se mueve el mouse en la pantalla con el click presionado
void motion_mouseFunc(int x, int y){
    mh->addClick(x, y);
    mh->setDrawer(true);
    ANGULO+=10;
}

void Init(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

static void idle(void){
    glutPostRedisplay();
}

int main(int argc, char *argv[]){
   srand (time(NULL));

    //Se inicializa a los punteros y se agregan al controlador del Juego (gamehandler)    
   tex = new Texto();
   launcher = new ObjectsLauncher();
   mh = new MouseHandler();
   gm = new GameHandler();
   gm->set(mh, launcher, tex);
   textu = new texture("madera2.bmp", 480, 480);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(WIN_ANCHO, WIN_ALTO);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Fruit Ninja");
   glutDisplayFunc(displayFn);   
   glutReshapeFunc(MiReshapeFunc);
   glutIdleFunc(idle);
   glutMotionFunc(motion_mouseFunc);
   glutPassiveMotionFunc(passive_mouseFunc);
   //texture = LoadGLTexture("descarga3.bmp", 480, 480);
   ////////////////
    #ifndef __APPLE__
    Inicia_SDL_mixer(); 
    c_musica *musica = new c_musica( "Sonidos/fondo.wav");
    musica->reproduce();
    #endif
    //Mix_AllocateChannels(2);
    //choque    = new c_sonido( "Sonidos/DigitalStream.wav", 100, 128 );
    //explosion = new c_sonido( "Sonidos/Explosion.wav", 1, 128 );

    // Mix_Chunk *sound = Mix_LoadWAV("Sonidos/DigitalStream.wav");
//Mix_PlayChannel(-1, sound, 0);

    ///////////////////7
    //Llamada a las funciones de OpenGl

     ///////////////////////

    // for (int i = 0; i < 10000; ++i)
    // {
    //     if(i==5000)
    //         musica->para();
    // }
    //choque->reproduce();    delete choque;
    //explosion->para(); delete explosion;
    // musica->para();    delete musica;
////////////////////////////
   Init();
   glutMainLoop();
   return 0;   
}