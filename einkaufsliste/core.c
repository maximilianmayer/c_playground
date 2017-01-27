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

// create datatype for structs
typedef struct shop shop_st;

// create default shop_st pointer
shop_st *shop_0=NULL;
shop_st *shop_last=NULL;

const char file_shop[10]="shops.txt\0";

int menu_main();
int menu_shop();
void input_shop();
void new_shop(char name[], char street[], int *zipcode, char city[]);
void get_shops();
int fwrite_shop(shop_st *shop_pt);

/* 
 * functions not yet implemented
 *
void new_bill();
void new_product();
 *
 */


int main() {
  int selection, sel_menu;
  do {
    selection=menu_main(); 
    switch (selection) {
      case 0: 
        printf("Goodbye!\n");
        return 0;
        break;
      case 1:
        do {
          sel_menu=menu_shop();
          switch (sel_menu) {
            case 0: // no action, just return;
              break;
            case 1:
              input_shop();
              break;
            case 2:
              get_shops();
              break;
            case 3:
              printf("Funktion noch nicht implementiert!\n");
              break;
            default: 
              printf("Ungültige Eingabe! Kehre zurück zu vorigem Menü zurück.\n");
              break;
          }
        } while (sel_menu > 0);
        break;
      case 2:
        printf("funktion noch nicht implementiert! \n", selection);
        break;
      default: 
        printf("Ungültige Eingabe\n");
        return 1;
        break;
    }
  } while (selection > 0);
}

// START MENU

int menu_main() {
  char delim[8]="=======";
  int select;
  printf("\n- Main Menu\n%s\n",delim);  
  printf("Bitte auswaehlen:\n");
  printf("1: shop menu\n");
  /*
  printf("2: neuen Beleg eingeben\n");
  printf("3: neues Produkt anlegen\n");
  */
  printf("0: Beenden\n");
  printf("%s\nEingabe: ",delim);
  scanf("%i",&select);
  getchar();
  if (select == 10) select = 0;
  return select;
}

int menu_shop() {
  char delim[8]="=======";
  int select;
  printf("\n- Shop Menu\n%s\n",delim);  
  printf("Bitte auswaehlen:\n");
  printf("1: neuen Shop anlegen\n");
  printf("2: Shops anzeigen\n");
  printf("3: Shop bearbeiten\n");
  printf("0: Beenden\n");
  printf("%s\nEingabe: ",delim);
  scanf("%i",&select);
  getchar();
  if (select == 10) select = 0;
  return select;
}

// END MENU

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

void get_shops() {
  struct shop *shop_pt;
  FILE *file;
  if ( (file = fopen(file_shop,"r")) != NULL) {
    const char s[2] = ",";     
    char *token;
    char line[256];
    while ( fgets(line, sizeof(line), file) )  {
      // if shop == null create it
      if (shop_0 == NULL ) {
        if((shop_0 =  malloc(sizeof(struct shop))) == NULL) {
          perror("Kein Speicherplatz vorhanden fuer neuen shop");
          return;
        } else {
          memcpy(&shop_pt, &shop_0, sizeof(shop_0));
        }// else iterate over next until we get the last element. then create new one
      }else {
        memcpy(&shop_pt, &shop_0, sizeof(shop_0));
        while (shop_pt->next != NULL) {
          shop_pt=shop_pt->next;
        }
        if((shop_pt->next = malloc(sizeof(struct shop))) == NULL) {
          perror("Kein Speicherplatz vorhanden fuer neuen shop");
          return;
        }
      }
      token = strtok(line,s);
    
      // printf("Token: %s\t",token);   // some debug output
      /*
      while (token != NULL) {
        printf("Token: %s\n",token);
      token = strtok(NULL,s);
      }
      */
      shop_pt->id = atoi(token);
      printf("Shop ID: %i\n",shop_pt->id);
      while (token != NULL) {
        printf("Token: %s\n",token);
      token = strtok(NULL,s);
      }
      
    }
  } else {
    perror("cannot open file: file_shop");
    return;
  }
  fclose(file);
}

void new_shop(char name[], char street[], int *zipcode, char city[]) {
  struct shop *shop_pt;
  // check if first shop is already existing
  // if not create it
  if (shop_0 == NULL ) {
    if((shop_0 =  malloc(sizeof(struct shop))) == NULL) {
      perror("Kein Speicherplatz vorhanden fuer neuen shop");
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
      perror("Kein Speicherplatz vorhanden fuer neuen shop");
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
  }

  if ( fwrite_shop(shop_pt) != 0) {
    printf("Es gab einen Fehler beim Speichern des Datensatzes.\n");
  }
}

int fwrite_shop(shop_st *shop_pt) {
  FILE *file;
  if ( (file = fopen(file_shop,"a")) == NULL ) {
    perror("cannot open file: file_shop");
    return 1;
  }else {
    printf("Schreibe Datensatz in datei: %s\n",file_shop);
    fprintf(file,"%i,%s,%s,%i,%s\n", shop_pt->id, shop_pt->name, shop_pt->adr_street, shop_pt->adr_zip, shop_pt->adr_city);
    fclose(file);
  }
  return 0;
}

