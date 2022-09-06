/*
 ============================================================================
 Name        : TP 1.c
 Author      : Comparada, Francisco. Cisana, Joaquin. Dimaio, Bruno.
 Version     : Final
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

#define G printf("├───────────────────────┼───────────────────────────────────────────────────────────────────────┤\n");
#define G1 printf("└───────────────────────┴───────────────────────────────────────────────────────────────────────┘\n");
#define G2 printf("┌───────────────────────┬───────────────────────────────────────────────────────────────────────┐\n");

typedef struct Matrix{//estructura para definir la matriz

	int F;//las filas de la matris van a ser las variables aleatorias como Sb, Sa y el tiempo.
	int C;//las columnas de la matris van a ser la cantidad de eventos a simular.
	int **values;//es el puntero con doble intdireccion para crear los espacio a la las filas y las columas
}matriz;

int validar_numero(char num[]){
/*La funcion validar numero toma lo ingresado por teclado y se asegura de que solamente sea un numero entero positivo*/
    int i;
    for(i=0; i<strlen(num); i++){//desde i=0 hasta la longitud de la cadena especificada (num) en bytes, a excepción del byte nulo final.
        if(!(isdigit(num[i]))){/*isdigit es una macro que verifica el entero c pertenece al rango caracteres de digitos decimales, que
        depende de la categoría local LC_CTYPE, por defecto, el rango es de ('0' a '9'). Si lo ingresado por tecaldo  y puesto en num, no es un
        digito de 0-9 entonces pide que se vuelva a ingresar otro valor nuevamente*/
            printf("Debe ingresar un numero entero positivo. Pruebe con otro.\n");
            return 0;
        }
    }
    return 1;
}

int MENU(int n){
/*La funcion Menu pide por pantalla y devuelve a la funcion main la cantidad de eventos a simular*/
	int si=0,no=0;
	char eventos[5];
	char cadena[2];
	int numvalido,N=0;
	printf ("Si desea realizar una simulacion ingrese la palabra \"si\".\nSi desea finalizar la ejecucion del programa ingrese la palabra \"no\".\n");
	scanf ("%s",cadena);
	printf ("\n");
	if (strcmp (cadena,"si")==0)
		si=1;
	if (strcmp (cadena,"no")==0)
		no=1;

	while(si==0&&no==0){//validacion de que los datos ingresados por el el teclado sean unicamente las opciones si o no
			printf ("Por favor, ingrese \"si\" o \"no\". Procure que sea en minusculas. \n");
			scanf ("%s",cadena);
			printf ("\n");
			if(strcmp (cadena,"si")==0)
				si=1;
			if (strcmp (cadena,"no")==0)
				no=1;
			}
	if (si==1){
		printf("Ingrese la cantidad de eventos que quiera simular:\n");
	    while(N==0){//validacion de que el numero de eventos a sumular sea mayor a cero y no sea una letra
	    	scanf ("%s",eventos);
	    	printf ("\n");
		    N=validar_numero(eventos);//llama a la funcuin para validar lo ingresado por teclado
	    }
	    numvalido=atoi(eventos);
	    n=numvalido;
	}
    else{
    	n=-1;
    }
	return n;
}

void imprimeMatriz(matriz *myMatrix){
//Esta subrutina muestra la matriz de los eventos por pantalla
	int n,m;
	printf("Matriz de eventos.\n\n");
	printf("\t\t┌");
	for(n = 0; n < myMatrix->C; n++){
		printf("  ");
	}
	printf(" ┐\n");
    for(n = 0; n < myMatrix->F; n++){
    	if(n==0){
    		printf("Sensor_arriba\t│ ");
    	}
    	if(n==1){
    	    printf("Sensor_base\t│ ");
    	}
    	if(n==2){
    	    printf("Tiempo\t\t│ ");
    	}
    	for(m = 0; m < myMatrix->C; m++){
    		if (m!=(myMatrix->C)-1){
    			printf("%d ", myMatrix->values[n][m]);
    		}
    		else{
    			printf("%d │", myMatrix->values[n][m]);
    		}
        }
        printf("\n");
    }
    printf("\t\t└");
    	for(n = 0; n < myMatrix->C; n++){
    		printf("  ");
    	}
    	printf(" ┘\n");
    printf("\n");
    return;
}

void lugar(matriz *matrix, int m ){
/* En la subrrutina Lugar se reserva el espacio que va a ocupar la matriz (segun la cantidad de eventos pedidos para la simulacion).
Dichos espacios reservados querdaron reservados con ceros*/
	int i;
		// Alojar filas.
		matrix->F=3;
		matrix->C=m;
		matrix->values = (int**) calloc(3,sizeof(int*));//reservo el epacio para la cantidad de filas
		// Alojar columnas.
	    for(i=0;i<matrix->F;i++)
	        matrix->values[i]=(int*) calloc(m,sizeof(int));//reservo el espacio para la cantidad de columnas

}

