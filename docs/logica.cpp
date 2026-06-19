#include "logica.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

unordered_map <string, string> personas;			//tabla hash
unordered_map <string, producto> lista_productos;	//tabla hash
deque <compra> factura; 							//lista doble enlasada
queue <string> cierre; 								//cola



void cargar_sistema(){
	
	fstream ARCHIVO("inventario.csv", ios::in);
	
	if (!ARCHIVO.is_open()){
		
		cout<<"ERROR: archivo no encontrado"<<endl;
	}else{
		
		string linea;
		while (getline(ARCHIVO, linea)){
			
			stringstream ss(linea);
			string campo;
			int i = 0;
			producto temporal = {"", "", 0, 0};
			bool campo_valido = true;
			
			while (getline(ss, campo, ';')){
	
				try{
					switch(i){
						case 0: temporal.ID = campo; break;
						case 1: temporal.nombre = campo; break;
						case 2: temporal.precio = stoi(campo); break;
						case 3: temporal.cantidad = stoi(campo); break;
					}
				}catch(...){
					
					campo_valido = false;
					cout<<"ERROR: posibles archivos corruptos"<<endl;
					break;
				}
			
				i++;
			}
		
			if(campo_valido){
				lista_productos[temporal.ID] = temporal;
			}
		}
		
		ARCHIVO.close();
		cout<<"PRODUCTOS CARGADOS CORRECTAMENTE!!!"<<endl;
	}
}



void agregar_productos(string ID, string NOMBRE, int PRECIO, int CANTIDAD){
	
	if (lista_productos.find(ID) != lista_productos.end()){
		
		lista_productos[ID].cantidad += CANTIDAD;
		cout<<"EL PRODUCTO YA EXISTIA: su cantidad en stock sera actualizada"<<endl;
		actualizar_inventario();
		return;
	}
	
	producto temporal = {ID, NOMBRE, PRECIO, CANTIDAD};
	lista_productos[ID] = temporal;
	
	ofstream ARCHIVO("inventario.csv", ios::app);
	
	if (!ARCHIVO.is_open()){
		
		cout<<"ERROR: archivo no encontrado"<<endl;
	}else{
		
		ARCHIVO<< ID << ';' << NOMBRE << ';' << PRECIO << ';' << CANTIDAD <<endl;
		
		ARCHIVO.close();
		cout<<"PRODUCTO REGISTRADO CORRECTAMENTE!!!"<<endl;
	};
};



void actualizar_inventario(){
	
	ofstream ARCHIVO("inventario.csv");
	
	if (!ARCHIVO.is_open()){
		
		cout<<"ERROR: archivo no encontrado"<<endl;
	}else{
		
		for (const auto& [clave, valor] : lista_productos){
			
			ARCHIVO<< clave << ';' << valor.nombre << ';' << valor.precio << ';' << valor.cantidad <<endl;
		}
			
		ARCHIVO.close();
		cout<<"PRODUCTOS ACTUALIZADOS!!!"<<endl;
	};
}



void agregar_al_carro(string ID, int CANTIDAD){
	
	auto it = lista_productos.find(ID);
    if (it == lista_productos.end()) {
        cout << "ERROR: El producto con ID " << ID << " no existe." << endl;
        return;
    }
    
    int cantidad = lista_productos[ID].cantidad;
    if (CANTIDAD > cantidad){
    	cout << "ERROR: falta de disponivilidad en stock " << CANTIDAD << " mayor que: " << cantidad <<endl;
    	return;
	}
	
	producto temporal = lista_productos[ID];
	
	bool ya_estaba = false;
	
	for (auto& elemento : factura){
		
		if (elemento.articulo.ID == ID){
			
			ya_estaba = true;
			elemento.cantidad += CANTIDAD;
		}
	};
	
	
	if(!ya_estaba) {factura.push_back({temporal, CANTIDAD});}
};



void finalizar_compra(){
	
	int total = 0;
	fstream FACTURA("factura.txt", ios::out);
	
	if(!FACTURA.is_open()){
		
		cout<<"ERROR NO SE PUDO GENERAR LA FACTURA"<<endl;
	}else{
		
		while (!factura.empty()){
		
			int precio_cantidad = factura.front().articulo.precio * factura.front().cantidad;
			total += precio_cantidad;
			
			FACTURA<< "Producto: " + factura.front().articulo.nombre + "\t|por valor de: " << factura.front().articulo.precio
			<< " X "<< factura.front().cantidad << "\t|sub total: $" << precio_cantidad <<endl;
			
			lista_productos[factura.front().articulo.ID].cantidad -= factura.front().cantidad;
			
			factura.pop_front();
		};
		
		FACTURA<< "total: $" << total;
		
		FACTURA.close();
	};
	
	actualizar_inventario();
	
	FACTURA.open("factura.txt", ios::in);
	
	if(!FACTURA.is_open()){
		
		cout<<"ERROR NO SE PUDO CARGAR LA FACTURA EN EL CIERRE"<<endl;
	}else{
		string linea;
		string facturas_N;
		
		while (getline(FACTURA, linea)){
			
			facturas_N += linea + "\n";
		}
		
		cierre.push(facturas_N);
		FACTURA.close();
	}
}



void realizar_cierre(){
	
	int i = 1;
	int total = 0;
	fstream CIERRE("cierre.txt", ios::out);
	
	if (!CIERRE.is_open()){
		
		cout<<"ERROR NO SE PUDO GENERAR EL CIERRE"<<endl;		
	}else{

		while (!cierre.empty()){
			
			string monto = "";
			
			CIERRE<<"---------------factura ["<<i<<"]--\n";
			CIERRE<<cierre.front();
			
			for(int j = cierre.front().size() - 1; j >= 0; j--){
				
				if (cierre.front()[j] == '$') break;
				
				monto += cierre.front()[j];
			}
			
			try{
				
				reverse(monto.begin(), monto.end());
				total += stoi(monto);
			}catch(...){
				cout<<monto;
			}
			
			i++;
			cierre.pop();
		}
		
		CIERRE<<"--------------- final cierre: [$"<<total<<"]--\n";
	}
}