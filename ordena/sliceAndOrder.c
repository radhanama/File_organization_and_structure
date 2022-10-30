#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

void intercala(int n);

int main(int argc, char**argv)
{
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, part;
	int n = 8;

	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	part = qtd/n;
	for(int i = 0; i < n; i++){
		int tam = part*i;
		char nameFile[20]; 
		sprintf(nameFile,"cep_%d.dat", i);
		if(qtd < (part*i)){
			tam = qtd - tam;
		}
		e = (Endereco*) malloc(tam*sizeof(Endereco));
		rewind(f);
		if(fread(e,sizeof(Endereco),(tam),f) == tam)
		{
			printf("Lido = OK\n");
		}
		qsort(e,tam,sizeof(Endereco),compara);
		printf("Ordenado = OK\n");
		saida = fopen(nameFile,"wb");
		fwrite(e,sizeof(Endereco),tam,saida);
		fclose(saida);
		printf("Escrito = OK\n");
		free(e);
	}
	intercala(n);
	fclose(f);
}

void intercala(int n)
{
	FILE *a, *b, *saida;
	Endereco ea, eb;
	int fim = n -1;
	int current = 0;
	char firstFile[20];
	char secondFile[20];
	char outFile[20];

	while(current < fim){
		int temp1 = current+1;
		int temp2 = fim+1;
		sprintf(firstFile,"cep_%d.dat", current);
		sprintf(secondFile,"cep_%d.dat", temp1);
		sprintf(outFile,"cep_%d.dat", temp2);
		a = fopen(firstFile,"rb");
		b = fopen(secondFile,"rb");
		saida = fopen(outFile,"wb");

		fread(&ea,sizeof(Endereco),1,a);
		fread(&eb,sizeof(Endereco),1,b);

		// eof -> End Of File
		while(!feof(a) && !feof(b))
		{
			if(compara(&ea,&eb)<0) // ea < eb
			{
				fwrite(&ea,sizeof(Endereco),1,saida);
				fread(&ea,sizeof(Endereco),1,a);
			}
			else // ea >= eb
			{
				fwrite(&eb,sizeof(Endereco),1,saida);
				fread(&eb,sizeof(Endereco),1,b);
			}
		}

		while(!feof(a))
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);		
		}
		
		while(!feof(b))
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);		
		}

		fclose(a);
		fclose(b);
		fclose(saida);
		remove(firstFile);
		remove(secondFile);
		fim++;
		current+=2;
	}
}