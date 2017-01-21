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
void new_shop();
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


//  printf("auswahl: %i", selection);
  switch (selection) {
    case '0': 
      printf("goodbye!\n");
      exit;
    case '1': 
      input_shop();
      break;
    default: 
      printf("Ungültige Eingabe\n");
      exit;
  }
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
  if (select == 10) select=0;
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
  /*
  printf("Straße: ");
  fgets(s_adr_street,sizeof(s_adr_street),stdin);
  getchar();
  printf("PLZ: ");
//  fgets(s_adr_zip,sizeof(s_adr_zip),stdin);
  scanf("%i",&s_adr_zip);  
  getchar();
  printf("Stadt: ");
  fgets(s_adr_city,sizeof(s_adr_city),stdin);
  getchar();
  printf("------\n");
  printf("Name: %s\n",s_name);
  printf("Straße: %s\n",s_adr_street);
  printf("PLZ: %d\n",s_adr_zip);
  printf("Stadt: %s\n", s_adr_city);
  */
  printf("------\nSind diese Eingaben Korrekt(y/n)?: ");
  correct=getchar();
  if (correct == 'y') {
    printf("YAY!");
    // call new_shop and hand vars over
  } // if not just end
  
}

void new_shop() {
  struct shop *shop_pt;
  // check if first shop is already existing
  // if not create it
  if (shop_0 == NULL ) {
    if((shop_0 =  malloc(sizeof(struct shop))) == NULL) {
      fprintf(stderr, "Kein Speicherplatz vorhanden fuer neuen shop\n");
      return;
    }
    struct shop shop_0;
  // otherwise hop thorugh chain until shop_pt->next is NULL 
  }else {
    shop_pt = shop_0;
    while (shop_pt->next != NULL) {
      shop_pt=shop_pt->next;
    }
    if((shop_pt->next = malloc(sizeof(struct shop))) == NULL) {
      fprintf(stderr, "Kein Speicherplatz vorhanden fuer neuen shop\n");
      return;
    }
  }
}

void new_bill() {
}

void new_product() {

}
