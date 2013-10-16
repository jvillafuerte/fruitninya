#include "MouseHandler.h"

class Texto
{
public:
    ptrdiff_t font;
    ptrdiff_t font2;
    char buff[30];
    int nivel, frutas;
    bool estado;
    
    Texto(){
        font=(ptrdiff_t)GLUT_BITMAP_HELVETICA_18;
        font2=(ptrdiff_t)GLUT_BITMAP_HELVETICA_12;
        nivel = 1;
        frutas = 0;
        estado = false;
    }

    void set(){
    }

    char * to_char(int nivel)
    {
        sprintf (buff, "%d", nivel);
        return buff;
    }

    void resetPerspectiveProjection() {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    } 

    void renderBitmapString(float x, float y, void *font,const char *string){
        const char *c;
        glRasterPos2f(x, y);
        for (c=string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }

    void print(){
        glColor3f(1.0f, 1.0f, 0.0f);
        renderBitmapString(350,580,(void *)font,"Fruit Ninja");
        renderBitmapString(650,550, (void*)font2, "Frutas Cortadas: ");   
        renderBitmapString(650,580, (void*)font2, "Nivel: ");
        renderBitmapString(690,580, (void*)font2, to_char(nivel));
        renderBitmapString(750,550, (void*)font2, to_char(frutas));
        if(estado)
            renderBitmapString(350,350,(void *)font,"Perdiste!");
    }

    void set_nivel(int n){
        nivel = n;
    }

    void set_frutas(int f){
        frutas = f;
    }
};