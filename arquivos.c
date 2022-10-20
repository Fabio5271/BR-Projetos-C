// Programa básico para trabalhar com a lida e escrita de arquivos, no caso uma lista de produtos

#include <stdio.h>
#include <stdlib.h>

typedef struct {  // Estrutura de dados do produto
	char nome[20];
	float valor;
} t_produto;

char filepath[100];

void preencher(t_produto *produto){  // Permite preencher o nome e o valor do produto através de seu enderço de memória
	printf("Insira o nome do produto: ");
	scanf("%19s",produto->nome);
	printf("Insira o valor do produto: ");
	scanf("%f",&produto->valor);
}

void salvar_produtos_txt(int n, t_produto prods[n]){  // Recebe a quantidade de produtos e o vetor prods[], que percorre os produtos e armazena em um arquivo.
	FILE *fp;
	printf("\nInsira o caminho do arquivo a ser escrito: ");
	scanf("%99s",filepath);
	fp = fopen(filepath,"w");
	if (fp == NULL){
		printf("Falha ao abrir %s\n", filepath);
	}
	else {
		printf("\n\'%s\' Aberto com sucesso!\n\n", filepath);
		for (int i=0;i<n;i++){
		fprintf(fp,"%s\t%.2f\n",prods[i].nome,prods[i].valor);
		}
		fclose(fp);
	}
}

void ler_produtos_txt(char *path){  // Recebe o caminho do arquivo e imprime seus dados na tela
	FILE *fp;
	fp = fopen(filepath,"r");
	char nome[30]; float valor;
	while (fscanf(fp,"%[^\t]%f%*c",nome,&valor)!=EOF){
		printf("%s\t%.2f\n",nome,valor);
	}
	fclose(fp);
}

void med_prc_txt(char *path, int n){  // Imprime a média dos preços no arquivo
	FILE *fp;
  fp = fopen(filepath,"r");
	float valor[n]; float med=0; int x=0;
	for(int i=0;i<n;i++){
		while (fscanf(fp,"%*c")!='\n' && fscanf(fp,"%*c")!=EOF){
			fscanf(fp,"%f",&valor[x]);
			x++;
  	}
	}
  fclose(fp);
	
	for(int i=0;i<n;i++){
		med = med + valor[i];
	}
	printf("\nMédia dos preços: %.2f\n",med / n);
}

int main() {  // Faz o alocamento de memória e implementa as funções 
	int qtd;
	printf("Insira a quantidade de produtos a serem criados: ");
	scanf("%d",&qtd);
	t_produto *prods = malloc(qtd*sizeof(t_produto));  //variável dinâmica
	
	for(int i=0;i<qtd;i++){
		preencher(&prods[i]);
	}
	
	// Execução das funções:
	salvar_produtos_txt(qtd, prods);
	ler_produtos_txt(filepath);
	med_prc_txt(filepath,qtd);

	free(prods);

  return 0;
} 
