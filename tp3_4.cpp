#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Producto{
    int productoID;
    int cantidad;
    char *tipoProd;
    float precioUnitario;
} Prod;

typedef struct Cliente{
    int clienteID;
    char *nombre;
    int CantProdsAPedir;
    Prod *productos;
} cliente;

void cargarClientes(cliente *array, int tamanio);
void cargarProductos(Prod *array, int tamanio);
int costoProd(Prod producto);
void mostrar(cliente *array, int tamanio);
int mostrarProductos(Prod producto);

char *tiposProd[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

int main(){
    srand(time(NULL));

    int cantClientes;
    cliente *personas;

    //Apartado 1
    
    do{
        printf("Ingrese la cantidad de clientes (max 5 clientes): \n");
        scanf("%d", &cantClientes);
    }while(cantClientes > 5);


    personas = (cliente*)malloc(sizeof(cliente)*cantClientes);

    cargarClientes(personas, cantClientes);

    mostrar(personas, cantClientes);

    for(int i = 0; i <cantClientes; i++){
        free((personas + i)->nombre);

        for(int j = 0; j < (personas + i)->CantProdsAPedir; j++){
            free(((personas + i)->productos) + j);
        }
    }
    free(personas);

    return 0;
}

void cargarClientes(cliente *array, int tamanio)
{
    for(int i = 0; i < tamanio; i++){
        (array + i)->clienteID = (i+1);
        
        fflush(stdin);
        printf("Ingrese el nombre del cliente %d\n", i+1);
        (array + i)->nombre = (char*)malloc(sizeof(char)*30);
        gets((array +i)->nombre);

        (array + i)->CantProdsAPedir = rand()% 5 + 1;

        (array + i)->productos = (Prod*)malloc(sizeof(Prod)*(array->CantProdsAPedir));

        cargarProductos((array + i)->productos, (array + i)->CantProdsAPedir);
    }
}

void cargarProductos(Prod *array, int tamanio)
{
    for(int i = 0; i < tamanio; i++){
        int ProdAleatorio;

        (array + i)->productoID = i + 1;

        (array + i)->cantidad = rand()% 10 + 1;

        //(array + i)->tipoProd = (char*)malloc(sizeof(char)*13);
        ProdAleatorio = rand()% 4;
        (array + i)->tipoProd = tiposProd[ProdAleatorio];

        (array + i)->precioUnitario = (float)(rand()% 910 + 1000) /10;

    }
}

int costoProd(Prod producto){
    return producto.cantidad * producto.precioUnitario;
}

void mostrar(cliente *array, int tamanio)
{
    float suma;

    for(int i = 0; i < tamanio; i++){
        suma = 0;
        printf("\n----- CLiente %d -----\n", (array + i)->clienteID);
        printf("ID: %d \n", (array + i)->clienteID);
        printf("Nombre: %s\n", (array + i)->nombre);
        printf("Cantidad de Productos a pedir: %d \n", (array + i)->CantProdsAPedir);
        printf("\n---- PRODUCTOS ----\n");
        for(int j = 0; j < (array + i)->CantProdsAPedir; j++){
            suma += mostrarProductos(*((array + i)->productos + j));
        }
        printf("El cliente debe pagar $%.2f", suma);
    }
}

int mostrarProductos(Prod producto)
{
    printf("ID: %d \n", producto.productoID);
    printf("Cantidad: %d\n", producto.cantidad);
    printf("Tipo: %s \n", producto.tipoProd);
    printf("Precio Unitario: %.2f\n", producto.precioUnitario);

    return costoProd(producto);
}