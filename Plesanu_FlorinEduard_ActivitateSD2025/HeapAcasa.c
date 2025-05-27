#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float pret;
    char* model;
} Masina;

typedef struct {
    Masina* vector;
    int nrMasini;
    int capacitate;
} Heap;

Masina citireMasina(FILE* f) {
    Masina m;
    char buffer[100];
    fgets(buffer, 100, f);

    char* token = strtok(buffer, ",\n");
    m.id = atoi(token);

    token = strtok(NULL, ",\n");
    m.pret = atof(token);

    token = strtok(NULL, ",\n");
    m.model = (char*)malloc(strlen(token) + 1);
    strcpy(m.model, token);

    return m;
}

void afisareMasina(Masina m) {
    printf("Id: %d | Pret: %.2f | Model: %s\n", m.id, m.pret, m.model);
}

Heap initHeap(int capacitate) {
    Heap h;
    h.vector = (Masina*)malloc(sizeof(Masina) * capacitate);
    h.nrMasini = 0;
    h.capacitate = capacitate;
    return h;
}

void filtrare(Heap* h, int poz) {
    int max = poz;
    int st = 2 * poz + 1;
    int dr = 2 * poz + 2;

    if (st < h->nrMasini && h->vector[st].pret > h->vector[max].pret)
        max = st;
    if (dr < h->nrMasini && h->vector[dr].pret > h->vector[max].pret)
        max = dr;

    if (max != poz) {
        Masina aux = h->vector[poz];
        h->vector[poz] = h->vector[max];
        h->vector[max] = aux;
        filtrare(h, max);
    }
}

void adaugaInHeap(Heap* h, Masina m) {
    if (h->nrMasini < h->capacitate) {
        h->vector[h->nrMasini] = m;
        h->nrMasini++;
        for (int i = h->nrMasini / 2 - 1; i >= 0; i--) {
            filtrare(h, i);
        }
    }
}

Masina extrageMax(Heap* h) {
    Masina m = h->vector[0];
    h->vector[0] = h->vector[h->nrMasini - 1];
    h->nrMasini--;
    filtrare(h, 0);
    return m;
}

void elibereazaHeap(Heap* h) {
    for (int i = 0; i < h->nrMasini; i++) {
        free(h->vector[i].model);
    }
    free(h->vector);
}

int main() {
    FILE* f = fopen("masini.txt", "r");
    if (!f) {
        printf("Fisierul nu a putut fi deschis.\n");
        return 1;
    }

    Heap h = initHeap(10);
    while (!feof(f)) {
        Masina m = citireMasina(f);
        adaugaInHeap(&h, m);
    }
    fclose(f);

    printf("Masini in heap:\n");
    for (int i = 0; i < h.nrMasini; i++) {
        afisareMasina(h.vector[i]);
    }

    printf("\nMasini extrase in ordinea pretului:\n");
    while (h.nrMasini > 0) {
        Masina m = extrageMax(&h);
        afisareMasina(m);
        free(m.model);
    }

    elibereazaHeap(&h);
    return 0;
}
