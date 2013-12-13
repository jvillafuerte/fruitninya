#include "Texture.h"

//Declaro punteros a todas las estructuras
MouseHandler * mh;
GameHandler * gm;
ObjectsLauncher * launcher;
Texto * tex;

GLuint texture;

int ANGULO = 10;

GLint LoadGLTexture(const char *filename, int width, int height)
{
 GLuint texture;
 unsigned char *data;
 FILE *file;
 file = fopen(filename,"r");
 if (file == NULL) return 0;
 
 data = (unsigned char*) malloc(width * height * 3);
 fread(data, width * height * 3, 1, file);
 fclose(file);


    glGenTextures(1, &texture); // allocate a texture name
    glBindTexture(GL_TEXTURE_2D, texture); // select our current texture
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when texture area is large, bilinear filter the first mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); // build our texture mipmaps
    free(data); // free buffer

    return texture;
  }



//Manda a dibujar el recorrido del mouse y se ejecuta la funcion principal "GameHandler"
  void displayFn(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mh->dibujar();
    gm->run();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture );

    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,MIN_Z+20);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(WIN_ANCHO,0,MIN_Z+20);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(WIN_ANCHO,WIN_ALTO,MIN_Z+20);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,WIN_ALTO,MIN_Z+20);
    glEnd();
    glDisable(GL_TEXTURE_2D); 

    glutSwapBuffers();
  }

  void MiReshapeFunc(GLsizei w, GLsizei h){
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIN_ANCHO, 0, WIN_ALTO, MIN_Z, MAX_Z);

    GLfloat ambientLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = {WIN_ANCHO/2, WIN_ALTO/2, 600.0f, 1.0f };

    // Asignando componentes a la luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
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

  static void idle(void){
    glutPostRedisplay();
  }

  int main(int argc, char *argv[]){
   srand (time(NULL));
    //Se inicializa a los punteros y se agregan al controlador del Juego (gamehandler)    
   tex = new Texto();
   launcher = new ObjectsLauncher();
   mh = new MouseHandler();
   gm = new GameHandler(); gm->set(mh, launcher, tex);

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

   texture = LoadGLTexture("texturas/madera2.bmp", 480, 480);
    #ifndef __APPLE__
   Inicia_SDL_mixer(); 
   c_musica *musica = new c_musica( "Sonidos/fondo.wav");
   musica->reproduce();
    #endif

   Init();
   glutMainLoop();
   return 0;   
 }