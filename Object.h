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
#include "glm.h"

#ifndef __APPLE__
#include "Sonido.cpp"
#endif


using namespace std;

int s[2] = {-1, 1};

// Punteros a los modelos
GLMmodel * bomba;
GLMmodel * manzana;
GLMmodel * manzana_a;
GLMmodel * manzana_b;
GLMmodel * pera;
GLMmodel * pera_a;
GLMmodel * pera_b;
GLMmodel * pinia;
GLMmodel * pinia_a;
GLMmodel * pinia_b;
GLMmodel * platano;
GLMmodel * platano_a;
GLMmodel * platano_b;

char * rutas_modelos[4] = {"models/apple/apples.obj",
                        "models/pera/pera.obj",
                        "models/melon/melon.obj",
                        "models/coco/coco.obj"};

char * rutas_mitades[8] = {
    "models/apple/apples_ladoa.obj", "models/apple/apples_ladob.obj",
    "models/pera/perlado_a.obj", "models/pera/perlado_b.obj",
    "models/melon/melonlado_a.obj", "models/melon/melonlado_b.obj",
    "models/coco/cocolado_a.obj", "models/coco/cocolado_b.obj"
};

GLMmodel * modelos[4] = {manzana, pera, pinia, platano};

// vector< vector<char *> > ;
GLMmodel * modelos_mitades[8] ={
    manzana_a, manzana_b,
    pera_a, pera_b,
    pinia_a, pinia_b,
    platano_a, platano_b
};

class Punto
{
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Punto(GLfloat xx, GLfloat yy, GLfloat zz=0){
        x=xx;
        y=yy;
        z=zz;
    }
    Punto(Punto * p){
        x = p->x;
        y = p->y;
        z = p->z;
    }
    ~Punto(){
        x=y=z=0;
    }
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
    GLfloat x0, y0;
    GLfloat vel_x, vel_y;
    GLfloat rot;
    GLfloat sentido;
    bool dibujar_;
    bool es_bomba;
    GLfloat R, G, B;
    Objeto(){
        centro = new Punto(0, 0);
        tam=0;
        ang=0;
        vel=0;
        tiempo =0;
        velx= vel*cos(ang * PI / 180);
        vely= vel*sin(ang * PI / 180);
        rot = rand() % 50;
        int i = rand() % 2;
        sentido = s[i];
        dibujar_ = true;
        es_bomba = false;
    }

    Objeto(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat tamm, GLfloat angg, GLfloat vel_){
        centro = new Punto(xx, yy, zz);
        tam=tamm;
        ang=angg;
        vel=vel_;
        velx= vel*cos(ang * PI / 180);
        vely= vel*sin(ang * PI / 180);
        dibujar_ = true;
    }

    void set(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat tamm, GLfloat angg, GLfloat vel_, GLfloat R=1, GLfloat G=0, GLfloat B=0){
        centro = new Punto(xx, yy, zz);
        tam=tamm;
        ang=angg;
        vel=vel_;
        y0 = yy;
        x0 = xx;
        if(ang>0){
            vel_x= vel*cos(ang * PI / 180);
            vel_y= vel*sin(ang * PI / 180);
        }else
        {
            vel_x= -1*vel*cos(ang * PI / 180);
            vel_y= -1*vel*sin(ang * PI / 180);
        }
        dibujar_ = true;
        this->R = R;
        this->G = G;
        this->B = B;
    }

    ~Objeto(){
        centro = NULL;
        delete centro;

    }
    virtual void dibujar(){
        if(dibujar_){
            glBegin(GL_QUADS);
            glColor3f(R, G, B);
            glVertex3f(centro->x-tam, centro->y-tam, centro->z);
            glVertex3f(centro->x+tam, centro->y-tam, centro->z);
            glVertex3f(centro->x+tam, centro->y+tam, centro->z);
            glVertex3f(centro->x-tam, centro->y+tam, centro->z);
            glEnd();
        }
    }

