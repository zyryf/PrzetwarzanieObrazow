#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>

void odczyt(struct zdjecie *grafika,int wielkosc_grafika);
void spr_komentarz(FILE *plik);
void zapis(struct zdjecie *grafika, int indeks_akt_obrazu);
struct zdjecie* dod_do_tablicy(struct zdjecie *grafika, int wielkosc_grafika);
void progowanie(struct zdjecie *grafika, int indeks_akt_obrazu);
void negatyw(struct zdjecie *grafika, int indeks_akt_obrazu);
void obrot_o_kat(struct zdjecie *grafika, int indeks_akt_obrazu);
void histogram(struct zdjecie *grafika, int indeks_akt_obrazu);
void pieprz_sol(struct zdjecie *grafika, int indeks_akt_obrazu);
struct zdjecie* usuwanie_z_tablicy(struct zdjecie *grafika, int indeks_akt_obrazu, int wielkosc_grafika);

struct zdjecie
{
	char *standard;
	char *nazwa;
	int wysokosc;
	int szerokosc;
	int max_szarosc;
	int **piksele; 

};


int main(void)
{
	
	struct zdjecie *grafika; // stworzenie tablicy struktor
	int wielkosc_grafika = 1;
	grafika = malloc(wielkosc_grafika * sizeof(struct zdjecie)); // tablica posiada na poczatek 1 strukture
	
	
	
	printf("\n MENU UZYSTKOWNIKA\n");
	printf("1. Zaladuj obraz\n");
	printf("2. Wyswietlenie tablicy struktur\n");
	printf("3. Usun aktywny obraz\n");
	printf("4. Wybranie obrazu na ktorym chcesz pracowac(obrazu aktywnego)\n");
	printf("5. Progowanie\n");
	printf("6. Negatyw\n");
	printf("7. Odbicie o kat 90 stopni\n");
	printf("8. Histogram\n");
	printf("9. Pieprz i sol\n");
	printf("10. Zapis obrazu\n");
	printf("11. Wyjscie\n");
	
	int wybor;
	int pozycja_wyswietlenie;
	int spr_zaladowanie = 0;
	char *obraz_praca;
	obraz_praca = malloc(20 * sizeof(char));
	int pozycja_praca;
	int indeks_akt_obrazu = 0;
	int spr_aktywny = 0;
	
	for (;;) //nieskonczona petla - program zakonczy sie dopiero gdy uzytkownik wybierze taka opcja w menu
	{

		
		
		printf("\nPodaj nr operacji ktora chcesz wykonac:");

		while (scanf("%d", &wybor) == 0) // idiotopodornosc
		{
			printf("blad nie jest to liczba\n");
			int c;
			while ((c = getchar()) != '\n');
		}
		int c;
		while ((c = getchar()) != '\n');

		
		
		switch (wybor)
		{
		
		case 1:
			
			odczyt(grafika, wielkosc_grafika); 
			grafika = dod_do_tablicy(grafika,wielkosc_grafika);
			wielkosc_grafika++;
			spr_zaladowanie = 1;
			
			printf("Zaladowano!\n");
			break;
		case 2:
			
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			
			if (spr_aktywny == 1)
			{
				printf("\n OBRAZ NA KTORYM PRACUJESZ---->%s\n", grafika[indeks_akt_obrazu].nazwa);
			}
				


			for (pozycja_wyswietlenie = 0; pozycja_wyswietlenie < wielkosc_grafika - 1; pozycja_wyswietlenie++)
			{
				printf("\n%d ELEMENT TABLICY STRUKTUR---->%s\n", pozycja_wyswietlenie + 1, grafika[pozycja_wyswietlenie].nazwa);		
			}

			break;
		case 3:
			
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			
			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}
			
			
		   grafika = usuwanie_z_tablicy(grafika, indeks_akt_obrazu, wielkosc_grafika);
		   wielkosc_grafika--;
		   spr_aktywny = 0;
			printf("Usunieto obraz\n");

		case 4:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}

			
		wejscie:
			printf("Podaj nazwa obrazu (razem z typem np.pgm) na ktorym chcesz pracowac\n");
			scanf("%s", obraz_praca);


			for (pozycja_praca=0; pozycja_praca < wielkosc_grafika - 1; pozycja_praca++)
			{

				if (strcmp(grafika[pozycja_praca].nazwa, obraz_praca) == 0) // porowanie czy dwa wyrazy sa sobie rowne
				{
					indeks_akt_obrazu = pozycja_praca;
					printf("Dzialasz na obrazie %s\n", grafika[indeks_akt_obrazu].nazwa);
					spr_aktywny = 1;
					break;

				}

			}

			if (spr_aktywny == 0)
			{
				printf("Nie ma takiego obrazu!\n");
				
				goto wejscie;
			}
			break;
		case 5:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}

			
			progowanie(grafika, indeks_akt_obrazu);
			printf("Zastosowano progowanie.\n");
			break;
		case 6:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}

			negatyw(grafika, indeks_akt_obrazu);
			printf("Zastosowano negatyw.\n");
			break;
		case 7:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}

			obrot_o_kat(grafika, indeks_akt_obrazu);
			
			printf("Obrocono o kat 90 stopni.\n");

			break;
		case 8:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}


			histogram(grafika, indeks_akt_obrazu);

			break;
		case 9:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}
			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}

			pieprz_sol(grafika, indeks_akt_obrazu);
			printf("Zastosowano filtr pieprz i sol\n");

			break;
		case 10:
			if (spr_zaladowanie == 0)
			{
				printf("Nie zaladowano zadnego obrazu!\n");
				break;
			}

			if (spr_aktywny == 0)
			{
				printf("Nie wybrano aktywnego obrazu!\n");
				break;
			}

			zapis(grafika, indeks_akt_obrazu);
			printf("Obraz zostal zapisany!\n");

			break;									
			
		case 11:
			exit(0);
		default:
			printf("W menu nie ma takiej opcji!\n");
			break;
			}

		}	
	system("PAUSE");

}

