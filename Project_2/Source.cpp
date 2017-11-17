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
	struct auta * dalsi;

}AUTA;

void	fnc_n(AUTA **auta_first);
void	fnc_v(AUTA *auta_first);
void	fnc_p(AUTA **auta_first);

//custom function for cleaner code
char*	safe_copy_string_form_file(FILE *f);
int		safe_copy_int_from_file(FILE *f);
void	alloc_auta(AUTA* auta_alloc);



void main() {
	AUTA *auta_first;
	char function_char;

	auta_first = NULL;
	function_char = 'a';

	while (function_char != 'k') {
		scanf("%c", &function_char);
		
		switch (function_char)
		{
		case 'n':
			fnc_n(&auta_first);			
			break;
		case 'v':
			fnc_v(auta_first);
			break;
		case 'p':
			fnc_p(&auta_first);
		default:
			break;
		}

	}

	return;
}

void fnc_n(AUTA **auta_first) {
	FILE *file_to_read;
	AUTA *auta_act;
	int number_of_records, type_of_record;
	char ch;

	//inicialization of variables
	number_of_records = 0;


	//opening of file
	file_to_read = fopen("auta.txt", "r");
	if (file_to_read == NULL) {
		printf("Zaznamy nebolu nacitane\n");
		return;
	}

	//inicial allocation of struct + error handling
	auta_act = (AUTA *)malloc(sizeof(AUTA));
	if (auta_act == NULL) {
		printf("nedostatok pamati\n");
	}
	auta_act->dalsi = NULL;
	*auta_first = auta_act;



	while (!feof(file_to_read)) {
		//recognizing start and counting of records
		if ((ch = fgetc(file_to_read)) == '$') {
			number_of_records++;
		
		}
		else if (ch == '\0') {
			break;
		}
		else
		{
			alloc_auta(auta_act);

			//reading from file and saving it to linked list
			auta_act->kategoria = safe_copy_string_form_file(file_to_read);
			auta_act->znacka = safe_copy_string_form_file(file_to_read);
			auta_act->predajca = safe_copy_string_form_file(file_to_read);
			auta_act->cena = safe_copy_int_from_file(file_to_read);
			auta_act->rok_vyroby = safe_copy_int_from_file(file_to_read);
			auta_act->stav_vozidla = safe_copy_string_form_file(file_to_read);

			if (number_of_records == 1) {
				auta_act->dalsi = (auta*)malloc(sizeof(auta));
				alloc_auta(auta_act->dalsi);
				auta_act = auta_act->dalsi;
				auta_act->dalsi = NULL;
		
			}
			else
			{
				auta_act->dalsi = (auta*)malloc(sizeof(auta));
				alloc_auta(auta_act->dalsi);
				auta_act = auta_act->dalsi;
				auta_act->dalsi = NULL;
			}
		}
	}
	printf("Nacitalo sa %d zaznamov\n", number_of_records);
	free(auta_act->dalsi);
	fclose(file_to_read);
}

void fnc_v(AUTA *auta_first) {
	AUTA* auta_print = auta_first;
	int number_of_elements = 0;

	if (auta_first == NULL) {
		return;
	}

	while (auta_print->dalsi != NULL) {
		printf("%d.\n", ++number_of_elements);
		printf("kategoria: %s\n", auta_print->kategoria);
		printf("zancka: %s\n", auta_print->znacka);
		printf("predajca: %s\n", auta_print->predajca);
		printf("cena: %d\n", auta_print->cena);
		printf("rok_vyroby: %d\n", auta_print->rok_vyroby);
		printf("stav_vozidla: %s\n", auta_print->stav_vozidla);
		auta_print = auta_print->dalsi;
	}

}

void fnc_p(AUTA **auta_first) {
	AUTA *auta_act, *auta_posun, *auta_buffer_1, *auta_buffer_2 = NULL;
	int position_add, position_actual;

	//get position where we will add new element of linked list
	scanf("%d", &position_add);
	position_actual = 0;

	//inicial allocation of struct + error handling
	auta_act = *auta_first;

	while (auta_act->dalsi != NULL) {
		position_actual++;

		if (position_actual == position_add) {
			auta_posun = auta_act;
			printf("auta_act: %s\n", auta_act->kategoria);
			auta_buffer_1 = auta_posun;
			while (auta_posun->dalsi != NULL) {
				if (auta_buffer_1 != NULL) {
					printf("b_1%s\n", auta_buffer_1->kategoria);
					auta_buffer_2 = auta_posun->dalsi;
					auta_posun->dalsi = auta_buffer_1;
					auta_buffer_1 = NULL;
					if (position_actual == position_add) {

					}
				}
				else 
				{
					printf("b_2%s\n", auta_buffer_2->kategoria);
					auta_buffer_1 = auta_posun->dalsi;
					auta_posun->dalsi = auta_buffer_2;
					auta_buffer_2 = NULL;
				}
				printf("posun: %s\n", auta_posun->kategoria);
				auta_posun = auta_posun->dalsi;
				position_actual++;
			}
			break;
		}
		else
		{
			auta_act = auta_act->dalsi;
		}
	}
}

char*	safe_copy_string_form_file(FILE *f) {
		/*
		* making of string from  file without '\n'
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

		for (i = 0; i < 50; i++) {
			buffer_char = fgetc(f);
			if ((buffer_char == '\n') || (feof(f))) {
				buffer_string[i] = '\0';
				break;
			}
			buffer_string[i] = buffer_char;
		}

		return buffer_string;
}

int	safe_copy_int_from_file(FILE *f) {
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

void   alloc_auta(AUTA* auta_act) {
	auta_act->kategoria = (char*)malloc(kategoria_size * sizeof(char));
	auta_act->znacka = (char*)malloc(znacka_size * sizeof(char));
	auta_act->predajca = (char*)malloc(predajca_size * sizeof(char));
	auta_act->stav_vozidla = (char*)malloc(stav_vozidla_size * sizeof(char));
}