#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	long size;
	int end;
	long middle = 0;
	int start = 0;
	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("./cep_ordenado.dat","rb");
	fseek(f, 0, SEEK_END);
	size = ftell(f);	// get the size of file
	end = (size / sizeof(Endereco))-1; // get number of documents in the file
	while(end >= start)
	{
		// get the middle of the file
		middle = (start+end)/2; 
		// put the point of read to the middle of the file
		fseek(f, (middle)*sizeof(Endereco), SEEK_SET);
		// read the middle file 
		qt = fread(&e,sizeof(Endereco),1,f); 
		// compare if the middle file is smaller than the wanted cep
		if(strncmp(argv[1],e.cep,8) < 0){
			// the end of the file will be the middle -1 because the wanted cep is smaller than the middle
			end = middle - 1; 
		}
		
		// compare if the middle cep is gigger than the wanted cep
		if(strncmp(argv[1],e.cep,8) > 0){
			// the start of the file will be the middle +1 because the wanted cep is bigger than the middle
			start = middle + 1; 
		}
		// compare if the middle cep is equal than the wanted cep
		if(strncmp(argv[1],e.cep,8)==0){ 
			// print the address
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
	}
	fclose(f);
}

