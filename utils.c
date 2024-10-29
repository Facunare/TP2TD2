#include "utils.h"

// strLen devuelve la longitud total de una cadena de caracteres
int strLen(char* src) {
	int contador = 0;
	
	while(src[contador]!=NULL){
		contador++;
	}

    return contador;
}

// strDup genera una copia del string pasado por parametro
char* strDup(char* src) {

	char* copia = (char*)malloc((sizeof(char))*(strLen(src)+1)); 
	
	// copia caracter por caracter
	for (int i=0; i<strLen(src); i++){
		copia[i]=src[i];
	}
	
	copia[strLen(src)]=0;
	return copia;
}

// Keys Predict

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
    return kt;
}

// keysPredictAddWord agrega una nueva palabra a la estructura kt
void keysPredictAddWord(struct keysPredict* kt, char* word) {
	
	if(strLen(word)==0){
		return 0;
	}
	int index_palabra = 0;
	struct node** pp = &(kt->first);
	
	while(word[index_palabra] != NULL){
		
		struct node* founded = findNodeInLevel(pp, word[index_palabra]);
		
		// si no encontró el nodo, lo crea.
		if(founded==NULL){
			kt->totalKeys++;
			founded = addSortedNewNodeInLevel(pp, word[index_palabra]);
		}
		
		// si es el ultimo caracter, crea la palabra.
		if(index_palabra == strLen(word)-1){
			founded->word = strDup(word);
			founded->end = 1;
		}
		
		pp = &(founded->down);
		index_palabra++;
		
	}
	
	kt->totalWords++;
}

// keysPredictRemoveWord se encarga de borrar una palabra de la estructura kt.
void keysPredictRemoveWord(struct keysPredict* kt, char* word) {

	int index_palabra = 0;
	struct node** pp = &(kt->first);
	while(word[index_palabra] != NULL){
		struct node* founded = findNodeInLevel(pp, word[index_palabra]);
		if((strLen(word)-1)==index_palabra && founded->end == 1){
			free(founded->word);
			founded->word = 0;
			// preguntar si hay que hacer free(founded->word) o founded->word = 0;
			founded->end = 0;
			kt->totalWords--;
		}
		
		pp = &(founded->down);
		index_palabra++;
	}
	
}

// keysPredictFind se encarga de encontrar una palabra en la estructura kt.
// retorna NULL si no la encuentra; si la encuentra retorno el puntero al nodo.
struct node* keysPredictFind(struct keysPredict* kt, char* word) {
	
	int index_palabra = 0;
	struct node** pp = &(kt->first);

	while(word[index_palabra] != NULL){
		struct node* founded = findNodeInLevel(pp, word[index_palabra]);
		if(founded==NULL){
			return 0;
		}else{
			int equal = 1;
			if(founded->end == 1){
				for(int i = 0; i<strLen(word); i++){
					if(founded->word[i] != word[i]){
						equal = 0;
					}
				}
				if(equal==1){
					return founded;	
				}				
			}
		}
		
		pp = &(founded->down);
		index_palabra++;
	}
	
}


// keysPredictRun retorna un arreglo de strings con todas las palabras comenzadas por un prefijo especifico.
char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
	
	int index_palabra = 0;
	struct node** pp = &(kt->first);
	struct node* founded = 0;
	
	// navegar hasta el nodo correspondiente al ultimo caracter del prefijo.
	while(partialWord[index_palabra] != NULL){
		founded = findNodeInLevel(pp, partialWord[index_palabra]);
		pp = &(founded->down);
		index_palabra++;
		
	}
	
	if(founded->end){
		(*wordsCount)++;
	}
	
	// contar todas las palabras comenzadas con el prefijo (reservar memoria con ese tamaño)
	*wordsCount = keysPredictCountWordAux(*pp, *wordsCount, 0);
	
	char** foundWords = (char**)malloc(*wordsCount * sizeof(char*));
	
	// agregar al arreglo las palabras encontradas.
	int cont = 0;
	if(founded->end){
		foundWords[cont] = strdup(founded->word);
		cont++;
	}
	keysPredictCountWordAux(*pp, cont, foundWords);
	;
	return foundWords;
}

