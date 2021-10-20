#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student
{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
} student;

int ProcitajBrRedakaIzDatoteke(char *nazivDatoteke);
student *AlocirajMemorijuProcitajStudente(int brojStudenata, char *nazivDatoteke);

int main()
{
    int brStudenata = 0;
    char datoteka[1024];
    student *studenti = NULL;
    int j = 0;
    int i = 0;
    double maxBrBodova = 0;
    double relativniBodovi = 0;

    printf("Upisi ime datoteke: ");
    scanf(" %s", &datoteka);

    brStudenata = ProcitajBrRedakaIzDatoteke(datoteka);
    if (brStudenata != -1)
    {
        printf("Broj studenata: %d\n", brStudenata);
    }

    studenti = AlocirajMemorijuProcitajStudente(brStudenata, datoteka);
    if (studenti != NULL)
    {
        maxBrBodova = studenti[0].bodovi;
        while (i < brStudenata)
        {
            if (studenti[i].bodovi > maxBrBodova)
            {
                maxBrBodova = studenti[i].bodovi;
            }
            i++;
        }
        while (j < brStudenata)
        {
            relativniBodovi = (studenti[j].bodovi / maxBrBodova) * 100;
            printf("\nIme: %s  Prezime: %s  Apsolutni bodovi: %lf  Relativni bodovi: %lf", studenti[j].ime, studenti[j].prezime, studenti[j].bodovi, relativniBodovi);
            j++;
        }
    }

    return 0;
}

int ProcitajBrRedakaIzDatoteke(char *nazivDatoteke)
{
    FILE *datoteka = NULL;
    char buffer[MAX_LINE] = {0};
    int br = 0;

    datoteka = fopen(nazivDatoteke, "r");
    if (!datoteka)
    {
        printf("greska");
        return -1;
    }
    while (!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        br++;
    }

    fclose(datoteka);
    return br;
}

student *AlocirajMemorijuProcitajStudente(int brojStudenata, char *nazivDatoteke)
{
    FILE *datoteka = NULL;
    student *studenti = NULL;
    int i = 0;

    studenti = (student *)malloc(brojStudenata * sizeof(student));
    datoteka = fopen(nazivDatoteke, "r");

    if (!datoteka)
    {
        printf("greska alociranja");
        free(studenti);
        return NULL;
    }
    while (!feof(datoteka))
    {
        fscanf(datoteka, " %s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        i++;
    }

    fclose(datoteka);
    return studenti;
}
