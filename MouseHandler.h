#include "launcher.h"

class MouseHandler
{
public:
    vector<Punto *> puntos;
    bool flag;
    int timer;
    bool drawer;

    MouseHandler(){
        flag = false;
        timer = 1000;
        drawer = false;
    }

    void addClick(GLint x, GLint y){
        Punto * p = new Punto(x, y);
        puntos.push_back(p);
    }

    void setDrawer(bool state){
        drawer = state;
    }

    void dibujar(){
        if(drawer)
        {
            for (int i = 1; i < puntos.size(); i++)
            {
                glLineWidth(i % 100);
                glBegin(GL_LINES);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(puntos[i-1]->x, WIN_ALTO - puntos[i-1]->y);
                glVertex2f(puntos[i]->x, WIN_ALTO - puntos[i]->y);
                glEnd();
            }
            if(puntos.size() > 20)
                puntos.erase(puntos.begin());
        }
        else{
            puntos.clear();
        }
        if(timer == 0 && drawer){
            puntos.clear();
            flag = false;
            timer = 500;
            drawer = false;
        }
        if(drawer)
            timer--;
    }

    ~MouseHandler(){}
};