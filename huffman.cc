#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;



//*************************//
//** VARIABLES GLOBALES **//
//************************//
struct nodo{
	char simbolo[3];
	int probabilidad;
	char bit[100]; // para saber luego como es la palabra
	struct nodo *left;
	struct nodo *right;
	struct nodo *padre;
};
typedef struct nodo *Tnodo; //defino poder llamar a la estructura nodo como un puntero mediante Tnodo
Tnodo p_nodo; //puntero a la estructura nodo
Tnodo lista_ordenada,lista_aux; //con lista_aux recorro lista_ordenada
int num_simbolos=0;



//***************************//
//******** FUNCIONES ********//
//***************************//
void introducir_nodo_arbol(char simbolo[2],int tamanho_simbolo){
	Tnodo p_aux,p_aux2;
	bool introducido = false;
	
	if (p_nodo == NULL){ //Arbol vacio
		p_nodo = new(nodo);
		memcpy(p_nodo->simbolo,simbolo,tamanho_simbolo);
		p_nodo->probabilidad=1;
		p_nodo->right=NULL;
		p_nodo->left=NULL;
	}else { //Arbol con elementos
		p_aux = p_nodo;
		while (introducido == false){
			if (strcmp(simbolo,p_aux->simbolo)== 0){
				p_aux->probabilidad++;
				introducido = true;
				continue;
			}
			if (strcmp(simbolo,p_aux->simbolo)> 0){
				if (p_aux->left!=NULL){
					p_aux = p_aux->left;
					continue;
				}else {
					p_aux2 = new (nodo);
					memcpy(p_aux2->simbolo,simbolo,tamanho_simbolo);
					p_aux2->probabilidad=1;
					p_aux->left=p_aux2;
					p_aux2->padre=p_aux;
					introducido = true;
					continue;
				}
			}
			if (strcmp(simbolo,p_aux->simbolo)< 0){
				if (p_aux->right!=NULL){
					p_aux = p_aux->right;
				}else {
					p_aux2 = new (nodo);
					memcpy(p_aux2->simbolo,simbolo,tamanho_simbolo);
					p_aux2->probabilidad=1;
					p_aux->right=p_aux2;
					p_aux2->padre=p_aux;
					introducido = true;
				}
			}
			
		}
		
		
	}
}

void introducir_nodo_lista(Tnodo nuevo_nodo){
	Tnodo nuevo_nodo_padre;
	
	if (lista_ordenada==NULL) {
		lista_ordenada=nuevo_nodo;
		nuevo_nodo=nuevo_nodo->padre; //si el arbol fuese de un solo nodo daria error!!!
		if (nuevo_nodo->right==lista_ordenada) nuevo_nodo->right=NULL;
		if (nuevo_nodo->left==lista_ordenada) nuevo_nodo->left=NULL;
		lista_ordenada->padre=NULL;
	    lista_aux=lista_ordenada;
	}else {
		lista_aux->right=nuevo_nodo;
		lista_aux->left=nuevo_nodo;
		if (nuevo_nodo->padre!=NULL){ 
			nuevo_nodo_padre=nuevo_nodo->padre;
			nuevo_nodo->padre=lista_aux;
			if (nuevo_nodo_padre->right==nuevo_nodo) nuevo_nodo_padre->right=NULL;
			if (nuevo_nodo_padre->left==nuevo_nodo) nuevo_nodo_padre->left=NULL;
		}else { //cuando sea p_nodo (cabeza del arbol) solo hay que añadirlo al final
			nuevo_nodo->padre=lista_aux;
			p_nodo=NULL; //ya no hay nada en el arbol, para que pare el bucle de la linea 113
		}
		
		lista_aux=lista_aux->left; //tambien se podria hacer right sin ningun problema
		
	}
}

void arbol_a_lista(){
	Tnodo p_aux;
	while (p_nodo!=NULL) { //Mientras el arbol no se queda vacio
		p_aux=p_nodo;
		while ((p_aux->right!=NULL) || (p_aux->left!=NULL)) { //Para llegar a una hoja final
			if (p_aux->right!=NULL) {
				p_aux=p_aux->right;
			}else {
				if (p_aux->left!=NULL) {
					p_aux=p_aux->left;
				}
			}
		}
		introducir_nodo_lista(p_aux);
	}
	
}

