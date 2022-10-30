#include <stdio.h>

int main(int argc, char** argv)
{
	FILE *entrada;
	int count [256];
	int words=0;
	int c;

	for(int i = 0; i<256; i++){
		count[i] = 0;
	}

	if(argc != 2)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"r");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	// read file and count words and letters
	c = fgetc(entrada);
	while(c != EOF)
	{
		if(c == 32)
			words++;
		count[c]++;
		c = fgetc(entrada);
	}

	// Questão 1
	printf("quest 1: number of words: %d\n", words);

	// Questão 2
	printf("quest 2: %d\n", words);
	for(int i = 0; i<sizeof(count); i++){
		if((('a'>=i>='z')||('A'>=i>='Z'))&&count[i]!=0){
			printf("The letter %c was apeared %d times\n", i, count[i]); 
		}
	}

	fclose(entrada);
	return 0;
}

