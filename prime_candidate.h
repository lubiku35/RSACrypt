/**
 *  PrimeCandidate
 *
 *
 *  @brief  Prime candidate class
 *  @file   prime_candidate.h
 */

#ifndef RSA_PRIME_CANDIDATE_H
#define RSA_PRIME_CANDIDATE_H

#include <boost/multiprecision/cpp_int.hpp>

class PrimeCandidate {
private:
    // Prime candidate
    boost::multiprecision::cpp_int candidate;
    // Prime candidate status
    [[maybe_unused]] bool isPrime;
public:
    // Default constructor
    PrimeCandidate();

    // Constructor
    [[maybe_unused]] PrimeCandidate(boost::multiprecision::cpp_int candidate, bool isPrime);

    // Get prime candidate
    [[nodiscard]] const boost::multiprecision::cpp_int &getCandidate() const;

    // Set prime candidate
    void setCandidate(const boost::multiprecision::cpp_int &candidate);

    // Get prime candidate status
    [[nodiscard]] bool getIsPrime() const;

    // Set prime candidate status
    void setIsPrime(bool isPrime);
};


#endif //RSA_PRIME_CANDIDATE_H