void odczyt(struct zdjecie *grafika, int wielkosc_grafika )
{
	
	grafika[wielkosc_grafika-1].standard = malloc(2 * sizeof(char));
	grafika[wielkosc_grafika-1].nazwa = malloc(20 * sizeof(char));
	
    poczatek:

	printf("Podaj nazwe pliku ( razem z typem np.pgm) jaki chcesz otworzyc: ");
	scanf("%s", grafika[wielkosc_grafika-1].nazwa);
	
	
	FILE *plik;
	
	plik = fopen(grafika[wielkosc_grafika - 1].nazwa, "r");
	
	if (fopen(grafika[wielkosc_grafika - 1].nazwa, "r") == NULL) // sprawdzanym czy udalo sie otowrzyc plik
	{
		printf("Nie ma takiego pliku!\n");
		goto poczatek;
	}
	
		
	spr_komentarz(plik);

	fscanf(plik, "%c %c ", &grafika[wielkosc_grafika - 1].standard[0], &grafika[wielkosc_grafika - 1].standard[1]); //zczytywanie standardu
	
    spr_komentarz(plik);
	
	fscanf(plik, "%d ", &grafika[wielkosc_grafika - 1].szerokosc); //zczytywanie szerokosc
	
	spr_komentarz(plik);

	fscanf(plik, "%d", &grafika[wielkosc_grafika - 1].wysokosc); //zczytywanie wysokosc
	
	spr_komentarz(plik);
	
	fscanf(plik, "%d", &grafika[wielkosc_grafika - 1].max_szarosc); //zczytywanie max szarosci

	start:
	grafika[wielkosc_grafika - 1].piksele = malloc(grafika[wielkosc_grafika - 1].wysokosc * sizeof(*grafika[wielkosc_grafika - 1].piksele));  //dynamicznie alokowianie tablicy dwuwymiarowej
	int i;
	
	if (grafika[wielkosc_grafika - 1].piksele != NULL) //zabezpieczenie przed wyciekami pamieci
	{
		for (i = 0; i < grafika[wielkosc_grafika - 1].wysokosc; i++)
		{
			grafika[wielkosc_grafika - 1].piksele[i] = malloc(grafika[wielkosc_grafika - 1].szerokosc * sizeof(grafika[wielkosc_grafika - 1].piksele)); // dynamic
		}
		if (grafika[wielkosc_grafika - 1].piksele[i] == NULL)
		{
			for (i = 0; i < grafika[wielkosc_grafika - 1].wysokosc; i++)
			{
				free(grafika[wielkosc_grafika - 1].piksele[i]);
			}
			free(grafika[wielkosc_grafika - 1].piksele);
			goto start;

		}
	}
	else
	{
		
		printf("Niepowodzenie alokacji!\n");
		goto start;
		
	}

	int pozycja_1;
	int pozycja_2;
	for (pozycja_2=0; pozycja_2 < grafika[wielkosc_grafika - 1].wysokosc; pozycja_2++)
	{

        for (pozycja_1=0; pozycja_1 < grafika[wielkosc_grafika - 1].szerokosc; pozycja_1++)
		{
			spr_komentarz(plik);
			fscanf(plik, "%d", &grafika[wielkosc_grafika - 1].piksele[pozycja_2][pozycja_1]);

        }
	
	}
	
	fclose(plik);	
}

