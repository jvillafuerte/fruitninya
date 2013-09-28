#include "constantes.h"
class Punto
{
public:
	GLfloat x;
	GLfloat y;
	Punto(GLfloat xx, GLfloat yy){
		x=xx;
		y=yy;
	}
	~Punto(){}
	/* data */
};

class Objeto
{
public:
	Punto centro;
	GLfloat tam;
	GLfloat acel;
    GLfloat ang;
	Objeto(GLfloat xx, GLfloat yy, GLfloat tamm, GLfloat acell, GLfloat angg){
		centro.x=xx;
		centro.y=yy;
		tam=tamm;
		acel=acell;
		ang=angg;
	}

	~Objeto(){}
	void Dibujar(){
		GL.Begin(GL.QUADS);
		GL.Color(Color.red);
		GL.Vertex3(centro.x-tam, centro.y-tam);
		GL.Vertex3(centro.x+tam, centro.y+tam);
		GL.Vertex3(centro.x+tam, centro.y-tam);
		GL.Vertex3(centro.x-tam, centro.y+tam);
		GL.End();
	}
	void mover(){
        if(!existe)
            return;
        ang = tetta*pi/180;
        centro.x = vel_base+posX+acel*cos(ang);
        centro.y = vel_base+posY+acel*sin(ang);
        if(acel >= 0.00005)
            acel = acel-0.0000005;
        else
            acel = 0.00005;
    }

	/* data */
};