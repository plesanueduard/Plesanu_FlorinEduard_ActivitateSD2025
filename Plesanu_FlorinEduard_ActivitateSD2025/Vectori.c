#include<stdio.h>
#include<malloc.h>

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

struct Sablon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	struct Telefon *vectorNou=NULL;

	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
}

void copiazaAnumiteElemente(struct Telefon* vector, char nrElemente, float prag, struct Telefon** vectorNou, int* dimensiune) {
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	struct Telefon t;
	t.id = 1;

	return t;
}
	


int main() {
	struct Telefon* telefoane=NULL;
	int nrTelefoane=3;
	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 128, "Motorola", 1000, 'M');
	telefoane[2] = initializare(3, 512, "Huawei", 3000, 'L');
	afisareVector(telefoane, nrTelefoane);
	return 0;
}