#include "rsa.h"

/**
 * Low level prime candidate primality test (Divisibility test)
 *
 * This function is responsible for performing the low level primality test for prime candidates. It will check if the
 * prime candidate is divisible by any of `FIRST_PRIMES` vector from `helper` class. If the prime candidate is divisible by any of
 * `FIRST_PRIMES` vector from `helper` class, then the prime candidate is not prime.
 *
 * @brief Low level prime candidate primality test (Divisibility test)
 * @param helper Helper class instance
 * @param candidate Prime candidate
 * @return True if prime candidate is prime, false otherwise
 */
bool RSA::isLowLevelPrimeCandidate(Helper &helper, const boost::multiprecision::cpp_int& candidate) {
    // Get first n primes from helper class
    const std::vector<unsigned int> &FIRST_PRIMES = helper.getFirstPrimes();

    // Loop through first n primes
    for (const auto &FIRST_PRIME: FIRST_PRIMES) {
        // Check if prime candidate is divisible by first n primes
        if (candidate % FIRST_PRIME == 0) return false;
    }

    // Additional checks
    if (candidate <= 1 || candidate % 2 == 0 || candidate % 3 == 0 || candidate % 5 == 0) return false;

    return true;
}

/**
 * High level prime candidate primality test (Miller-Rabin test)
 *
 * This function is responsible for performing the high level primality test for prime candidates. It will check if the
 * prime candidate is prime using the Miller-Rabin test.
 *
 * @see https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 * @brief High level prime candidate primality test (Miller-Rabin test)
 * @param candidate Prime candidate
 * @return True if prime candidate is prime, false otherwise
 */
bool RSA::isHighLevelPrimeCandidate(const boost::multiprecision::cpp_int &candidate) {
    boost::multiprecision::cpp_int d = candidate - 1;

    // Find the highest power of 2, k, such that d = 2^k * m
    int k = 0;
    while (d % 2 == 0) {
        d /= 2;
        ++k;
    }
    // Compute m = (n - 1) / 2^k
    boost::multiprecision::cpp_int m = d;

    // Generate random number in range [2, n - 2]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis(2, static_cast<unsigned long long>(candidate - 2));
    boost::multiprecision::cpp_int a = dis(gen);

    // Compute x = a^m mod n
    boost::multiprecision::cpp_int x = boost::multiprecision::powm(a, m, candidate);

    // Check if x is not 1 and not n - 1
    if (x != 1 && x != candidate - 1) {
        for (boost::multiprecision::cpp_int i = 2; i < MAX_RABIN_ITERATIONS; ++i) {
            x = boost::multiprecision::powm(x, i, candidate);

            if (x == 1) return false; // Composite
            if (x == candidate - 1) return true; // Probable prime
        }

        return false;
    }

    // If x is 1 or n - 1, consider it a probable prime
    return true;
}

/**
 * Compute modulus N
 *
 * This function is responsible for computing the modulus N. It will compute the modulus N using the formula:
 * N = p * q
 *
 * @brief Compute modulus N
 * @param p Prime number
 * @param q Prime number
 */
void RSA::computeModulusN(const boost::multiprecision::cpp_int &p, const boost::multiprecision::cpp_int &q) {
    this->modulus_N = p * q;
}

/**
 * Compute phi N
 *
 * This function is responsible for computing the phi N. It will compute the phi N using the formula:
 * phi N = (p - 1) * (q - 1)
 *
 * @brief Compute phi N
 * @param p Prime number
 * @param q Prime number
 */
void RSA::computePhiN(const boost::multiprecision::cpp_int &p, const boost::multiprecision::cpp_int &q) {
    this->phi_N = (p - 1) * (q - 1);
}

/**
 * Compute public exponent E
 *
 * This function sets the public exponent E to 65537. This is the most common value for E.
 * It is a Fermat prime and is used to avoid some security issues.
 * It is also a safe prime.
 *
 * @brief Compute public exponent E
 */
void RSA::setPublicExponentE() {
    this->publicExponent_E = PUBLIC_EXPONENT_E;
}

// Getters

/**
 * Get modulus N
 *
 * This function is responsible for returning the modulus N.
 *
 * @brief Get modulus N
 * @return Modulus N
 */
const boost::multiprecision::cpp_int &RSA::getModulusN() const {
    return modulus_N;
}

/**
 * Get phi N
 *
 * This function is responsible for returning the phi N.
 *
 * @brief Get phi N
 * @return Phi N
 */
const boost::multiprecision::cpp_int &RSA::getPhiN() const {
    return phi_N;
}

/**
 * Get public exponent E
 *
 * This function is responsible for returning the public exponent E.
 *
 * @brief Get public exponent E
 * @return Public exponent E
 */
const boost::multiprecision::cpp_int &RSA::getPublicExponentE() const {
    return publicExponent_E;
}