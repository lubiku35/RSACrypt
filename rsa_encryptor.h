#ifndef RSA_RSA_ENCRYPTOR_H
#define RSA_RSA_ENCRYPTOR_H

#include "rsa.h"

class RSAEncryptor : public RSA {
private:
    // Private key D
    boost::multiprecision::cpp_int D;
    // Message M
    std::string M;
    // Encrypted message C
    boost::multiprecision::cpp_int C;
public:
    // Constructor with boost::multiprecision::cpp_int message
    RSAEncryptor(const RSA& parent, const std::string& m);

    // Getters
    [[nodiscard]] boost::multiprecision::cpp_int getD() const;

    [[nodiscard]] std::string getM() const;

    [[nodiscard]] boost::multiprecision::cpp_int getC() const;

    // Setters
    void setD(boost::multiprecision::cpp_int d);

    void setM(std::string m);

    void setC(boost::multiprecision::cpp_int c);

    // Encrypt message
    std::vector<boost::multiprecision::cpp_int> encryptMessage();

};


#endif //RSA_RSA_ENCRYPTOR_H
