#include <iostream>                  // used for input and output operations
#include <vector>                    // provides the vector container class, which is a dynamic array that can resize itself automatically
#include <ctime>                     // provides functions for working with time and date
#include <string>                    // provides functionalities for working with strings
#include <sstream>                   // provides functionalities for working with input/output streams, useful for converting between strings and other data types
#include "picosha2.h"                // this header file includes the Picosha2 library, used for computing SHA-256 hash values.

using namespace std;                 // allows to use symbols from the std namespace without needing to prefix them with 'std::'

std::string sha256(const std::string& src) {                                // sha256 is a function with specific parameter constant input src and declares 'src' as a reference to 'std::string'
    std::vector<unsigned char> hash(picosha2::k_digest_size);               // declares a vector(dynamic array) 'hash' to store elements of type 'unsigned char' i.e bytes of the SHA-256 hash and 'k_digest_size' represents size of hash produced by SHA-256 Algorithm
    picosha2::hash256(src.begin(), src.end(), hash.begin(), hash.end());    // hash256 is a function designed to compute the SHA-256 hash and arguments specify the range of data to be hashed, src. represents iterator pointing to beginning and end of the input string and hash. represents iterator pointing to the beginning and end of th vector'hash'
    std::string hex_hash;                                                   // hex_hash is initialized as empty string 
    picosha2::bytes_to_hex_string(hash.begin(), hash.end(), hex_hash);      // bytes_to_hex_string is a function from picosha2 to convert bytes of hash(stored in vector 'hash') into hexadecimal string , hash. represents as explained above and stores it in 'hex_hash'
    return hex_hash;                                                        // returns the value stored in 'hex_hash'- hexadecimal representation of the SHA-256 hash 
}

struct Block {                        // declaring a struct named 'Block'  user-defined data type that allows to group together related data fields under a single name
// below are the member variables within the Block structure
    int index;                        // index(integer) of the block
    string timestamp;                 // time when block added to the blockchain
    string data;                      // data stored in the block, could be transaction data, or state of the product in supply chain
    string previousHash;              // hash of the previous block in the blockchain
    string hash;                      // hash of the current block
    unsigned int nonce;               // Nonce for proof-of-work

    Block(int idx, const string& ts, const string& d, const string& prevHash) :         // defining a constructor for the Block struct with parameter index, timestamp, data and previous hash of the block
        index(idx), timestamp(ts), data(d), previousHash(prevHash), nonce(0) {          // each variable is initialized with the corresponding parameter value
            hash = calculateHash();                                                     // contains the initialization of the hash variable using the calculateHash() function. 
        }

    string calculateHash() {                                                                    // declaring a function named calculateHash() to calculate hash which returns a string.
        string input = to_string(index) + timestamp + data + previousHash + to_string(nonce);   // concatenating the block's index, timestamp, data, previous hash, and nonce into a single string named 'input'
        return sha256(input);                                                                   // computes SHA-256 hash of 'input' using 'sha256' function defined previously
    }

    void mineBlock(int difficulty) {                        // declaring a void function 'mineblock' taking integer parameter and modifing the 'nonce' and 'hash' of Block                
        string prefix(difficulty, '0');                     // prefix(string) represents the target hash pattern that the block's hash must meet to be considered valid
        while (hash.substr(0, difficulty) != prefix) {      // using while loop for recalculating the hash until a hash meeting the required difficulty is found 
            nonce++;                                        // incrementing nonce within loop
            hash = calculateHash();                         // newly calculated hash is stored in the hash variable.
        }
    }
};

class Blockchain {                          // defining a class Blockchain which is a collection of blocks
private:                                    // encapsulating the blockchain data structure to maintain vector of blocks and storing the difficulty level of proof of work
    vector<Block> chain;                    // stores individual blocks
    int difficulty;                         // Difficulty for proof-of-work

public:
    Blockchain() : difficulty(0) {                                                      // constructor function to create a new instance of blockchain with default difficulty '0'
        chain.emplace_back(Block(0, getCurrentTimestamp(), "Genesis Block", "0"));      // creating a genesis block with index and previous hash 0 and timestamp when it is created 
    }

