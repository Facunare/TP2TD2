#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void predictAndPrintAll(struct keysPredict* kt, char* partialWord ) {
    char** words;
    int wordsCount;
    words = keysPredictRun(kt, partialWord, &wordsCount);
    printf("Predicts: %s = ", partialWord);
    for(int i=0; i<wordsCount; i++) {
        printf("%s,", words[i]);
    }
    printf("\n");
    deleteArrayOfWords(words, wordsCount);
}

void findAndPrintAll(struct keysPredict* kt, char* word ) {
    struct node* result = keysPredictFind(kt, word);
    printf("Find: %s = %i\n", word, result==0);
}

int main() {

    // strLen
    int len = strLen("hola");
    printf("strLen(\"hola\") -> \"%i\"\n", len);
    printf("\n");
	int strVacio = strLen("");
	printf("strLen(\"\") -> \"%i\"\n", strVacio);
	printf("\n");
	int strUnCaracter = strLen("h");
	printf("strLen(\"h\") -> \"%i\"\n", strUnCaracter);
	printf("\n");
	int strAlfanumerico = strLen("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	printf("strLen(\"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\") -> \"%i\"\n", strAlfanumerico);
	printf("\n");
	int strConEspacios = strLen("a b c");
	printf("strLen(\"a b c\") -> \"%i\"\n", strConEspacios);
	printf("\n");
	int strCharsEspeciales= strLen("a!b!c");
	printf("strLen(\"a!b!c\") -> \"%i\"\n", strCharsEspeciales);
	printf("\n");
	
    // strDup
    char* dup = strDup("hola");
    printf("strDup(\"hola\") -> \"%s\"\n", dup);
    free(dup);
    printf("\n");
	char* dupVacio = strDup("");
	printf("strDup(\"\") -> \"%s\"\n", dupVacio);
	free(dup);
	printf("\n");
	char* dupUnCaracter = strDup("h");
	printf("strDup(\"h\") -> \"%s\"\n", dupUnCaracter);
	free(dup);
	printf("\n");
	char* dupAlfanumerico = strDup("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	printf("strDup(\"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\") -> \"%s\"\n", dupAlfanumerico);
	free(dup);
	printf("\n");
	char* dupConEspacios = strDup(" a b");
	printf("strDup(\" a b\") -> \"%s\"\n", dupConEspacios);
	free(dup);
	printf("\n");
	char* dupCharsEspeciales = strDup("a!b!");
	printf("strDup(\"a!b!\") -> \"%s\"\n", dupCharsEspeciales);
	free(dup);
	printf("\n");
	
	
    // keysPredict
    struct keysPredict* kt = keysPredictNew();
    
   // keysPredictAddWord 
	keysPredictAddWord(kt, "");
    keysPredictAddWord(kt, "a"); 
    keysPredictAddWord(kt, "ala");
	keysPredictAddWord(kt, "ale");
	keysPredictAddWord(kt, "bar");
	keysPredictAddWord(kt, "casa");
	keysPredictAddWord(kt, "casa");
	keysPredictAddWord(kt, "la");
	keysPredictAddWord(kt, "lo");
	keysPredictAddWord(kt, "los");
	keysPredictAddWord(kt, "papa");
	keysPredictAddWord(kt, "papas");
	keysPredictAddWord(kt, "pato");
	keysPredictAddWord(kt, "patos");
	keysPredictAddWord(kt, "patoba");
	keysPredictAddWord(kt, "patobica");
	keysPredictAddWord(kt, "papanatas");
	keysPredictAddWord(kt, "papalos");
	keysPredictAddWord(kt, "australopitecus");
	keysPredictPrint(kt);
	
	keysPredictFind(kt, "papas"); // comprobar si esta la palabra antes de ser eliminada
	
	// keysPredictRemoveWord
	keysPredictRemoveWord(kt, "la");
	keysPredictRemoveWord(kt, "lo");
	keysPredictRemoveWord(kt, "los");
	keysPredictRemoveWord(kt, "papa");
	keysPredictRemoveWord(kt, "papas");
	keysPredictRemoveWord(kt, "");
	
	keysPredictPrint(kt);
	
	keysPredictFind(kt, "papas"); // comprobar si esta la palabra despues de ser eliminada
	keysPredictFind(kt, "australopitecus");
	keysPredictFind(kt, "patobica");
	keysPredictFind(kt, "hola");
	keysPredictFind(kt, "boca");
	keysPredictFind(kt, "");
	keysPredictFind(kt, "river");
	
	// keysPredictRun	
	int words = 0;
	char** found = keysPredictRun(kt, "a", &words);
	printf("%i\n", words);
	for(int i=0; i<words; i++) {
		printf("%s\n", found[i]);
	}
	

	// keysPredictListAll
	int wordsCount3 = 0;
	char** words3 = keysPredictListAll(kt, &wordsCount3);
	printf("%i\n", wordsCount3);
	for(int i=0; i<wordsCount3; i++) {
		printf("%s\n", words3[i]);
	}
	// keysPredict con una sola palabra
	struct keysPredict* kt2 = keysPredictNew();
	keysPredictAddWord(kt2, "hola");
	keysPredictAddWord(kt2, "hola");
	int wordsCount4 = 0;
	char** words4 = keysPredictListAll(kt2, &wordsCount4);
	printf("%i\n", wordsCount4);
	for(int i=0; i<wordsCount4; i++) {
		printf("%s\n", words4[i]);
	}
	/*
	keysPredictPrint(kt2);
    /*
	keysPredictDelete(kt);
	printf("===\n");
	keysPredictPrint(kt);
	
	printf("===\n");
	
	
	
    // keysPredict - encontrar palabras
    findAndPrintAll(kt, "papa");
    findAndPrintAll(kt, "pata");
    findAndPrintAll(kt, "a");
    findAndPrintAll(kt, "zazz");

    // keysPredict - predecir palabras
    predictAndPrintAll(kt,"or");
    predictAndPrintAll(kt,"ab");
    predictAndPrintAll(kt,"pa");
    predictAndPrintAll(kt,"pap");
    predictAndPrintAll(kt,"q");
    predictAndPrintAll(kt,"zap");

    // keysPredict - predecir palabras
    keysPredictRemoveWord(kt,"");
    keysPredictRemoveWord(kt,"zaz");
    keysPredictRemoveWord(kt,"aaa");
    keysPredictRemoveWord(kt,"papa");
    keysPredictRemoveWord(kt,"pata");
    keysPredictPrint(kt);

    // keysPredict - borrar diccionario
    keysPredictDelete(kt);
*/
    return 0;
}
