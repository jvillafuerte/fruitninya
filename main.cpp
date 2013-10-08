#include "constantes.h"
#include "launcher.h"
lanzar o;
int i=0;
GLfloat angRotac=0;


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

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    if(o.objects[i].centro->y<0){
        i++;
    }
        
        glPushMatrix();
        glTranslatef(o.objects[i].centro->x,o.objects[i].centro->y,0);
        glRotated(angRotac,0,0,1);
        glTranslatef(-o.objects[i].centro->x,-o.objects[i].centro->y,0);  
        o.objects[i].dibujar();
        o.objects[i].mover();

        glPopMatrix();
        glutSwapBuffers();
        glFlush();
        angRotac+=1;  
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
    o.set(200);
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