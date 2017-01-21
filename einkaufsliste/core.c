#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>

/*
 * Ziel: Eingekaufte Produkte erfassen und in einem Datastore strukturiert hinterlegen.
 *
 */

char delim[8]="=======\n";
int menu();
void new_bill();

void main() {
 
  int selection;
  selection=menu();


  switch (selection) {
    case 0: 
      printf("goodbye!\n");
      exit;
    case 1: 
      new_bill();
      break;
    default: 
      printf("Ungültige Eingabe\n");
      exit;
  }
}

int menu() {
  int select;
  printf("Menu\n%s",delim);  
  printf("Bitte auswählen:\n");
  printf("1: neuer Einkauf\n");
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

void new_shop() {
  struct shop {
    int id;
    char name[20];
    char adr_zip[5];
    char adr_city[40];
    char adr_street[100];
    // later geolocation ;)!
  };
}

void new_bill() {
  struct bill {
    int id;
    char date[10];
    char payment; // e.g 0 = cash, 1 = ec etc
    int *shop;
  };
}

void new_product() {

  struct product{
    int id;
    char name[40];
    char ean[13];
    float price;
    int *bill;
  };
}
