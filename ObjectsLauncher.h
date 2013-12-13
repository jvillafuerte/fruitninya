#include "Object.h"
#include "constantes.h"

//La clase ObjectLauncher sera la encargada de lanzar un vector de objetos ( Frutas y Bombas)
class ObjectsLauncher
{
public:
  vector<Fruta *> frutas;
  vector<Bomba *> bombas;
  int max_frutas;
  int max_bombas;
  bool empty;

  ObjectsLauncher(){
    max_frutas = 0;
    max_bombas = 0;
    empty = true;
  }

  void set_max(int max_frutas, int max_bombas){
    this->max_frutas = max_frutas;
    this->max_bombas = max_bombas;
    empty = false;
  }

  void create_objects(){
    empty = false;
    int z = MIN_Z;
    //Crea un numero max de frutas en el vector de objetos 
    for (int i=0 ; i < max_frutas; i++){                
      z += 100;
      frutas.push_back(new Fruta());
      frutas[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),z,40,((rand()%10)+80)*frutas[i]->sentido,
                     (rand()%20)+80);
    }
    //Crea un numero maximo de bombas en el vector de objetos
    for (int i=0; i < max_bombas; i++){  
      z += 100;
      bombas.push_back(new Bomba());
      bombas[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),z,30,((rand()%10)+80)*bombas[i]->sentido,
                     (rand()%20)+80);
    }
  }

  void run(){
    //Crea un numero max de frutas en el vector de objetos 
    for (int i=0 ; i < max_frutas; i++){                
      frutas[i]->mover();
      frutas[i]->rotar();
    }
    //Crea un numero maximo de bombas en el vector de objetos
    for (int i=0; i < max_bombas; i++){  
      bombas[i]->mover();
      bombas[i]->rotar();
    }
  }

  bool get_status(){
    //Si es que recorrio y todos salieron entonces el vector de objetos estara vacio.
    bool emptyy = true;        

    //Crea un numero max de frutas en el vector de objetos 
    for (int i=0 ; i < max_frutas; i++){           
        //verifica si el objeto esta fuera de la pantalla     
      if(frutas[i]->centro->y > -ORIGEN_Y){      
        emptyy = false;
      }
    }
    //Crea un numero maximo de bombas en el vector de objetos
    for (int i=0; i < max_bombas; i++){  
      //verifica si el objeto esta fuera de la pantalla
      if(bombas[i]->centro->y > -ORIGEN_Y){      
        emptyy = false;                          
      }
    }
    if(emptyy) empty = true;
    else empty = false;

    return empty;
  }

  void destroy(){
    frutas.clear();  
    bombas.clear();
  }

  ~ObjectsLauncher(){}
};