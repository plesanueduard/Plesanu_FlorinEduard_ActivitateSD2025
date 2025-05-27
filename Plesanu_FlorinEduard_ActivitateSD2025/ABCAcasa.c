#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
} Masina;

typedef struct Nod {
    Masina info;
    struct Nod* st;
    struct Nod* dr;
} Nod;

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    fgets(buffer, 100, file);
    char* token;
    Masina m;

    token = strtok(buffer, ",\n");
    m.id = atoi(token);
    m.nrUsi = atoi(strtok(NULL, ",\n"));
    m.pret = atof(strtok(NULL, ",\n"));

    token = strtok(NULL, ",\n");
    m.model = malloc(strlen(token) + 1);
    strcpy(m.model, token);

    token = strtok(NULL, ",\n");
    m.numeSofer = malloc(strlen(token) + 1);
    strcpy(m.numeSofer, token);

    m.serie = *strtok(NULL, ",\n");

    return m;
}

void afisareMasina(Masina m) {
    printf("Id: %d\n", m.id);
    printf("Nr usi: %d\n", m.nrUsi);
    printf("Pret: %.2f\n", m.pret);
    printf("Model: %s\n", m.model);
    printf("Nume sofer: %s\n", m.numeSofer);
    printf("Serie: %c\n\n", m.serie);
}

void adaugaMasinaInArbore(Nod** arbore, Masina m) {
    if (!(*arbore)) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = m;
        nou->st = NULL;
        nou->dr = NULL;
        *arbore = nou;
    }
    else {
        if (m.id < (*arbore)->info.id) {
            adaugaMasinaInArbore(&((*arbore)->st), m);
        }
        else if (m.id > (*arbore)->info.id) {
            adaugaMasinaInArbore(&((*arbore)->dr), m);
        }
    }
}

Nod* citireArboreDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    Nod* radacina = NULL;
    if (f) {
        while (!feof(f)) {
            Masina m = citireMasinaDinFisier(f);
            adaugaMasinaInArbore(&radacina, m);
        }
        fclose(f);
    }
    return radacina;
}

void afisareInOrdine(Nod* arbore) {
    if (arbore) {
        afisareInOrdine(arbore->st);
        afisareMasina(arbore->info);
        afisareInOrdine(arbore->dr);
    }
}

void afisarePreOrdine(Nod* arbore) {
    if (arbore) {
        afisareMasina(arbore->info);
        afisarePreOrdine(arbore->st);
        afisarePreOrdine(arbore->dr);
    }
}

void afisarePostOrdine(Nod* arbore) {
    if (arbore) {
        afisarePostOrdine(arbore->st);
        afisarePostOrdine(arbore->dr);
        afisareMasina(arbore->info);
    }
}

void dezalocareArbore(Nod** arbore) {
    if (*arbore) {
        dezalocareArbore(&(*arbore)->st);
        dezalocareArbore(&(*arbore)->dr);
        free((*arbore)->info.model);
        free((*arbore)->info.numeSofer);
        free(*arbore);
        *arbore = NULL;
    }
}

Masina getMasinaByID(Nod* arbore, int id) {
    Masina m;
    m.id = -1;
    if (arbore) {
        if (arbore->info.id < id) {
            return getMasinaByID(arbore->dr, id);
        }
        else if (arbore->info.id > id) {
            return getMasinaByID(arbore->st, id);
        }
        else {
            return arbore->info;
        }
    }
    return m;
}

int numarNoduri(Nod* arbore) {
    if (!arbore) return 0;
    return 1 + numarNoduri(arbore->st) + numarNoduri(arbore->dr);
}

int inaltimeArbore(Nod* arbore) {
    if (!arbore) return 0;
    int hSt = inaltimeArbore(arbore->st);
    int hDr = inaltimeArbore(arbore->dr);
    return 1 + (hSt > hDr ? hSt : hDr);
}

float pretTotal(Nod* arbore) {
    if (!arbore) return 0;
    return arbore->info.pret + pretTotal(arbore->st) + pretTotal(arbore->dr);
}

float pretTotalSofer(Nod* arbore, const char* nume) {
    if (!arbore) return 0;
    float suma = 0;
    if (strcmp(arbore->info.numeSofer, nume) == 0) {
        suma += arbore->info.pret;
    }
    suma += pretTotalSofer(arbore->st, nume);
    suma += pretTotalSofer(arbore->dr, nume);
    return suma;
}

int main() {
    Nod* radacina = citireArboreDinFisier("masini_arbore.txt");

    printf("Parcurgere in ordine:\n");
    afisareInOrdine(radacina);

    printf("Parcurgere post-ordine:\n");
    afisarePostOrdine(radacina);

    printf("Parcurgere pre-ordine:\n");
    afisarePreOrdine(radacina);

    int id = 8;
    printf("\nCautare masina cu id %d:\n", id);
    Masina m = getMasinaByID(radacina, id);
    if (m.id != -1) {
        afisareMasina(m);
    }
    else {
        printf("Masina nu a fost gasita.\n");
    }

    float total = pretTotal(radacina);
    printf("\nPret total masini: %.2f\n", total);

    const char* nume = "Popescu";
    float suma = pretTotalSofer(radacina, nume);
    printf("Pret total pentru soferul %s: %.2f\n", nume, suma);

    printf("Numar total noduri: %d\n", numarNoduri(radacina));
    printf("Inaltime arbore: %d\n", inaltimeArbore(radacina));

    dezalocareArbore(&radacina);
    return 0;
}
