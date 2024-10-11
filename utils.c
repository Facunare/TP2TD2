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
	// "casa"
	int index_palabra = 0;
	struct node* p;
	while(word[index_palabra] != NULL){
		p = findNodeInLevel(kt, word[index_palabra]);
		if(p==NULL){
			addSortedNewNodeInLevel(kt,word[index_palabra]);
		}else{
			if(index_palabra == strLen(word)-1){
				char* copia = strDup(word);
				p->word = word;
				p->end = 1;
			}
			p = p->down;
		}
		index_palabra++;
	}
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {

    // COMPLETAR
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {

    // COMPLETAR

    return 0;
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
	struct node* temp = list;
	while(temp->next != 0){
		if(temp->character == character){
			return temp;
		}
		temp = temp->next;
	}
	
	return 0;
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
	struct node* newNode = 0;
	struct node* prox = list;
	struct node* prev = 0;
    newNode->character = character;
	
	while(prox != 0){
		if(prox->character > newNode->character){
			prev->next = newNode;
			newNode->next = prox;
		}
		prev = prox;
		prox = prox->next;
		
	}
}

void deleteArrayOfWords(char** words, int wordsCount) {
	for(int i = 0; i < wordsCount; i++){
		free(**(words + i));
	}
	
	free(*words);
	
}
