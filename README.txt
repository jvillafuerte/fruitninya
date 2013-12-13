LINUX----------
g++ -lGL -lGLU -lglut -lm main.cpp -o app
g++ main.cpp -lGL -lGLU -lglut -lSDL_mixer -std=c++11 -lSDL -lm -o app
g++ main.cpp glm.c -lGL -lGLU -lglut -lSDL_mixer -std=c++11 -lSDL -lm -o app


MAC------------
g++ -framework OpenGL -framework GLUT -framework IOKit -lobjc -I /opt/local/include/SOIL/ main.cpp -o app

EJECUTAR-------
./app
