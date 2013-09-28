Para compilar se debe hacer desde una terminar:
-En linux el comando es:
g++ -lGL -lGLU -lglut -lm main.cpp -o app
-En OSX el comando es:
g++ -framework OpenGL -framework GLUT -framework IOKit -lobjc main.cpp -o app

Y para ejecutar:
./app