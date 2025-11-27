#include <stdio.h>
#include <iostream>
using namespace std;

const int MAX_TERM = 10;

class Polinomio
{
private :
    struct Trm
    {
        int coef;
        int exp;
    } term_arr[ MAX_TERM ];
    
    int n_trms;
    
public :
    Polinomio( ) ;
    void add_trm (int c, int e ) ;
    void sum_pol (Polinomio &p_add1, Polinomio &p_add2 ) ;
    void mult_pol (Polinomio &p_mult1, Polinomio &p_mult2 ) ;
    void show( ) ;
};

Polinomio :: Polinomio( )
{
	n_trms = 0 ;
	for (int i = 0 ; i < MAX_TERM;i++ )
	{
		term_arr[i].coef = 0 ;
		term_arr[i].exp = 0 ;
	}
}

void Polinomio :: add_trm ( int c, int e )
{
	term_arr[n_trms].coef = c ;
	term_arr[n_trms].exp = e ;
	n_trms ++ ;
}

void Polinomio :: show( )
{
	int ind_cst = 0 ;
	for (int i = 0 ; i < n_trms ; i++ )
	{
		if (term_arr[i].exp != 0 )
			cout << term_arr[ i ].coef << "x^" << term_arr[ i ].exp << "+";
		else
		{
			cout << term_arr[i].coef ;
			ind_cst = 1 ;
		}
	}
	if ( !ind_cst )
		cout << "\b\b " ;
}

void Polinomio :: sum_pol ( Polinomio &p_add1, Polinomio &p_add2 )
{
	int coef_res, exp_res;
	Polinomio p_temp ;
    
	int c1 = p_add1.n_trms ;
	int c2 = p_add2.n_trms ;
	
	for (int i = 0, j = 0 ; i <= c1 || j <= c2 ; )
	{
		if (p_add1.term_arr[i].coef == 0 && p_add2.term_arr[j].coef == 0 )
			break ;
        
		if (p_add1.term_arr[i].exp >= p_add2.term_arr[ j ].exp )
		{
			if (p_add1.term_arr[i].exp == p_add2.term_arr[j].exp )
			{
				coef_res = p_add1.term_arr[i].coef + p_add2.term_arr[j].coef ;
				exp_res = p_add1.term_arr[i].exp ;
				i++ ;
				j++ ;
			}
			else
			{
				coef_res = p_add1.term_arr[i].coef ;
				exp_res = p_add1.term_arr[i].exp ;
				i++ ;
			}
		}
		else
		{
			coef_res = p_add2.term_arr[j].coef ;
			exp_res = p_add2.term_arr[j].exp ;
			j++ ;
		}
		p_temp.add_trm ( coef_res, exp_res ) ;
	}
	*this = p_temp ;
}

void Polinomio :: mult_pol ( Polinomio &p_mult1, Polinomio &p_mult2 )
{
	int coef_res, exp_res ;
	Polinomio p_prod_parcial, p_res_acum ;
    
	if (p_mult1.n_trms != 0 && p_mult2.n_trms != 0 )
	{
		for (int i = 0 ; i < p_mult1.n_trms ; i++ )
		{
			Polinomio p_temp_mult ;
            
			for ( int j = 0 ; j < p_mult2.n_trms ; j++ )
			{
				coef_res = p_mult1.term_arr[i].coef * p_mult2.term_arr[j].coef ;
				exp_res = p_mult1.term_arr[i].exp + p_mult2.term_arr[j].exp ;
				p_temp_mult.add_trm ( coef_res, exp_res ) ;
			}
            
			if ( i != 0 )
			{
				p_prod_parcial.sum_pol ( p_res_acum, p_temp_mult ) ;
				p_res_acum = p_prod_parcial ;
			}
			else
				p_res_acum = p_temp_mult ;
		}
		*this = p_res_acum;
	}
}

int main( )
{
	Polinomio p1 ;
	p1.add_trm ( 1, 4 );
	p1.add_trm ( 2, 3 );
	p1.add_trm ( 2, 2 );
	p1.add_trm ( 2, 1 );
	
	Polinomio p2 ;
	p2.add_trm ( 2, 3 );
	p2.add_trm ( 3, 2 );
	p2.add_trm ( 4, 1 );
    
	Polinomio p_res ;
	p_res.mult_pol( p1, p2 ) ;
    
	cout << endl << "Primer polinomio: " << endl ;
	p1.show( ) ;
	cout << endl << "Segundo polinomio: " << endl ;
	p2.show( ) ;
	cout << endl << "Polinomio resultante: " << endl ;
	p_res.show( ) ;
    
	return 0 ;
}