    virtual void mover(){
        rot += 0.1 * sentido;
        tiempo+=0.005;
        centro->y= y0 + vel_y*tiempo-GRAVEDAD*tiempo*tiempo/2;
        centro->x = x0  + vel_x * tiempo;
    }

    virtual void rotar(){
        // glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(centro->x, centro->y, centro->z);
        glRotated(rot, 0, 0, 1);
        glRotated(rot, 1, 0, 0);
        glTranslatef(-centro->x, -centro->y, -centro->z);
        dibujar();
        glPopMatrix();
    }

    virtual void cortar(Objeto * & a , Objeto * & b){
        a->set(centro->x, centro->y, centro->z, tam/2, ang+20, 5, this->R, this->G, this->B);
        b->set(centro->x, centro->y, centro->z, tam/2, ang-20, 5, this->R, this->G, this->B);
    }
    
    void set_dibujar(bool val){
        dibujar_ = val;
    }
};


class Bomba:public Objeto
{
public:
    int radio;

    #ifndef __APPLE__
    c_musica * musica2;
    #endif
    Bomba(){
        radio = 20;
        es_bomba = true;
        #ifndef __APPLE__
        musica2 = new c_musica("Sonidos/Explosion.wav");
        #endif
        if (!bomba) {
            bomba = glmReadOBJ("models/bombi/bombi.obj");
            if (!bomba) exit(0);
        }

    }
    ~Bomba(){}
    void circle(float x, float y){
        int segments=30; 
        glBegin( GL_TRIANGLE_FAN ); 
        glVertex2f(x, y); 
        for(int n = 0; n <= segments; ++n)
        { 
            float const t = 2*M_PI*(float)n/(float)segments;
            glVertex2f(x + sin(t)*radio, y + cos(t)*radio);
        } 
        glEnd();
    } 

    void dibujar(){
        if(dibujar_){ 
            glPushMatrix(); 
            glTranslatef(centro->x,centro->y, centro->z); 
            glRotatef(rot,0.0,0.0,1.0); 
            glRotatef(rot,0.0,1.0,0.0); 
            glmUnitize(bomba);
            glmFacetNormals(bomba);
            glmScale(bomba, 40);
            glmDraw(bomba, GLM_SMOOTH | GLM_MATERIAL); 
            glTranslatef( -centro->x, -centro->y, -centro->z);
            glLoadIdentity(); 
            glPopMatrix();
        }
    }
    void rotar(){
        dibujar();
    }
    void cortar(){
        #ifndef __APPLE__
        musica2->reproduce();
        #endif
    }
};

// char * sonidos[4] = {"Sonidos/cortar.wav",
//                      "Sonidos/cortar2.wav",
//                      "Sonidos/corta3.wav",
//                      "Sonidos/corta4.wav"};


class Mitad:public Objeto
{
public:
    int indice;
    int cual_mitad;
    int indice_real;
    Mitad(){}
    Mitad(int ind, int cm){
        indice=ind;
        cual_mitad=cm;
        indice_real = indice*2 + cual_mitad;
        cout<<indice_real<<endl;
        if (!modelos_mitades[indice_real]) {
            modelos_mitades[indice_real] = glmReadOBJ(rutas_mitades[indice_real]);
            if (!modelos_mitades[indice_real]) exit(0);
        }
        // if(cm==0){
        //     glPushMatrix(); 
        //     glTranslatef(centro->x,30+centro->y, centro->z); 
        //     glRotatef(30,0.0,0.0,1.0); 
        //     // glRotatef(rot,0.0,1.0,0.0); 
        //     // glTranslatef( -centro->x, -centro->y, -centro->z);
        //     // glLoadIdentity(); 
        //     // glPopMatrix();
        // }
    }

    ~Mitad(){}

