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
	printf("-Funcion \"strLen\":\n");
	printf("\n");
	printf("\n");
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
	int strNumeros= strLen("0123456789");
	printf("\n");
	printf("strLen(\"0123456789\")-> \"%i\"\n", strNumeros);
	printf("\n");
	printf("\n");
	
	// strDup
	printf("-Funcion \"strDup\":\n");
	printf("\n");
	printf("\n");
	char* dup = strDup("hola");
	printf("strDup(\"hola\") -> \"%s\"\n", dup);
	free(dup);
	printf("\n");
	char* dupVacio = strDup("");
	printf("strDup(\"\") -> \"%s\"\n", dupVacio);
	free(dupVacio);
	printf("\n");
	char* dupUnCaracter = strDup("h");
	printf("strDup(\"h\") -> \"%s\"\n", dupUnCaracter);
	free(dupUnCaracter);
	printf("\n");
	char* dupAlfanumerico = strDup("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	printf("strDup(\"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\") -> \"%s\"\n", dupAlfanumerico);
	free(dupAlfanumerico);
	printf("\n");
	char* dupConEspacios = strDup(" a b");
	printf("strDup(\" a b\") -> \"%s\"\n", dupConEspacios);
	free(dupConEspacios);
	printf("\n");
	char* dupCharsEspeciales = strDup("a!b!");
	printf("strDup(\"a!b!\") -> \"%s\"\n", dupCharsEspeciales);
	free(dupCharsEspeciales);
	printf("\n");
	char* dupTexto = strDup ("Hace mucho tiempo en una galaxia muy, muy lejana donde las pantallas capacitivas eran solo un producto de la ciencia ficcion (...)");
	printf("strDup (\"Hace mucho tiempo en una galaxia muy, muy lejana donde las pantallas capacitivas eran solo un producto de la ciencia ficcion (...) \")\n->\"%s\"\n", dupTexto);
	free(dupTexto);
	printf("\n");
	
	
	// Diccionario 1. keysPredict
	struct keysPredict* kt = keysPredictNew();
	
	// keysPredictAddWord 
	keysPredictAddWord(kt, "");
	keysPredictAddWord(kt, "a"); 
	keysPredictAddWord(kt, "ala");
	keysPredictAddWord(kt, "ale");
	keysPredictAddWord(kt, "bar");
	keysPredictAddWord(kt, "casa");
	keysPredictAddWord(kt, "la");
	keysPredictAddWord(kt, "lo");
	keysPredictAddWord(kt, "los");
	keysPredictAddWord(kt, "papa");
	keysPredictAddWord(kt, "papas");
	keysPredictAddWord(kt, "pato");
	keysPredictAddWord(kt, "patos");
	keysPredictAddWord(kt, "patova");
	keysPredictAddWord(kt, "patovica");
	keysPredictAddWord(kt, "papanatas");
	keysPredictAddWord(kt, "papalos");
	keysPredictAddWord(kt, "australopitecus");
	
	printf("\n\nDiccionario 1.\n\n");
	keysPredictPrint(kt);
	
	
	keysPredictFind(kt, "papas"); // Comprobamos si está la palabra antes de ser eliminada
	
	// keysPredictRemoveWord
	keysPredictRemoveWord(kt, "la");
	keysPredictRemoveWord(kt, "lo");
	keysPredictRemoveWord(kt, "los");
	keysPredictRemoveWord(kt, "papa");
	keysPredictRemoveWord(kt, "papas");
	keysPredictRemoveWord(kt, "hamburguesa"); // borrar una palabra que no existe
	keysPredictRemoveWord(kt, "");
	
	printf("\n-Borramos las palabras: 'la', 'lo', 'los', 'papa', 'papas'\n\n");
	keysPredictPrint(kt);
	
	keysPredictFind(kt, "papas"); // Comprobamos si está la palabra después de ser eliminada
	keysPredictFind(kt, "australopitecus");
	keysPredictFind(kt, "patovica");
	keysPredictFind(kt, "hola");
	keysPredictFind(kt, "boca");
	keysPredictFind(kt, "");
	keysPredictFind(kt, "river");
	
	// keysPredictRun. Imprimimos la lista de palabras del Diccionario 1 que empiecen con "a"
	int wordsCount = 0;
	char** words = keysPredictRun(kt, "a", &wordsCount);
	printf("\n-La cantidad de palabras de su diccionario (1) que empiezan con la letra 'a' son: %i\n", wordsCount);
	printf("Estas son: \n\n");
	
	for(int i=0; i<wordsCount; i++) {
		printf("%s\n", words[i]);
	}
	
	deleteArrayOfWords(words, wordsCount);
	
	
	// keysPredictListAll. Imprimimos la lista de palabras del Diccionario 1
	int wordsCount3 = 0;
	char** words3 = keysPredictListAll(kt, &wordsCount3);
	printf("\n-La cantidad de palabras de su diccionario (1) son: %i\n", wordsCount3);
	printf("Estas son: \n\n");
	for(int i=0; i<wordsCount3; i++) {
		printf("%s\n", words3[i]);
	}
	
	deleteArrayOfWords(words3, wordsCount3);
	
	
	// Diccionario 2. keysPredict con una sola palabra. 
	struct keysPredict* kt2 = keysPredictNew();
	keysPredictAddWord(kt2, "hola");	//Verificamos que no se duplique la palabra en el diccionario
	keysPredictAddWord(kt2, "hola");
	
	printf("\n\nDiccionario 2.\n\n");
	keysPredictPrint(kt2);
	
	// keysPredictListAll. Imprimimos la lista de palabras del Diccionario 2
	int wordsCount4 = 0;
	char** words4 = keysPredictListAll(kt2, &wordsCount4);
	printf("\n-La cantidad de palabras de su diccionario (2) son: %i\n", wordsCount4);
	printf("Esta es: \n\n");
	for(int i=0; i<wordsCount4; i++) {
		printf("%s\n", words4[i]);
	}
	
	deleteArrayOfWords(words4, wordsCount4);
	
	
	// Diccionario 3. keysPredict casos chicos  
	struct keysPredict* kt3 = keysPredictNew();
	keysPredictAddWord(kt3, "alfajor");
	keysPredictAddWord(kt3, "canoa");
	keysPredictAddWord(kt3, "rinoceronte");
	keysPredictAddWord(kt3, "casa");
	keysPredictAddWord(kt3, "rino");
	keysPredictAddWord(kt3, "celular");	//Agregamos "celular" como caso de test
	keysPredictAddWord(kt3, "casamiento"); //Agregamos "casamiento" como caso de test
	
	
	printf("\n\nDiccionario 3.\n\n");
	keysPredictPrint(kt3);
	printf("\n");
	
	keysPredictRemoveWord(kt3, "canoa"); //Borramos la palabra "canoa"
	
	keysPredictAddWord(kt3, "pato");	//Agregamos la palabra "pato"
	
	
	//Borramos 'canoa' y agregamos 'pato'
	printf("-Borramos:'canoa' y agregamos: 'pato'\n\n");
	keysPredictPrint(kt3);
	
	//Imprimimos la lista de palabras del Diccionario 3
	int wordsCount5 = 0;
	char** words5 = keysPredictListAll(kt3, &wordsCount5);
	printf("\n-La cantidad de palabras de su diccionario (3) son: %i\n", wordsCount5);
	printf("Estas son: \n\n");
	for(int i=0; i<wordsCount5; i++) {
		printf("%s\n", words5[i]);
	}
	
	deleteArrayOfWords(words5, wordsCount5);
	
	
	//Imprimimos la lista de palabras que empiecen con 'c'
	int wordsCount6 = 0;
	char** words6 = keysPredictRun(kt3, "c", &wordsCount6);
	printf("\n-La cantidad de palabras de su diccionario (3) que empiezan con la letra 'c' son: %i\n", wordsCount6);
	printf("Estas son: \n\n");
	
	for(int i=0; i<wordsCount6; i++) {
		printf("%s\n", words6[i]);
	}
	
	deleteArrayOfWords(words6, wordsCount6);
	
	//Imprimimos la lista de palabras que empiecen con 'ca'
	int wordsCount7 = 0;
	char** words7 = keysPredictRun(kt3, "ca", &wordsCount7);
	printf("\n-La cantidad de palabras de su diccionario (3) que empiezan con la letra 'ca' son: %i\n", wordsCount7);
	printf("Estas son: \n\n");
	
	for(int i=0; i<wordsCount7; i++) {
		printf("%s\n", words7[i]);
	}
	
	deleteArrayOfWords(words7, wordsCount7);
	
	//Imprimimos la lista de palabras que empiecen con 'casa'
	int wordsCount8 = 0;
	char** words8 = keysPredictRun(kt3, "casa", &wordsCount8);
	printf("\n-La cantidad de palabras de su diccionario (3) que empiezan con la letra 'casa' son: %i\n", wordsCount8);
	printf("Estas son: \n\n");
	
	for(int i=0; i<wordsCount8; i++) {
		printf("%s\n", words8[i]);
	}
	
	deleteArrayOfWords(words8, wordsCount8);
	
	//Imprimimos la lista de palabras que empiecen con 'casas'
	int wordsCount9 = 0;
	char** words9 = keysPredictRun(kt3, "casas", &wordsCount9);
	printf("\n-La cantidad de palabras de su diccionario (3) que empiezan con la letra 'casas' son: %i\n", wordsCount9);
	if (wordsCount9==NULL){
		printf("No se encontro la palabra\n");
	}else{
		printf("Estas son: \n\n");
		for(int i=0; i<wordsCount9; i++) {
			printf("%s\n", words9[i]);
		}
	}

	deleteArrayOfWords(words9, wordsCount9);
	
	// Diccionario 4. keysPredict casos grandes
	struct keysPredict* kt4 = keysPredictNew();
	
	keysPredictAddWord(kt4, "distancia");
	keysPredictAddWord(kt4, "diccionario");
	keysPredictAddWord(kt4, "dibujo");
	keysPredictAddWord(kt4, "direccion");
	keysPredictAddWord(kt4, "diferencia");
	keysPredictAddWord(kt4, "disculpa");
	keysPredictAddWord(kt4, "distinto");
	keysPredictAddWord(kt4, "directriz");
	keysPredictAddWord(kt4, "dilema");
	keysPredictAddWord(kt4, "directo");

	keysPredictAddWord(kt4, "helado");
	keysPredictAddWord(kt4, "helio");
	keysPredictAddWord(kt4, "heladera");
	keysPredictAddWord(kt4, "herencia");
	keysPredictAddWord(kt4, "heredabilidad");
	keysPredictAddWord(kt4, "hectarea");
	keysPredictAddWord(kt4, "hepatitis");
	keysPredictAddWord(kt4, "hectagono");
	keysPredictAddWord(kt4, "hembra");
	keysPredictAddWord(kt4, "hervir");
	
	keysPredictAddWord(kt4, "lampara");
	keysPredictAddWord(kt4, "ladrillo");
	keysPredictAddWord(kt4, "lago");
	keysPredictAddWord(kt4, "lagrima");
	keysPredictAddWord(kt4, "lancha");
	keysPredictAddWord(kt4, "latido");
	keysPredictAddWord(kt4, "laboratorio");
	keysPredictAddWord(kt4, "lapiz");
	keysPredictAddWord(kt4, "lana");
	keysPredictAddWord(kt4, "lanzamiento");
	
	keysPredictAddWord(kt4, "reloj");
	keysPredictAddWord(kt4, "regreso");
	keysPredictAddWord(kt4, "recuerdo");
	keysPredictAddWord(kt4, "recurso");
	keysPredictAddWord(kt4, "recamara");
	keysPredictAddWord(kt4, "relato");
	keysPredictAddWord(kt4, "reclamo");
	keysPredictAddWord(kt4, "reducir");
	keysPredictAddWord(kt4, "revisar");
	keysPredictAddWord(kt4, "reunir");
	
	keysPredictAddWord(kt4, "sendero");
	keysPredictAddWord(kt4, "secador");
	keysPredictAddWord(kt4, "sediento");
	keysPredictAddWord(kt4, "seguro");
	keysPredictAddWord(kt4, "señal");
	keysPredictAddWord(kt4, "seleccion");
	keysPredictAddWord(kt4, "secreto");
	keysPredictAddWord(kt4, "semanal");
	keysPredictAddWord(kt4, "separar");
	keysPredictAddWord(kt4, "servicio");
	
	keysPredictAddWord(kt4, "cambio");
	keysPredictAddWord(kt4, "camaron");
	keysPredictAddWord(kt4, "camisa");
	keysPredictAddWord(kt4, "caminata");
	keysPredictAddWord(kt4, "camion");
	keysPredictAddWord(kt4, "camara");
	keysPredictAddWord(kt4, "campana");
	keysPredictAddWord(kt4, "camino");
	keysPredictAddWord(kt4, "camuflaje");
	keysPredictAddWord(kt4, "camarada");
	
	keysPredictAddWord(kt4, "nivel");
	keysPredictAddWord(kt4, "nieve");
	keysPredictAddWord(kt4, "nido");
	keysPredictAddWord(kt4, "niño");
	keysPredictAddWord(kt4, "ninguno");
	keysPredictAddWord(kt4, "nivelar");
	keysPredictAddWord(kt4, "nitrato");
	keysPredictAddWord(kt4, "nivea");
	keysPredictAddWord(kt4, "niembro");
	keysPredictAddWord(kt4, "nifilifi");
	
	keysPredictAddWord(kt4, "pagina");
	keysPredictAddWord(kt4, "pacto");
	keysPredictAddWord(kt4, "palabra");
	keysPredictAddWord(kt4, "paleta");
	keysPredictAddWord(kt4, "palo");
	keysPredictAddWord(kt4, "panadero");
	keysPredictAddWord(kt4, "pantalon");
	keysPredictAddWord(kt4, "papel");
	keysPredictAddWord(kt4, "paraguas");
	keysPredictAddWord(kt4, "partido");
	
	keysPredictAddWord(kt4, "tacon");
	keysPredictAddWord(kt4, "taladro");
	keysPredictAddWord(kt4, "tallo");
	keysPredictAddWord(kt4, "tambor");
	keysPredictAddWord(kt4, "tango");
	keysPredictAddWord(kt4, "tapiz");
	keysPredictAddWord(kt4, "tarjeta");
	keysPredictAddWord(kt4, "taza");
	keysPredictAddWord(kt4, "tarzan");
	keysPredictAddWord(kt4, "tampoco");
	
	keysPredictAddWord(kt4, "venado");
	keysPredictAddWord(kt4, "ventana");
	keysPredictAddWord(kt4, "verdura");
	keysPredictAddWord(kt4, "verso");
	keysPredictAddWord(kt4, "vestido");
	keysPredictAddWord(kt4, "ventilar");
	keysPredictAddWord(kt4, "ventilador");
	keysPredictAddWord(kt4, "ventanal");
	keysPredictAddWord(kt4, "venir");
	keysPredictAddWord(kt4, "vestimenta");
	
	keysPredictPrint(kt4);
	
	keysPredictRemoveWord(kt4, "distancia");
	keysPredictRemoveWord(kt4, "diccionario");
	keysPredictRemoveWord(kt4, "dibujo");
	keysPredictRemoveWord(kt4, "direccion");
	keysPredictRemoveWord(kt4, "diferencia");
	keysPredictRemoveWord(kt4, "disculpa");
	keysPredictRemoveWord(kt4, "distinto");
	keysPredictRemoveWord(kt4, "directriz");
	keysPredictRemoveWord(kt4, "dilema");
	keysPredictRemoveWord(kt4, "directo");
	
	keysPredictRemoveWord(kt4, "helado");
	keysPredictRemoveWord(kt4, "helio");
	keysPredictRemoveWord(kt4, "heladera");
	keysPredictRemoveWord(kt4, "herencia");
	keysPredictRemoveWord(kt4, "heredabilidad");
	keysPredictRemoveWord(kt4, "hectarea");
	keysPredictRemoveWord(kt4, "hepatitis");
	keysPredictRemoveWord(kt4, "hectagono");
	keysPredictRemoveWord(kt4, "hembra");
	keysPredictRemoveWord(kt4, "hervir");	
	
	keysPredictRemoveWord(kt4, "lampara");
	keysPredictRemoveWord(kt4, "ladrillo");
	keysPredictRemoveWord(kt4, "lago");
	keysPredictRemoveWord(kt4, "lagrima");
	keysPredictRemoveWord(kt4, "lancha");
	keysPredictRemoveWord(kt4, "latido");
	keysPredictRemoveWord(kt4, "laboratorio");
	keysPredictRemoveWord(kt4, "lapiz");
	keysPredictRemoveWord(kt4, "lana");
	keysPredictRemoveWord(kt4, "lanzamiento");
	
	keysPredictRemoveWord(kt4, "reloj");
	keysPredictRemoveWord(kt4, "regreso");
	keysPredictRemoveWord(kt4, "recuerdo");
	keysPredictRemoveWord(kt4, "recurso");
	keysPredictRemoveWord(kt4, "recamara");
	keysPredictRemoveWord(kt4, "relato");
	keysPredictRemoveWord(kt4, "reclamo");
	keysPredictRemoveWord(kt4, "reducir");
	keysPredictRemoveWord(kt4, "revisar");
	keysPredictRemoveWord(kt4, "reunir");
	
	keysPredictRemoveWord(kt4, "sendero");
	keysPredictRemoveWord(kt4, "secador");
	keysPredictRemoveWord(kt4, "sediento");
	keysPredictRemoveWord(kt4, "seguro");
	keysPredictRemoveWord(kt4, "señal");
	keysPredictRemoveWord(kt4, "seleccion");
	keysPredictRemoveWord(kt4, "secreto");
	keysPredictRemoveWord(kt4, "semanal");
	keysPredictRemoveWord(kt4, "separar");
	keysPredictRemoveWord(kt4, "servicio");
	
	keysPredictPrint(kt4);
	
	int wordsCount10 = 0;
	char** words10 = keysPredictRun(kt4, "ca", &wordsCount10);
	printf("\n-La cantidad de palabras de su diccionario (4) que empiezan con el prefijo 'ca' son: %i\n", wordsCount10);
	printf("Estas son: \n\n");
	
	for(int i = 0; i < wordsCount10; i++) {
		printf("%s\n", words10[i]);
	}
	deleteArrayOfWords(words10, wordsCount10);
	
	int wordsCount11 = 0;
	char** words11 = keysPredictRun(kt4, "ni", &wordsCount11);
	printf("\n-La cantidad de palabras de su diccionario (4) que empiezan con el prefijo 'ni' son: %i\n", wordsCount11);
	printf("Estas son: \n\n");
	
	for(int i = 0; i < wordsCount11; i++) {
		printf("%s\n", words11[i]);
	}
	deleteArrayOfWords(words11, wordsCount11);
	
	int wordsCount12 = 0;
	char** words12 = keysPredictRun(kt4, "pa", &wordsCount12);
	printf("\n-La cantidad de palabras de su diccionario (4) que empiezan con el prefijo 'pa' son: %i\n", wordsCount12);
	printf("Estas son: \n\n");
	
	for(int i = 0; i < wordsCount12; i++) {
		printf("%s\n", words12[i]);
	}
	deleteArrayOfWords(words12, wordsCount12);
	
	int wordsCount13 = 0;
	char** words13 = keysPredictRun(kt4, "ta", &wordsCount13);
	printf("\n-La cantidad de palabras de su diccionario (4) que empiezan con el prefijo 'ta' son: %i\n", wordsCount13);
	printf("Estas son: \n\n");
	
	for(int i = 0; i < wordsCount13; i++) {
		printf("%s\n", words13[i]);
	}
	deleteArrayOfWords(words13, wordsCount13);
	
	int wordsCount14 = 0;
	char** words14 = keysPredictRun(kt4, "ve", &wordsCount14);
	printf("\n-La cantidad de palabras de su diccionario (4) que empiezan con el prefijo 've' son: %i\n", wordsCount14);
	printf("Estas son: \n\n");
	
	for(int i = 0; i < wordsCount14; i++) {
		printf("%s\n", words14[i]);
	}
	deleteArrayOfWords(words14, wordsCount14);
	
	
	// keysPredict - encontrar palabras
	/*findAndPrintAll(kt, "papa");
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
	keysPredictDelete(kt);*/
	
	return 0;
}
