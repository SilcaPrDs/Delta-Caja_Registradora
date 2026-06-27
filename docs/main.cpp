#include "logica.h"
#include <iostream>

using namespace std;

int main(){
	
	producto p1 = {"1011", "queso", 100, 20};
	producto p2 = {"1030", "pan", 233, 10};
	
	cargar_sistema();
	
	
	
	agregar_al_carro("1011", 3);
	agregar_al_carro("1030", 3);
	agregar_al_carro("1011", 3);
	
	finalizar_compra();
	
	agregar_productos("1011","queso",100,30);
	
	agregar_al_carro("1011", 3);
	agregar_al_carro("1030", 2);
	agregar_al_carro("2003", 6);
	
	finalizar_compra();
	
	agregar_al_carro("1001", 3);
	agregar_al_carro("1030", 2);
	agregar_al_carro("2003", 6);
	agregar_al_carro("1030", 2);
	
	editar_producto("3002");
	editar_producto("1011");
	
	finalizar_compra();
	
	realizar_cierre();
	
	return 0;
}
