#ifndef LOGICA_H
#define LOGICA_H

#include <string>
#include <unordered_map>
#include <deque>
#include <queue>

struct producto {
    std::string ID;
    std::string nombre;
    int precio;
    int cantidad;
};

struct compra {
    producto articulo;
    int cantidad;
};

void agregar_productos(const std::string ID, const std::string NOMBRE, int PRECIO, int CANTIDAD);
void agregar_al_carro(const std::string ID, int CANTIDAD);
void finalizar_compra();
void cargar_sistema();
void realizar_cierre();
void actualizar_inventario();

#endif 