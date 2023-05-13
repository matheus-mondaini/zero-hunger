#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //TODO: Try this library to identify var types and to convert characters case
#include <stdbool.h> //TODO: Try this library to use booleans instead of integers

// Defining date structs

typedef struct {
    char name [100];
    char id [20]; //In Brazil, everyone has a ID called CPF/RG. ID will be the PK for each person and being a national number helps to verify the person. If your country doesn't have a national ID like mine, you can create an ordinary numeric PK that will do the same.
    char address;
    char city [100];
    char state [2];
    float income;
    int family_size;
    int family_members_needing_meds;
    bool is_vegetarian;
    bool requires_assistance;
    char classification [20];
    float food_allocation;
    int availability;
}Candidate;

typedef struct {
    char name [50];
    char id [20];
    char address [50];
    int state;
    int city;
    char food[100][100];
    float kg[100];
    int can_colect[100];
    int num_food_itens;
}Producer;

typedef struct {
    int id_candidate;
    int id_producer;
    char food[100];
    float kg;
    char expiration_date[20];
}Donation;

// Functions prototypes:

int MainMenu();
void CandidatesMenu();
void ProducersMenu();
//TOO: void DonationsMenu();
void NewCandidates();
void ListCandidates();
void SearchCandidates();
void UpdateCandidates();
void RemoveCandidates();
void NewProducer();
void ListPoducers();
//TODO: void SearchProducers();
//TODO: void UpdateProducers();
//TODO: void RemoveProducers();
void NewDonation();
void ListDonations();
void SearchDonations();
//void StoreDate(); //TODO: Save the current data of the system in a database
//void LoadDate(); //TODO:  Retrive the previously saved data and load it back

// Global Variables

Candidate *candidates;
int qt_candidates= 0;
Producer *producers;
int qt_producers = 0;
Donation *donations;
int qt_donations = 0;

// Main Function

void main() {
    int option;
    do {
    option = MainMenu();
    switch (option) {
        case 1:
            CandidatesMenu();
            break;
        case 2:
            ProducersMenu();
            break;
        case 3:
            //TODO: DonationsMenu();
            break;
        case 4:
            //TODO: StoreDate();
            break;
        case 5:
            printf("Exiting the program.\\n");
            break;
        default:
            printf("Invalid choice. Please try again.\\n");
            break;
        }
    } while (option != 5);

    // Frees memory allocated to data structures
    free(candidates);
    free(producers);
    free(donations);
}

// Funtion that displays the Main Menu

int MainMenu() {
    int option;

    printf("\\n--- FOOD DONATION MANAGEMENT SYSTEM ---\\n");
    printf("\\n1. Manage Candidates\\n");
    printf("2. Manage Producers\\n");
    printf("3. Manage Donations\\n");
    printf("4. Storage Data\\n");
    printf("5. Exit Program\\n");
    printf("\\nChoose an option: ");
    scanf("%d", &option);

    return option;
}

// Function to display the candidates management

