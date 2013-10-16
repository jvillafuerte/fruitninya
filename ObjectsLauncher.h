#include "Object.h"
#include "constantes.h"

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
        for ( ; i < max_frutas; i++)
        {
            objetos.push_back(new Fruta());
            objetos[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),(rand()%20)+10,((rand()%10)+80)*objetos[i]->sentido,
                            (rand()%20)+80);
        }
        for (; i < (max_frutas + max_bombas); i++)
        {
            objetos.push_back(new Bomba());
            objetos[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),(rand()%20)+10,((rand()%10)+80)*objetos[i]->sentido,
                            (rand()%20)+80);
        }
    }

    void run(){
        int max = max_frutas + max_bombas;
        for (int i = 0; i < max; i++)
        {
            objetos[i]->mover();
            objetos[i]->rotar();
        }
    }

    bool get_status(){
        int max = max_frutas + max_bombas;
        for (int i = 0; i < max; i++){
            if(objetos[i]->centro->y > -ORIGEN_Y){
                empty = false;
                return false;
            }
        }
        empty = true;
        return empty;
    }
    
    void destroy(){
        objetos.clear();
    }

    ~ObjectsLauncher(){}
};