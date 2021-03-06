#include "ObjectsLauncher.h"

class MouseHandler
{
public:
  // La secuencia de puntos por los que pasa el mouse cuando se hace click!
  vector<Punto *> puntos;   
  //Tiempo que permanecera en la pantalla el efecto
  int timer;  
  bool drawer;  

  MouseHandler(){
    timer = 100;
    drawer = false;
  }

  void addClick(GLint x, GLint y){
  //Recibe la coordenana y lo agrega al vector 
    Punto * p = new Punto(x, WIN_ALTO - y); 
    puntos.push_back(p);
  }

  void setDrawer(bool state){
  //Para ver si se  dibuja o no
    drawer = state;             
  }

  //Recorrer el vector de puntos y dibujar lineas entre cada dos puntos del vector
  //El grosor de la linea va aumentada segun la posicion del indice del vector
  void dibujar(){
    glDisable(GL_LIGHTING);
    if(drawer){
      for (int i = 1; i < puntos.size(); i++){
        glLineWidth(i % 100);
        glBegin(GL_LINES);
        glColor3f(0.1f, 0.3f, 0.7f);
        glVertex2f(puntos[i-1]->x, puntos[i-1]->y);
        glVertex2f(puntos[i]->x, puntos[i]->y);
        glEnd();
      }
      if(puntos.size() > 10){
        puntos.erase(puntos.begin());
      }
    }
    else{
      puntos.clear();
    }
    if(timer == 0 && drawer){
      puntos.clear();
      timer = 500;
      drawer = false;
    }
    if(drawer){
      timer--;
    }
    glEnable(GL_LIGHTING);
  }

  ~MouseHandler(){}
};