void LlenaMatriz(matriz *mimatrix){
/*En la subrutina Llena Matriz le llega el puntero al registro, en el cual, se encuentra el puntero a la matriz completada anteriormente
con ceros y lo llena con valores "al alzar" de 0 y 1*/
	int n,m,value,k=0;

	for(n=0;n<mimatrix->F;n++){
        for(m=1;m<mimatrix->C;m++){
            value=rand() % 2;
            mimatrix->values[n][m]=value;
        }
    }
	while ((((mimatrix->values[0][k])==0)&&((mimatrix->values[1][k])==0))||(((mimatrix->values[0][k])==1)&&((mimatrix->values[1][k])==1))){
	    /*La variable Tiempo nos indica que transcurrieron dos minutos desde que alguno de los dos motores se haya encendido. Entendemos que
	    no tiene sentido que aparezca un uno en la variable Tiempo antes de que aparezca algún evento relevante para nuestro sistema que
	    encienda un motor. Por esta razón, limitamos de alguna forma dicha variable para que se imposibilite el suceso que mencionamos
	    anteriormente. Asi, usamos la siguiente sentencia "while"*/
		mimatrix->values[2][k+1] = 0;
		k++;
	}
}

void eventos (matriz *matrix){
/*la subrutina eventos recibe el puntero al registro, en el cual, se encuentra el puntero a la matriz completada anteriormente
con ceros y unos. La funcion debe leer toda la matriz y mostrar los distintos menasajes por pantalla segun se la combinaciond de 0 y 1 aleatorios*/
	int j,ma=0,mb=0;
	int p=0;
	//inicialmente todos los motores y la variable de control "p" estan en 0

	printf("Tabla de eventos.\n");

	G2;
	printf("│\tN° de evento\t│\tAccion\t\t\t\t\tEstado de los motores\t│\n");
	G;

	for(j=0;j<matrix->C-1;j++){
		if (p==0){//si el motor esta parado
			if ((matrix->values[0][j])!=(matrix->values[1][j])){/*si los valore de Sb y Sa son distintos (estando el motor apagado) se enciende
			el motor*/
				p=1;
				j=j+1;
				((matrix->values[0][j])==1)?printf("│\tEvento %d\t│\tSensor_base DETECTADO \t\t\tMotor_arriba ACTIVO.\t│\n",j)&&(ma=1):printf("│\tEvento %d\t│\tSensor_arriba DETECTADO \t\tMotor_abajo ACTIVO.\t│\n",j)&&(mb=1);//muestra por pantalla que motor esta prendido
				G;
			}
			else {
				printf("│\tEvento %d \t│\tNo modifica estado del motor.\t\t\t\t\t│\n",j+1);/*si el valor de Sb o Sa son iguales,muestra
				por pantalla que no habra algun cambio.Puede ser el caso que no se detectara nada en ambos sensores o que se detectaran al
				mismo tiempo que dos personas llegaran a la escalera, desestimando asi el evento*/
				G;
			}
		}
		if (p==1){/*si el motor Ma o Mb se encuentra en marcha, por algun sensore Sb o Sa, este seguira asi hasta que se encuentre por delante un 1
		en la tercera fila, simulando asi el paso de dos minutos*/
			if (matrix->values[2][j]==1){//Si en en la tercera fila (variable t) se encuentra un 1
				printf("│\tEvento %d\t│\tPasaron 2 minutos",j+1);
				if (ma==1){//si el motor hacia arriba se encontraba encendido muestra lo siguiente
					printf("\t\t\tMotor_arriba APAGADO.\t│\n");
					G;
					ma=0;
					p=0;
				}
				if (mb==1){//si el motor hacia abajo se encontraba encendido muestra lo siguiente
					printf("\t\t\tMotor_abajo APAGADO.\t│\n");
					G;
					mb=0;
					p=0;
				}
			}
			else {/*si la variable t del evento formado por la columna,se encuentra un 0, entonces descarta el evento y sigue a la siguiente
			columna (seguira buscando hasta que no haya un 1)*/
				printf("│\tEvento %d \t│\tNo modifica estado del motor.\t\t\t\t\t│\n",j+1);
				G;
			}
		}
	}
	if(p==1){/*si se llega al ultimo evento y justo se activa el motor, por siguiente, se lo dejara acturar por dos minutos mas y finalizara
	la simulacion*/
		printf("│\tEvento %d\t│\tPasaron 2 minutos",j+1);
		if (ma==1){
			printf("\t\t\tMotor_arriba APAGADO.\t│\n");
			G1;
			ma=0;
			}
		if (mb==1){
			printf("\t\t\tMotor_abajo APAGADO.\t│\n");
			G1;
			mb=0;
			}
	}
	if(p==0) {
		printf("│\tEvento %d\t│\tNo modifica estado del motor.\t\t\t\t\t│\n",j+1);
		G1;
	}
	printf("\n─────────────────────────────────────── Fin de simulacion ───────────────────────────────────────\n\n\n");
}

void Libera(matriz *matrix){
	int i;
		for (i=0;i<3;i++){
			free(matrix->values[i]);//libero el puntero a las columnas
		}
	free(matrix->values);//libero el puntero a las filas
	free(matrix);//libero el puntero al registro
	/*if(matrix != NULL)
    {
        //get input from the user
        for(i = 0; i < 3; i++)
              printf("%d \n", matrix->values[i]);
    }

	*/
}

int main(void)
{
	int n=0;
	setbuf(stdout,0);
	n=MENU(n);
		while (n!=-1)
		{
			matriz *pm=(matriz*)malloc(sizeof(matriz));
			srand(time(NULL)); /* seeds random function */
			if( pm==NULL){
				printf("No se pudo reservar memoria para el arreglo");
				return -1;
			}
			lugar(pm,n);
			LlenaMatriz(pm);
			imprimeMatriz(pm);
			eventos(pm);
			Libera(pm);
			n=MENU(n);//vuelve a pedir el menu a menos que se desee finaliar la simulacion, poniendo en n=-1
		}
	printf("¡Programa finalizado!\n");
	return EXIT_SUCCESS;
}
