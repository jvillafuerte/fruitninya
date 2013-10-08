#include "Object.h"
#include "constantes.h"
class lanzar{
	public:
		Objeto * objects;
		int tam;
		int ve[2];

		lanzar(){
			ve[0]=-1;
			ve[1]=1;
		}

		void set(int numbers){
			tam = numbers;
			objects = new Objeto[numbers];
			for (int i = 0; i < numbers; ++i)
			{
			    Objeto nuevo;
				objects[i]=nuevo;
			}
			for (int i = 0; i < numbers; ++i)
			{
				objects[i].set((rand()%400)+200,1,(rand()%20)+10,((rand()%10)+80)*ve[rand()%2],
					(rand()%20)+80);
			}
		}

};