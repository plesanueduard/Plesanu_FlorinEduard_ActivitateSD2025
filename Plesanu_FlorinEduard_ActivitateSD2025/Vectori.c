#include<stdio.h>
#include<malloc.h>
#define CRT_SECURE_NO_WARNINGS_

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id,int RAM,const char* producator,float pret,char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = RAM;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator)) + 1);
		strcpy_s(t.producator,strlen(producator)+1,producator);
		t.pret = pret;
		t.serie = serie;
	return t;
}

void afisare(struct Telefon t) {
	if (t.producator != NULL)
		{
			printf("%d Telefonul %s seria %c are ram: %d si costa %5.2f RON\n", t.id, t.producator, t.serie, t.RAM, t.pret); //fiecare % e pt afisare de fiecare variabila
		}
		else {
			printf("Telefonul din seria %c nu are producator",t.serie); //puteam sa pun si restul de variabile ca mi le arata pe toate inafara de cel din dezalocare
		}
}

void afisareVector(struct Telefon* vector, int nrElemente) {
	for (int i = 0;i < nrElemente;i++) {
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	struct Telefon *vectorNou=NULL;
	vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
	for (int i = 0;i < nrElementeCopiate;i++) {
		vectorNou[i] = vector[i];	
		vectorNou[i].producator = (char*)malloc(strlen(vector[i].producator) + 1); // de fiecare data cand avem pointer ii facem loc
		strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
	}
	return vectorNou;
}



void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0;i < nrElemente;i++) {
		if (vector[i].pret >= pretMinim) {
			(*dimensiune)++;
		}
	}
	if ((*vectorNou) != NULL) {
		free(vectorNou);
	}
	*vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * (*dimensiune));
	int k = 0;
	for (int i = 0;i < nrElemente;i++) {
		if (vector[i].pret >= pretMinim) {
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s((*vectorNou)[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);
			k++;
		}
	}
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	struct Telefon t;
	t.id = 1;

	return t;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	int i = 0;
	for (i = 0;i < (*nrElemente);i++)
	{
		if ((*vector)[i].producator != NULL) {
			free((*vector)[i].producator);
		}
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}


int main() {
	struct Telefon* telefoane=NULL;
	int nrTelefoane=3;
	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 128, "Motorola", 1000, 'M');
	telefoane[2] = initializare(3, 512, "Huawei", 2200, 'L');
	afisareVector(telefoane, nrTelefoane);

	struct Telefon* primeleTelefoane = NULL;
	int nrPrimeleTelefoane = 2;

	primeleTelefoane = copiazaPrimeleNElemente(telefoane,nrTelefoane,nrPrimeleTelefoane);
	printf("\n\n Primele telefoane: \n");
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);
	dezalocare(&primeleTelefoane,&nrPrimeleTelefoane);
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);

	struct Telefon* telefoaneScumpe=NULL;
	int nrTelefoaneScumpe = 0;
	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 1000, &telefoaneScumpe, &nrTelefoaneScumpe);
	printf("\n\nTelefoane scumpe:\n");
	afisareVector(telefoaneScumpe, nrTelefoaneScumpe);
	return 0;
}