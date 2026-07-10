#include <windows.h>
#include <commctrl.h>
#include <string>
#include "logica.h"

using namespace std;

HWND boton_agregar, campo1, campo2, campo3, campo4;


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_CREATE: {
			
			//boton 1 "agregar producto" con ID 1:
			boton_agregar = CreateWindowEx(
			
			0,											//estilo funcion
			"BUTTON",									//tipo
			"cargar producto",							//texto
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,	//estilos visuales
			40, 50,										//pocision X e Y
			150,25,										//ancho y alto
			hwnd,										//ventana padre
			(HMENU)1,									//identificador ID
			GetModuleHandle(NULL),						//instancia
			NULL
			
			);
			
			//recortes del boton 1:
			HRGN recortes = CreateRoundRectRgn(0, 0, 150, 25, 25, 25); //X, Y, ancho, alto, Elipse ancho, Elipse alto
			SetWindowRgn(boton_agregar, recortes, TRUE); //aplicar
			
			//campo 1 "ID" con ID 2:
			campo1 = CreateWindowEx(
			
			WS_EX_CLIENTEDGE,							//estilo funcion
			"EDIT",										//tipo
			"",											//texto
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_NUMBER,		//estilos visuales
			40, 80,										//pocision X e Y
			150,25,										//ancho y alto
			hwnd,										//ventana padre
			(HMENU)2,									//identificador ID
			GetModuleHandle(NULL),						//instancia
			NULL
			
			);
			
			//texto de guia para el campo 1:
			SendMessage(campo1, EM_SETCUEBANNER, TRUE, (LPARAM)L"ID");
			
			//campo 2 "nombre" con ID 3:
			campo2 = CreateWindowEx(
			
			WS_EX_CLIENTEDGE,							//estilo funcion
			"EDIT",										//tipo
			"",											//texto
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,		//estilos visuales
			40, 110,									//pocision X e Y
			150,25,										//ancho y alto
			hwnd,										//ventana padre
			(HMENU)3,									//identificador ID
			GetModuleHandle(NULL),						//instancia
			NULL
			
			);
			
			//texto de guia para el campo 2:
			SendMessage(campo2, EM_SETCUEBANNER, TRUE, (LPARAM)L"Nombre");
			
			//campo 3 "precio" con ID 4:
			campo3 = CreateWindowEx(
			
			WS_EX_CLIENTEDGE,							//estilo funcion
			"EDIT",										//tipo
			"",											//texto
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_NUMBER,		//estilos visuales
			40, 140,									//pocision X e Y
			150,25,										//ancho y alto
			hwnd,										//ventana padre
			(HMENU)4,									//identificador ID
			GetModuleHandle(NULL),						//instancia
			NULL
			
			);
			
			//texto de guia para el campo 3:
			SendMessage(campo3, EM_SETCUEBANNER, TRUE, (LPARAM)L"Precio");
			
			//campo 4 "cantidad" con ID 5:
			campo4 = CreateWindowEx(
			
			WS_EX_CLIENTEDGE,							//estilo funcion
			"EDIT",										//tipo
			"",											//texto
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_NUMBER,		//estilos visuales
			40, 170,									//pocision X e Y
			150,25,										//ancho y alto
			hwnd,										//ventana padre
			(HMENU)5,									//identificador ID
			GetModuleHandle(NULL),						//instancia
			NULL
			
			);
			
			//texto de guia para el campo 4:
			SendMessage(campo4, EM_SETCUEBANNER, TRUE, (LPARAM)L"Cantidad");
			
			break;
		}
		
		case WM_COMMAND: {
			
			//deteccion del boton con ID 1, agregar porducto
			if (LOWORD(wParam) == 1){
                
                char id[8], nombre[60], precio[60], cantidad[60]; 			//variables para guardar las cadenas
                string ID, NOMBRE, PRECIO, CANTIDAD, mensaje;
                
                GetWindowText(campo1, id, sizeof(id));				//guardando el id
                GetWindowText(campo2, nombre, sizeof(nombre));		//guardando el nombre
                GetWindowText(campo3, precio, sizeof(precio));		//guardando el precio
                GetWindowText(campo4, cantidad, sizeof(cantidad));	//guardando la cantidad
                
                ID = id; NOMBRE = nombre; PRECIO = precio; CANTIDAD = cantidad;	//transformando los valores de cadenas char a string
                
                mensaje = "producto cargado: \nID: " + ID + "\nnombre: " + NOMBRE + "\nprecio: " + PRECIO + "\ncantidad: " + CANTIDAD;
                
                //mensaje
                
                MessageBox(hwnd, mensaje.c_str(), "Aviso", MB_OK);
                
                //restaurando los valores de los campos...
            	SetWindowText(campo1, "");
     			SetWindowText(campo2, "");
       			SetWindowText(campo3, "");
       			SetWindowText(campo4, "");
       			
       			
       			try{
       				
       				agregar_productos(ID, NOMBRE, stoi(PRECIO), stoi(CANTIDAD));
				}catch(...){
				   	
				   	MessageBox(hwnd, "no se que paso", "ERROR", MB_OK);
				   }
       			
            }
			
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	InitCommonControls();
	
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
