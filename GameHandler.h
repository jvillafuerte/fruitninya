#include "texto.h"
#include "utils.h"


class GameHandler
{
public:   //punteros  a los demas objetos
    MouseHandler * mousehandler;
    ObjectsLauncher * objectslauncher;
    Texto * tex;
    vector<Objeto *> cortados;
    int nivel, frutas;
    bool estado;          //el estado del juego si a terminado (en funcion a bomba)

    GameHandler(){
        estado = false;
    }

    void set(MouseHandler * mh, ObjectsLauncher * ol, Texto * t){
        mousehandler = mh;
        objectslauncher = ol;
        tex = t;
        objectslauncher->set_max(rand() % MAX_OBJETOS_INICIAL, 1);
        objectslauncher->create_objects();
        nivel = 1;
        frutas = 0;
    }

    void run(){          // lanzador , verifica si en juego sigue o ya termino
        if(!estado){
            objectslauncher->run();
            if(objectslauncher->get_status()){
                objectslauncher->destroy();
                int obj = (rand() % MAX_OBJETOS);
                int fru = obj - nivel / 2;
                int bom = 1 + nivel / 2;
                objectslauncher->set_max(fru, bom);
                objectslauncher->create_objects();
            }
            detectar_corte();
            mover_cortados();
        }
        tex->set_nivel(nivel);
        tex->set_frutas(frutas);
        tex->print();
    }

    void mover_cortados(){     // mueve los dos objetos resultantes del corte
        for (int i = 0; i < cortados.size(); i++)
        {
            c_musica *musica = new c_musica( "Sonidos/Choque.wav");
            cortados[i]->mover();
            cortados[i]->rotar();
        }
    }

    //compara la posicion del mause y del punto centro de objeto, tambien actualiza el contador de frutas cortdas y nivel
    //Se hace calculando la distancia euclideana
    void detectar_corte(){
        if(mousehandler->puntos.size()){
            for (int j = 0; j < objectslauncher->objetos.size(); j++)
            {
                if(distancia(mousehandler->puntos[mousehandler->puntos.size()-1], 
                   objectslauncher->objetos[j]->centro) <= objectslauncher->objetos[j]->tam)
                {
                    if(objectslauncher->objetos[j]->es_bomba) {
                        tex->estado = true;
                        estado = true;
                    }
                    objectslauncher->objetos[j]->set_dibujar(false);
                    cortados.push_back(new Objeto);
                    cortados.push_back(new Objeto);
                    int max = cortados.size();
                    objectslauncher->objetos[j]->cortar(cortados[max-1], cortados[max-2]);
                    objectslauncher->objetos.erase(objectslauncher->objetos.begin() + j);
                    frutas++;
                    nivel = 1 + frutas / 10;
                }
            }
        }
    }

    ~GameHandler(){}
};