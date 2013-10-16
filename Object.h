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

using namespace std;

int s[2] = {-1, 1};

class Punto   // Centro de la Figura
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
    ~Punto(){
        x=y=0;
    }
};

class Objeto  //Clase padre (Fruta y Bombas)
{
public:
    Punto * centro;
    GLfloat tam;  
    GLfloat ang;
    GLfloat vel;
    GLfloat velx,vely;     //Velocidades Iniciales
    GLfloat tiempo;
    GLfloat x0, y0;        //Posiciones Iniciales  
    GLfloat vel_x, vel_y;  //Velocidades Variantes
    GLfloat rot;           //Angulo de Rotacion
    GLfloat sentido;       // 1 y -1 izquierda y derecha
    bool dibujar_;         // status para dibujar
    bool es_bomba;         // status si es bomba
    GLfloat R, G, B;       // colores random

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

    Objeto(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat angg, GLfloat vel_){
        centro = new Punto(xx, yy);
        tam=tamm;
        ang=angg;
        vel=vel_;
        velx= vel*cos(ang * PI / 180);  // Obtencion velocidad en X , segun el angulo
        vely= vel*sin(ang * PI / 180);  // Obtencion velocidad en Y , segun el angulo
        dibujar_ = true;

    }

    //Funcion Set para la modificacion de datos
    void set(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat angg, GLfloat vel_, GLfloat R=1, GLfloat G=0, GLfloat B=0){ 
        centro = new Punto(xx, yy);   
        tam=tamm;
        ang=angg;
        vel=vel_;
        y0 = yy;
        x0 = xx;
        if(ang>0){                          //La direccion del objeto el cual sera lanzado
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

    //Los metodos virtuales evaluaran si la funcion es llamada en el Padre o en el Hijo
    virtual void dibujar(){
        if(dibujar_){         
            glBegin(GL_QUADS);
            glColor3f(R, G, B);
            glVertex3f(centro->x-tam, centro->y-tam, 0);
            glVertex3f(centro->x+tam, centro->y-tam, 0);
            glVertex3f(centro->x+tam, centro->y+tam, 0);
            glVertex3f(centro->x-tam, centro->y+tam, 0);
            glEnd();
        }
    }

    virtual void mover(){
        rot += 0.1 * sentido;
        tiempo+=0.01;
        centro->y= y0 + vel_y*tiempo-GRAVEDAD*tiempo*tiempo/2;
        centro->x = x0  + vel_x * tiempo;
    }

    virtual void rotar(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(centro->x, centro->y, 0);
        glRotated(rot, 0, 0, 1);
        glTranslatef(-centro->x, -centro->y, 0);
        dibujar();
        glPopMatrix();

    }

    virtual void cortar(Objeto * & a , Objeto * & b)  // Recibe 2 Objetos "hijos", los cuales seran inicializados
    {
        a->set(centro->x, centro->y, tam/2, ang+20, 5, this->R, this->G, this->B);
        b->set(centro->x, centro->y, tam/2, ang-20, 5, this->R, this->G, this->B);
    }
    
    void set_dibujar(bool val){
        dibujar_ = val;
    }
};


//La clase Bomba heredara de objeto con la diferencia que es una figura constante de radio 20 ,
// y un parametro extra si es bomba el cual avisara a la clase "GameHandler.h" para enviar un mensaje
class Bomba:public Objeto  
{
public:
    int radio;
    Bomba(){
        radio = 20;
        es_bomba = true;
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
        if(dibujar_)
        { 
            glColor3f(1.0,1.0,1.0);
            circle(centro->x,centro->y);
            glEnd();
        }
    }
    
    void mover(){
        rot += 0.1 * sentido;
        tiempo+=0.01;
        centro->y= y0 + vel_y*tiempo-GRAVEDAD*tiempo*tiempo/2;
        centro->x = x0  + vel_x * tiempo;
    }

    void rotar(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(centro->x, centro->y, 0);
        glRotated(rot, 0, 0, 1);
        glTranslatef(-centro->x, -centro->y, 0);
        dibujar();
        glPopMatrix();

    }
};


//Al igual que la clase Bomba la clase fruta tendra un puntero a funcion la cual contendra 3 metodos de dibujos
// Y seran llamados con un metodo random
class Fruta:public Objeto
{
public:
    GLfloat R, G, B;
    typedef void (Fruta::*funciones)();   //Puntero a funcion en una clase
    funciones func[2];
    funciones dibuja;                     //Puntero a funcion para dibujar 
    int indice;                           //Para ver cual de las fucnciones se dibujará


    Fruta(){
        R = 0.3 + rand() % 2;
        G = 0.3 + rand() % 2;
        B = 0.3 + rand() % 2;
        func[0] = &Fruta::cuadrado;      
        func[1] = &Fruta::rectangulo;
        func[2] = &Fruta::triangulo;
        indice = rand() % 3;
        dibuja = (this->func[indice]);
    }
    ~Fruta(){}

    void cuadrado(){
        if(dibujar_){
            glBegin(GL_QUADS);
            glColor3f(R, G, B);
            glVertex3f(centro->x-tam, centro->y-tam, 0);
            glVertex3f(centro->x+tam, centro->y-tam, 0);
            glVertex3f(centro->x+tam, centro->y+tam, 0);
            glVertex3f(centro->x-tam, centro->y+tam, 0);
            glEnd();
        }
    }

    void rectangulo(){
        if(dibujar_){
            glBegin(GL_QUADS);
            glColor3f(R, G, B);
            glVertex3f(centro->x-tam, centro->y-tam, 0);
            glVertex3f(centro->x+2*tam, centro->y-tam, 0);
            glVertex3f(centro->x+2*tam, centro->y+tam, 0);
            glVertex3f(centro->x-tam, centro->y+tam, 0);
            glEnd();
        }
    }

    void triangulo(){
        if(dibujar_){
            glBegin(GL_TRIANGLES);
            glColor3f(R, G, B);
            glVertex3f(centro->x-tam, centro->y-tam, 0);
            glVertex3f(centro->x+2*tam, centro->y-tam, 0);
            glVertex3f(centro->x+2*tam, centro->y+tam, 0);
            glEnd();
        }
    }

    void dibujar(){
        (this->*dibuja)();   // Llama al puntero funcion dibuja, el cual invoca un metodo que le toco al iniciar con el indice
    }

    void mover(){
        rot += 0.1 * sentido;
        tiempo += 0.01;
        centro->y= y0 + vel_y*tiempo-GRAVEDAD*tiempo*tiempo/2;
        centro->x = x0  + vel_x * tiempo;
    }

    void rotar(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(centro->x, centro->y, 0);
        glRotated(rot, 0, 0, 1);
        glTranslatef(-centro->x, -centro->y, 0);
        dibujar();
        glPopMatrix();
    }

    void cortar(Objeto * & a , Objeto * & b)
    {
        a->set(centro->x, centro->y, tam/2, ang+20, 5, this->R, this->G, this->B);
        b->set(centro->x, centro->y, tam/2, ang-20, 5, this->R, this->G, this->B);
    }

};