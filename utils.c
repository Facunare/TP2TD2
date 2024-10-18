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

    // COMPLETAR

    return 0;
}

int keysPredictCountWordAux(struct node* n) {

    // COMPLETAR
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {

    // COMPLETAR

    return 0;
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
