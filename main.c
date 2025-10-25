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

