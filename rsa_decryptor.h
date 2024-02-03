#ifndef RSA_RSA_DECRYPTOR_H
#define RSA_RSA_DECRYPTOR_H

#include "rsa.h"

class RSADecryptor : public RSA {
private:
    boost::multiprecision::cpp_int privateKey_D;
public:
    // Default constructor
    RSADecryptor();

    // Constructor
    explicit RSADecryptor(const RSA& parent);

    // Find private key D
    void findPrivateKeyD();

    // Find modular inverse
    boost::multiprecision::cpp_int modInverse();

    // Getters
    [[nodiscard]] boost::multiprecision::cpp_int getPrivateKeyD() const;

    // Setters
    void setPrivateKeyD(boost::multiprecision::cpp_int privateKeyD);

    // Decrypt message
    std::string decryptMessage(const std::vector<boost::multiprecision::cpp_int>& encryptedMessage);

    // Decrypt message with given private key D and modulus N
    static std::string decryptMessage(const std::string& encryptedMessage,
                               const boost::multiprecision::cpp_int& privateKeyD,
                               const boost::multiprecision::cpp_int& modulusN);

    static boost::multiprecision::cpp_int
    extendedEuclideanAlgorithm(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int m);
};


#endif //RSA_RSA_DECRYPTOR_H