void zapis(struct zdjecie *grafika, int indeks_akt_obrazu)
{
	
	FILE *plik;
  
	char nazwa[20];
	printf("Podaj nazwe pliku do ktorego chcesz zapisac obraz\n");
	scanf("%s", nazwa);

	plik = fopen(nazwa, "w");

	fprintf(plik,"%c%c\n", grafika[indeks_akt_obrazu].standard[0], grafika[indeks_akt_obrazu].standard[1]);
	fprintf(plik, "%d %d\n", grafika[indeks_akt_obrazu].szerokosc, grafika[indeks_akt_obrazu].wysokosc);
	fprintf(plik, "%d\n", grafika[indeks_akt_obrazu].max_szarosc);


	int pozycja_1;
	int pozycja_2;
	for (pozycja_2 = 0; pozycja_2 < grafika[indeks_akt_obrazu].wysokosc; pozycja_2++)
	{

		for (pozycja_1 = 0; pozycja_1 < grafika[indeks_akt_obrazu].szerokosc; pozycja_1++)
		{
			
			fprintf(plik, "%d ", grafika[indeks_akt_obrazu].piksele[pozycja_2][pozycja_1]);

		}

		fprintf(plik, "\n");

	}
	
	fclose(plik);
	
}

void spr_komentarz(FILE *plik)
{
	char c;
	fscanf(plik, "%c", &c);
	
	
	while (c == '#')
	{
		
	  while (c != '\n')
		{
			fscanf(plik, "%c", &c);
		}
		
	
		fscanf(plik, "%c", &c);
	}
	fseek(plik, -1, SEEK_CUR);
	
}

struct zdjecie* dod_do_tablicy(struct zdjecie *grafika, int wielkosc_grafika)
{
	//realokowanie tablicy o jenda strukture wiecej
	struct zdjecie *temp;

poczatek:

	temp = realloc(grafika, (wielkosc_grafika + 1) * sizeof(struct zdjecie));
	if (temp != NULL) // sprawdzenie powodzenia realokacji
	{
		grafika = temp;
	}
	else
	{
		free(temp);
		goto poczatek;
	}

	

	return grafika;
}

void progowanie(struct zdjecie *grafika, int indeks_akt_obrazu)
{
	int prog_rozdzielenia;
	
	printf("Podaj prog rodzielenia\n");
	
	while (scanf("%d", &prog_rozdzielenia) == 0) // idiotopodornosc
	{
		printf("blad nie jest to liczba\n");
		int c;
		while ((c = getchar()) != '\n');
	}
	int c;
	while ((c = getchar()) != '\n');

	if (prog_rozdzielenia >= grafika[indeks_akt_obrazu].max_szarosc)
	{
		printf("Prog rozdzielenia jest wiekszy lub rowny maksymalnej szarosci!\n");
	}
	
	int pozycja_1;
	int pozycja_2;
	for (pozycja_2 = 0; pozycja_2 <grafika[indeks_akt_obrazu].szerokosc; pozycja_2++)
	{

		for (pozycja_1 = 0; pozycja_1 <grafika[indeks_akt_obrazu].wysokosc; pozycja_1++)
		{
			
			if (grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2] < prog_rozdzielenia)
			{
				grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2] = 0;
			}
			else
			{
				grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2] = grafika[indeks_akt_obrazu].max_szarosc;
			}

		}

	}

}

