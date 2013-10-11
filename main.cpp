#include "GameHandler.h"

MouseHandler * mh;
GameHandler * gm;
ObjectsLauncher * launcher;


void displayFn(){
    glClear(GL_COLOR_BUFFER_BIT);
    mh->dibujar();
    gm->run();
    glutSwapBuffers();
    glFlush();
}

void MiReshapeFunc(GLsizei w, GLsizei h){
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, WIN_ANCHO, 0, WIN_ALTO);

}

void passive_mouseFunc(int x, int y){
    mh->setDrawer(false);
}

void motion_mouseFunc(int x, int y){
    mh->addClick(x, y);
    mh->setDrawer(true);
}

void Init(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glEnable(GL_FLAT);
    // glEnable(GL_SMOOTH);
    //glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char ** argv){
    srand (time(NULL));
    // o.set(200);
    mh = new MouseHandler();
    gm = new GameHandler();
    launcher = new ObjectsLauncher();
    // launcher->set_max(5);
    // launcher->create_objects();
    gm->set(mh, launcher);
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
}