#include <boost/multiprecision/cpp_int.hpp>
#include "helper.h"

#ifndef RSA_RSA_H
#define RSA_RSA_H

#define MAX_RABIN_ITERATIONS 3500
#define PUBLIC_EXPONENT_E 65537

class RSA {
private:
    boost::multiprecision::cpp_int modulus_N;
    boost::multiprecision::cpp_int phi_N;
    boost::multiprecision::cpp_int publicExponent_E;
public:
    // Low level prime candidate primality test (Divisibility test)
    bool isLowLevelPrimeCandidate(Helper &helper, const boost::multiprecision::cpp_int& candidate);

    // High level prime candidate primality test (Miller-Rabin test)
    bool isHighLevelPrimeCandidate(const boost::multiprecision::cpp_int& candidate);

    // Compute modulus N
    void computeModulusN(const boost::multiprecision::cpp_int& p, const boost::multiprecision::cpp_int& q);

    // Compute phi N
    void computePhiN(const boost::multiprecision::cpp_int& p, const boost::multiprecision::cpp_int& q);

    // Compute public exponent E
    void setPublicExponentE();

    // Get modulus N
    [[nodiscard]] const boost::multiprecision::cpp_int &getModulusN() const;

    // Get phi N
    [[nodiscard]] const boost::multiprecision::cpp_int &getPhiN() const;

    // Get public exponent E
    [[nodiscard]] const boost::multiprecision::cpp_int &getPublicExponentE() const;
};


#endif //RSA_RSA_H
