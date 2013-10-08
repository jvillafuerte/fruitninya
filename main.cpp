#include "Object.h"
#include "constantes.h"

Objeto o;

void dibujar(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(20.0, 20.0);
    glVertex2f(37.32, 30);
    glVertex2f(27.32, 47.32);
    glVertex2f(10, 37.32);
    glEnd();
    glPointSize(3);
    // Se pinta de amarillo el punto B para poder ver la transformacion
    glBegin(GL_POINTS);
        glColor3f(1.0,1.0,0.0);
        glVertex2f(37.32, 30);
    glEnd();
}

void eje(){
    // se dibuja el eje carteciano para poder guiarnos en las transformaciones
    glBegin(GL_LINES);
        glPointSize(3);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.0f,-50.0f);
        glVertex2f(0.0f,50.0f);
        glVertex2f(50.0f,0.0f);
        glVertex2f(-50.0f,0.0f);
    glEnd();
}

void displayFn(){
    glClear(GL_COLOR_BUFFER_BIT);
    o.dibujar();
    o.mover();
    glFlush();
}

void MiReshapeFunc(GLsizei w, GLsizei h){
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, WIN_ANCHO, 0, WIN_ALTO);
   
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
    o.set(5,5,10,60,50);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_ANCHO, WIN_ALTO);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Fruit Ninja");
    glutDisplayFunc(displayFn);
    glutReshapeFunc(MiReshapeFunc);
    glutIdleFunc(idle);
    Init();
    glutMainLoop();
}