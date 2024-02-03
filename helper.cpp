#include "helper.h"

/**
 * Generate prime candidate
 *
 * This function generates a prime candidate of size BIT_LENGTH.
 * It uses the std::bitset library to create a bitset of size BIT_LENGTH.
 * The first and last bit are set to 1 and the rest of the bits are set to random values.
 *
 * @return std::bitset<BIT_LENGTH>
 */
std::bitset<MAX_BIT_LENGTH> Helper::generatePrimeCandidate() {
    // Create bitset of size CANDIDATE_SIZE
    std::bitset<MAX_BIT_LENGTH> candidate_bitset;

    // Set the first and last bit to 1
    candidate_bitset.set(0);
    candidate_bitset.set(MAX_BIT_LENGTH - 1);

    // Generate random number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    // Generate random bits
    for (int i = 1; i < MAX_BIT_LENGTH - 1; i++) { candidate_bitset.set(i, dis(gen)); }

    return candidate_bitset;
}

/**
 * Convert bitset to cpp_int
 *
 * This function converts a bitset to cpp_int. It is used to convert the prime candidate bitset to cpp_int.
 * It uses the to_ullong() function from the boost::multiprecision::cpp_int library.
 * Maximum bitset size is set to 64 bits due to the limitations of the to_ullong() function.
 *
 * @param bitset
 * @return
 */
boost::multiprecision::cpp_int Helper::bitsetToCppInt(std::bitset<MAX_BIT_LENGTH> bitset) {
    return bitset.to_ullong();
}

/**
 * Sieve of Eratosthenes algorithm
 *
 * This function implements the Sieve of Eratosthenes algorithm.
 * It is used to generate the first n prime numbers.
 * The first n prime numbers are stored in the FIRST_PRIMES vector.
 *
 * @param max_n
 */
void Helper::sieveOfEratosthenes(Helper &helper, const size_t max_n) {
    // Create a boolean array "prime[0...n]"
    bool prime[max_n + 1];
    // Initialize all entries it as true. A value in prime[i] will finally be false if i is Not a prime, else true.
    memset(prime, true, sizeof(prime));

    // Loop to update prime[]
    for (int p = 2; p * p <= max_n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p]) {
            for (int i = p * p; i <= max_n; i += p) { prime[i] = false; }
        }
    }

    // Store primes in FIRST_PRIMES vector
    for (int p = 2; p <= max_n; p++) {
        if (prime[p]) { helper.FIRST_PRIMES.emplace_back(p); }
    }
}


// Getters

/**
 * Get first n primes
 *
 * This function returns the first n primes.
 *
 * @return const std::vector<unsigned int> &
 */
const std::vector<unsigned int> &Helper::getFirstPrimes() const {
    return FIRST_PRIMES;
}

boost::multiprecision::cpp_int Helper::stringToCppInt(char *string) { return boost::multiprecision::cpp_int(string); }
