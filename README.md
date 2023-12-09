# In-Memory Key-Value Database with Transaction Support
## Overview
This C++ program implements an in-memory key-value database with transaction support. The database provides basic functionalities such as get, put, begin_transaction, commit, and rollback. It ensures data consistency during transactions, preventing dirty writes.

### Instructions
To run the code, follow these steps:

#### 1. Compile the Code:

* Open a terminal and navigate to the directory containing the in_memory_db.cpp file.
* Run the following command to compile the code (on macOS):
`g++ -o mycode in_memory_db.cpp`
* On Windows, use:
`g++ -o mycode.exe in_memory_db.cpp`

### 2. Run the Executable:

* Execute the compiled program:
* On macOS:
`./mycode`
* On Windows:
`mycode.exe`

### 3. Review Output:

* The program will display the results of the database operations based on the example usage in the main() function.

## Future Modifications

* Enhanced Error Handling:
Improve error handling for edge cases and unexpected inputs to make the code more robust.

* Documentation:
Expand comments and documentation within the code to provide clearer explanations of the implementation details.

* Optimizations:
Explore opportunities for code optimizations and improvements in data structures to enhance performance.

* Additional Features:
Consider adding more features to the database, such as support for different data types, indexing, or concurrent transactions.

