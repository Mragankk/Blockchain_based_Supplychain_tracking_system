#include <iostream> 
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include "picosha2.h"

using namespace std;

std::string sha256(const std::string& src) {
    std::vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(src.begin(), src.end(), hash.begin(), hash.end());
    std::string hex_hash;
    picosha2::bytes_to_hex_string(hash.begin(), hash.end(), hex_hash);
    return hex_hash;
}

struct Block {
    int index;
    string timestamp;
    string data;
    string previousHash;
    string hash;
    unsigned int nonce; // Nonce for proof-of-work

    Block(int idx, const string& ts, const string& d, const string& prevHash) : 
        index(idx), timestamp(ts), data(d), previousHash(prevHash), nonce(0) {
            hash = calculateHash();
        }

    string calculateHash() {
        string input = to_string(index) + timestamp + data + previousHash + to_string(nonce);
        return sha256(input);
    }

    // Proof-of-work mining
    void mineBlock(int difficulty) {
        string prefix(difficulty, '0');
        while (hash.substr(0, difficulty) != prefix) {
            nonce++;
            hash = calculateHash();
        }
    }
};

class Blockchain {
private:
    vector<Block> chain;
    int difficulty; // Difficulty for proof-of-work

public:
    Blockchain() : difficulty(0) {
        chain.emplace_back(Block(0, getCurrentTimestamp(), "Genesis Block", "0"));
    }

    void addBlock(const string& data) {
        const Block& lastBlock = chain.back();
        Block newBlock(lastBlock.index + 1, getCurrentTimestamp(), data, lastBlock.hash);
        newBlock.mineBlock(difficulty);
        chain.emplace_back(newBlock);
    }


    Block getDataByHash(const string& hash) {
        for (const Block& block : chain) {
            if (block.hash == hash) {
                return block;
            }
        }

        return Block(-1, "", "", "");
    }
    
    string getCurrentTimestamp() {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return buf;
    }

    void printChain() {
        cout << "-------BLOCKCHAIN-------"<< endl;
        for (const Block& block : chain) {
            cout << "Index: " << block.index << endl;
            cout << "Timestamp: " << block.timestamp << endl;
            cout << "Data: " << block.data << endl;
            cout << "Previous Hash: " << block.previousHash << endl;
            cout << "Hash: " << block.hash << endl << endl;
        }
    }
};

int main() {
    Blockchain blockchain;

    string product;
    while (true) {
        cout << "Enter the step of the product (type 'done' to finish): ";
        getline(cin, product);
        if (product == "done")
            break;
        blockchain.addBlock(product);
    }

    blockchain.printChain();

    int option;
    string inputHash;
    while (true) {
        cout << "Select an option:" << endl;
        cout << "1. Retrieve data, index, timestamp" << endl;
        cout << "2. End" << endl;
        cout << "Enter option: ";
        cin >> option;
        cin.ignore();
        
        switch (option) {
            case 1: {
                cout << "Enter the hash to retrieve data: ";
                getline(cin, inputHash);

                Block blockInfo = blockchain.getDataByHash(inputHash);

                if (blockInfo.index != -1) {
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
                return 0;
            }
            default: {
                cout << "Invalid option. Please enter a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}
