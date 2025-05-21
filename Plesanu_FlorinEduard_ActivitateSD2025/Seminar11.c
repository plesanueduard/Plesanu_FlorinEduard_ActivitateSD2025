#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraMasina Masina;
struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    if (!fgets(buffer, 100, file)) {
        Masina gol = { 0, 0, 0.0f, NULL, NULL, 0 };
        return gol;
    }

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

    aux = strtok(NULL, sep);
    m1.serie = aux[0];

    return m1;
}

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr. usi: %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n", masina.serie);
}

typedef struct NodListaPrincipala NodListaPrincipala;
typedef struct NodListaSecundara NodListaSecundara;

struct NodListaPrincipala {
    NodListaPrincipala* next;
    NodListaSecundara* vecini;
    Masina info;
};

struct NodListaSecundara {
    NodListaPrincipala* info;
    NodListaSecundara* next;
};

NodListaPrincipala* inserareListaPrincipala(NodListaPrincipala* cap, Masina info) {
    NodListaPrincipala* nou = (NodListaPrincipala*)malloc(sizeof(NodListaPrincipala));
    nou->info = info;
    nou->next = NULL;
    nou->vecini = NULL;

    if (!cap)
        return nou;

    NodListaPrincipala* p = cap;
    while (p->next)
        p = p->next;
    p->next = nou;

    return cap;
}

NodListaSecundara* inserareListaSecundara(NodListaSecundara* cap, NodListaPrincipala* info) {
    NodListaSecundara* nou = (NodListaSecundara*)malloc(sizeof(NodListaSecundara));
    nou->info = info;
    nou->next = cap;
    return nou;
}

NodListaPrincipala* cautaNodDupaID(NodListaPrincipala* listaPrincipala, int id) {
    while (listaPrincipala && listaPrincipala->info.id != id)
        listaPrincipala = listaPrincipala->next;
    return listaPrincipala;
}

void inserareMuchie(NodListaPrincipala* listaPrincipala, int idStart, int idStop) {
    NodListaPrincipala* nodStart = cautaNodDupaID(listaPrincipala, idStart);
    NodListaPrincipala* nodStop = cautaNodDupaID(listaPrincipala, idStop);
    if (nodStart && nodStop) {
        nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
        nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
    }
}

NodListaPrincipala* citireNoduriMasiniDinFisier(const char* numeFisier) {
    NodListaPrincipala* listaPrincipala = NULL;
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului %s\n", numeFisier);
        return NULL;
    }
    while (!feof(f)) {
        Masina m = citireMasinaDinFisier(f);
        if (m.model != NULL && m.numeSofer != NULL) {
            listaPrincipala = inserareListaPrincipala(listaPrincipala, m);
        }
    }
    fclose(f);
    return listaPrincipala;
}

void citireMuchiiDinFisier(NodListaPrincipala* listaPrincipala, const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului %s\n", numeFisier);
        return;
    }
    int idStart, idStop;
    while (fscanf(f, "%d %d", &idStart, &idStop) == 2)
        inserareMuchie(listaPrincipala, idStart, idStop);
    fclose(f);
}

void stergereListaSecundara(NodListaSecundara** cap) {
    NodListaSecundara* aux;
    while ((*cap)) {
        aux = (*cap)->next;
        free(*cap);
        (*cap) = aux;
    }
}

void dezalocareNoduriGraf(NodListaPrincipala** listaPrincipala) {
    NodListaPrincipala* aux;
    while ((*listaPrincipala)) {
        aux = (*listaPrincipala)->next;
        stergereListaSecundara(&((*listaPrincipala)->vecini));
        free((*listaPrincipala)->info.model);
        free((*listaPrincipala)->info.numeSofer);
        free(*listaPrincipala);
        *listaPrincipala = aux;
    }
}

void afisareGraf(NodListaPrincipala* cap) {
    while (cap) {
        afisareMasina(cap->info);
        printf("Vecini: ");
        NodListaSecundara* v = cap->vecini;
        while (v) {
            printf("%d ", v->info->info.id);
            v = v->next;
        }
        printf("\n\n");
        cap = cap->next;
    }
}

int main() {
    NodListaPrincipala* graf = citireNoduriMasiniDinFisier("masini.txt");
    if (graf == NULL) {
        return -1;
    }

    citireMuchiiDinFisier(graf, "muchii.txt");

    printf("=== GRAF ===\n\n");
    afisareGraf(graf);

    dezalocareNoduriGraf(&graf);

    return 0;
}
