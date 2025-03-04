# LOGISTICS PLANNING
This project is based on a logistics planning and cost calculation scenario. It simulates the travel of a courier from a starting point to five customer locations on a 10x10 matrix. The program determines the courier's route based on the customers' positions and calculates the total cost.

Scenario

A company has received product requests from 5 different customers. Each customer’s request is located at a specific point. The courier needs to start from (0,0), visit each customer, and then return to the starting point. The travel costs are represented by randomly assigned numbers on the 10x10 matrix. These numbers represent the cost between two points.

Steps

Random Matrix Creation:

A 10x10 matrix is created, and each cell is assigned a random value between 1 and 100. These values represent the travel costs.

Customer and Courier Locations:

5 random customer points are selected, and these points are shown in blue. The positions of the customer points on the matrix and their address information (using the Pointer concept) are printed. The courier is represented in red at the starting point (0,0) with the letter 'K'.

Courier Route Plan:

The courier visits all customer points and moves to the next adjacent point after each visit. The travel cost to the visited point is added to the total cost. The points visited by the courier are shown in green.

Return to the Starting Point:

After visiting all customer points, the courier returns to the starting point (0,0). The final route taken by the courier is shown.

Total Travel Cost:

The total travel cost is updated and printed to the screen after each step.

Saving Customer Information:

At the end of the program, customer information and the total travel costs are written to a file called "Cost.txt".

Technologies Used

C++: The primary language used for database operations, file writing, random number generation, matrix operations, and colored outputs. Pointers: Pointers are used to show customer addresses.

