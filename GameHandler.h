#include "texto.h"
#include "utils.h"

class GameHandler
{
public:
    MouseHandler * mousehandler;
    ObjectsLauncher * objectslauncher;
    Texto * tex;
    vector<Objeto *> cortados;
    int nivel, frutas;

    GameHandler(){}

    void set(MouseHandler * mh, ObjectsLauncher * ol, Texto * t){
        mousehandler = mh;
        objectslauncher = ol;
        tex = t;
        objectslauncher->set_max(5);
        objectslauncher->create_objects();
        nivel = 1;
        frutas = 0;
    }

    void run(){
        objectslauncher->run();
        if(objectslauncher->get_status()){
            objectslauncher->destroy();
            objectslauncher->set_max((rand() % 5));
            objectslauncher->create_objects();
        }
        detectar_corte();
        mover_cortados();
        tex->set_nivel(nivel);
        tex->set_frutas(frutas);
        tex->print();
    }

    void mover_cortados(){
        for (int i = 0; i < cortados.size(); i++)
        {
            cortados[i]->mover();
            cortados[i]->rotar();
        }
    }

    void detectar_corte(){
        register int kk = 0;
        for (int i = 0; i < mousehandler->puntos.size(); i++)
        {
            for (int j = 0; j < objectslauncher->objetos.size(); j++)
            {
                if(distancia(mousehandler->puntos[i], 
                   objectslauncher->objetos[j]->centro) <= objectslauncher->objetos[j]->tam)
                {
                    objectslauncher->objetos[j]->set_dibujar(false);
                    cortados.push_back(new Objeto);
                    cortados.push_back(new Objeto);
                    int max = cortados.size();
                    objectslauncher->objetos[j]->cortar(cortados[max-1], cortados[max-2]);
                    objectslauncher->objetos.erase(objectslauncher->objetos.begin() + j - 1);
                    frutas++;
                    nivel = 1 + frutas / 10;
                }
            }
        }
    }
    
    ~GameHandler(){}
};