#include "texto.h"
#include "utils.h"
#include <unistd.h>



class GameHandler
{
public:   //punteros  a los demas objetos
MouseHandler * mousehandler;
ObjectsLauncher * objectslauncher;
Texto * tex;
vector<Mitad *> cortados;
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
        tex->actualizar_tiempo();
        tex->print();
        controlar_tiempo();
        set_nivel();
    }

    void mover_cortados(){     // mueve los dos objetos resultantes del corte
        for (int i = 0; i < cortados.size(); i++)
        {
            // c_musica *musica = new c_musica( "Sonidos/Choque.wav");
            cortados[i]->mover();
            cortados[i]->rotar();
        }
    }

    //compara la posicion del mause y del punto centro de objeto, tambien actualiza el contador de frutas cortdas y nivel
    //Se hace calculando la distancia euclideana
    void detectar_corte(){
        int combo=0;
        if(mousehandler->puntos.size()){
            for (int j = 0; j < objectslauncher->frutas.size(); j++)
            {
                if(distancia(mousehandler->puntos[mousehandler->puntos.size()-1], 
                   objectslauncher->frutas[j]->centro) <= objectslauncher->frutas[j]->tam)
                {
                    objectslauncher->frutas[j]->set_dibujar(false);
                    cortados.push_back(new Mitad);
                    cortados.push_back(new Mitad);
                    int max = cortados.size();
                    combo++;
                    objectslauncher->frutas[j]->cortar(cortados[max-1], cortados[max-2]);
                    objectslauncher->frutas.erase(objectslauncher->frutas.begin() + j);
                    frutas++;
                    tex->puntaje++;
                    if (combo==3)
                    {
                        tex->puntaje+= 3;
                    }
                    if (combo==4)
                    {
                        tex->puntaje+= 8;
                    }

                }
                combo++;

            }
            combo =0;
            for (int j = 0; j < objectslauncher->bombas.size(); j++)
            {
                if(distancia(mousehandler->puntos[mousehandler->puntos.size()-1], 
                   objectslauncher->bombas[j]->centro) <= objectslauncher->bombas[j]->tam)
                {
                    tex->estado = true;
                    estado = true;
                    tex->tiempo_terminado = true;
                }
            }
        }
    }

    void controlar_tiempo(){
        if(tex->tiempo <= 0){
            tex->tiempo_terminado = true;
            estado = true;
        }
    }

    void set_nivel(){
        if (tex->tiempo % 15 == 0 && tex->tiempo>=0)
        {
            nivel=7-tex->tiempo/15;

        }
    }
    ~GameHandler(){}
};