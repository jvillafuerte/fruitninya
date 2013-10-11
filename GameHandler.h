#include "MouseHandler.h"


class GameHandler
{
public:
    MouseHandler * mousehander;
    ObjectsLauncher * objectslauncher;
    GameHandler(){}
    void set(MouseHandler * mh, ObjectsLauncher * ol){
        mousehander = mh;
        objectslauncher = ol;
        objectslauncher->set_max(5);
        objectslauncher->create_objects();
    }
    void run(){
        objectslauncher->run();
        if(objectslauncher->get_status()){
            objectslauncher->destroy();
            objectslauncher->set_max((rand() % 5));
            objectslauncher->create_objects();
        }
        // cout<<objectslauncher->empty<<endl;
        // while(true){
        // }
    }
    ~GameHandler(){}
};