void CandidatesMenu()
{
    int option;

    printf("--------Candidates Management--------");
    printf("1. Register New Candidate");
    printf("2. List all registered candidates");
    printf("3. Search candidate by name");
    printf("4. Update a candidate's information");
    printf("5. Remove a candidate");
    printf("6. Exit");
    printf("---------------------------------------");

    scanf("%d", option);

    do {
    switch (option) {
        case 1:
            NewCandidates(&candidates, qt_candidates); //TODO: Test it when both contains &, and when neither of them has &. If there is no Candidates yet, maybe it will be necessary doing another function, called if null 
            break;
        case 2:
            ListCandidates(candidates, qt_candidates);
            break;
        case 3:
            SearchCandidates(candidates, qt_candidates);
            break;
        case 4:
            UpdateCandidates(candidates, qt_candidates);
            break;
        case 5:
            RemoveCandidates(&candidates, qt_candidates);
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (option != 6);

    free(candidates);
}

// Function to add a new candidate

void NewCandidates (Candidate** candidates, int* qt_candidates) {
    // Allocate memory for a new candidate
    *candidates = (Candidate*)realloc(*candidates, (*qt_candidates + 1) * sizeof(Candidate));
    Candidate* newCandidate = *candidates + *qt_candidates;
    bool verified_id;
    // Read candidate information from user input
    printf("Enter candidate's name: ");
    scanf("%s", newCandidate->name);
        
        do
        {
            printf("Enter candidate's CPF/RG: ");
            scanf("%s", newCandidate->id);
            verified_id = VerifyID(newCandidate->id);
        } while (!verified_id);
    
    printf("Enter candidate's address: ");
    scanf(" %[^\n]s", newCandidate->address);

    printf("Enter candidate's income: ");
    scanf("%f", &(newCandidate->income));

    printf("Enter candidate's family size: ");
    scanf("%d", &(newCandidate->family_size));

    printf("Enter number of family members needing medication: ");
    scanf("%d", &(newCandidate->family_members_needing_meds));

    printf("Is the candidate vegetarian? (1 for Yes, 0 for No): ");
    scanf("%d", &(newCandidate->is_vegetarian));

    printf("Does the candidate require assistance in food Collection? (1 for Yes, 0 for No): ");
    scanf("%d", &(newCandidate->requires_assistance));

    printf("Enter candidate's availability (morning: 1, afternoon: 2, evening: 3): ");
    scanf("%d", &(newCandidate->availability));

    // Increment the number of candidates
    (*qt_candidates)++;

    printf("\nCandidate added successfully!\n\n");

}

// Function to list all registered candidates
void ListCandidates(Candidate* candidates, int qt_candidates) {
    printf("-------- List of Candidates --------\n");
    for (int i = 0; i < qt_candidates; i++) {
        printf("Candidate %d:\n", i + 1);
        printf("Name: %s\n", candidates[i].name);
        printf("CPF/RG: %s\n", candidates[i].id);
        printf("Address: %s\n", candidates[i].address);
        printf("Income: %d\n", candidates[i].family_size);
        printf("Family size: %d\n", candidates[i].family_size);
        printf("Number of family members needing medication: %d\n", candidates[i].family_members_needing_meds);
        printf("Is vegeterian: ");
            if (candidates[i].is_vegetarian == 1)
                printf("Yes\n");
            else
                printf("No\n");
        printf("Requires assistance in food Collection: ");
            if (candidates[i].requires_assistance == 1)
                printf("Yes\n");
            else
                printf("No\n");
        printf("Availability: ");
        if (candidates[i].availability == 1) 
            printf("Morning\n");
        if (candidates[i].availability == 2)
            printf("Afternoon\n"); 
        if (candidates[i].availability == 3)     
            printf("Evening:\n\n");
    }
    printf("------------------------------------\n");
}

// Function to search for a candidate by name
void SearchCandidates(Candidate* candidates, int qt_candidates) {
    char searchName[100];
    printf("Enter candidate's name to search: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < qt_candidates; i++) {
        if (strcmp(candidates[i].name, searchName) == 0) {
            printf("Candidate found:\n");
            printf("Name: %s\n", candidates[i].name);
            // Print other candidate information here...
            printf("\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Candidate not found.\n\n");
    }
}

// Function to update a candidate's information
void UpdateCandidates(Candidate* candidates, int qt_candidates) {
    char searchName[100];
    printf("Enter candidate's name to update: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < qt_candidates; i++) {
        if (strcmp(candidates[i].name, searchName) == 0) {
            printf("Candidate found:\n");
            printf("Name: %s\n", candidates[i].name);
            // Print other candidate information here...
            printf("\n");

            // Update candidate information here...

            printf("Candidate information updated successfully!\n\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Candidate not found.\n\n");
    }
}

// Function to remove a candidate
void RemoveCandidates(Candidate** candidates, int* qt_candidates) {
    char searchName[100];
    printf("Enter candidate's name to remove: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < *qt_candidates; i++) {
        if (strcmp((*candidates)[i].name, searchName) == 0) {
            // Shift candidates after the removal position to the left
            for (int j = i; j < *qt_candidates - 1; j++) {
                (*candidates)[j] = (*candidates)[j + 1];
            }
            // Decrease the number of candidates
            (*qt_candidates)--;

            // Reallocate memory to adjust the size
            *candidates = (Candidate*)realloc(*candidates, (*qt_candidates) * sizeof(Candidate));

            printf("Candidate removed successfully!\n\n");
            found = 1;
            break;
        }
    }

    if (!found) {
    printf("Candidate not found.\n\n");
    }
}

void ProducersMenu() {
    Producer* producers = NULL;
    int num_producers = 0;

    int option;
    
    printf("-------- Producers Management --------\n");
    printf("1. Register New Producer\n");
    printf("2. Add Food Item for Collection\n");
    printf("3. List All Registered Producers\n");
    printf("4. Exit\n");
    printf("---------------------------------------");

    scanf("%d", option);

    do {
    switch (option) {
        case 1:
            NewProducer(&producers, qt_producers); //TODO: Test it when both contains &, and when neither of them has &. If there is no Producers yet, maybe it will be necessary doing another function, called if null 
            break;
         case 2:
            ListPoducers(producers, qt_producers);
            break;
        case 3:
            //TODO: SearchProducers(producers, qt_producers);
            break;
        case 4:
            //TODO: UpdateProducers(producers, qt_producers);
            break;
        case 5:
            //TODO: RemoveProducers(&producers, qt_producers);
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (option != 6);

    free(producers);
}

void NewProducer(Producer** producers, int* num_producers) {
    Producer producer;
    printf("Enter producer name: ");
    scanf(" %[^\n]s", producer.name);
    printf("Enter producer address: ");
    scanf(" %[^\n]s", producer.address);
    printf("Enter producer ID: ");
    scanf("%d", &producer.id);

    producer.num_food_itens = 0;

    (*num_producers)++;
    *producers = (Producer*)realloc(*producers, (*num_producers) * sizeof(Producer));
    (*producers)[*num_producers - 1] = producer;

    printf("Producer registered successfully!\n\n");
}

void AddFoodItem(Producer* producers, int num_producers) {
    int id;
    printf("Enter producer ID: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < num_producers; i++) {
        if (producers[i].id == id) {
            printf("Enter food name: ");
            scanf(" %[^\n]s", producers[i].food[producers[i].num_food_itens]);
            printf("Enter quantity (in kg): ");
            scanf("%d", &producers[i].kg[producers[i].num_food_itens]);
            printf("Is the food item available for Collection? (0 = No, 1 = Yes): ");
            scanf("%d", &producers[i].can_colect[producers[i].num_food_itens]);

            producers[i].num_food_itens++;
            found = 1;

            printf("Food item added successfully!\n\n");
            break;
        }
    }

    if (!found) {
        printf("Producer not found.\n\n");
    }
}

void PrintProducer(Producer producer) {
    printf("Name: %s\n", producer.name);
    printf("Address: %s\n", producer.address);
    printf("ID: %d\n", producer.id);
    printf("Food Items for Collection:\n");
    for (int i = 0; i < producer.num_food_itens; i++) {
        printf("- Food: %s, Quantity: %d kg, Collectable: %s\n", producer.food[i], producer.kg[i],
               producer.can_colect[i] ? "Yes" : "No");
    }
    printf("\n");
}

void ListPoducers(Producer* producers, int num_producers) {
    if (num_producers == 0) {
        printf("No producers registered.\n\n");
        return;
    }

    printf("-------- Registered Producers --------\n");
    for (int i = 0; i < num_producers; i++) {
        printf("Producer %d:\n", i + 1);
        PrintProducer(producers[i]);
    }
    printf("--------------------------------------\n\n");
}

// Function to verifies the ID in Brazil

int VerifyID(char cpf_cnpj[]) {

    int lenght = strlen(cpf_cnpj);
    if (lenght == 11 && VerifyCPF(cpf_cnpj)) {
        printf("Valid CPF.\\n");
        return 1;
    } else if (lenght == 14 && VerifyCNPJ(cpf_cnpj)) {
        printf("Valid CNPJ.\\n");
        return 1;
    } else {
        printf("Invalid CPF or CNPJ.\\n");
        return 0;
    }

}

int VerifyCPF(char *cpf) {
    
    int i, j, sum = 0, checkerDigit, checkerDigit2;

    // Checks if all characters are numbers
    
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }

    // Checks the first checker digit

    for (i = 0, j = 10; i < 9; i++, j--) {
        sum += (cpf[i] - '0') * j;
    }
    checkerDigit = 11 - (sum % 11);
    if (checkerDigit >= 10) {
        checkerDigit = 0;
    }
    if (checkerDigit != cpf[9] - '0') {
        return 0;
    }

    // Checks the second checker digit

    sum = 0;
    for (i = 0, j = 11; i < 10; i++, j--) {
        sum += (cpf[i] - '0') * j;
    }
    checkerDigit2 = 11 - (sum % 11);
    if (checkerDigit2 >= 10) {
        checkerDigit2 = 0;
    }
    if (checkerDigit2 != cpf[10] - '0') {
        return 0;
    }

    return 1;
}

int VerifyCNPJ(char *cnpj) {
    int i, j, sum = 0, checkerDigit, checkerDigit2;

    // Checks if all characters are numbers
    
    for (i = 0; i < 14; i++) {
        if (!isdigit(cnpj[i])) {
            return 0;
        }
    }

    // Checks the first checker digit

    sum = 0;
    for (i = 0, j = 5; i < 12; i++) {
        sum += (cnpj[i] - '0') * j;
        if (j == 2) {
            j = 9;
        } else {
            j--;
        }
    }
    checkerDigit = 11 - (sum % 11);
    if (checkerDigit >= 10) {
        checkerDigit = 0;
    }
    if (checkerDigit != cnpj[12] - '0') {
        return 0;
    }

    // Checks the second checker digit

    sum = 0;
    for (i = 0, j = 6; i < 13; i++) {
        sum += (cnpj[i] - '0') * j;
        if (j == 2) {
            j = 9;
        } else {
            j--;
        }
    }
    checkerDigit2 = 11 - (sum % 11);
    if (checkerDigit2 >= 10) {
    checkerDigit2 = 0;
    }
    if (checkerDigit2 != cnpj[13] - '0') {
    return 0;
    }

    return 1;
}

// TODO: Donation System

// To Ignore: Old drafts, first donation system ideas


// Classifying candidates
/*
void ClassifyCandidates(Candidate candidates[], int num_candidates) {
    float income_per_person;
    for (int i = 0; i < num_candidates; i++) {
        if (candidates[i].family_members_needing_meds == 0) {
            income_per_person = candidates[i].income / candidates[i].family_size;
            if (income_per_person < 100) {
                sprintf(candidates[i].classification, "Low Income");
            } else if (income_per_person < 500) {
                sprintf(candidates[i].classification, "Medium Income");
            } else {
                sprintf(candidates[i].classification, "High Income");
            }
        } else {
            sprintf(candidates[i].classification, "Medical Issues");
        }
    }
}

void DistributeFood(Producer producers[], int num_producers, Candidate candidates[], int num_candidates) {
    float total_kg;
    for (int i = 0; i < num_producers; i++) {
        total_kg = producers[i].kg;
        for (int j = 0; j < num_candidates; j++) {
            if (candidates[j].food_allocation > 0) {
                float allocated_food = total_kg * candidates[j].food_allocation;
                candidates[j].food_allocation = 0; // Reset food allocation for the candidate
                total_kg -= allocated_food;
                printf("Food sent from %s to Candidate %d: %.2f kg\n", producers[i].name, j+1, allocated_food);
            }
        }
    }
}

void Collection() {

    int num_candidates = sizeof(candidates) / sizeof(candidates[0]);

    ClassifyCandidates(candidates, num_candidates);

    int num_producers = sizeof(producers) / sizeof(producers[0]);

    DistributeFood(producers, num_producers, candidates, num_candidates);
}
*/