#include <iostream>
#include <fstream>
using namespace std;

void escribirFibonacciBinario(){
	ofstream out_fch("D:/fibonacci.bin", ios::binary); 
    
	int trm1 = 0;
	int trm2 = 1;
    
	for (int i = 0; i < 20; i++) {
		out_fch.write(reinterpret_cast<char*>(&trm1), sizeof(int));
        
		int siguiente_trm = trm1 + trm2; 
        
		trm1 = trm2;
		trm2 = siguiente_trm;
	}
	out_fch.close();
	cout << "Funcion escribirFibonacciBinario:\n";
	cout << "Terminos de Fibonacci escritos en el archivo correctamente.\n" << endl;
}

void leerFibonacciBinario() {
	cout << "Funcion leerFibonacciBinario:\n";
	ifstream in_fch("D:/fibonacci.bin", ios::binary);
    
	int trm_val; 
	int cnt = 1; 
    
	while (in_fch.read(reinterpret_cast<char*>(&trm_val), sizeof(int))) {
		cout << "Termino " << cnt << ": " << trm_val << endl;
		cnt++;
	}
	in_fch.close();
}

int main() {
    escribirFibonacciBinario();
    leerFibonacciBinario();
    return 0;
}
