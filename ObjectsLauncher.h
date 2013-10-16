#include "Object.h"
#include "constantes.h"

//La clase ObjectLauncher sera la encargada de lanzar un vector de objetos ( Frutas y Bombas)
class ObjectsLauncher
{
public:
    vector<Objeto *> objetos;
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
        int i = 0;
        for ( ; i < max_frutas; i++)                //Crea un numero max de frutas en el vector de objetos 
        {
            objetos.push_back(new Fruta());
            objetos[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),(rand()%20)+10,((rand()%10)+80)*objetos[i]->sentido,
                            (rand()%20)+80);
        }
        for (; i < (max_frutas + max_bombas); i++)  //Crea un numero maximo de bombas en el vector de objetos
        {
            objetos.push_back(new Bomba());
            objetos[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),(rand()%20)+10,((rand()%10)+80)*objetos[i]->sentido,
                            (rand()%20)+80);
        }
    }

    void run(){
        int max = max_frutas + max_bombas;
        for (int i = 0; i < max; i++)       //Manda a ejecutar todos los datos del vector creado.
        {
            objetos[i]->mover();
            objetos[i]->rotar();
        }
    }

    bool get_status(){
        int max = max_frutas + max_bombas;
        for (int i = 0; i < max; i++){
            if(objetos[i]->centro->y > -ORIGEN_Y){      //verifica si el objeto esta fuera de la pantalla
                empty = false;                          
                return false;
            }
        }
        empty = true;        //Si es que recorrio y todos salieron entonces el vector de objetos estara vacio.
        return empty;
    }
    
    void destroy(){
        objetos.clear();   
    }

    ~ObjectsLauncher(){}
};