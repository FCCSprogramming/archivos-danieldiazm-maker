#include <iostream>
#include <fstream>

using namespace std;

int main(){
	int n_ver, n_tri; 
    
	string arch_lag = "laguna.txt";
	string arch_area = "area.txt";

	ifstream input_strm;
	ofstream output_strm;
	
	input_strm.open(arch_lag, ios::in);	
	output_strm.open(arch_area, ios::out);
	
	if (!input_strm.good()) {
		cout << "Hay un error al abrir '"
			 << arch_lag << "'" << endl;
		return EXIT_FAILURE;

	}
    if (!output_strm.good()) {
		cout << "Hay un error al abrir '"
			 << arch_area << "'" << endl;
		return EXIT_FAILURE;

	}	
    
	input_strm >> n_tri;
	input_strm >> n_ver;
    
	int i = 0;
    
	float **P_coord = new float*[n_ver];
	int **T_ind = new int*[n_tri];
    
	for (i = 0; i < n_ver; i++)
		P_coord[i] = new float[2];
    
	for (i = 0; i < n_tri; i++)
		T_ind[i] = new int[3]; 	
    
	i = 0;
	while (!input_strm.eof() && (i < n_ver)) {
		input_strm >> P_coord[i][0] >> P_coord[i][1];
		i++;
	}
    
	i = 0;
	while (!input_strm.eof() && (i < n_tri)) {
		input_strm >> T_ind[i][0] >> T_ind[i][1] >> T_ind[i][2];
		i++;
	}
	
	float area_tot = 0;
	for (i = 0; i < n_tri; i++){
		float x1 = P_coord[T_ind[i][0] - 1][0];
		float y1 = P_coord[T_ind[i][0] - 1][1];
		float x2 = P_coord[T_ind[i][1] - 1][0];
		float y2 = P_coord[T_ind[i][1] - 1][1];
		float x3 = P_coord[T_ind[i][2] - 1][0];
		float y3 = P_coord[T_ind[i][2] - 1][1];
		area_tot += 0.5 * abs(x1 * (y3 - y2) + x2 * (y1 - y3) + x3 * (y2 - y1));
	}
    
	output_strm << area_tot;	
    
	input_strm.close();	
	output_strm.close();
	
	for (i = 0; i < n_ver; i++)
		delete[] P_coord[i];
	
	for (i = 0; i < n_tri; i++)
		delete[] T_ind[i];	
	
	delete[] T_ind;	
	delete[] P_coord;	
    
    return 0;
}