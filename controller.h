/**
 * Controller
 *
 * @file controller.h
 * @brief Controller class header file
 */

#include <iostream>
#include <chrono>

#include "helper.h"
#include "rsa.h"
#include "menu.h"
#include "prime_candidate.h"
#include "rsa_encryptor.h"
#include "rsa_decryptor.h"

#ifndef RSA_CONTROLLER_H
#define RSA_CONTROLLER_H

class Controller {
private:
    // RSA object
    RSA rsa;
    // Helper object
    Helper helper;
    // Menu object
    Menu menu;
public:
    // Default constructor
    Controller();

    // Constructor
    Controller(RSA &rsa, Helper &helper, Menu &menu);

    // Handle user parameters
    void handleUserParameters(int argc, char *argv[]);

    // Control Encryption process function
    [[maybe_unused]] void controlEncryption(const std::string &message);


    // Control Decryption process function
    [[maybe_unused]] void controlDecryption(const std::string &message, const boost::multiprecision::cpp_int &privateKeyD,
                                            const boost::multiprecision::cpp_int &modulusN);

    // Get RSA object
    [[nodiscard]] const RSA & getRsa() const;

    // Get Helper object
    [[nodiscard]] Helper getHelper() const;

    // Get Menu object
    [[nodiscard]] const Menu &getMenu() const;


};

#endif //RSA_CONTROLLER_H