// keysPredictCountWordAux es una funcion recursiva que se encarga de contar palabras
int keysPredictCountWordAux(struct node* n, int cont, char** foundWords) {
	struct node* current = n;
	
	// contar palabras o inserlas en el arreglo de punteros a strings segun corresponda
	while(current) {
		if(current->end) {
			if(foundWords != NULL){
				foundWords[cont] = strDup(current->word);	
			}
			cont++;
			
			
		}
		
		// llamada recursiva para contar palabras en el nivel inferior al nodo actual
		cont = keysPredictCountWordAux(current->down, cont, foundWords);
		current = current->next; // avanzar al siguiente nodo de un mismo nivel
	}
	
	return cont;
}

// keysPredictListAll se encarga de listar todas las palabras almacenadas
char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
	
	struct node** pp = &(kt->first);

	// reservar espacio de memoria segun cantidad de palabras encontradas
	*wordsCount = keysPredictCountWordAux(*pp, *wordsCount, 0);
	char** foundWords = (char**)malloc(*wordsCount * sizeof(char*));
	
	// insertar las palabras en el array
	keysPredictCountWordAux(*pp, 0, foundWords);
	
	return foundWords;
}

void keysPredictDelete(struct keysPredict* kt) {
	keysPredictDeleteAux(kt->first);
	free(kt);
}
void keysPredictDeleteAux(struct node* n) {
	struct node* current = n;
	while (current) {
		// Recursivamente eliminamos los nodos descendentes.
		keysPredictDeleteAux(current->down);
		
		// Contamos las palabras que tiene este nodo.
		int cont = 0;
		struct node* temp = current;
		while (temp) {
			if (temp->word) {
				cont++;
			}
			temp = temp->next;
		}
		
		// Si hay palabras, se crea un arreglo de palabras para eliminar.
		if (cont > 0) {
			char** words = (char**)malloc(cont * sizeof(char*));
			int index = 0;
			
			// Rellenamos el arreglo con las palabras para eliminar.
			temp = current;
			while (temp) {
				if (temp->word) {
					words[index++] = temp->word;
				}
				temp = temp->next;
			}
			
			// Eliminamos las palabras usando la función `deleteArrayOfWords`.
			deleteArrayOfWords(words, cont);
		}
		
		// Guardamos el puntero al siguiente antes de liberar el nodo actual.
		struct node* next = current->next;
		free(current);
		current = next;
	}
}

void keysPredictPrint(struct keysPredict* kt) {
    printf("--- Predict --- Keys: %i Words: %i\n", kt->totalKeys, kt->totalWords);
    keysPredictPrintAux(kt->first, 0);
    printf("---\n");
}

void keysPredictPrintAux(struct node* n, int level) {
    if(!n) return;
    struct node* current = n;
    while(current) {
        for(int i=0; i<level;i++) printf(" |   ");
        if(current->end) {
            printf("[%c]\n",current->character);
        } else  {
            printf(" %c \n",current->character);
        }
        keysPredictPrintAux(current->down, level+1);
        current = current->next;
    }
}

// Auxiliar functions

// findNodeInLevel se encarga de comprobar si un nodo se encuentra presente en un nivel especifico
struct node* findNodeInLevel(struct node** list, char character) {
	
	// comprobar si la lista esta vacia
	struct node* temp = *list;
	if (temp == NULL) {
		return NULL;
	}
	
	// buscar el nodo pedido segun caracter
	while(temp != NULL){
		if(temp->character == character){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

// addSortedNewNodeInLevel se engarga de agregar un nodo en un nivel especifico segun orden alfabetico
// (teniendo en cuenta el caso que el nodo sea el primero de la lista o si la lista se encontraba vacia)
struct node* addSortedNewNodeInLevel(struct node** list, char character){
	
	// creacion y seteo de nuevo nodo
	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	newNode->character = character;
	newNode->next = 0;
	newNode->end = 0;
	newNode->word = 0;
	newNode->down = 0;
	
	// comprobar si la lista esta vacia o si el nodo es el primero de la lista
	if(*list == NULL || (*list)->character > character){
		newNode->next = *list;
		*list = newNode;       
		return newNode;
	}
	
	// insertar el nodo en la lista segun orden alfabetico
	struct node* current = *list;
	while (current->next != NULL && current->next->character < character) {
		current = current->next;
	}
	
	newNode->next = current->next;
	current->next = newNode;
	
	return newNode;
	
};
	
// deleteArrayOfWords se encarga de liberar la memoria reservada para un array de palabras
// (libera cada palabra individualmente y luego libera el array que las contiene)
void deleteArrayOfWords(char** words, int wordsCount) {
	// libera palabra por palabra
	for(int i = 0; i < wordsCount; i++){
		free(words[i]);
	}
	
	// libera arreglo completo
	free(words);	
}
