#include "rsa_decryptor.h"

/**
 * RSADecryptor
 *
 * Default constructor
 */
RSADecryptor::RSADecryptor() {}

/**
 * RSADecryptor
 *
 * Constructor
 *
 * @param parent
 */
RSADecryptor::RSADecryptor(const RSA &parent) : RSA(parent) {}

/**
 * Extended Euclidean Algorithm
 *
 * This function implements the extended Euclidean algorithm to find the modular inverse of a number.
 * Modular inverse of an integer a is an integer x such that (a*x) % m = 1, where m is the modulus.
 *
 * @param a
 * @param m
 * @return
 */
boost::multiprecision::cpp_int RSADecryptor::extendedEuclideanAlgorithm(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int m) {
    // Initialize variables for the extended Euclidean algorithm
    boost::multiprecision::cpp_int original_m = m;
    boost::multiprecision::cpp_int quotient, remainder;
    boost::multiprecision::cpp_int x_current = 0, x_previous = 1;

    // Special case: If m is 1, return 0
    if (m == 1)
        return 0;

    // Apply the extended Euclidean algorithm to find the modular inverse
    while (a > 1) {
        // Calculate quotient and remainder in each iteration
        quotient = a / m;
        remainder = a % m;

        // Update a and m for the next iteration
        a = m;
        m = remainder;

        // Update x_current and x_previous
        boost::multiprecision::cpp_int temp = x_current;
        x_current = x_previous - quotient * x_current;
        x_previous = temp;
    }

    // Make x_previous positive
    if (x_previous < 0)
        x_previous += original_m;

    return x_previous;
}

/**
 * modInverse
 *
 * This function is responsible for finding the modular inverse of a number.
 *
 * @return boost::multiprecision::cpp_int
 */
boost::multiprecision::cpp_int RSADecryptor::modInverse() {
    return extendedEuclideanAlgorithm(this->getPublicExponentE(), this->getPhiN());
}


/**
 * findPrivateKeyD
 *
 * This function is responsible for finding the private key D. It will find the private key calculating the modular
 * inverse of the public exponent E. The modular inverse is calculated using the extended Euclidean algorithm which is
 * called in the modInverse function.
 *
 * @brief Find private key D
 */
void RSADecryptor::findPrivateKeyD() {
    this->setPrivateKeyD(this->modInverse());
}

/**
 * decryptMessage
 *
 * This function is responsible for decrypting the encrypted message. It will decrypt the message using the private
 * key D.
 *
 * @brief Decrypt message
 * @param encryptedMessage Encrypted message
 * @return Decrypted message
 */
std::string RSADecryptor::decryptMessage(const std::vector<boost::multiprecision::cpp_int> &encryptedMessage) {
    std::string decryptedMessage;

    // Decrypt message
    for (auto & i : encryptedMessage) {
        boost::multiprecision::cpp_int decrypted = boost::multiprecision::powm(i, this->getPrivateKeyD(), this->getModulusN());
        decryptedMessage += static_cast<char>(decrypted.convert_to<int>());
    }

    return decryptedMessage;
}

/**
 * decryptMessage
 *
 * This function is responsible for decrypting the encrypted message. It will decrypt the message using the private
 * key D and modulus N.
 *
 * @param encryptedMessage
 * @param privateKeyD
 * @param modulusN
 * @return
 */
std::string RSADecryptor::decryptMessage(const std::string& encryptedMessage, const boost::multiprecision::cpp_int& privateKeyD,
                                         const boost::multiprecision::cpp_int& modulusN) {
    // Convert encrypted message to vector of integers
    std::vector<boost::multiprecision::cpp_int> encryptedMessageVector;
    std::stringstream ss(encryptedMessage);
    boost::multiprecision::cpp_int i;

    // Read every integer from the string stream
    while (ss >> i)
    {
        encryptedMessageVector.push_back(i);
        if (ss.peek() == ' ')
            ss.ignore();
    }

    std::string decryptedMessage;

    // Decrypt message
    for (auto &i: encryptedMessageVector) {
        boost::multiprecision::cpp_int decrypted = boost::multiprecision::powm(i, privateKeyD, modulusN);
        decryptedMessage += static_cast<char>(decrypted.convert_to<int>());
    }

    return decryptedMessage;
}


// Getters

/**
 * getPrivateKeyD
 *
 * Getter for private key D
 *
 * @return boost::multiprecision::cpp_int
 */
boost::multiprecision::cpp_int RSADecryptor::getPrivateKeyD() const { return privateKey_D; }


// Setters

/**
 * setPrivateKeyD
 *
 * Setter for private key D
 *
 * @param privateKeyD
 */
void RSADecryptor::setPrivateKeyD(boost::multiprecision::cpp_int privateKeyD) { privateKey_D = privateKeyD; }