void ordenar_lista_mayor_a_menor_probabilidad(int principio){
	int cambio=0;
	Tnodo lista_ordenada_aux,lista_ordenada_aux2;
	
	//"Aislamos" el primer nodo
	if (principio!=1) {
		lista_aux=lista_ordenada->left;
		lista_aux->padre=NULL;
		lista_ordenada->left=NULL;
		lista_ordenada->right=NULL;
		lista_ordenada_aux=lista_ordenada;
		lista_ordenada->padre=NULL;
	}
	
	while (lista_aux!=NULL) {
		cambio=0;
		lista_ordenada_aux=lista_ordenada;
		
		while (cambio==0){
			//con la segunda condicion si llega al ultimo nodo y todavia no se cumplio, se añade al final.
			if ((lista_ordenada_aux->probabilidad<lista_aux->probabilidad) || (lista_ordenada_aux->right==NULL)) {
				if ((lista_ordenada_aux->probabilidad>=lista_aux->probabilidad) && (lista_ordenada_aux->right==NULL)){ //Ultimo nodo de la lista_ordenada, añado al final
					lista_ordenada_aux->right=lista_aux;
					if (principio!=1) lista_ordenada_aux->left=lista_aux;
					lista_aux->padre=lista_ordenada_aux;
					lista_aux=lista_aux->right; //avanzo al nodo del siguiente paso	
					if (lista_aux!=NULL) lista_aux->padre=NULL; //si ya termino esta en NULL y no existe padre
					lista_ordenada_aux->right->right=NULL; //Pongo el final de la lista en NULL
					if (principio!=1) lista_ordenada_aux->left->left=NULL;
				}else {  
					if ((lista_ordenada_aux==lista_ordenada)) { //Primer nodo de la lista_ordenada, se añade al principio de todo
						lista_ordenada=lista_aux;
						lista_aux=lista_aux->right; //avanzo al nodo del siguiente paso
						if (lista_aux!=NULL) lista_aux->padre=NULL; //si ya termino esta en NULL
						lista_ordenada->right=lista_ordenada_aux;
						lista_ordenada->left=lista_ordenada_aux;
						lista_ordenada_aux->padre=lista_ordenada;
						lista_ordenada->padre=NULL;
					}else{//introduzco en el anterior de lista_ordenada_aux
						lista_ordenada_aux2=lista_ordenada_aux;
						lista_ordenada_aux=lista_ordenada_aux->padre;
						if (principio!=1) lista_ordenada_aux->left=lista_aux;
						lista_ordenada_aux->right=lista_aux;
						lista_aux->padre=lista_ordenada_aux;
						lista_aux=lista_aux->right; //avanzo al nodo del siguiente paso
						if (lista_aux!=NULL) lista_aux->padre=NULL; //si ya termino esta en NULL
						lista_ordenada_aux->right->right=lista_ordenada_aux2; //Meto el nuevo nodo en el medio de los 2
						if (principio!=1) lista_ordenada_aux->left->left=lista_ordenada_aux2;
						lista_ordenada_aux2->padre=lista_ordenada_aux->right; 
					}
				}
				cambio=1;
			}else lista_ordenada_aux=lista_ordenada_aux->right;
		}
	}
}

//FUNCION PARA VER POR PANTALLA LA LISTA CON LOS DATOS Y DEPURAR ERRORES
void imprimir_lista(int donde){
	Tnodo recorrer;
	cout << "------LISTA DE SIMBOLOS-----\n";
	cout << "numero simbolos: "<<num_simbolos<<"\n";
	recorrer=lista_ordenada;
	while (recorrer!=NULL) {
		cout<<"simbolo: "<<recorrer->simbolo<<", prob: "<<recorrer->probabilidad<<", palabra: "<<recorrer->bit<<endl;
		if (donde==0) recorrer=recorrer->left;
		if (donde==1) recorrer=recorrer->right;
	}
}



