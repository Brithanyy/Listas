#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///ESTRUCTURAS:
typedef struct{
    char nombre[30];
    int edad;
}stPersona;

typedef struct{
    stPersona persona;
    struct nodo * siguiente; /// --> Direccion de memoria del siguiente NODO
}nodo;

///PROTOTIPADO FUNCIONES:
void cargarArchivoPersonas(stPersona persona, char nombreArchi[20]);
stPersona crearUnaPersona();
void mostrarArchivo(stPersona persona, char nombreArchi[20]);
void mostrarUnaPersona(stPersona persona);
nodo *inicLista();
nodo *crearNodo(stPersona persona);
nodo *agregarAlFinal(nodo *lista, nodo *nodoInsertar);
nodo *insertarPersonasAListas(char nombreArchi[20], nodo *lista);
void mostrarNodos(nodo *lista);
void mostrarUnSoloNodo(nodo *lista);
int buscarDatoLista(nodo *lista, int edad);
nodo *insertarEnOrden(nodo *lista,nodo *nodoInsertar);
nodo *insertarPersonasAListasEnOrden(char nombreArchi[20], nodo *lista);
nodo *insertarPrincipio(nodo *lista, nodo *nodoInsertar);
nodo *buscarUltimoNodo(nodo *lista);
nodo *insertarNodosALista3(nodo *lista1, nodo *lista2, nodo *lista3);
nodo *invertirElementosLista(nodo *lista, nodo *listaNueva);
nodo *agregarPrincipio(nodo *lista, nodo *nodoInsertar);
void borrarTodaLaLista(nodo **lista);

int main(){
    stPersona persona;
    char nombreArchivo[20] = {"personas.bin"};
    char nombreArchivo2[20] = {"personas2.bin"}; ///NOMBRE DE NUESTRO ARCHIVO.
    ///cargarArchivoPersonas(persona,nombreArchivo); Lo comentamos xq ya le cargamos datos
    //mostrarArchivo(persona,nombreArchivo);
    //cargarArchivoPersonas(persona,nombreArchivo2);
    ///Creamos variable Estatica del nodo
    nodo *lista;
    ///INICIALIZAMOS LISTA:
    lista = inicLista();
    /// Le agregamos todas las personas del archivo a los nodos.
    lista = insertarPersonasAListasEnOrden(nombreArchivo,lista);
    ///Mostrando la lista:
    printf("\nMostrando lista 1:\n");
    mostrarNodos(lista);
    ///CREAMOS OTRA LISTA PARA HACER EL PUNTO 2:
    nodo *lista2;
    lista2 = inicLista();
    printf("\n\nMostrando lista 2:\n");
    lista2 = insertarPersonasAListasEnOrden(nombreArchivo2,lista2);
    mostrarNodos(lista2);
///3)Hacer una función que retorne un 1 (uno) o 0 (cero)
///si existe un determinado elemento en una lista dada.
///(considerar caso ordenada y caso desordenada)
    int dato;
    printf("Ingrese la edad a buscar: ");
    fflush(stdin);
    scanf("%i", &dato);
    int resultado = buscarDatoLista(lista2,dato);
    if(resultado == 1) printf("\nEdad Encontrada.\n");
    else printf("\nLo sentimos. Esa edad no se encuentra en el sistema.\n");
///4)Hacer una función que intercale en orden los elementos de dos listas
///ordenadas generando una nueva lista. Se deben redireccionar los
///punteros, no se deben crear nuevos nodos.
    nodo *lista3 = inicLista();
    lista3 = insertarNodosALista3(lista,lista2,lista3);
    printf("\n\nMOSTRANDO LISTA 3\n\n");
    mostrarNodos(lista3);
    printf("\n\n-------------------------------------------------------->\n\n");
///5)Invertir los elementos de una lista redireccionando solamente los
///punteros. (No se deben crear nuevos nodos)
    nodo *listaNueva = inicLista();
    listaNueva = invertirElementosLista(lista3, listaNueva);
    printf("\nMOSTRANDO LISTA NUEVA INVERTIDA:\n");
    mostrarNodos(listaNueva);
    borrarTodaLaLista(&lista3);
    printf("\nMOSTRANDO EL PUNTERO DE LA LISTA 3 = %p\n", lista3);
}
///FUNCIONES

