#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date




struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod {
	Masina info;
	struct Nod* urmator;
	struct Nod* precedent;
}Nod;

typedef struct Lista {
	Nod* prim;
	Nod* ultim;
}Lista;

//creare structura pentru un nod dintr-o lista dublu inlantuita

//creare structura pentru Lista Dubla 

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
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

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

void afisareListaMasiniInceput(Lista list) {
	//pun -> doar daca am pointer
	Nod* p = list.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->urmator;
	}
}

//nu trebuia sa pun pointer pt ca nu modific lista in sine
//recomandat sa pun un pointer constant daca vreau sa folosesc
void adaugaMasinaInListaSF(Lista* list, Masina masinaNoua) {
	// la orice inserare creez nodul
	Nod* inserat = (Nod*)malloc(sizeof(Nod));
	inserat->info = masinaNoua; // shallow
	inserat->urmator = NULL;
	if (list->ultim) {
		list->ultim->urmator = inserat;
	}
	else {
		list->prim = inserat;
	}
	list->ultim = inserat;
}

void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->urmator = list->prim;
	p->precedent = NULL;
	if (list->prim) {
		list->prim->precedent = p;
	}
	else {
		list->ultim = p;
	}
	list->prim = p;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista list;
	list.prim = NULL;
	list.ultim = NULL;
	while (!feof(f)) {
	
		//adaugaMasinaInListaSF(&list, citireMasinaDinFisier(f));
		adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));
	}
	fclose(f);
	return list;
}

void afisareListaMasiniSf(Lista list) {
	Nod* p = list.ultim;
	while (p) {
		afisareMasina(p->info);
		p = p->precedent;
	}
}

void dezalocareLDMasini(Lista* lista) {
	
	Nod* p = lista->prim;
	while (p->urmator != NULL) {
		free(p->info.numeSofer);
		free(p->info.model);
		p = p->urmator;
		free(p->precedent);

	}
	free(p->info.numeSofer);
	free(p->info.model);
	free(p);
	lista->prim = NULL;
	lista->ultim = NULL;
}

float calculeazaPretMediu(Lista lista) {
	Nod* aux = lista.prim;
	float suma = 0;
	float cnt = 0;
	while (aux) {
		suma += aux->info.pret;
		cnt++;
		aux = aux->urmator;
	}
	return suma/cnt;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {
	Lista list;
	list = citireLDMasiniDinFisier("Masini.txt");
	//afisareListaMasiniInceput(list);
	afisareListaMasiniSf(list);
	float pretMediu = calculeazaPretMediu(list);
	printf("Pret mediu %.2f", pretMediu);
	dezalocareLDMasini(&list);
	return 0;
}