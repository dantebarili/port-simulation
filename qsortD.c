#include <stdio.h>

#define TOLOWER(x) ( ((x) >= 'A' && (x) <= 'Z')  ? (x) + 'a' - 'A' : (x) )

typedef struct {
	char nombre[20];
	char apellido[20];
	float nota;
} alumno_t;

void swap_gen(void *pv1, void *pv2, size_t size);
void qsortD(void *base, size_t elem, size_t size, int (*compar) (const void*, const void*));
int comparAlu(const void* p1, const void* p2);
void print_alu(alumno_t * palu);
int comparNum(const void*, const void*);


int main(void){
	
	//prueba
	int arrNum[10]={1,10,3,5,6,8,2,7,9,4};
	
	alumno_t arralu[5] = {
	{"Dante" , "Pepito" , 1.0},
	{"Juan" , "Barili" , 7.0},
	{"Anastasio" , "Barili" , 7.0},
	{"Juan" , " " , 10.0},
	{"Juan" , "Baril" , 10.0}
	};
	
	printf("\nInstancia 1: ");
	print_alu(&arralu[0]);
	printf("\nInstancia 2: ");
	print_alu(&arralu[1]);	
	printf("\nInstancia 3: ");
	print_alu(&arralu[2]);	
	printf("\nInstancia 4: ");
	print_alu(&arralu[3]);
	printf("\nInstancia 5: ");
	print_alu(&arralu[4]);

	qsortD(arralu, sizeof(arralu)/sizeof(arralu[0]), sizeof(arralu[0]), comparAlu);
	

	printf("\n\nArreglo ordenado:\n");
	printf("\nInstancia 1: ");
	print_alu(&arralu[0]);
	printf("\nInstancia 2: ");
	print_alu(&arralu[1]);	
	printf("\nInstancia 3: ");
	print_alu(&arralu[2]);
	printf("\nInstancia 4: ");
	print_alu(&arralu[3]);
	printf("\nInstancia 5: ");
	print_alu(&arralu[4]);
	
	qsortD(arrNum, sizeof(arrNum)/sizeof(arrNum[0]), sizeof(arrNum[0]), &comparNum);
	
	printf("\n\nArreglo num ordenado:\n");
	for(int x=0; x<10; x++){
	
		printf("%d, ",arrNum[x]);
	
	}
	
	return 0;
}

void swap_gen(void *pv1, void *pv2, size_t size){

	// copio byte a byte de memoria segun size del dato
	char* p1 = (char*)pv1;
	char* p2 = (char*)pv2;
	
	char temp[size];
	
	for(size_t i=0; i<size; i++){	// guardo
		temp[i] = *(p1+i);
	}
	
	for(size_t i=0; i<size; i++){	// guardo
		*(p1+i) = *(p2+i);
	}
	
	for(size_t i=0; i<size; i++){	// guardo
		*(p2+i) = temp[i];
	}

}

void qsortD(void *base, size_t elem, size_t size, int (*compar) (const void*, const void*)){
	
	int mov;
	char* p1;	// apunta al primer char del primer elemento
	char* p2;		// apunta al primer char del segundo elemento
	
	do{
		mov = 0;
		p1 = (char*)base;	// apunta al primer char del primer elemento
		p2 = p1+size;		// apunta al primer char del segundo elemento
		
		for(size_t i=0;i<elem-1;i++){			//iterador de elemento para saber cuando terminar bubblesort
			
			int rta = (*compar)((const void*)p1, (const void*)p2);
			
			if (rta > 0){
			
				swap_gen((void*)p1, (void*)p2, size);
				mov++;
				// si el elem1 es mayor lo mueve a la derecha y continua bubble
				// si elem 2 es mayor (devuelve negativo) sigue con bubble, orden correcto entre e1 y e2
				
			}
			
			// me muevo al proximo par de elementos
			p1 = p1 + size;		
			p2 = p2 + size;
			
		}	
		
	}while(mov!=0);

}

int comparAlu(const void* p1,const void* p2){	// compara struct alumno_t
	
	alumno_t * palu1 = (alumno_t*)p1;
	alumno_t * palu2 = (alumno_t*)p2;
	
	if (palu1->nota > palu2->nota){
		return -1;
	}else if(palu1->nota < palu2->nota){
		return 1;
	}else{
		
		for(int i=0; i<20; i++){	//por apellido
			
			char l1 = TOLOWER(palu1->apellido[i]);
			char l2 = TOLOWER(palu2->apellido[i]);
			
			if( (l1 > l2) ){
				
				return 1;			
			
			} else if ( (l1 < l2) ){
			
				return -1;
			
			} 
			
		}	
		//por nombre
				
		for (int j=0; j<20; j++){
					
			char l1 = TOLOWER(palu1->nombre[j]);
			char l2 = TOLOWER(palu2->nombre[j]);
				
			if( (l1 > l2) || (l1 == '\0') ){
					
				return 1;
							
			} else if ( (l1 < l2) || (l2 == '\0') ){
			
				return -1;
				
			} 
						
		}
							
		return 0;
		
	}
}



//prueba qsortD
int comparNum(const void* p1, const void* p2){

	return ( *((int*)p1) - *((int*)p2) );	//orden num ascendente

}

//muestra
void print_alu(alumno_t * palu){
	
	printf("\n");
	printf("Nombre: ");
	for(int i=0; i<20; i++){	
		printf("%c",palu->nombre[i]);
	}
	
	printf("\n");
	printf("Apellido: ");
	for(int i=0; i<20; i++){	
		printf("%c",palu->apellido[i]);
	}
	
	printf("\n");
	printf("Nota: ");
	printf("%f",palu->nota);
	printf("\n");

}