///CARGANDO ARCHIVOS CON PERSONAS:
void cargarArchivoPersonas(stPersona persona, char nombreArchi[20]){
    FILE *punteroArchi = fopen(nombreArchi,"ab"); /// ABRIMOS EL ARCHIVO
    char eleccion = 's';
    if(punteroArchi != NULL){
        while(eleccion == 's'){
            persona = crearUnaPersona();
            fwrite(&persona,sizeof(stPersona),1,punteroArchi); ///AGREGAMOS PERSONAS AL ARCHIVO
            printf("Pulsa 's' si desea cargar otra persona: ");
            fflush(stdin);
            scanf("%c", &eleccion);
            printf("\n");
        }
        fclose(punteroArchi); ///CERRAMOS EL ARCHIVO
    }
}
stPersona crearUnaPersona(){
    stPersona persona;
    printf("Nombre: ");
    fflush(stdin);
    gets(persona.nombre);
    printf("Edad: ");
    fflush(stdin);
    scanf("%i", &persona.edad);
    return persona;
}
///MOSTRAR ARCHIVO PERSONAS:
void mostrarArchivo(stPersona persona, char nombreArchi[20]){
    FILE *punteroArchi = fopen(nombreArchi, "rb"); ///ABRIMOS EL ARCHIVO MODO LECTURA
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&persona,sizeof(stPersona),1,punteroArchi);
            if(!feof(punteroArchi)){
                mostrarUnaPersona(persona);
            }
        }
    }
}
void mostrarUnaPersona(stPersona persona){
    printf("\n------------------------------------->\n");
    printf("Nombre: %s \n", persona.nombre);
    printf("Edad: %i ", persona.edad);
    printf("\n------------------------------------->\n");
}

///Inicializamos LISTA:
nodo *inicLista(){
    return NULL;
}
///Crear nodo
nodo *crearNodo(stPersona persona){
    nodo *aux = (nodo *)malloc(sizeof(nodo));
    aux->persona = persona;
    aux->siguiente = NULL;
    return aux;
}
///BUSCAR ULTIMO NODO.
nodo *buscarUltimoNodo(nodo *lista){
    nodo *aux = lista;
    while(aux != NULL){
        aux = aux->siguiente;
    }
    return aux;
}
///AGREGAR NODO AL FINAL
nodo *agregarAlFinal(nodo *lista, nodo *nodoInsertar){
    nodo *aux = lista;
    if(lista == NULL){
        lista = nodoInsertar; ///Si la lista esta vacia creo el nuevo nodo.
    }else{
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = nodoInsertar;
    }
    return lista;
}

///Insertar datos de archivo a nodos.
nodo *insertarPersonasAListas(char nombreArchi[20], nodo *lista){
    FILE *punteroArchi = fopen(nombreArchi, "rb");
    stPersona persona;
    if(punteroArchi != NULL){
            while(!feof(punteroArchi)){
                fread(&persona,sizeof(stPersona),1,punteroArchi);
                nodo *nodoInsertar = crearNodo(persona);
                if(!feof(punteroArchi)){
                    lista = agregarAlFinal(lista,nodoInsertar);
            }
        }
        fclose(punteroArchi);
    }else printf("\nError al abrir el archivo.\n");
    return lista;
}

///Mostrar datos de una lista
void mostrarNodos(nodo *lista){
    while(lista != NULL){
        mostrarUnSoloNodo(lista);
        lista = lista->siguiente;
    }
}
void mostrarUnSoloNodo(nodo *lista){
    printf("\n--------------------------------------->\n");
    printf("Nombre: %s \n", lista->persona.nombre);
    printf("Edad: %i ", lista->persona.edad);
    printf("\n--------------------------------------->\n");
}

///PUNTO 3
int buscarDatoLista(nodo *lista, int edad){
    int flag = 0;
    nodo *aux = lista;
    while(aux != NULL){
        if(aux->persona.edad == edad){
            flag = 1;
            aux = aux->siguiente;
        }else aux = aux->siguiente;
    }
    return flag;
}


