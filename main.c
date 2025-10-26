#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 10
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0  // Current fuel price

// Vehicle structure
typedef struct {
    char name[20];
    int capacity;          // in kg
    float rate_per_km;     // base rate per kilometer
    float avg_speed;       // average speed in km/h
    float fuel_efficiency; // km per liter
} Vehicle;

// Delivery structure - stores all delivery information
typedef struct {
    int id;
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    float weight;
    int vehicle_type;
    float distance;
    float base_cost;
    float fuel_used;
    float fuel_cost;
    float operational_cost;
    float profit;
    float customer_charge;
    float estimated_time;
    int completed;  // 1 if completed, 0 if pending
} Delivery;


char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distance[MAX_CITIES][MAX_CITIES];
Delivery deliveries[MAX_DELIVERIES];
Vehicle vehicles[3];  // We have 3 types of vehicles
int city_count = 0;
int delivery_count = 0;
int delivery_id_counter = 1;


void initializeSystem();
void displayMainMenu();
void manageCities();
void manageDistances();
void displayDistanceTable();
void inputOrEditDistance();
void handleDeliveryRequest();
void calculateDeliveryDetails(int source, int dest, float weight, int vehicle_type);
void viewDeliveryRecords();
void generatePerformanceReport();
void findLeastCostRoute();
void exhaustiveSearch(int source, int dest, int *path, int *path_length, float *min_distance);
void displayRoute(int *path, int path_length, float distance);
float calculatePathDistance(int *path, int path_length);

int main() {
    initializeSystem();

    int choice;

    // Main program loop
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                manageCities();
                break;
            case 2:
                manageDistances();
                break;
            case 3:
                handleDeliveryRequest();
                break;
            case 4:
                viewDeliveryRecords();
                break;
            case 5:
                generatePerformanceReport();
                break;
            case 6:
                findLeastCostRoute();
                break;
            case 7:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while(choice != 7);

    return 0;

    void initializeSystem() {
    // Initialize cities with some default  cities
    strcpy(cities[0], "Colombo");
    strcpy(cities[1], "Kandy");
    strcpy(cities[2], "Galle");
    strcpy(cities[3], "Jaffna");
    city_count = 4;


    int i, j;
    for(i = 0; i < MAX_CITIES; i++) {
        for(j = 0; j < MAX_CITIES; j++) {
            if(i == j) {
                distance[i][j] = 0;  // distance from city to itself is 0
            } else {
                distance[i][j] = -1; // -1 means no direct connection
            }
        }
    }

    // Set some realistic distances between  cities (approximate)
    distance[0][1] = distance[1][0] = 120; // Colombo-Kandy
    distance[0][2] = distance[2][0] = 115; // Colombo-Galle
    distance[0][3] = distance[3][0] = 400; // Colombo-Jaffna
    distance[1][2] = distance[2][1] = 200; // Kandy-Galle
    distance[1][3] = distance[3][1] = 350; // Kandy-Jaffna
    distance[2][3] = distance[3][2] = 450; // Galle-Jaffna

    // Initialize our fleet of vehicles
    strcpy(vehicles[0].name, "Van");
    vehicles[0].capacity = 1000;     // 1 ton capacity
    vehicles[0].rate_per_km = 30;    // 30 LKR per km
    vehicles[0].avg_speed = 60;      // 60 km/h average
    vehicles[0].fuel_efficiency = 12; // 12 km per liter

    strcpy(vehicles[1].name, "Truck");
    vehicles[1].capacity = 5000;     // 5 ton capacity
    vehicles[1].rate_per_km = 40;    // 40 LKR per km
    vehicles[1].avg_speed = 50;      // slower due to size
    vehicles[1].fuel_efficiency = 6;  // less fuel efficient

    strcpy(vehicles[2].name, "Lorry");
    vehicles[2].capacity = 10000;    // 10 ton capacity
    vehicles[2].rate_per_km = 80;    // highest rate
    vehicles[2].avg_speed = 45;      // slowest but highest capacity
    vehicles[2].fuel_efficiency = 4;  // least fuel efficient

    printf("Logistics Management System Initialized!\n");
    printf("Default cities and distances loaded.\n");
}
void displayMainMenu() {
    printf("\n======================================================\n");
    printf("           LOGISTICS MANAGEMENT SYSTEM\n");
    printf("======================================================\n");
    printf("1. Manage Cities\n");
    printf("2. Manage Distances\n");
    printf("3. Handle Delivery Request\n");
    printf("4. View Delivery Records\n");
    printf("5. Generate Performance Report\n");
    printf("6. Find Least Cost Route\n");
    printf("7. Exit\n");
    printf("======================================================\n");
}
void manageCities() {
    int choice;

    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n");
        printf("2. View Cities\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(city_count < MAX_CITIES) {
                    printf("Enter city name: ");
                    scanf("%s", cities[city_count]);
                    city_count++;
                    printf("City added successfully!\n");
                } else {
                    printf("Maximum number of cities reached! Can't add more.\n");
                }
                break;

            case 2:
                printf("\n--- Available Cities ---\n");
                int i;
                for(i = 0; i < city_count; i++) {
                    printf("%d. %s\n", i, cities[i]);
                }
                break;

            case 3:
                // Go back to main menu
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 3);
}


