#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
//#include <sqlite3.h>

/*
 * Ziel: Eingekaufte Produkte erfassen und in einem Datastore strukturiert hinterlegen.
 * Datastore: 1. file -> done, 2. sqlite ->tbf, 3. whatever -> not sure if
 *
 * Step1: Läden anlegen, speichern -> done
 * Step2: Läden aus Datei(en) auslesen -> WIP
 * Step3: Rechnungen anlegen & speichern -> tbd
 */

int menu();
void input_shop();
void new_shop(char name[], char street[], int *zipcode, char city[]);
void new_bill();
void new_product();
//void shop_write(struct shop *pt);

// 
struct shop {
  int id;
  char name[20];
  int  adr_zip;
  char adr_city[40];
  char adr_street[100];
  struct shop *next;
  // later geolocation ;)!
};

struct bill {
  int id;
  char date[10];
  char payment; // e.g 0 = cash, 1 = ec etc
  //struct shop *shop_pt; // pointer to shop ID
};

struct product {
  int id;
  char name[40];
  char ean[13];
  char type;    // regular product, reduced etc
  float price;
  //struct bill *bill_pt; // pointer to bill ID
};

  struct shop *shop_0=NULL;
  struct shop *shop_last=NULL;


void main() {
 
  int selection;
  do {
    selection=menu(); 
    // debug output
    //printf("DEBUG: Wert von selection: %d\n",selection);
    switch (selection) {
      case 0: 
        printf("Goodbye!\n");
        break;
      case 1:
        //printf("DEBUG: 1 entered %i\n", selection);
        input_shop();
        break;
      case 2:
        printf("funktion noch nicht implementiert! \n", selection);
        break;
      default: 
        printf("Ungültige Eingabe\n");
        break;
    }
    /* some debug output -- remove later
    printf("DEBUG: int-Wert von selection in loop: %d\n",selection);
    printf("DEBUG: end of loop reached!\n");
    */
  }
  while (selection > 0);
}

int menu() {
  char delim[8]="======\n";
  int select;
  printf("Menu\n%s",delim);  
  printf("Bitte auswaehlen:\n");
  printf("1: neuen Shop anlegen\n");
  printf("2: neuen Beleg eingeben\n");
  printf("3: neues Produkt anlegen\n");
  printf("0: Beenden\n");
  printf("%sEingabe: ",delim);
  scanf("%i",&select);
  getchar();
  if (select == 10) select = 0;
  return select;
}
void input_shop() {
  char s_name[20]; 
  int  s_adr_zip;
  char s_adr_city[40];
  char s_adr_street[100];
  char correct='n';

  printf("Eingabe neuer Shop\n--------------\n");
  printf("Name: ");
  scanf ("%s",s_name);
  getchar();
  printf("Straße: ");
  scanf ("%s",s_adr_street);
  getchar();
  printf("PLZ: ");
  scanf("%i",&s_adr_zip);  
  getchar();
  printf("Stadt: ");
  scanf("%s",s_adr_city);  
  getchar();
  printf("------\n");
  printf("Name: %s\n",s_name);
  printf("Straße: %s\n",s_adr_street);
  printf("PLZ: %d\n",s_adr_zip);
  printf("Stadt: %s\n", s_adr_city);
  printf("------\nSind diese Eingaben Korrekt(y/n)?: ");
  correct=getchar();
  if (correct == 'y') {
    // call new_shop() 
    new_shop(s_name, s_adr_street, &s_adr_zip, s_adr_city);
  }

  
}

void new_shop(char name[], char street[], int *zipcode, char city[]) {
  struct shop *shop_pt;
  // check if first shop is already existing
  // if not create it
  if (shop_0 == NULL ) {
    if((shop_0 =  malloc(sizeof(struct shop))) == NULL) {
      fprintf(stderr, "Kein Speicherplatz vorhanden fuer neuen shop\n");
      return;
    }
    memcpy(&shop_pt, &shop_0, sizeof(shop_0));
    // fill struct with function parameters
    shop_pt->id=0;
    strcpy(shop_pt->name,name);
    strcpy(shop_pt->adr_street,street);
    strcpy(shop_pt->adr_city,city);
    shop_pt->adr_zip=*zipcode;
    // reset pointer to next value as we're on the last
    shop_pt->next=NULL;
  // otherwise hop thorugh chain until shop_pt->next is NULL 
  // */
  }else {
    memcpy(&shop_pt, &shop_0, sizeof(shop_0));
    //shop_pt = shop_0;
    int i=0;
    while (shop_pt->next != NULL) {
      shop_pt=shop_pt->next;
      i++;
    }
    if((shop_pt->next = malloc(sizeof(struct shop))) == NULL) {
      fprintf(stderr, "Kein Speicherplatz vorhanden fuer neuen shop\n");
      return;
    }
    // set current shop_pt pointer to newly created struct
    shop_pt=shop_pt->next; 
    // fill struct with function parameters
    shop_pt->id=i;
    strcpy(shop_pt->name,name);
    strcpy(shop_pt->adr_street,street);
    strcpy(shop_pt->adr_city,city);
    shop_pt->adr_zip=*zipcode;
    // reset pointer to next value as we're on the last
    shop_pt->next=NULL;
    //shop_write(shop_pt);

  }
  // write record to file
  char filename[10]="shops.txt";
  //printf("filename: %s", filename);
  
  FILE *file;
  if ( (file = fopen(filename,"a")) == NULL ) {
    printf("error: cannot open file: %s\n",filename);
  }else {
    printf("Schreibe Datensatz in datei: %s\n",filename);
    fprintf(file,"ID:%i, Name:%s, Address:%s, zipcode:%i, City:%s\n", shop_pt->id, shop_pt->name, shop_pt->adr_street, shop_pt->adr_zip, shop_pt->adr_city);
    fclose(file);
  }
  
}
/*
void shop_write(struct shop *pt) {
    printf("ID: %i\n",pt->id);
    printf("Name: %s\n",pt->name);

}
*/

void new_bill() {
}

void new_product() {

}