nodo *insertarEnOrden(nodo *lista,nodo *nodoInsertar){
    stPersona auxPersona;
    if(lista == NULL) lista = nodoInsertar;
    else{///Se supone que al menos tiene un nodo
        if(nodoInsertar->persona.edad < lista->persona.edad){
            ///Insertamos al principio
            auxPersona = nodoInsertar->persona;
            nodoInsertar->persona = lista->persona;
            lista->persona = auxPersona;
        }else{ ///Buscamos el lugar correcto donde insertar.
            nodo *ante = lista;
            nodo *sig = lista->siguiente;
            while(sig != NULL && (nodoInsertar->persona.edad > sig->persona.edad)){
                ante = sig;
                sig = sig->siguiente;
            }
            ///CUANDO SALE DEL WHILE ES PORQUE YA ENCONTRO EL LUGAR DONDE INSERTAR
            ///ACA HACEMOS EL CAMBIO
            nodoInsertar->siguiente = sig;
            ante->siguiente = nodoInsertar;
        }
    }
    return lista;
}
///INSERTAR AL LISTA DE ARCHIVO EN ORDEN:
///Insertar datos de archivo a nodos.
nodo *insertarPersonasAListasEnOrden(char nombreArchi[20], nodo *lista){
    FILE *punteroArchi = fopen(nombreArchi, "rb");
    stPersona persona;
    if(punteroArchi != NULL){
            while(!feof(punteroArchi)){
                fread(&persona,sizeof(stPersona),1,punteroArchi);
                nodo *nodoInsertar = crearNodo(persona);
                if(!feof(punteroArchi)){
                    lista = insertarEnOrden(lista,nodoInsertar);
            }
        }
        fclose(punteroArchi);
    }else printf("\nError al abrir el archivo.\n");
    return lista;
}
///INSERTAR AL PRINCIPIO:
nodo *insertarPrincipio(nodo *lista, nodo *nodoInsertar){
    if(lista == NULL) lista = nodoInsertar;
    else{
        nodoInsertar->siguiente = lista;
        lista = nodoInsertar;
    }
    return lista;
}
///PUNTO 4:
nodo *insertarNodosALista3(nodo *lista1, nodo *lista2, nodo *lista3){
///ESTA COMPROBACION LA HACEMOS FUERA DEL WHILE PORQUE LISTA 3 NO TIENE NADA.
///POR ENDE LE ALMACENAMOS UN DATO EN ELLA. NO UTILZIAMOS EL PUNTERO XQ NO TIENE NADA.
    if(lista3 == NULL){
        if(lista1->persona.edad < lista2->persona.edad){
        lista3 = lista1;
        lista1 = lista1->siguiente;
        }else{
        lista3 = lista2;
        lista2 = lista2->siguiente;
        }
    }
    nodo *auxLista3 = lista3;///A AUX LE ALMACENAMOS LISTA 3. QUE YA TIENE UN DATO
    while(lista1 != NULL && lista2 != NULL){
///Aca en el while lo recorremos y vamos comparando en base a edades.
        if(lista1->persona.edad < lista2->persona.edad){
            auxLista3->siguiente = lista1;
            lista1 = lista1->siguiente;
        }else{
            auxLista3->siguiente = lista2;
            lista2 = lista2->siguiente;
            }
        auxLista3 = auxLista3->siguiente; ///Incremetamos el puntero a lista
    }
///SI UNA LISTA ES MAS GRANDE QUE OTRA Y LE QUEDARON NODOS LOS ENLAZAMOS.
    if(lista1 == NULL) auxLista3 = lista2;
    else auxLista3 = lista1;

    return lista3;
}
///Agregar al principio:
nodo *agregarPrincipio(nodo *lista, nodo *nodoInsertar){
    if(lista == NULL) lista = nodoInsertar;
    else{
        nodoInsertar->siguiente = lista;
        lista = nodoInsertar;
    }
    return lista;
}
///PUNTO 5: invertir los elementos de una lista:
nodo *invertirElementosLista(nodo *lista, nodo *listaNueva){
    nodo *aux = lista;
    nodo *nuevoNodo;
    if(listaNueva ==  NULL){
        while(aux != NULL){
            nuevoNodo = crearNodo(aux->persona);
            listaNueva = agregarPrincipio(lista,nuevoNodo);
            aux = aux->siguiente;
        }
    }
    return listaNueva;
}
///Borrar toda la lista Recursiva: con punteros dobles
void borrarTodaLaLista(nodo **lista){
    if(*lista == NULL) printf("\nLista borrada con exito. %p\n", *lista);
    else{
        borrarTodaLaLista(&(*lista)->siguiente);
    }
    free(*lista);
    *lista = NULL;
}








