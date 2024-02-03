#include "prime_candidate.h"

/**
 * Constructor
 *
 * @param candidate
 * @param isPrime
 */
[[maybe_unused]] PrimeCandidate::PrimeCandidate(boost::multiprecision::cpp_int candidate, bool isPrime)
    : candidate(candidate), isPrime(isPrime)
{}


/**
 * Default constructor
 */
PrimeCandidate::PrimeCandidate()
    : candidate(0), isPrime(false)
{}

/**
 * Get prime candidate
 *
 * @return const boost::multiprecision::cpp_int&
 */
const boost::multiprecision::cpp_int &PrimeCandidate::getCandidate() const {
    return candidate;
}


/**
 * Set prime candidate
 *
 * @param candidate
 */
void PrimeCandidate::setCandidate(const boost::multiprecision::cpp_int &candidate) {
    this->candidate = candidate;
}

/**
 * Get prime candidate status
 *
 * @return bool
 */
bool PrimeCandidate::getIsPrime() const {
    return this->isPrime;
}

/**
 * Set prime candidate status
 *
 * @param isPrime
 */
void PrimeCandidate::setIsPrime(bool isPrime) {
    this->isPrime = isPrime;
}

