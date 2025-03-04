#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <clocale>
#include <algorithm>  // For std::max
#include <sstream>    // For using std::ostringstream

const int SIZE = 10;  // Matrix size
const int CUSTOMER_COUNT = 5;  // Number of customers

// Function prototypes
void createMatrix(int matrix[SIZE][SIZE]);
void printMatrix(int matrix[SIZE][SIZE], int courierX, int courierY, bool visited[SIZE][SIZE], int customers[CUSTOMER_COUNT][2], bool afterMove = false);
void selectCustomers(int customers[CUSTOMER_COUNT][2], bool visited[SIZE][SIZE], int* addresses[CUSTOMER_COUNT]);
int calculateRoute(int matrix[SIZE][SIZE], int customers[CUSTOMER_COUNT][2], bool visited[SIZE][SIZE], int& totalCost);
void writeResultsToFile(int customers[CUSTOMER_COUNT][2], int totalCost, int* addresses[CUSTOMER_COUNT]);

int main() {
    setlocale(LC_ALL, "Turkish");  // For Turkish character support
    srand(time(0));  // Initialize random number generator

    int matrix[SIZE][SIZE];  // Matrix to hold the cost of the paths
    bool visited[SIZE][SIZE] = { false };  // Visited cells
    int customers[CUSTOMER_COUNT][2];  // Customer coordinates
    int* addresses[CUSTOMER_COUNT];  // Array of pointers to customer addresses
    int totalCost = 0;  // Total route cost

    // Create matrix and customer information
    createMatrix(matrix);
    selectCustomers(customers, visited, addresses);

    std::cout << "\nInitial Matrix (Customers and Courier):\n";
    printMatrix(matrix, 0, 0, visited, customers);  // Print the initial matrix

    // Calculate the courier route
    totalCost = calculateRoute(matrix, customers, visited, totalCost);

    // Write results to file
    writeResultsToFile(customers, totalCost, addresses);

    // Print results to the console
    std::cout << "\nTotal Cost: " << totalCost << "\nResults have been saved to Cost.txt.\n";

    return 0;
}

// Fills the matrix with random symmetric cost values
void createMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i <= j) {  // Create only the upper triangle and diagonal
                matrix[i][j] = rand() % 100 + 1;  // Random cost between 1 and 100
                matrix[j][i] = matrix[i][j];  // Make it symmetric
            }
        }
    }
}

// Custom function to convert integers to strings
std::string to_string_custom(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Prints the matrix and the locations of the courier and customers
void printMatrix(int matrix[SIZE][SIZE], int courierX, int courierY, bool visited[SIZE][SIZE], int customers[CUSTOMER_COUNT][2], bool afterMove) {
    if (afterMove) {
        std::cout << "\nMatrix After Move:\n";  // Title for matrix after move
    }

    // Fixed width
    const int width = 3;  // 3-character width for each cell (padding with zero for single digits)
    const int space_between_columns = 2;  // Space between columns

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            bool isCustomer = false;
            for (int k = 0; k < CUSTOMER_COUNT; k++) {
                if (customers[k][0] == i && customers[k][1] == j) {
                    isCustomer = true;
                    break;
                }
            }

            // Print the costs with 3-character width
            if (i == courierX && j == courierY) {
                std::cout << "\033[31m" << std::setw(width) << "C" << "\033[0m";  // Red for courier position
            }
            else if (isCustomer) {
                std::cout << "\033[34m" << std::setw(width) << matrix[i][j] << "\033[0m";  // Blue for customers
            }
            else if (visited[i][j]) {
                std::cout << "\033[32m" << std::setw(width) << matrix[i][j] << "\033[0m";  // Green for visited cells
            }
            else {
                std::cout << std::setw(width) << matrix[i][j];  // Other cells
            }

            // Add 2 spaces between columns
            if (j < SIZE - 1) {
                std::cout << "  ";  // 2 spaces
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;  // Add a space between matrices and other output
}

// Randomly selects customer positions
void selectCustomers(int customers[CUSTOMER_COUNT][2], bool visited[SIZE][SIZE], int* addresses[CUSTOMER_COUNT]) {
    for (int i = 0; i < CUSTOMER_COUNT; i++) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (visited[x][y] || (x == 0 && y == 0));  // Check for conflicts (excluding courier position)

        customers[i][0] = x;
        customers[i][1] = y;
        addresses[i] = &customers[i][0];  // Single address assignment
        visited[x][y] = true;
    }

    std::cout << "\nCustomer Locations and Addresses:\n";
    for (int i = 0; i < CUSTOMER_COUNT; i++) {
        std::cout << "Customer " << i + 1 << ": (" << customers[i][0] << ", " << customers[i][1] << ") Address: [" << addresses[i] << "]\n";
    }
    std::cout << std::endl;
}

// Calculates the courier's route, total cost, and prints the progress
int calculateRoute(int matrix[SIZE][SIZE], int customers[CUSTOMER_COUNT][2], bool visited[SIZE][SIZE], int& totalCost) {
    int courierX = 0, courierY = 0;  // Starting point (Courier)

    // Mark the starting point as visited
    visited[0][0] = true;

    for (int i = 0; i < CUSTOMER_COUNT; i++) {
        int targetX = customers[i][0];
        int targetY = customers[i][1];

        // Move to the target customer location
        while (courierX != targetX || courierY != targetY) {
            if (courierX < targetX) courierX++;
            else if (courierX > targetX) courierX--;

            if (courierY < targetY) courierY++;
            else if (courierY > targetY) courierY--;

            // Add the cost of the cell to the total cost
            totalCost += matrix[courierX][courierY];
            visited[courierX][courierY] = true;

            // Print the matrix and current total cost
            printMatrix(matrix, courierX, courierY, visited, customers, true);
            std::cout << "Current Total Cost: " << totalCost << "\n\n";
        }
    }

    // After visiting all customers, return to the starting point
    while (courierX != 0 || courierY != 0) {
        if (courierX > 0) courierX--;
        if (courierY > 0) courierY--;

        // Add the cost of returning to the starting point
        totalCost += matrix[courierX][courierY];
        visited[courierX][courierY] = true;

        // Print the matrix and current total cost
        printMatrix(matrix, courierX, courierY, visited, customers, true);
        std::cout << "Current Total Cost: " << totalCost << "\n\n";
    }

    return totalCost;
}

// Writes results to a file
void writeResultsToFile(int customers[CUSTOMER_COUNT][2], int totalCost, int* addresses[CUSTOMER_COUNT]) {
    std::ofstream file("cost.txt");
    if (file.is_open()) {
        // Write customer locations and addresses first
        file << "Customer Locations and Addresses:\n";
        for (int i = 0; i < CUSTOMER_COUNT; i++) {
            file << "Customer " << i + 1 << ": (" << customers[i][0] << ", " << customers[i][1] << ") Address: [" << addresses[i] << "]\n";
        }

        // Add two new lines
        file << "\n\n";

        // Write the total cost
        file << "Total Cost: " << totalCost;

        file.close();
    }
    else {
        std::cout << "File could not be opened!\n";
    }
}
