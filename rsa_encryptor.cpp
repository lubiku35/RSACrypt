#include "rsa_encryptor.h"

RSAEncryptor::RSAEncryptor(const RSA &parent, const std::string &m) : RSA(parent) {
    this->setM(m);
}

/**
 * encryptMessage
 *
 *
 * @param rsa
 * @return std::vector<boost::multiprecision::cpp_int>
 */
std::vector<boost::multiprecision::cpp_int> RSAEncryptor::encryptMessage() {
    // Convert every char in string to its ascii decimal value
    std::vector<boost::multiprecision::cpp_int> asciiValues;
    for (char c : this->getM()) {
        // Convert each character to its ASCII value
        asciiValues.push_back(static_cast<boost::multiprecision::cpp_int>(static_cast<unsigned char>(c)));
    }

    // Encrypt each ascii value
    std::vector<boost::multiprecision::cpp_int> encryptedAsciiValues;
    for (const boost::multiprecision::cpp_int& asciiValue: asciiValues)
        // Compute the power of the message and the public exponent e modulo n
        encryptedAsciiValues.emplace_back(boost::multiprecision::powm(asciiValue, this->getPublicExponentE(), this->getModulusN()));

    return encryptedAsciiValues;
}

// Getters

/**
 * getM
 *
 * Getter for M - message
 *
 * @return std::string
 */
std::string RSAEncryptor::getM() const { return M; }

/**
 * getC
 *
 * Getter for C - encrypted message
 *
 * @return boost::multiprecision::cpp_int
 */
boost::multiprecision::cpp_int RSAEncryptor::getC() const { return C; }


// Setters


/**
 * setM
 *
 * Setter for M - message
 *
 * @param m
 */
void RSAEncryptor::setM(std::string m) { M = m; }

/**
 * setC
 *
 * Setter for C - encrypted message
 *
 * @param c
 */
void RSAEncryptor::setC(boost::multiprecision::cpp_int c) { C = c; }


