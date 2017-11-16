#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>

#define kategoria_size  50
#define znacka_size  50
#define predajca_size  100
#define stav_vozidla_size  200

typedef struct auta
{
	char *kategoria;
	char *znacka;
	char *predajca;
	int cena;
	int rok_vyroby;
	char *stav_vozidla;
	struct auta *dalsi;

}AUTA;

void	fnc_n();
char*	safe_copy_string(FILE *f);
int		safe_copy_int(FILE *f);


void main() {
	char function_char;

	function_char = 'a';

	while (function_char != 'k') {
		scanf("%c", &function_char);
		
		switch (function_char)
		{
		case 'n':
			fnc_n();
			
			break;
		case 'v':
			printf("treba spravit\n");
			break;
		default:
			break;
		}

	}

	return;
}

void fnc_n() {
	FILE *file_to_read;
	AUTA *auta_first, *auta_act;
	int number_of_records, type_of_record;
	char ch, *buffer_string;

	number_of_records = 0;
	auta_first = NULL;
	auta_act = NULL;

	file_to_read = fopen("auta.txt", "r");
	if (file_to_read == NULL) {
		printf("Zaznamy nebolu nacitane\n");
		return;
	}

	buffer_string = (char *)malloc(51 * sizeof(char));
	if (buffer_string == NULL) {
		printf("Buffer string allocation error");
	}


	auta_first = (AUTA *)malloc(sizeof(AUTA));
	auta_act = (AUTA *)malloc(sizeof(AUTA));

	auta_first->kategoria = (char*)malloc(kategoria_size * sizeof(char));
	auta_first->znacka = (char*)malloc(znacka_size * sizeof(char));
	auta_first->predajca = (char*)malloc(predajca_size * sizeof(char));
	auta_first->stav_vozidla = (char*)malloc(stav_vozidla_size * sizeof(char));



	while (!feof(file_to_read)) {
		if ((ch = fgetc(file_to_read)) == '$') {
			number_of_records++;
			printf("%c%d\n", ch, number_of_records);
		}
		else
		{
			auta_act->kategoria = (char*)malloc(kategoria_size * sizeof(char));
			auta_act->znacka = (char*)malloc(znacka_size * sizeof(char));
			auta_act->predajca = (char*)malloc(predajca_size * sizeof(char));
			auta_act->stav_vozidla = (char*)malloc(stav_vozidla_size * sizeof(char));
			auta_act->dalsi = NULL;

			auta_act->kategoria = safe_copy_string(file_to_read);
			printf("%s\n", auta_act->kategoria);
			auta_act->znacka = safe_copy_string(file_to_read);
			printf("%s\n", auta_act->znacka);
			auta_act->predajca = safe_copy_string(file_to_read);
			printf("%s\n", auta_act->predajca);
			auta_act->cena = safe_copy_int(file_to_read);
			printf("%d\n", auta_act->cena);
			auta_act->rok_vyroby = safe_copy_int(file_to_read);
			printf("%d\n", auta_act->rok_vyroby);
			auta_act->stav_vozidla = safe_copy_string(file_to_read);
			printf("%s\n", auta_act->stav_vozidla);

			if (number_of_records == 1) {
				auta_first = auta_act;
				printf("\n1 == %s\n", auta_first->kategoria);
				auta_act = auta_act->dalsi;
				auta_act = (AUTA *)malloc(sizeof(AUTA));
				auta_act->kategoria = (char*)malloc(kategoria_size * sizeof(char));
				auta_act->znacka = (char*)malloc(znacka_size * sizeof(char));
				auta_act->predajca = (char*)malloc(predajca_size * sizeof(char));
				auta_act->stav_vozidla = (char*)malloc(stav_vozidla_size * sizeof(char));
				auta_act->dalsi = NULL;
			}
			else
			{
				auta_act = auta_act->dalsi;
				auta_act = (AUTA *)malloc(sizeof(AUTA));
				auta_act->kategoria = (char*)malloc(kategoria_size * sizeof(char));
				auta_act->znacka = (char*)malloc(znacka_size * sizeof(char));
				auta_act->predajca = (char*)malloc(predajca_size * sizeof(char));
				auta_act->stav_vozidla = (char*)malloc(stav_vozidla_size * sizeof(char));
				auta_act->dalsi = NULL;
			}
			printf("________________hotovo \n");
			printf("%s\n", auta_first->kategoria);
			printf("%s\n________________\n", auta_first->znacka);
		}
	}
}

char*	safe_copy_string(FILE *f) {
	/*
	* making of string from  file
	*	copy from file until the '\n'
	*	'\n' replaced by '\0'
	*	returned the string
	*/
	char buffer_char = '\0';
	char *buffer_string = NULL;
	int i = 0;

	//allocation of *buffer_string
	//need to change the 51 nuber to dinamic number
	buffer_string = (char *)malloc(51 * sizeof(char));
	if (buffer_string == NULL) {
		printf("error");
	}

	for (i = 0; i < 50 ; i++) {
		buffer_char = fgetc(f);
		if ((buffer_char == '\n')||(feof(f))){
			buffer_string[i] = '\0';
			break;
		}
		buffer_string[i] = buffer_char;
	}

	return buffer_string;
}

int	safe_copy_int(FILE *f) {
	char integer_str[11];
	int integer;

	for (int i = 0; i < 11; i++) {
		integer_str[i] = fgetc(f);
		if (integer_str[i] == '\n') {
			integer_str[i] = '\0';
			break;
		}
	}
	sscanf(integer_str, "%d", &integer);

	return integer;
}