LINUX----------
g++ -lGL -lGLU -lglut -lm main.cpp -o app

MAC------------
g++ -framework OpenGL -framework GLUT -framework IOKit -lobjc -I /opt/local/include/SOIL/ main.cpp -o app

EJECUTAR-------
./app
