#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#include <GL/glu.h>
#endif
#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <iostream>


GLfloat grave = -9.8;
class Punto
{
public:
    GLfloat x;
    GLfloat y;
    Punto(GLfloat xx, GLfloat yy){
        x=xx;
        y=yy;
    }
    Punto(Punto * p){
        x = p->x;
        y = p->y;
    }
    ~Punto(){}
};

class Objeto
{
public:
    Punto * centro;
    GLfloat tam;
    GLfloat ang;
    GLfloat vel;
    GLfloat velx;
    GLfloat vely;
    GLfloat tiempo;
    GLfloat y0;
    GLfloat x0;
    GLfloat v0;
    GLfloat v0x;

    Objeto(){
    	centro = new Punto(0, 0);
        tam=0;
        ang=0;
        vel=0;
        tiempo =0;
        velx= vel*cos(ang * PI / 180);
        vely= vel*sin(ang * PI / 180);
    }

    Objeto(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat angg, GLfloat vel_){
        centro = new Punto(xx, yy);
        tam=tamm;
        ang=angg;
        vel=vel_;
        velx= vel*cos(ang * PI / 180);
        vely= vel*sin(ang * PI / 180);

    }
    void set(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat angg, GLfloat vel_){
        centro = new Punto(xx, yy);
        tam=tamm;
        ang=angg;
        vel=vel_;
        velx= vel*cos(ang * PI / 180);
        vely= vel*sin(ang * PI / 180);
        y0=yy;
        x0=xx;
        v0x=velx;
        v0  = vely;
    }

    ~Objeto(){}
    void dibujar(){
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,0.0);;
        glVertex3f(centro->x-tam, centro->y-tam, 0);
        glVertex3f(centro->x+tam, centro->y-tam, 0);
        glVertex3f(centro->x+tam, centro->y+tam, 0);
        glVertex3f(centro->x-tam, centro->y+tam, 0);
        glEnd();
    }
    void mover(){
    	tiempo+=0.001;
        vely = v0 + grave*tiempo;
        velx = v0x;
    	centro->y = y0 + vely * tiempo+0.5*grave*tiempo*tiempo;
    	centro->x = x0 + velx * tiempo;
    }

};

// class Lanzador
// {
// public:
//     vector<Objeto> objetos;
//     Lanzador(arguments){}
//     ~Lanzador(){}
// };