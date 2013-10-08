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
    GLfloat tiempo;
    Objeto(){
    	centro = new Punto(0, 0);
        tam=0;
        ang=0;
        vel=0;
        tiempo =0;
    }

    Objeto(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat angg, GLfloat vel_){
        centro = new Punto(xx, yy);
        tam=tamm;
        ang=angg;
        vel=vel_;

    }
    void set(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat angg, GLfloat vel_){
        centro = new Punto(xx, yy);
        tam=tamm;
        ang=angg;
        vel=vel_;

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
    	tiempo+=0.01;
    	GLfloat velx= vel*cos(ang * PI / 180);
    	GLfloat vely= vel*sin(ang * PI / 180);
    	//centro->x=centro->x +1;
    	centro->y=centro->y + vely*tiempo-0.5*GRAVEDAD*tiempo*tiempo;

    	centro->x += velx * tiempo;



        // ang = tetta*pi/180;
        // centro.x = vel_base+posX+acel*cos(ang);
        // centro.y = vel_base+posY+acel*sin(ang);
        // if(acel >= )
        //     acel = acel-0.0000005;
        // else
        //     acel = 0.00005;
    }

};

// class Lanzador
// {
// public:
//     vector<Objeto> objetos;
//     Lanzador(arguments){}
//     ~Lanzador(){}
// };