void negatyw(struct zdjecie *grafika, int indeks_akt_obrazu)
{

	int pozycja_1;
	int pozycja_2;
	for (pozycja_2 = 0; pozycja_2 <grafika[indeks_akt_obrazu].szerokosc; pozycja_2++)
	{

		for (pozycja_1 = 0; pozycja_1 <grafika[indeks_akt_obrazu].wysokosc; pozycja_1++)
		{

			grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2] = grafika[indeks_akt_obrazu].max_szarosc - grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2];
				
		}
	}
}

void obrot_o_kat(struct zdjecie *grafika, int indeks_akt_obrazu)
{
	int **tablica_pomoc;// tworze tablica pomocnicza o wymiarach takich jak grafika.piksele
	tablica_pomoc = malloc(grafika[indeks_akt_obrazu].wysokosc*sizeof(*tablica_pomoc)); //dynamiczna alokacja
	 if(tablica_pomoc != NULL)
	{
		 int pozycja;
		 for (pozycja = 0; pozycja < grafika[indeks_akt_obrazu].wysokosc; pozycja++)
		 {
			 tablica_pomoc[pozycja] = malloc(grafika[indeks_akt_obrazu].szerokosc*sizeof(**tablica_pomoc));

			 if (tablica_pomoc[pozycja] == NULL)
			 {
				 printf("Nie udalo sie zaalkowac pamieci\n");
			 }
		 
		 
		 }
			 
	}
	  
	 int pozycja_x;
	 int pozycja_y;
	 for (pozycja_y = 0; pozycja_y <grafika[indeks_akt_obrazu].szerokosc; pozycja_y++)
	 {

		 for (pozycja_x = 0; pozycja_x <grafika[indeks_akt_obrazu].wysokosc; pozycja_x++)
		 {

			 tablica_pomoc[pozycja_x][pozycja_y] = grafika[indeks_akt_obrazu].piksele[pozycja_x][pozycja_y]; /*
																									  
																									  przypisanie wartosci
																									  grafika.piskele do tablica_pomoc
																									  */
																									   
		 }

	 } 
	 
	
	int pozycja_z;
	for (pozycja_z = 0; pozycja_z < grafika[indeks_akt_obrazu].wysokosc; pozycja_z++) //zwalniam po szerokosci
	{

		free(grafika[indeks_akt_obrazu].piksele[pozycja_z]);

	}

			
	free(grafika[indeks_akt_obrazu].piksele); //zawlniam pamiec tablicy grafika.piksele
		
		
	int temp = grafika[indeks_akt_obrazu].szerokosc;

	grafika[indeks_akt_obrazu].szerokosc = grafika[indeks_akt_obrazu].wysokosc;  //zamiana wysokosc i szerokosc tablicy
	grafika[indeks_akt_obrazu].wysokosc = temp;

		grafika[indeks_akt_obrazu].piksele = malloc(grafika[indeks_akt_obrazu].wysokosc * sizeof(*(grafika[indeks_akt_obrazu].piksele))); //dynamiczna alokacja
	if (grafika[indeks_akt_obrazu].piksele != NULL)
	{
		int pozycja;
		for (pozycja = 0; pozycja < grafika[indeks_akt_obrazu].wysokosc; pozycja++)
		{
			grafika[indeks_akt_obrazu].piksele[pozycja] = malloc(grafika[indeks_akt_obrazu].szerokosc * sizeof(**(grafika[indeks_akt_obrazu].piksele)));

			if (grafika[indeks_akt_obrazu].piksele == NULL)
			{
				printf("Nie udalo sie zaalokowac pamieci\n");
			}


		}
	}
	
	int pozycja_1;
	int pozycja_2;
	
	for (pozycja_2 = 0; pozycja_2 < grafika[indeks_akt_obrazu].szerokosc; pozycja_2++)
	{

		for (pozycja_1 = 0; pozycja_1 < grafika[indeks_akt_obrazu].wysokosc; pozycja_1++)
		{

			grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2] = tablica_pomoc[pozycja_2][pozycja_1]; //zamiana wierszy z kolumnami
			
		}
		
	}		
}

