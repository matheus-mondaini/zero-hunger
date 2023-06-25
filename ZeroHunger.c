#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char name[100];
    char id[20];
    char address[100];
    char city[100];
    char state[3];
    float income;
    int family_size;
    int family_members_needing_meds;
    bool is_vegetarian;
    bool requires_assistance;
    char classification[20];
    float food_allocation;
    int availability;
} Candidate;

typedef struct {
    char name[50];
    char id[20];
    char address[50];
    char state[3];
    char city[50];
    char food[100][100];
    float kg[100];
    int can_collect[100];
    int num_food_items;
} Producer;

typedef struct {
    int candidate_id;
    int producer_id;
    char food[100];
    float kg;
    char expiration_date[20];
} Donation;

Candidate* candidates = NULL;
int num_candidates = 0;

Producer* producers = NULL;
int num_producers = 0;

Donation* donations = NULL;
int num_donations = 0;

int MainMenu();
void CandidatesMenu();
void ProducersMenu();
void DonationsMenu();

void StoreData();
void LoadData();

void NewCandidate();
void ListCandidates();
void SearchCandidate();
void UpdateCandidate();
void RemoveCandidate();

void NewProducer();
void AddFoodItem();
void ListProducers();
void SearchProducer();
void UpdateProducers();
void RemoveProducer();

void NewDonation();
void ListDonations();
void SearchDonation();
void SearchDonationByCandidateID();
void SearchDonationByProducerID();
void SearchDonationByFood();

bool VerifyID();
bool VerifyCPF();
bool VerifyCNPJ();

void FreeMemory();

int main()
{
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
                DonationsMenu();
                break;
            case 4:
                StoreData();
                break;
            case 5:
                LoadData();
                break;
            case 6:
                FreeMemory();
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (option != 6);

    return 0;
}

int MainMenu() {
    int option;

    printf("\n--- FOOD DONATION MANAGEMENT SYSTEM ---\n");
    printf("\n1. Manage Candidates\n");
    printf("2. Manage Producers\n");
    printf("3. Manage Donations\n");
    printf("4. Store Data\n");
    printf("5. Load Data\n");
    printf("6. Exit Program\n");
    
    printf("\nChoose an option: ");
    scanf("%d", &option);

    return option;
}

