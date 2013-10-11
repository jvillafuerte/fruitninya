#include "MouseHandler.h"
    
class Texto
{
    public:    
      int font;
      int font2;
      char buff[30];

    Texto(){

    }

    void set(){
        font=(int)GLUT_BITMAP_HELVETICA_18;
        font2=(int)GLUT_BITMAP_HELVETICA_12; 
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
    }
};