//******************************//
//***** PROGRAMA PRINCIPAL *****/
//******************************//
int main(int argc, char *argv[]){
	ifstream f1;
	char simbolo[3];
	int tamanho_simbolo=0,tamanho=0;
	float probabilidad=0.0,longitud_media=0.0,entropia=0.0;
	Tnodo lista_huffman,nuevo_1,nuevo_0,nuevo;
	
	if (argc==3){
		
		tamanho_simbolo = atoi(argv[2]);
		
		/////////////////////////////////////////////////////////
		/////    LECTURA DEL FICHERO  Y CREACION DEL ARBOL  /////
		/////////////////////////////////////////////////////////
		f1.open(argv[1],ifstream::in);
		while (!f1.eof()) {
			f1.read(simbolo,tamanho_simbolo);
			if (!f1.eof()){ //Asi el ultimo no aparece dos veces (despues del read) :/
				num_simbolos++;
				introducir_nodo_arbol(simbolo,tamanho_simbolo);
			}
		}
		
		f1.close();
		
		
		////////////////////////////////////
		//// ARBOL A LISTA Y ORDENACION ////
		////////////////////////////////////
		if (p_nodo->left!=NULL) {
			arbol_a_lista();
		}else {
			lista_ordenada=p_nodo;
		}
		
		if (lista_ordenada->left!=NULL) {
			ordenar_lista_mayor_a_menor_probabilidad(0);
		}
		
		////////////////////////////////////
		////      CALCULO HUFFMAN      /////
		////////////////////////////////////
		lista_huffman=lista_ordenada;
		while (lista_huffman->left!=NULL) lista_huffman=lista_huffman->left; //Lo ponemos en el ultimo nodo
		if (lista_huffman==lista_ordenada) {
			strcpy((char *)&lista_ordenada->bit,"1");
			tamanho=(strlen((char *)&lista_ordenada->bit)*lista_ordenada->probabilidad);
		}else{
			do {
				
				nuevo_1=lista_huffman;
				lista_huffman=lista_huffman->padre;
				nuevo_0=lista_huffman;
				lista_huffman=lista_huffman->padre;
				lista_huffman->right=NULL; // NO PASA NADA PORQUE EL HIJO QUEDE APUNTANDO AL PADRE??????????
				nuevo=new(nodo);
				memcpy(nuevo->simbolo,"xxx",3);
				nuevo->probabilidad=nuevo_1->probabilidad+nuevo_0->probabilidad;
				nuevo->right=NULL;
				nuevo->left=NULL;
				
				lista_aux=nuevo;
				
				ordenar_lista_mayor_a_menor_probabilidad(1);
				
				if (lista_huffman->right!=NULL) lista_huffman=lista_huffman->right; // En caso de que el nodo nuevo se añada al final de la lista avanzamos al siguiente
				
				nuevo_1->padre=nuevo;
				nuevo_0->padre=nuevo;
				strcpy((char *)&nuevo_1->bit,"1");
				strcpy((char *)&nuevo_0->bit,"0");
			} while ((lista_ordenada->right->right!=NULL));
			
			strcpy((char *)&lista_ordenada->bit,"0");
			strcpy((char *)&lista_ordenada->right->bit,"1");
			lista_aux=lista_ordenada;
			
			lista_ordenada->right->padre=NULL;  //Cuando terminan las iteraciones y solo quedan 2 nodos, el segundo NO debe ser el padre del primero
			
			while (lista_aux!=NULL) {
				if (strcmp(lista_aux->simbolo,"xxx")!=0){
					lista_huffman=lista_aux->padre;
					while (lista_huffman!=NULL) {
						strcat((char *)&lista_aux->bit,(char *)&lista_huffman->bit);
						
						lista_huffman=lista_huffman->padre;
						
					}
					tamanho=tamanho+(strlen((char *)&lista_aux->bit)*lista_aux->probabilidad); //Aqui la probabilidad es el numero de veces que aparece (un entero)
					
				}
				lista_aux=lista_aux->left;
			}
		}
		
		////////////////////////////////////
		////  RESULTADOS POR PANTALLA  /////
		////////////////////////////////////
		lista_huffman=lista_ordenada;
		while (strcmp(lista_huffman->simbolo,"xxx")==0) {
			lista_huffman=lista_huffman->left;
		}
		cout << "///********************TABLA CON EL CODIGO*****************///"<<endl;
		cout << "// SIMBOLO     PROBABILIDAD        PALABRA CODIGO ASIGNADA //"<<endl<<endl;
		while (lista_huffman!=NULL) {
			probabilidad=(float)lista_huffman->probabilidad/num_simbolos; // Aqui la probabilidad es la probabilidad real
			longitud_media=longitud_media+(strlen((char *)&lista_huffman->bit)*probabilidad);
			entropia=entropia+probabilidad*(float)(log10(1/probabilidad));
			cout <<"   "<<hex<<lista_huffman->simbolo<<"           "<<probabilidad<<"               "<<lista_huffman->bit<<endl;
			lista_huffman=lista_huffman->left;
		}
		cout << "///*******************************************************///"<<endl;

		cout << "Longitud del fichero original: "<<num_simbolos*tamanho_simbolo<<" bytes"<<endl;
		cout << "Longitud del fichero comprimido: "<<tamanho<<" bits o "<<(int)ceil(tamanho/8.0)<<" bytes"<<endl;
		cout << "La tasa de compresion es :"<<(float)((ceil(tamanho/8.0))/(num_simbolos*tamanho_simbolo))<<endl;
		cout << "La longitud del codigo es :"<<longitud_media<<endl;
		cout << "La eficiencia es : "<<((entropia/(float)log10(2))/longitud_media)<<endl;
		
	}else{
		cout<<"ERROR: numero de parametros incorrecto"<<endl;
	}
}
