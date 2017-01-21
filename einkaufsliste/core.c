#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>

/*
 * Ziel: Eingekaufte Produkte erfassen und in einem Datastore strukturiert hinterlegen.
 *
 */

int menu();
void input_shop();
void new_shop(char name[], char street[], int *zipcode, char city[]);
void new_bill();
void new_product();

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
  selection=menu();
  while (selection > '0') {
    switch (selection) {
      case '0': 
        printf("goodbye!\n");
        exit;
      case '1': 
        input_shop();
        break;
      case '2': 
        break;
      default: 
        printf("Ungültige Eingabe\n");
        exit;
    }
    selection=menu();
    printf("%d\n",selection);
  }
    printf("%c\n",menu());
}

int menu() {
  char delim[8]="=======\n";
  int select;
  printf("Menu\n%s",delim);  
  printf("Bitte auswählen:\n");
  printf("1: neuen Shop anlegen\n");
  printf("2: neuen Beleg eingeben\n");
  printf("3: neues Produkt anlegen\n");
  printf("0: Beenden\n");
  printf("%sEingabe: ",delim);
  //scanf("%i",&select);
  //getchar for 1 digit values!
  select=getchar();
  // debug output
  // printf("%i\n",select);
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
    // fill struct with function parameters
    shop_0->id=0;
    strcpy(shop_0->name,name);
    strcpy(shop_0->adr_street,street);
    strcpy(shop_0->adr_city,city);
    shop_0->adr_zip=*zipcode;
    // reset pointer to next value as we're on the last
    shop_0->next=NULL;
    printf("ID: %i\n",shop_0->id);
    printf("Name: %s\n",shop_0->name);
  // otherwise hop thorugh chain until shop_pt->next is NULL 
  // */
  }else {
    shop_pt = shop_0;
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
    printf("ID: %i\n",shop_pt->id);
    printf("Name: %s\n",shop_pt->name);
  }
}

void new_bill() {
}

void new_product() {

}