    void dibujar(){
        if(dibujar_){ 
            glPushMatrix(); 
            glTranslatef(centro->x,centro->y, centro->z); 
            glRotatef(rot,0.0,0.0,1.0); 
            glRotatef(rot,0.0,1.0,0.0); 
            glmUnitize(modelos_mitades[indice_real]);
            glmFacetNormals(modelos_mitades[indice_real]);
            glmScale(modelos_mitades[indice_real], 40);
            glmDraw(modelos_mitades[indice_real], GLM_SMOOTH | GLM_MATERIAL); 
            glTranslatef( -centro->x, -centro->y, -centro->z);
            glLoadIdentity(); 
            glPopMatrix();
        }
    }

    void set(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat tamm, GLfloat angg, GLfloat vel_, GLfloat R=1, GLfloat G=0, GLfloat B=0, int ind=0, int cm=0){
        centro = new Punto(xx, yy, zz);
        tam=tamm;
        ang=angg;
        vel=vel_;
        y0 = yy;
        x0 = xx;
        if(ang>0){
            vel_x= vel*cos(ang * PI / 180);
            vel_y= vel*sin(ang * PI / 180);
        }else
        {
            vel_x= -1*vel*cos(ang * PI / 180);
            vel_y= -1*vel*sin(ang * PI / 180);
        }
        dibujar_ = true;
        this->R = R;
        this->G = G;
        this->B = B;

        indice=ind;
        cual_mitad=cm;
        indice_real = indice*2 + cual_mitad;
        cout<<indice_real<<endl;
        if (!modelos_mitades[indice_real]) {
            modelos_mitades[indice_real] = glmReadOBJ(rutas_mitades[indice_real]);
            if (!modelos_mitades[indice_real]) exit(0);
        }
        if(cm==0){
            // ang=-ang;
            glPushMatrix(); 
            glTranslatef(centro->x,100+centro->y, centro->z); 
            glRotated(130,1,0,0); 
            // glRotatef(rot,0.0,1.0,0.0); 
            // glTranslatef( -centro->x, -centro->y, -centro->z);
            glLoadIdentity(); 
            // glPopMatrix();
        }
    }

    void rotar(){
        dibujar();
    }

    void cortar(Mitad * & a , Mitad * & b){

    }


};

class Fruta:public Objeto
{
public:
    int indice;
    #ifndef __APPLE__
    c_musica * musica;
    #endif
    Fruta(){
        #ifndef __APPLE__
        musica = new c_musica("Sonidos/cortar2.wav");
        #endif
        indice = rand() % 4;
        if (!modelos_mitades[indice]) {
            modelos[indice] = glmReadOBJ(rutas_modelos[indice]);
            if (!modelos[indice]) exit(0);
        }
    }
    ~Fruta(){}

    //ejecuta alguna de las funciones de arriba segun fue asignado aleatoriamente en el constructor
    void dibujar(){
        if(dibujar_){ 
            glPushMatrix(); 
            glTranslatef(centro->x,centro->y, centro->z); 
            glRotatef(rot,0.0,0.0,1.0); 
            glRotatef(rot,0.0,1.0,0.0); 
            glmUnitize(modelos[indice]);
            glmFacetNormals(modelos[indice]);
            glmScale(modelos[indice], 40);
            glmDraw(modelos[indice], GLM_SMOOTH | GLM_MATERIAL); 
            glTranslatef( -centro->x, -centro->y, -centro->z);
            glLoadIdentity(); 
            glPopMatrix();
        }
    }

    void rotar(){
        dibujar();
    }

    void cortar(Mitad * & a , Mitad * & b){
        #ifndef __APPLE__
        musica->reproduce();
        #endif
        a->set(centro->x, centro->y, centro->z, tam/2, -PI/6, this->vel/4, this->R, this->G, this->B, indice, 0);
        b->set(centro->x, centro->y, centro->z, tam/2, PI/6, this->vel/4, this->R, this->G, this->B, indice, 1);
        #ifndef __APPLE__
        musica->para();
        #endif
    }
};