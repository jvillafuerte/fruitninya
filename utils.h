int distancia(const Punto & a, const Punto & b){                      //Funcion para calcular distancia euclidiana
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
