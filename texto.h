#include "MouseHandler.h"
#include <time.h> 

class Texto
{
public:
    ptrdiff_t font;    //fuente 1
    ptrdiff_t font2;   //fuente 2
    char buff[30];     //almncenamiento
    int nivel, frutas;  
    bool estado;       //para ver si imprime el texto de termino juego
    int tiempo;
    time_t  tiempo_i;
    struct tm * now ;
    time_t tiempo_now;
    bool tiempo_terminado;
    int puntaje;
    Texto(){  // inicilizador
        font=(ptrdiff_t)GLUT_BITMAP_HELVETICA_18;
        font2=(ptrdiff_t)GLUT_BITMAP_HELVETICA_12;
        nivel = 1;
        frutas = 0;
        estado = false;
        tiempo = 90;
        tiempo_i = time(0);
        now = localtime( & tiempo_i );
        tiempo_terminado = false;
        puntaje=0;
    }
    void actualizar_tiempo(){
        time(&tiempo_now);
        if(difftime(tiempo_now,tiempo_i)>=1)
            tiempo--;
        time(&tiempo_i);
    }

    void set_puntaje(int puntaje_){
        puntaje=puntaje_;
    }

    char * to_char(int nivel)    //convertir de entero a string
    {
        sprintf (buff, "%d", nivel);
        return buff;
    }

    char * time_to_char(int tiempo)    //convertir de entero a string
    {
        int min,sec;
        min = tiempo/60;
        sec = tiempo%60;
        if(sec < 10) 
            sprintf (buff, "%d:0%d", min, sec);
        else
            sprintf (buff, "%d:%d", min, sec);
        return buff;
    }


    void resetPerspectiveProjection() {   //reinicia la prespectiva de la preyeccion
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    } 

    void renderBitmapString(float x, float y, void *font,const char *string){   //renderizacion
        const char *c;
        glRasterPos2f(x, y);
        for (c=string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }

    void print(){

        GLfloat light_pos_titulo[] = { 350, 580, 0.0, 1.0 };
        GLfloat light_pos_cortadas[] = { 10, 560, 0.0, 1.0 };
        GLfloat light_pos_puntaje[] = { 10, 540, 0.0, 1.0 };
        GLfloat light_pos_nivel[] = { 5, 600, 0.0, 1.0 };
        GLfloat light_pos_tiempo[] = { 650, 580, 0.0, 1.0 };
        GLfloat light_pos_tiempo_cro[] = { 700, 580, 0.0, 1.0 };
        GLfloat light_pos_nivel_re[] = { 50, 580, 0.0, 1.0 };
        //GLfloat light_pos_top[] = { WIN_ANCHO/2, WIN_ALTO, 10.0, 1.0 };
        GLfloat color[] = {1.0f, 1.0f, 1.0f, 5.5f};
        //GLfloat color2[] = {1.0f, 1.0f, 1.0f, 0.5f};

        glLightfv(GL_LIGHT1, GL_POSITION, light_pos_titulo);
        glLightfv(GL_LIGHT2, GL_POSITION, light_pos_cortadas);
        glLightfv(GL_LIGHT3, GL_POSITION, light_pos_puntaje);
        glLightfv(GL_LIGHT4, GL_POSITION, light_pos_nivel);
        glLightfv(GL_LIGHT5, GL_POSITION, light_pos_tiempo);
        glLightfv(GL_LIGHT6, GL_POSITION, light_pos_tiempo_cro);
        glLightfv(GL_LIGHT7, GL_POSITION, light_pos_nivel_re);

        //lLightfv(GL_LIGHT1, GL_POSITION, light_pos_top);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, color);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, color);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, color);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, color);
        glLightfv(GL_LIGHT6, GL_DIFFUSE, color);
        glLightfv(GL_LIGHT7, GL_DIFFUSE, color);

        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(350,580,(void *)font,"Fruit Ninja");
        renderBitmapString(10,560, (void*)font2, "Frutas Cortadas: "); 
        renderBitmapString(10,540, (void*)font2, "Puntaje: ");   
        renderBitmapString(10,580, (void*)font2, "Nivel: ");
        renderBitmapString(650,580, (void*)font2, "Tiempo: ");
        renderBitmapString(50,580, (void*)font2, to_char(nivel));
        renderBitmapString(110,560, (void*)font2, to_char(frutas));
        renderBitmapString(80,540, (void*)font2, to_char(puntaje));
        if(!tiempo_terminado){
            if(tiempo<=10){
                glColor3f(1.0f, 0.0f, 0.0f);
                renderBitmapString(700,580, (void*)font2, time_to_char(tiempo));
            }
            renderBitmapString(700,580, (void*)font2, time_to_char(tiempo));
        }
        else
            renderBitmapString(700,580, (void*)font2, time_to_char(0));
        if(estado){
            glColor3f(1.0f, 0.0f, 0.0f);
            renderBitmapString(350,350,(void *)font,"Perdiste!");
        }else
            if(tiempo_terminado){
                glColor3f(1.0f, 0.0f, 0.0f);
                renderBitmapString(350,350,(void *)font,"Termino!");
            }
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
        glEnable(GL_LIGHT5);
        glEnable(GL_LIGHT6);
        glEnable(GL_LIGHT7);


    }

    void set_nivel(int n){
        nivel = n;
    }

    void set_frutas(int f){
        frutas = f;
    }
};