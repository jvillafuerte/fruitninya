#include "Object.h"
#include "constantes.h"

class ObjectsLauncher
{
public:
    vector<Objeto *> objetos;
    int max;
    bool empty;
    ObjectsLauncher(){
        max = 0;
        empty = true;
    }
    void set_max(int max){
        this->max = max;
        empty = false;
    }
    void create_objects(){
        empty = false;
        for (int i = 0; i < max; i++)
        {
            objetos.push_back(new Objeto());
            objetos[i]->set((rand()%400)+200,1 - (rand() % ORIGEN_Y),(rand()%20)+10,((rand()%10)+80)*objetos[i]->sentido,
                    (rand()%20)+80);
        }
    }
    void run(){
        for (int i = 0; i < max; i++)
        {
            objetos[i]->mover();
            objetos[i]->rotar();
        }
    }
    bool get_status(){
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