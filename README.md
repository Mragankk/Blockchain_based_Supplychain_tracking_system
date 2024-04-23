# BLOCKCHAIN BASED SUPPLYCHAIN TRACKING SYSTEM

A blockchain-based supply chain tracking system utilizes blockchain technology to enhance transparency, traceability, and security throughout the supply chain process.

**Decentralized Ledger:**
- All transactions and data exchanges within the supply chain are recorded. Each participant in the supply chain network has a copy of this ledger, ensuring transparency and eliminating the need for a central authority.

**Traceability:**
- Enables complete traceability of products from their origin to their final destination. Each step in the supply chain, from raw material sourcing to manufacturing, packaging, distribution, and retail, is recorded on the blockchain. This transparency helps in identifying inefficiencies, reducing fraud, and ensuring compliance with regulations.

**Immutable Records:**
- Once recorded on the blockchain, data cannot be altered or deleted, ensuring the integrity of the supply chain records. This feature prevents tampering and fraud, as any attempt to modify data would require consensus from the majority of participants in the network.

**Enhanced Security:**
- Employs cryptographic techniques to secure data and transactions. Each participant in the network has a unique cryptographic key, and transactions are encrypted, making them highly secure. This reduces the risk of data breaches and cyber attacks.

**Real-time Monitoring:**
- Participants in the supply chain can access real-time updates and insights into the movement of goods, inventory levels, and production status. This real-time visibility helps in making informed decisions and quickly addressing any issues that may arise.

**Compliance and Auditing:**
- Blockchain-based supply chain systems facilitate easier compliance with regulations and standards. Auditors can access the immutable records on the blockchain to verify compliance at each stage of the supply chain.

## Pre-requisites:

```
gcc (mingw-32 for windows)
picosha2
```

## PicoSHA2
- We use picoSHA2 library to perform SHA-256 hashing in the project.
- SHA-256 is a cryptographic hash function that produces a fixed-size (256-bit or 32-byte) hash value from input data of arbitrary size.
- Reason to use PicoSHA2 - It provides a simple and efficient way to compute hash values in C++ programs without dependencies on external libraries.
- Functions used in the project from PicoSHA2 library:
  -  `sha256()` : uses Picosha2 to calculate the SHA-256 hash of a given input string
  -  `hash256()` : to compute the hash
  -  `bytes_to_hex_string()`: converts the resulting hash into a hexadecimal string representation
  -   In the `Block` struct, the `calculateHash()` method is used to compute the hash of the block's data, including the index, timestamp, data, previous hash, and nonce and this method internally calls `sha256()` function 
 
 ## Classes
- `Block`:
   - it represents a single block in the blockchain.
   - contains member variables to store the block's index, timestamp, data, previous hash, current hash, and a nonce (used for proof-of-work).
   - it has a method `calculateHash()` to compute the hash of the block's data.
   - also include a method `mineblock()` to perform proof of work
- `Blockchain`:
   - it represents the blockchain, which is a collection of blocks.
   - initializes a new blockchain instance with a single genesis block, serving as the initial block in the chain
   - it contains a vector `chain` of Block objects to store the blocks
   - it includes methods to add new blocks to the blockchain `addBlock()`, get the current timestamp `getCurrentTimestamp()`, retrieve block data by hash `getDataByHash()`, and print the entire blockchain `printChain()`.
      
## Functions
- `sha256(const std::string& sr)`: computes the SHA-256 hash of the provided string (src) and returns the hexadecimal representation of the hash
- `calculateHash()`: calculates the hash of the block's data by concatenating the block's index, timestamp, data, previous hash, and nonce into a single string and passes it to the sha256() function and returns the hash of the block.
- `addBlock()`: adds a new block to the blockchain with the provided data also retrieves the previous block's hash and constructs a new block with incremented index, current timestamp, provided data, and previous hash,pPerforms proof-of-work mining for the new block.
- `getDataByHash()`: retrieves block data by the hash value by searching the blockchain for the block with the specified hash. Returns the block if found, otherwise returns a default block.
- `getCurrentTimestamp()`: Gets the current system timestamp in the format YYYY-MM-DD HH:MM:SS
- `printChain()`: Prints the entire blockchain, including index, timestamp, data, previous hash, and hash of each block.

## Output of a example

  ![image](https://github.com/Mragankk/Blockchain_based_Supplychain_tracking_system/assets/145200189/a5a60273-975d-4fe0-b392-0dc51f61907c)

