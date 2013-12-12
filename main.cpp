#include "GameHandler.h"
//#include "SOIL.h"

//Declaro punteros a todas las estructuras
MouseHandler * mh;
GameHandler * gm;
ObjectsLauncher * launcher;
Texto * tex;

typedef char BYTE;

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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when texture area is large, bilinear filter the first mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); // build our texture mipmaps
    free(data);  // free buffer
 
    return texture;
}

GLuint LoadTextureRAW( const char * filename, int wrap )
{
    GLuint texture;
    int width, height;
    unsigned char  * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "r" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = WIN_ANCHO;
    height = WIN_ALTO;

    data = (unsigned char*) malloc(width * height * 4);

    // read texture data
    fread( data, width * height * 4, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

/*
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
  
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
*/
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

    free( data );

    return texture;
}

//Manda a dibujar el recorrido del mouse y se ejecuta la funcion principal "GameHandler"
void displayFn(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_pos[] = { 10.0, 10.0, 10.0, 0.0 };
    GLfloat color[] = {0.0f, 1.0f, 0.0f, 0.2f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);
    //glColor3f(0.5,0.5,0.5);
    mh->dibujar();
    gm->run();

    /****/  
    //GLuint texture = LoadTextureRAW("ola.jpg",1);
    GLuint texture = LoadGLTexture("descarga3.jpg", 284,177);
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture );
   
    glBegin(GL_QUADS);
            glColor3f(0, 0, 1);
                
            glTexCoord2f(0.0f, 0.0f); 
            glVertex3f(0,0,0);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(WIN_ANCHO,0,0);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(WIN_ANCHO,WIN_ALTO,0);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(0,WIN_ALTO,0);
            
        /*
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 100, 0,  0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 100,  100,  0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 0,  100,  0.0f);*/
    glEnd();
    glDisable(GL_TEXTURE_2D); 

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
    glOrtho(0.0, WIN_ANCHO, 0.0, WIN_ALTO, -10.0, 10.0);

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
   gm = new GameHandler();
   gm->set(mh, launcher, tex);
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
   Init();
   glutMainLoop();
   return 0;   
}