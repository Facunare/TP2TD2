#include "utils.h"

int strLen(char* src) {
	int contador = 0;
	while(src[contador]!=NULL){
		contador++;
	}

    return contador;
}

char* strDup(char* src) {

	char* copia = (char*)malloc((sizeof(char))*(strLen(src)+1)); 
	
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

void keysPredictAddWord(struct keysPredict* kt, char* word) {
	
	int index_palabra = 0;
	struct node** pp = &(kt->first);

	while(word[index_palabra] != NULL){
		
		struct node* founded = findNodeInLevel(pp, word[index_palabra]);
		
		if(founded==NULL){
			kt->totalKeys++;
			founded = addSortedNewNodeInLevel(pp, word[index_palabra]);
		}
		
		if(index_palabra == strLen(word)-1){
			founded->word = strDup(word);
			founded->end = 1;
		}
		
		pp = &(founded->down);
		index_palabra++;
		
	}
	
	kt->totalWords++;
}

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

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
	
	int index_palabra = 0;
	struct node** pp = &(kt->first);
	while(word[index_palabra] != NULL){
		struct node* founded = findNodeInLevel(pp, word[index_palabra]);
		if(founded==NULL){
			return 0;
		}else{
			if(founded->end == 1 && strcmp(founded->word, word) == 0){ // preguntar si podemos usar strcmp()
				return founded;
			}
		}
		
		pp = &(founded->down);
		index_palabra++;
	}
	
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
	
	int index_palabra = 0;
	struct node** pp = &(kt->first);
	struct node* founded = 0;
	
	while(partialWord[index_palabra] != NULL){
		founded = findNodeInLevel(pp, partialWord[index_palabra]);
		pp = &(founded->down);
		index_palabra++;
		
	}
	
	if(founded->end){
		(*wordsCount)++;
	}
	
	int cont = 0;
	*wordsCount = keysPredictCountWordAux(*pp, *wordsCount, 0);
	char** foundWords = (char**)malloc(*wordsCount * sizeof(char*));
	
	if(founded->end){
		foundWords[cont] = strdup(founded->word);
		cont++;
	}
	keysPredictCountWordAux(*pp, cont, foundWords);
	
	return foundWords;
}

int keysPredictCountWordAux(struct node* n, int cont, char** foundWords) {
	struct node* current = n;
	
	while(current) {
		if(current->end) {
			
			if(foundWords != NULL){
				foundWords[cont] = strDup(current->word);	
			}
			cont++;
		}
		cont = keysPredictCountWordAux(current->down, cont, foundWords);
		current = current->next;
	}
	
	return cont;
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
	
	struct node** pp = &(kt->first);

	*wordsCount = keysPredictCountWordAux(*pp, *wordsCount, 0);
	char** foundWords = (char**)malloc(*wordsCount * sizeof(char*));

	keysPredictCountWordAux(*pp, 0, foundWords);
	
	return foundWords;
}

void keysPredictDelete(struct keysPredict* kt) {

    // COMPLETAR

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
	struct node* temp = *list;
	if (temp == NULL) {
		return NULL;
	}
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
	struct node* newNode = (struct node*) malloc(sizeof(struct node));

	newNode->character = character;
	newNode->next = 0;
	newNode->end = 0;
	newNode->word = 0;
	newNode->down = 0;
	
	if(*list == NULL || (*list)->character > character){
		newNode->next = *list;
		*list = newNode;       
		return newNode;
	}
	
	struct node* current = *list;
	while (current->next != NULL && current->next->character < character) {
		
		current = current->next;
	}
	
	newNode->next = current->next;
	current->next = newNode;
	
	return newNode;
	
};
	

void deleteArrayOfWords(char** words, int wordsCount) {
	for(int i = 0; i < wordsCount; i++){
		free(**(words + i));
	}
	
	free(*words);
	
}