void manageDistances() {
    int choice;

    do {
        printf("\n--- Distance Management ---\n");
        printf("1. Input/Edit Distance\n");
        printf("2. View Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputOrEditDistance();
                break;
            case 2:
                displayDistanceTable();
                break;
            case 3:
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 3);
}

void displayDistanceTable() {
    printf("\n--- Distance Table (km) ---\n");


    printf("%-15s", "");
    int i, j;
    for(i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");


    for(i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for(j = 0; j < city_count; j++) {
            if(distance[i][j] == -1) {
                printf("%-15s", "N/A");
            } else {
                printf("%-15d", distance[i][j]);
            }
        }
        printf("\n");
    }
}

void inputOrEditDistance() {
    int city1, city2, dist;

    printf("\nAvailable Cities:\n");
    int i;
    for(i = 0; i < city_count; i++) {
        printf("%d. %s\n", i, cities[i]);
    }

    printf("Enter source city index: ");
    scanf("%d", &city1);
    printf("Enter destination city index: ");
    scanf("%d", &city2);


    if(city1 < 0 || city1 >= city_count || city2 < 0 || city2 >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(city1 == city2) {
        printf("Distance from city to itself is always 0!\n");
        return;
    }

    printf("Enter distance between %s and %s (km): ", cities[city1], cities[city2]);
    scanf("%d", &dist);

    if(dist < 0) {
        printf("Distance cannot be negative!\n");
        return;
    }


    distance[city1][city2] = dist;
    distance[city2][city1] = dist;

    printf("Distance updated successfully!\n");
}
void handleDeliveryRequest() {
    if(city_count < 2) {
        printf("Need at least 2 cities to handle deliveries!\n");
        return;
    }

    int source, dest, vehicle_type;
    float weight;

    printf("\n--- New Delivery Request ---\n");

    // Show available cities
    printf("Available Cities:\n");
    int i;
    for(i = 0; i < city_count; i++) {
        printf("%d. %s\n", i, cities[i]);
    }

    printf("Enter source city index: ");
    scanf("%d", &source);
    printf("Enter destination city index: ");
    scanf("%d", &dest);


    if(source < 0 || source >= city_count || dest < 0 || dest >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(source == dest) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    if(distance[source][dest] == -1) {
        printf("No direct route exists between these cities!\n");
        printf("Try using the route finder for alternative paths.\n");
        return;
    }

    // Show vehicle options
    printf("\nAvailable Vehicles:\n");
    printf("1. Van (Capacity: %dkg, Rate: %.2f LKR/km)\n",
           vehicles[0].capacity, vehicles[0].rate_per_km);
    printf("2. Truck (Capacity: %dkg, Rate: %.2f LKR/km)\n",
           vehicles[1].capacity, vehicles[1].rate_per_km);
    printf("3. Lorry (Capacity: %dkg, Rate: %.2f LKR/km)\n",
           vehicles[2].capacity, vehicles[2].rate_per_km);

    printf("Select vehicle type (1-3): ");
    scanf("%d", &vehicle_type);

    if(vehicle_type < 1 || vehicle_type > 3) {
        printf("Invalid vehicle type!\n");
        return;
    }

    printf("Enter package weight (kg): ");
    scanf("%f", &weight);

    if(weight <= 0) {
        printf("Weight must be positive!\n");
        return;
    }


    if(weight > vehicles[vehicle_type-1].capacity) {
        printf("Weight exceeds vehicle capacity! Maximum for %s: %dkg\n",
               vehicles[vehicle_type-1].name, vehicles[vehicle_type-1].capacity);
        return;
    }

    // Calculate and display delivery details
    calculateDeliveryDetails(source, dest, weight, vehicle_type);
}