void histogram(struct zdjecie *grafika, int indeks_akt_obrazu)
{
	int *tablica;
	int wielkosc_tablicy = grafika[indeks_akt_obrazu].max_szarosc + 1;
	tablica = calloc(wielkosc_tablicy,sizeof(int));

	int pozycja_1;
	int pozycja_2;
	for (pozycja_2 = 0; pozycja_2 <grafika[indeks_akt_obrazu].szerokosc; pozycja_2++)
	{

		for (pozycja_1 = 0; pozycja_1 <grafika[indeks_akt_obrazu].wysokosc; pozycja_1++)
		{

			tablica[grafika[indeks_akt_obrazu].piksele[pozycja_1][pozycja_2]]++;
		}

	}

	FILE *plik;

	plik = fopen("histogram.csv", "w");
	
	int test = 0;
	
	int pozycja;
	for (pozycja = 0; pozycja < wielkosc_tablicy; pozycja++)
	{

		fprintf(plik, "%d;%d\n", pozycja, tablica[pozycja]);
		test++;

	}

	fclose(plik);
	

	printf("Hisogram zostal zapisany do pliku histogram.csv\n");

}

void pieprz_sol(struct zdjecie *grafika, int indeks_akt_obrazu)
{

	srand((unsigned int)time(NULL));
	int random = rand() % (grafika[indeks_akt_obrazu].szerokosc*grafika[indeks_akt_obrazu].wysokosc)+4000; /*randomowa ilosc zaszumionych
																										 probek w w przedziale od 4000
																										 do maksymalnej ilosc pikseli*/
	int random_1; 
	int random_2;
	int random_3;

    int pozycja;
	
	
	for (pozycja= 0; pozycja < random; pozycja++)
	{
		random_1 = rand() % grafika[indeks_akt_obrazu].wysokosc; // randomowa wysokosc tablicy pikseli
		random_2 = rand() % grafika[indeks_akt_obrazu].szerokosc; //randomowa szeroksc tablicy pikseli
		random_3 = rand() % 2; // liczba 0 lub 1;

		if (random_3 == 0)
		{
			grafika[indeks_akt_obrazu].piksele[random_1][random_2] = 0;
		}
		else
		{
			grafika[indeks_akt_obrazu].piksele[random_1][random_2] = grafika[indeks_akt_obrazu].max_szarosc;
		}
	}
			
}

struct zdjecie* usuwanie_z_tablicy(struct zdjecie *grafika, int indeks_akt_obrazu, int wielkosc_grafika)
{
	
	
	free(grafika[indeks_akt_obrazu].nazwa);
	free(grafika[indeks_akt_obrazu].standard);
	

	int pozycja;

	for (pozycja = 0; pozycja < grafika[indeks_akt_obrazu].wysokosc; pozycja++)
	{
		free(grafika[indeks_akt_obrazu].piksele[pozycja]);
	}

	free(grafika[indeks_akt_obrazu].piksele);

	
	
	int i;

	for (i = indeks_akt_obrazu; i < wielkosc_grafika - 1; i++) //przesuwam obrazy ktore znajdowaly sie w dalszych pozycjach o jeden w dol
	{
		grafika[i] = grafika[i + 1];
	}
	

	
	struct zdjecie *temp;
	temp = realloc(grafika, (wielkosc_grafika-1) * sizeof(struct zdjecie));
	if (temp != NULL)
	{
		grafika = temp;
	}
	else
	{
		printf("Niepowodzenie realokacji!\n");
	}
	
	
	
	return grafika;
}