    void addBlock(const string& data) {                                                     // declaring a function addblock which will siply add a new block by taking parameters as the data of new block directly
        const Block& lastBlock = chain.back();                                              // retrieving a reference to the last block in 'chain'
        Block newBlock(lastBlock.index + 1, getCurrentTimestamp(), data, lastBlock.hash);   // create a new block instance and assigning the index(incremented from last block), setting timestamp, data and also storing hash of previous block 
        newBlock.mineBlock(difficulty);                                                     // 'Block' object newBlock has a method named 'mineBlock()' that is being called with a parameter 'difficulty'
        chain.emplace_back(newBlock);                                                       //  adding new block to the end of 'chain' which is a vector 
    }

    Block getDataByHash(const string& hash) {                  // declaring a function to retrieve data using hash
        for (const Block& block : chain) {                     // iterating over each block in chain 
            if (block.hash == hash) {                          
                return block;    
            }
        }

        return Block(-1, "", "", "");                         // returning the Block takes parameter as (index,timestamp,data,previoushash)
    }
    
    string getCurrentTimestamp() {                             // function to get timestamp when block is created
        time_t now = time(0);                                  // variable 'now' contains current time as no. of seconds
        struct tm tstruct;                                     // structure variable tstruct of type tm(calender time)
        char buf[80];                                          // character array 'buf' of size 80 to store timestamp
        tstruct = *localtime(&now);                            // 'localtime' function will convert 'now' to local time
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);   // strtime function formats the time and date according to the specified as year, month, date
        return buf;
    }

    void printChain() {                                                 // void function printchain
        cout << "-------BLOCKCHAIN-------"<< endl;                   
        for (const Block& block : chain) {                              // iterating using for loop over each  'Block' 
            cout << "Index: " << block.index << endl;                   // Printing Block Information:
            cout << "Timestamp: " << block.timestamp << endl;
            cout << "Data: " << block.data << endl;
            cout << "Previous Hash: " << block.previousHash << endl;
            cout << "Hash: " << block.hash << endl << endl;
        }
    }
};

int main() {                     
    Blockchain blockchain;                                         // creating an instance of 'Blockchain' class named "blockchain"

    string product;
    while (true) {                                                          // using while loop for adding product step in block
        cout << "Enter the step of the product (type 'done' to finish): ";  // asking the user to enter next step of product
        getline(cin, product);                                              // reads a line of text from the input and stores it in the product variable.
        if (product == "done")
            break;
        blockchain.addBlock(product);
    }

    blockchain.printChain();                     // each block in the blockchain is iterated over, and its index, timestamp, data, previous hash, and hash are printed

    int option;
    string inputHash;
    while (true) {
        cout << "Select an option:" << endl;
        cout << "1. Retrieve data, index, timestamp" << endl;
        cout << "2. End" << endl;
        cout << "Enter option: ";
        cin >> option;                                // reads the user's input
        cin.ignore();                                 // clears the input
        
        switch (option) {                                    // it handles user's selection and executes cases accordingly
            case 1: { 
                cout << "Enter the hash to retrieve data: ";
                getline(cin, inputHash);

                Block blockInfo = blockchain.getDataByHash(inputHash);           // calling 'getdatabyhash' method of blockchain with arguments as 'inputhash'

                if (blockInfo.index != -1) {                                  // checks if the index of the retrieved block (blockInfo.index) is not equal to -1
                    cout << "------RETRIEVED DATA------"<< endl;
                    cout << "Index: " << blockInfo.index << endl;
                    cout << "Timestamp: " << blockInfo.timestamp << endl;
                    cout << "Data: " << blockInfo.data << endl;
                } else {
                    cout << "Hash not found in the blockchain." << endl;
                }
                break;
            }
            case 2: {
                cout << "Ended..." << endl;
                system("pause"); // Keep the console window open
                return 0;
            }
            default: {                       // executes if none of the cases match the option
                cout << "Invalid option. Please enter a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}
