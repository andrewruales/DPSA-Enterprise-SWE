#include <iostream>
#include <unordered_map>
#include <stdexcept>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> data;
    std::unordered_map<std::string, int> transactionData;
    bool inTransaction;

public:
    InMemoryDB() : inTransaction(false) {}

    int get(const std::string& key) {
        if (inTransaction && transactionData.count(key)) {
            return transactionData[key];
        } else if (data.count(key)) {
            return data[key];
        } else {
            return 0; // Assuming 0 for non-existent keys
        }
    }

    void put(const std::string& key, int val) {
        if (!inTransaction) {
            throw std::runtime_error("Transaction not in progress");
        }

        transactionData[key] = val;
    }

    void begin_transaction() {
        if (inTransaction) {
            throw std::runtime_error("Transaction already in progress");
        }

        inTransaction = true;
        transactionData.clear();
    }

    void commit() {
        if (!inTransaction) {
            throw std::runtime_error("No open transaction");
        }

        // Apply changes to the main state
        data.insert(transactionData.begin(), transactionData.end());

        // End the transaction
        inTransaction = false;
        transactionData.clear();
    }

    void rollback() {
        if (!inTransaction) {
            throw std::runtime_error("No ongoing transaction");
        }

        // Abort changes made within the transaction
        transactionData.clear();

        // End the transaction
        inTransaction = false;
    }
};

int main() {
    InMemoryDB inmemoryDB;

    // Example Usage
    std::cout << inmemoryDB.get("A") << std::endl; // Returns 0 because A doesn't exist yet

    try {
        inmemoryDB.put("A", 5); // Throws an error as a transaction is not in progress
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    inmemoryDB.begin_transaction(); // Starts a new transaction

    inmemoryDB.put("A", 5); // Sets value of A to 5 within the transaction

    std::cout << inmemoryDB.get("A") << std::endl; // Returns 0 as updates to A are not committed yet

    inmemoryDB.put("A", 6); // Updates A's value to 6 within the transaction

    inmemoryDB.commit(); // Commits the open transaction

    std::cout << inmemoryDB.get("A") << std::endl; // Returns 6, the last value of A to be committed

    try {
        inmemoryDB.commit(); // Throws an error because there is no open transaction
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        inmemoryDB.rollback(); // Throws an error because there is no ongoing transaction
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << inmemoryDB.get("B") << std::endl; // Returns 0 because B does not exist in the database yet

    inmemoryDB.begin_transaction(); // Starts a new transaction

    inmemoryDB.put("B", 10); // Sets key B’s value to 10 within the transaction

    inmemoryDB.rollback(); // Rollback the transaction - revert any changes made to B

    std::cout << inmemoryDB.get("B") << std::endl; // Returns 0 because changes to B were rolled back

    return 0;
}
