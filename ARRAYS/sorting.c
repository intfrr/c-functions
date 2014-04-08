#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void swap(int *a, int i, int j)
{
	int t;
	t = a[i], a[i] = a[j], a[j] = t;
}

void bubble_sort(int *a, int n) {
	int j, t = 1, m = 0;
	while (n-- && t)
		for (j = t = 0; j < n; j++) {
			if (a[j] <= a[j + 1]) continue;
			swap(a,j,j+1);
			t=1;
		}
}

void selection_sort(int *a, int n) {
	 for (int i = 0, pos; i < (n - 1); i++)
	 {
			pos = i;
			for (int j = i+1; j<n; j++) {
				if (a[pos] > a[j])
					pos = j;
			}
			if (pos != i)
				swap(a,i,pos);
	 }
}

void insertion_sort(int *a, int lo, int n) {
	 for(int i=lo+1, j, val; i<n; i++) {
			val = a[i];
			j = i-1;
			while(a[j] > val) {
				 a[j+1] = a[j];
				 --j;
				 if(j<0) break;
			}
			a[j+1] = val;
	 }
}


int linear_search(int *a, int n, int num) {
	int pos = -1;
	for(int i = 0; i <= n-1; i++)
		if (a[i] == num) {
			pos = i;
			break;
		}
	return pos;
}



int binary_search(int *a, int n, int num) {
	int pos = -1, mid, lo = 0, hi = n-1;
	while (lo <= hi) {
		mid = (lo+hi)/2;
		if (num == a[mid]){
			pos = mid;
			break;
		}
		else if (num < a[mid]){
			hi = mid-1;
		}
		else
			lo = mid+1;
	}
	return pos;
}


void read_rand_array(int *a, int n) {
	for(int i = 0; i < n; i++)
		a[i] = rand() % rand() % 90000 + 10000;
}

void print_int_array(int *a, int n) {
	for(int i=0; i<n; i++ )
			printf("%d ", a[i]);
}

void fflushstdin( void ) {
	int c;
	while( (c = fgetc( stdin )) != EOF && c != '\n' );
}


int is_single_char(char *c1) {
	char c2;
	if(scanf("%c%c", c1, &c2) != 2 || c2 != '\n')
	    return 0;
	else
	    return 1;
}

int is_number(int *num) {
	char c;
	if(scanf("%d%c", num, &c) != 2 || c != '\n')
	    return 0;
	else
	    return 1;
}

void validate_single_char_read(char *c){
	int success;
	do {
		printf("\nNUMBER:\t");
		if(!(success = is_single_char(c))) {
			printf("Please give valid option\n");
			fflushstdin();
		}
	} while(!success);
}

void validate_int_read(int *num, char *s){
	int success;
	do {
		printf("\n%s\t", s);
		if(!(success = is_number(num))) {
			printf("Please give a number\n");
			fflushstdin();
		}
	} while(!success);
}

void sort_array(int *a, int n) {
	char c;
	int success;

	do {
		printf("\n\nSorting algorithms: ");
		printf("\n[1].-Bubble\n[2].-Selection\n[3].-Insertion\n[4].-No-Sorting");
		printf("\nChoose:\t");
		if(!(success = is_single_char(&c)))
			fflushstdin();
		if(c < 49 || c > 52)
			printf("Please give a valid option\n");
	} while(!success || c < 49 || c > 52);

	switch (c)
	{
		case '1':
			bubble_sort (a, n);
			break;
		case '2':
			selection_sort(a, n);
			break;
		case '3':
			insertion_sort (a, 0, n);
			break;
		case '4':
			printf("\nDATA STAYS THE SAME\n");
			break;
		default:
			break;
	}
}

int is_sorted(int *a, int n) {
	for (int i = 1; i < n/2 + 1 ; i++)
	{
		if (a[i - 1] > a[i] || a[n-i] < a[n-i-1])
			return 0;
	}
	return 1;
}



int search_in_array(int *a, int n, int num) {
	int pos;

	if (is_sorted(a,n)) {
		printf("through binary search...");
		pos = binary_search(a, n, num);

	}
	else {
		printf("through linear search...");
		pos = linear_search(a, n, num);

	}
	return pos;
}

char* itoa(int i, char b[]) {
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0){
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do { //Move back, inserting digits as u go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

void write_arr_to_file(FILE *fp, int *a, int n) {
	char * s = malloc(sizeof(char) * 20);
	for(int i = 0; i<n; i++) {
		fprintf(fp, "%s ", itoa(a[i], s));
	}
}

void write_results_file(FILE *fp, int *a, int *b, int num, int pos, int n) {
	if((fp = fopen("out.txt", "w"))== NULL)
			exit(-1);
	else {
		fprintf(fp, "ARRAY BEFORE:\n");
		write_arr_to_file(fp, b, n);
		fprintf(fp, "\nARRAY AFTER:\n");
		write_arr_to_file(fp, a, n);
		if ( pos >= 0 ) {
			printf("\n\n%d found at %d position", num, pos+1);
			fprintf(fp, "\n\n%d found at %d position", num, pos+1);
		}
		else {
			printf("\n\n%d not found", num);
			fprintf(fp, "\n\n%d not found", num);
		}
	}

}



int main()
{

	FILE *fp;
	int n, num, pos, *b, *a;
	char c;



	//------- INSERCION DE DATOS EN EL ARREGLO ----------- //
	printf("\nSorting an array... ");
	validate_int_read(&n, "SIZE:");
	b = malloc (sizeof(int) * n);
	read_rand_array(b, n);
	a = b;

	// for (i = 0; i < n; i++)
	// 	scanf("%d", &a[i]);

	// -------- IMPRESION EN PANTALLA DEL ARREGLO DE DATOS DESORDENADO ---- //
	printf("\nBEFORE:\n");
	print_int_array(a, n);


	// ------ PETICION AL USUARIO DEL METODO A UTILIZAR PARA ORDENAR ------- //
	sort_array(a, n);

	// -------- IMPRESION EN PANTALLA DEL ARREGLO DE DATOS DESORDENADO ---- //
	printf("\nAFTER:\n");
	print_int_array(a, n);

	// -------- BUSQUEDA BINARIA //
	printf("\n\nSearching in the array... ");
	validate_int_read(&num, "NUMBER:");

	pos = search_in_array(a, n, num);


	printf("\n\nWriting in file... ");
	write_results_file(fp, a, b, num, pos, n);

	// fclose(fp);

	return 0;
}
