#include<stdio.h>
#include<stdlib.h>

struct Telefon {
	int id;
	int ram;
	char* producator;
	float pret;
	char serie;
};

struct Telefon initializare(int id,int ram,const char* producator,float pret,char serie) {
	struct Telefon t;
	t.id = id;
	t.ram = ram;
	t.producator = (char*)malloc(sizeof(char)*(strlen(producator)+1));  //creeam loc pentru ce introducem de la tastatura
	strcpy_s(t.producator,strlen(producator)+1,producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

void afisare(struct Telefon t) {
	printf("%d Telefonul %s seria %c are ram: %d si costa %5.2f RON\n",t.id,t.producator,t.serie,t.ram,t.pret); //fiecare % e pt afisare de fiecare variabila
}

void modificaPret(struct Telefon* t,float pretNou) {
	if (pretNou > 0) {  
		t->pret = pretNou;  // daca nu foloseam pointer ne ramanea acelasi pret, practic trimitem din main prin adresa o valoare in functia asta
	}
}

void dezalocare(struct Telefon* t) {
}

int main() {
	struct Telefon t;
	t = initializare(1, 16, "Samsung",1600.25,'A');   // la char se pune '' iar la char* se pune"" adica un fel de string e char*
	afisare(t);
	modificaPret(&t, 1000); // trebuie folosit & ca sa preia valoarea in functie
	afisare(t);
	return 0;
}