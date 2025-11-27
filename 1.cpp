#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Estructura para la fecha (Fecha)
struct T_FCH {
	int dia_fch, mes_fch;
};

// Estructura para la carga del bus (BusCarga)
struct T_CRG {
	int num_pas; // Número de Pasajeros
	T_FCH* fch_ptr; // Puntero a la fecha
};

int main(){
    // Arreglo de carga diaria por 360 días
	int carga_dia[360];
    
    // Inicialización de la carga diaria
	for (int i = 0; i < 360; i++){	
		carga_dia[i] = 500 + rand() % 201 ;	
	}

    // 1. Calcular carga máxima (CargaMax)
	int carga_max = 0;
	for (int i = 0; i < 360; i++){	
		if (carga_max < carga_dia[i]) carga_max = carga_dia[i];
	}

    // 2. Contar días de alta carga (NumAltaCarga)
	int num_alta_carga = 0;
	int min_carga_req = 0.95 * carga_max; // Mínimo de carga requerido (95%)
	
	for (int i = 0; i < 360; i++){	
		if (min_carga_req <= carga_dia[i]) num_alta_carga++;
	}
    
    // Imprimir el resumen inicial
	cout << "Se encontraron " << num_alta_carga << " dias con carga minima de "
	     << min_carga_req << " pasajeros" << endl;
    
    // 3. Crear y llenar la lista dinámica (ListaAltaCarga)
	T_CRG *lista_alta_carga = new T_CRG[num_alta_carga];
	int indice_lista = 0; // K
	
	for (int i = 0; i < 360; i++){	
		if (min_carga_req <= carga_dia[i]){
			T_FCH *fch_ptr = new T_FCH; // Puntero a Fecha
			
			// Cálculo de fecha
			fch_ptr->mes_fch = 1 + i / 30;
			fch_ptr->dia_fch = 1 + i - (fch_ptr->mes_fch - 1) * 30;
			
			lista_alta_carga[indice_lista].fch_ptr = fch_ptr;
			lista_alta_carga[indice_lista].num_pas = carga_dia[i];
			indice_lista++;
		}	
	} 	
    
    // 4. Imprimir la lista con formato (usando iomanip)
	for (int i = 0; i < num_alta_carga; i++){
		cout << setw(6) << lista_alta_carga[i].fch_ptr->dia_fch 
             << "/" 
             << setw(2) << lista_alta_carga[i].fch_ptr->mes_fch 
             << " : " 
             << setw(5) << lista_alta_carga[i].num_pas 
             << " pasajeros" << endl;
	}
    
    // 5. Liberación de memoria
    for (int i = 0; i < num_alta_carga; i++){
        delete lista_alta_carga[i].fch_ptr;
    }
    delete[] lista_alta_carga;

    return 0;
}