void CandidatesMenu() {
    int option;

    do {
        printf("\n-------- Candidates Management --------\n");
        printf("\n1. Register New Candidate\n");
        printf("2. List All Registered Candidates\n");
        printf("3. Search Candidate by Name\n");
        printf("4. Update Candidate Information\n");
        printf("5. Remove Candidate\n");
        printf("6. Back to Main Menu\n");
        printf("---------------------------------------\n");
        
        printf("\nChoose an option: ");
        scanf("%d", &option);

        switch (option) {
          case 1:
                NewCandidate();
                break;
            case 2:
                ListCandidates();
                break;
            case 3:
                SearchCandidate();
                break;
            case 4:
                UpdateCandidate();
                break;
            case 5:
                RemoveCandidate();
                break;
            case 6:
                printf("Returning to the main menu.\n");
                MainMenu();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (option != 6);
}

void ProducersMenu() {
    int option;

    do
    {
        printf("\n-------- Producers Management --------\n");
        printf("\n1. Register New Producer\n");
        printf("2. Add Food Item\n");
        printf("3. List All Registered Producers\n");
        printf("4. Search Producer by Name\n");
        printf("5. Update a Producer");
        printf("6. Remove a Producer");
        printf("7. Back to Main Menu\n");
        printf("---------------------------------------\n");
        
        printf("\nChoose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                NewProducer();
                break;
            case 2:
                AddFoodItem();
                break;
            case 3:
                ListProducers();
                break;
            case 4:
                SearchProducer();
                break;
            case 5:
                UpdateProducers();
                break;
            case 6:
                RemoveProducer();
                break;
            case 7:
                printf("Returning to the main menu.\n");
                MainMenu();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (option != 7);
    
}

void DonationsMenu() {
    int option;

    do
    {
        printf("\n-------- Donations Management --------\n");
        printf("\n1. Register New Donation\n");
        printf("2. List All Registered Donations\n");
        printf("3. Search Donation\n");
        printf("4. Back to Main Menu\n");
        printf("---------------------------------------\n");
        
        printf("\nChoose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                NewDonation();
                break;
            case 2:
                ListDonations();
                break;
            case 3:
                SearchDonation();
                break;
            case 4:
                printf("Returning to the main menu.\n");
                MainMenu();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (option != 4);
}

void StoreData() {
    FILE* file = fopen("data.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&num_candidates, sizeof(int), 1, file);
    fwrite(candidates, sizeof(Candidate), num_candidates, file);

    fwrite(&num_producers, sizeof(int), 1, file);
    fwrite(producers, sizeof(Producer), num_producers, file);

    fwrite(&num_donations, sizeof(int), 1, file);
    fwrite(donations, sizeof(Donation), num_donations, file);

    fclose(file);

    printf("Data stored successfully.\n");
}

void FreeMemory()
{
    free(candidates);
    free(producers);
    free(donations);
}

void LoadData() {
    FILE* file = fopen("data.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    FreeMemory();

    fread(&num_candidates, sizeof(int), 1, file);
    candidates = (Candidate*)malloc(num_candidates * sizeof(Candidate));
    fread(candidates, sizeof(Candidate), num_candidates, file);

    fread(&num_producers, sizeof(int), 1, file);
    producers = (Producer*)malloc(num_producers * sizeof(Producer));
    fread(producers, sizeof(Producer), num_producers, file);

    fread(&num_donations, sizeof(int), 1, file);
    donations = (Donation*)malloc(num_donations * sizeof(Donation));
    fread(donations, sizeof(Donation), num_donations, file);

    fclose(file);

    printf("Data loaded successfully.\n");
}

void NewCandidate() {
    Candidate candidate;
    bool verified_id;

    printf("\n---- Register New Candidate ----\n");

    printf("Name: ");
    scanf(" %[^\n]s", candidate.name);

    do {
        printf("CPF/RG: ");
        scanf(" %[^\n]s", candidate.id);
        verified_id = VerifyID(candidate.id);
    } while (!verified_id);

    printf("Address: ");
    scanf(" %[^\n]s", candidate.address);

    printf("City: ");
    scanf(" %[^\n]s", candidate.city);

    printf("State (2-letter code): ");
    do
    {
        scanf(" %[^\n]s", candidate.state);
        if(strlen(candidate.state) != 2)
            printf("Invalid state code. 2-letter code only: ");
    } while (strlen(candidate.state) != 2);

    printf("Income: ");
    scanf("%f", &candidate.income);

    printf("Family Size: ");
    scanf("%d", &candidate.family_size);

    printf("Number of Family Members Needing Medication: ");
    scanf("%d", &candidate.family_members_needing_meds);

    char response;
    printf("Is Vegetarian? (Y/N): ");
    scanf(" %c", &response);
    candidate.is_vegetarian = (toupper(response) == 'Y');

    printf("Requires Assistance? (Y/N): ");
    scanf(" %c", &response);
    candidate.requires_assistance = (toupper(response) == 'Y');

    if (candidate.requires_assistance) {
        printf("Classification (Low Income, Unemployed, Elderly, Disabled): ");
        scanf(" %[^\n]s", candidate.classification);
    } else {
        strcpy(candidate.classification, "N/A");
    }

    candidate.food_allocation = 0;
    candidate.availability = 0;

    candidates = (Candidate*)realloc(candidates, (num_candidates + 1) * sizeof(Candidate));
    candidates[num_candidates++] = candidate;

    printf("\nCandidate registered successfully.\n");

    printf("Type any keyword to continue...");
    system("pause");
}

void ListCandidates() {
    if (num_candidates == 0) {
        printf("No candidates registered.\n");
        return;
    }

    printf("\n--- Registered Candidates ---\n");

    for (int i = 0; i < num_candidates; i++) {
        printf("\nCandidate %d\n", i + 1);
        printf("Name: %s\n", candidates[i].name);
        printf("ID: %s\n", candidates[i].id);
        printf("Address: %s\n", candidates[i].address);
        printf("City: %s\n", candidates[i].city);
        printf("State: %s\n", candidates[i].state);
        printf("Income: %.2f\n", candidates[i].income);
        printf("Family Size: %d\n", candidates[i].family_size);
        printf("Number of Family Members Needing Medication: %d\n", candidates[i].family_members_needing_meds);
        printf("Is Vegetarian? %s\n", candidates[i].is_vegetarian ? "Yes" : "No");
        printf("Requires Assistance? %s\n", candidates[i].requires_assistance ? "Yes" : "No");
        printf("Classification: %s\n", candidates[i].classification);
        printf("Food Allocation: %.2f\n", candidates[i].food_allocation);
        printf("Availability: %d\n", candidates[i].availability);
    }

    printf("Type any keyword to continue...");
    system("pause");
}

void SearchCandidate() {
    char name[100];
    printf("Enter the name of the candidate: ");
    scanf(" %[^\n]s", name);

    bool found = false;
    for (int i = 0; i < num_candidates; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            found = true;
            printf("\nCandidate %d\n", i + 1);
            printf("Name: %s\n", candidates[i].name);
            printf("ID: %s\n", candidates[i].id);
            printf("Address: %s\n", candidates[i].address);
            printf("City: %s\n", candidates[i].city);
            printf("State: %s\n", candidates[i].state);
            printf("Income: %.2f\n", candidates[i].income);
            printf("Family Size: %d\n", candidates[i].family_size);
            printf("Number of Family Members Needing Medication: %d\n", candidates[i].family_members_needing_meds);
            printf("Is Vegetarian? %s\n", candidates[i].is_vegetarian ? "Yes" : "No");
            printf("Requires Assistance? %s\n", candidates[i].requires_assistance ? "Yes" : "No");
            printf("Classification: %s\n", candidates[i].classification);
            printf("Food Allocation: %.2f\n", candidates[i].food_allocation);
            printf("Availability: %d\n", candidates[i].availability);
        }
    }

    if (!found) {
        printf("Candidate not found.\n");
    }

    printf("Type any keyword to continue...");
    system("pause");
}

void UpdateCandidate() {
    if (num_candidates == 0) {
        printf("No candidates registered.\n");
    }

    char name[100];
    printf("Enter the name of the candidate to update: ");
    scanf(" %[^\n]s", name);

    bool found = false;
    for (int i = 0; i < num_candidates; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            found = true;
            printf("\nCandidate %d\n", i + 1);
            printf("Name: %s\n", candidates[i].name);
            printf("ID: %s\n", candidates[i].id);
            printf("Address: %s\n", candidates[i].address);
            printf("City: %s\n", candidates[i].city);
            printf("State: %s\n", candidates[i].state);
            printf("Income: %.2f\n", candidates[i].income);
            printf("Family Size: %d\n", candidates[i].family_size);
            printf("Number of Family Members Needing Medication: %d\n", candidates[i].family_members_needing_meds);
            printf("Is Vegetarian? %s\n", candidates[i].is_vegetarian ? "Yes" : "No");
            printf("Requires Assistance? %s\n", candidates[i].requires_assistance ? "Yes" : "No");
            printf("Classification: %s\n", candidates[i].classification);
            printf("Food Allocation: %.2f\n", candidates[i].food_allocation);
            printf("Availability: %d\n", candidates[i].availability);

            printf("\nEnter the updated information:\n");

            printf("Name: ");
            scanf(" %[^\n]s", candidates[i].name);

            printf("ID: ");
            scanf(" %[^\n]s", candidates[i].id);

            printf("Address: ");
            scanf(" %[^\n]s", candidates[i].address);

            printf("City: ");
            scanf(" %[^\n]s", candidates[i].city);

            do
            {
                scanf(" %[^\n]s", candidates[i].state);
                if(strlen(candidates[i].state) != 2)
                    printf("Invalid state code. 2-letter code only: ");
            } while (strlen(candidates[i].state) != 2);


            printf("Income: ");
            scanf("%f", &candidates[i].income);

            printf("Family Size: ");
            scanf("%d", &candidates[i].family_size);

            printf("Number of Family Members Needing Medication: ");
            scanf("%d", &candidates[i].family_members_needing_meds);

            char response;
            printf("Is Vegetarian? (Y/N): ");
            scanf(" %c", &response);
            candidates[i].is_vegetarian = (toupper(response) == 'Y');

            printf("Requires Assistance? (Y/N): ");
            scanf(" %c", &response);
            candidates[i].requires_assistance = (toupper(response) == 'Y');

            if (candidates[i].requires_assistance) {
                printf("Classification (Low Income, Unemployed, Elderly, Disabled): ");
                scanf(" %[^\n]s", candidates[i].classification);
            } else {
                strcpy(candidates[i].classification, "N/A");
            }

            printf("Candidate information updated successfully.\n");
        }
    }

    if (!found) {
        printf("Candidate not found.\n");
    }

    printf("Type any keyword to continue...");
    system("pause");
}

void RemoveCandidate() {
    char name[100];
    printf("Enter the name of the candidate to remove: ");
    scanf(" %[^\n]s", name);

    bool found = false;
    for (int i = 0; i < num_candidates; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            found = true;
            for (int j = i; j < num_candidates - 1; j++) {
                candidates[j] = candidates[j + 1];
            }
            num_candidates--;
            candidates = (Candidate*)realloc(candidates, num_candidates * sizeof(Candidate));
            printf("Candidate removed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Candidate not found.\n");
    }

    printf("Type any keyword to continue...");
    system("pause");
}

void NewProducer() {
    Producer producer;

    printf("\n---- Register New Producer ----\n");

    printf("Name: ");
    scanf(" %[^\n]s", producer.name);

    printf("ID: ");
    scanf(" %[^\n]s", producer.id);

    printf("Address: ");
    scanf(" %[^\n]s", producer.address);

    printf("City: ");
    scanf(" %[^\n]s", producer.city);

    printf("State (2-letter code): ");
    scanf(" %[^\n]s", producer.state);

    producer.num_food_items = 0;

    producers = (Producer*)realloc(producers, (num_producers + 1) * sizeof(Producer));
    producers[num_producers++] = producer;

    printf("Producer registered successfully.\n");

    printf("Type any keyword to continue...");
    system("pause");
}

void AddFoodItem() {
    if (num_producers == 0) {
        printf("No producers registered. Please register a producer first.\n");
        return;
    }

    char name[50];
    printf("Enter the name of the producer: ");
    scanf(" %[^\n]s", name);

    int producer_index = -1;
    for (int i = 0; i < num_producers; i++) {
        if (strcmp(producers[i].name, name) == 0) {
            producer_index = i;
            break;
        }
    }

    if (producer_index == -1) {
        printf("Producer not found.\n");
        return;
    }

    Producer* producer = &producers[producer_index];

    printf("Food Item: ");
    scanf(" %[^\n]s", producer->food[producer->num_food_items]);

    printf("Kilograms: ");
    scanf("%f", &producer->kg[producer->num_food_items]);

    producer->can_collect[producer->num_food_items] = 1;

    producer->num_food_items++;

    printf("Food item added successfully.\n");

    printf("Type any keyword to continue...");
    system("pause");
}

void ListProducers() {
    if (num_producers == 0) {
        printf("No producers registered.\n");
        return;
    }

    printf("\n--- Registered Producers ---\n");

    for (int i = 0; i < num_producers; i++) {
        printf("\nProducer %d\n", i + 1);
        printf("Name: %s\n", producers[i].name);
        printf("ID: %s\n", producers[i].id);
        printf("Address: %s\n", producers[i].address);
        printf("City: %s\n", producers[i].city);
        printf("State: %s\n", producers[i].state);

        printf("\nFood Items:\n");
        for (int j = 0; j < producers[i].num_food_items; j++) {
            printf("%d. %s - %.2f kg\n", j + 1, producers[i].food[j], producers[i].kg[j]);
        }
    }

    printf("Type any keyword to continue...");
    system("pause");
}

void SearchProducer() {
    char name[100];
    printf("Enter the name of the producer: ");
    scanf(" %[^\n]s", name);

    bool found = false;
    for (int i = 0; i < num_producers; i++) {
        if (strcmp(producers[i].name, name) == 0) {
            found = true;
            printf("\nProducer %d\n", i + 1);
            printf("Name: %s\n", producers[i].name);
            printf("ID: %s\n", producers[i].id);
            printf("Address: %s\n", producers[i].address);
            printf("City: %s\n", producers[i].city);
            printf("State: %s\n", producers[i].state);

            printf("\nFood Items:\n");
            for (int j = 0; j < producers[i].num_food_items; j++) {
                printf("%d. %s - %.2f kg\n", j + 1, producers[i].food[j], producers[i].kg[j]);
            }
        }
    }

    if (!found) {
        printf("Producer not found.\n");
    }

    printf("Type any keyword to continue...");
    system("pause");
}

void UpdateProducers() {
    if (num_producers == 0) {
        printf("No producers registered.\n");
    }

    char name[100];
    printf("Enter the name of the producer to update: ");
    scanf(" %[^\n]s", name);

    bool found = false;
    for (int i = 0; i < num_producers; i++) {
        if (strcmp(producers[i].name, name) == 0) {
            found = true;
            printf("\nProducer %d\n", i + 1);
            printf("Name: %s\n", producers[i].name);
            printf("ID: %s\n", producers[i].id);
            printf("Address: %s\n", producers[i].address);
            printf("City: %s\n", producers[i].city);
            printf("State: %s\n", producers[i].state);

            printf("\nFood Items:\n");
            for (int j = 0; j < producers[i].num_food_items; j++) {
                printf("%d. %s - %.2f kg\n", j + 1, producers[i].food[j], producers[i].kg[j]);
            }

            printf("\nEnter the updated information:\n");

            printf("Name: ");
            scanf(" %[^\n]s", producers[i].name);

            printf("ID: ");
            scanf(" %[^\n]s", producers[i].id);

            printf("Address: ");
            scanf(" %[^\n]s", producers[i].address);

            printf("City: ");
            scanf(" %[^\n]s", producers[i].city);

            printf("State (2-letter code): ");
            scanf(" %[^\n]s", producers[i].state);

            printf("Producer information updated successfully.\n");
        }
    }

    if (!found) {
        printf("Producer not found.\n");
    }

    printf("Type enter to continue...");
}

void RemoveProducer() {
    char name[100];
    printf("Enter the name of the producer to remove: ");
    scanf(" %[^\n]s", name);

    bool found = false;
    for (int i = 0; i < num_producers; i++) {
        if (strcmp(producers[i].name, name) == 0) {
            found = true;
            for (int j = i; j < num_producers - 1; j++) {
                producers[j] = producers[j + 1];
            }
            num_producers--;
            producers = (Producer*)realloc(producers, num_producers * sizeof(Producer));
            printf("Producer removed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Producer not found.\n");
    }

    printf("Type enter to continue...");
    system("pause");
}

void NewDonation() {
    if (num_producers == 0) {
        printf("No producers registered. Please register a producer first.\n");
        return;
    }

    if (num_candidates == 0) {
        printf("No candidates registered. Please register a candidate first.\n");
        return;
    }

    Donation donation;

    printf("\n---- Register New Donation ----\n");

    char producer_name[50];
    printf("Enter the name of the producer: ");
    scanf(" %[^\n]s", producer_name);

    int producer_index = -1;
    for (int i = 0; i < num_producers; i++) {
        if (strcmp(producers[i].name, producer_name) == 0) {
            producer_index = i;
            break;
        }
    }

    if (producer_index == -1) {
        printf("Producer not found.\n");
        return;
    }

    Producer* producer = &producers[producer_index];

    char candidate_name[100];
    printf("Enter the name of the candidate: ");
    scanf(" %[^\n]s", candidate_name);

    int candidate_index = -1;
    for (int i = 0; i < num_candidates; i++) {
        if (strcmp(candidates[i].name, candidate_name) == 0) {
            candidate_index = i;
            break;
        }
    }

    if (candidate_index == -1) {
        printf("Candidate not found.\n");
        return;
    }

    Candidate* candidate = &candidates[candidate_index];

    printf("Kilograms: ");
    scanf("%f", &donation.kg);
    donations = (Donation*)realloc(donations, (num_donations + 1) * sizeof(Donation));
    donations[num_donations++] = donation;

    printf("Donation registered successfully.\n");

    // Update producer's availability and candidate's food allocation
    producer->can_collect[producer->num_food_items - 1] = 0;
    candidate->food_allocation += donation.kg;
    candidate->availability = candidate->food_allocation >= 1.5 * candidate->family_members_needing_meds;

    printf("Type any keyword to continue...");
    system("pause");
    DonationsMenu();
}

void ListDonations() {
    if (num_donations == 0) {
        printf("No donations registered.\n");
        return;
    }

    printf("\n--- Registered Donations ---\n");

    for (int i = 0; i < num_donations; i++) {
        printf("\nDonation %d\n", i + 1);
    }

    printf("Type any keyword to continue...");
    system("pause");
    DonationsMenu();
}

void SearchDonation() {
    int choice;
    printf("\n--- Search Donations ---\n");
    printf("1. Search by Candidate ID\n");
    printf("2. Search by Producer ID\n");
    printf("3. Search by Food\n");
    printf("--------------------------\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            SearchDonationByCandidateID();
            break;
        case 2:
            SearchDonationByProducerID();
            break;
        case 3:
            SearchDonationByFood();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void SearchDonationByCandidateID() {
    int candidateID;
    printf("Enter the Candidate ID: ");
    scanf("%d", &candidateID);

    printf("Donations by Candidate ID %d:\n", candidateID);
    int found = 0;
    for (int i = 0; i < num_donations; i++) {
        if (donations[i].candidate_id == candidateID) {
            printf("Donation ID: %d\n", i + 1);
            printf("Producer ID: %d\n", donations[i].producer_id);
            printf("Food: %s", donations[i].food);
            printf("Kilograms: %.2f\n", donations[i].kg);
            printf("Expiration Date: %s", donations[i].expiration_date);
            printf("------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No donations found for Candidate ID %d.\n", candidateID);
    }
}

void SearchDonationByProducerID() {
    int producerID;
    printf("Enter the Producer ID: ");
    scanf("%d", &producerID);

    printf("Donations by Producer ID %d:\n", producerID);
    int found = 0;
    for (int i = 0; i < num_donations; i++) {
        if (donations[i].producer_id == producerID) {
            printf("Donation ID: %d\n", i + 1);
            printf("Candidate ID: %d\n", donations[i].candidate_id);
            printf("Food: %s", donations[i].food);
            printf("Kilograms: %.2f\n", donations[i].kg);
            printf("Expiration Date: %s", donations[i].expiration_date);
            printf("------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No donations found for Producer ID %d.\n", producerID);
    }
}

void SearchDonationByFood() {
    char food[100];
    printf("Enter the Food: ");
    getchar();
    fgets(food, sizeof(food), stdin);
    food[strcspn(food, "\n")] = '\0'; // Remove newline character

    printf("Donations with Food '%s':\n", food);
    int found = 0;
    for (int i = 0; i < num_donations; i++) {
        if (strcmp(donations[i].food, food) == 0) {
            printf("Donation ID: %d\n", i + 1);
            printf("Candidate ID: %d\n", donations[i].candidate_id);
            printf("Producer ID: %d\n", donations[i].producer_id);
            printf("Kilograms: %.2f\n", donations[i].kg);
            printf("Expiration Date: %s", donations[i].expiration_date);
            printf("------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No donations found with Food '%s'.\n", food);
    }
}

// Function to verifies the ID in Brazil

bool VerifyID(const char* cpf_cnpj) {

    int lenght = strlen(cpf_cnpj);
    if (lenght == 11 && VerifyCPF(cpf_cnpj)) {
        printf("Valid CPF.\n");
        return 1;
    } else if (lenght == 14 && VerifyCNPJ(cpf_cnpj)) {
        printf("Valid CNPJ.\n");
        return 1;
    } else {
        printf("Invalid CPF or CNPJ.\n");
        return 0;
    }

}

bool VerifyCPF(const char* cpf) {
    
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

bool VerifyCNPJ(const char* cnpj) {
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

void ExitProgram() {
    // Free dynamically allocated memory
    free(candidates);
    free(producers);
    free(donations);

    printf("Program exited.\n");
}