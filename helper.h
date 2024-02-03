/**
 *  Helper
 *
 *
 *  @brief  Helper class
 *  @file   helper.h
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <bitset>
#include <random>
#include <vector>

#ifndef RSA_HELPER_H
#define RSA_HELPER_H

#define MAX_BIT_LENGTH 64
#define MAX_FIRST_PRIMES 1000

class Helper {
private:
    // First n primes, unsigned int to declare only positive numbers
    std::vector<unsigned int> FIRST_PRIMES {};
public:
    // Generate n-bit prime candidate
    std::bitset<MAX_BIT_LENGTH> generatePrimeCandidate();

    // Convert bitset to cpp_int
    boost::multiprecision::cpp_int bitsetToCppInt(std::bitset<MAX_BIT_LENGTH> bitset);

    // Sieve of Eratosthenes algorithm
    void sieveOfEratosthenes(Helper &helper, const size_t max_n = MAX_FIRST_PRIMES);

    // Get first n primes
    [[nodiscard]] const std::vector<unsigned int> &getFirstPrimes() const;

    boost::multiprecision::cpp_int stringToCppInt(char *string);
};


#endif //RSA_HELPER_H
