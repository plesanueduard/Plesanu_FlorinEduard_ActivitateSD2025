#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;
//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	//informatia utila si adresa urmatorului nod
	Masina info;
	Nod* urm;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(/*lista de masini*/ Nod* cap) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()
	while (cap != NULL)
	{
		//afisam informatia din nod
		afisareMasina(cap->info);
		cap = cap->urm;
	}

}

void adaugaMasinaInLista(/*lista de masini*/ Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;

	nou->urm = NULL;
	if ((*cap) == NULL)
	{
		*cap = nou;

	}
	else
	{//facem o copie lui *cap pentru ca daca l-am folosi am pierde acesarea lantului complet,asa ca merge copia pana la final + nodul nou
		Nod* p = *cap;
		//verific "daca am unde sa ma asez"
		while (p->urm)
		{
			p = p->urm;
		}
		p->urm = nou;
	}
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = *cap;
	*cap = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	//declaram si intializam
	Nod* lista = NULL;
	while (!feof(f))
	{
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f)); //extragem adresa pointerului - &
	}
	fclose(f);
	return lista;

}


float calculeazaPretMediu(Nod* lista) {
	//if (!lista)
		//return 0;
	int count = 0;
	float sum = 0;
	while (lista) {
		sum += lista->info.pret;
		count++;
		lista = lista->urm;
	}
	return (count>0) ?sum/count:0;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float sum=0;
	while(lista){
		if (strcmp(numeSofer, lista->info.numeSofer) == 0) {
			sum += lista->info.pret;
		}
		lista = lista->urm;
	}
	return sum;
}

void dezalocareListaMasini(Nod** cap) {
	while ((cap) != NULL) {
		Nod* aux = (*cap);
		*cap = (*cap)->urm;
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
	}
}

char* getCeaMaiScumpaMasina(Nod* lista) {
	float pretulMax=0;
	char* modelScump=NULL;
	while (lista) {
		if (lista->info.pret > pretulMax) {
			pretulMax = lista->info.pret;
			modelScump = lista->info.model;
		}
		lista = lista->urm;
	}
	if (pretulMax > 0) {
		char* nou = malloc(strlen(modelScump) + 1);
		strcpy_s(nou, strlen(modelScump) + 1, modelScump);
		return nou;
	}
	return NULL;
}

int main() {
	//adresa primului nod
	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	printf("%.2f \n",calculeazaPretMediu(cap));
	printf("%.2f \n",calculeazaPretulMasinilorUnuiSofer(cap,"Ionescu"));
	printf("%s", getCeaMaiScumpaMasina(cap));

	dezalocareListaMasini(&cap);

	return 0;
}