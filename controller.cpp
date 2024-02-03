/**
 * Controller class implementation
 *
 * @brief Controller class implementation
 * @file controller.cpp
 */

#include "controller.h"


/**
 * Convert time point to milliseconds
 *
 * @brief Convert time point to milliseconds
 * @tparam TimePoint
 * @param tp
 * @return
 */
template <typename TimePoint>
std::chrono::duration<double> to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(tp);
}


/**
 * Default constructor
 *
 * @brief Default constructor
 */
Controller::Controller() = default;

/**
 * Constructor
 *
 * @brief Constructor
 * @param rsa
 * @param helper
 * @param menu
 */
Controller::Controller(RSA &rsa, Helper &helper, Menu &menu)
    : rsa(rsa), helper(helper), menu(menu)
{
    // Print Banner and Welcome message
    Menu::printBanner();
    Menu::printWelcomeMessage();
}

/**
 * Get user parameters
 *
 * This function is responsible for getting user parameters and calling appropriate functions.
 *
 * @brief Get user parameters
 * @param argc
 * @param argv
 */
void Controller::handleUserParameters(int argc, char *argv[]) {
    std::vector<std::string> allowed = {"-h", "--help", "-e", "--encrypt", "-d", "--decrypt"};

    // Check if no arguments are provided
    if (argc == 1) {
        std::cerr << "Error: No arguments provided." << std::endl;
        exit(1);
    }


    // Start at 1 to skip the program name
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        // Check if argument is allowed
        if (std::find(allowed.begin(), allowed.end(), arg) == allowed.end()) {
            std::cerr << "Error: Invalid argument: " << arg << std::endl;
            exit(1);
        }

        if (arg == "-h" || arg == "--help") {
            Menu::printHelpMenu();
            exit(1);
        }
        else if (arg == "-e" || arg == "--encrypt") {
            if (i + 1 < argc) {
                this->controlEncryption(argv[i + 1]);
                exit(1);
            }
            else {
                std::cerr << "Error: -e option requires one argument." << std::endl;
                exit(1);
            }
        }
        else if (arg == "-d" || arg == "--decrypt") {
            if (i + 3 < argc) {
                // Convert private key and modulus N to cpp_int
                try {
                    boost::multiprecision::cpp_int privateKeyD = helper.stringToCppInt(argv[i + 2]);
                    boost::multiprecision::cpp_int modulusN = helper.stringToCppInt(argv[i + 3]);
                    // Decrypt with additional parameters
                    this->controlDecryption(argv[i + 1], privateKeyD, modulusN);
                    i += 3; // Skip the additional parameters
                    exit(1);
                } catch (const std::exception& e) {
                    std::cerr << "\nError: -d option requires three arguments: <string> <private_key> <modulus_N>"
                              << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "\nError: -d option requires three arguments: <string> <private_key> <modulus_N>"
                          << std::endl;
                exit(1);
            }
        }
    }
}

/**
 * Control encryption
 *
 * This function is responsible for controlling whole process of the encryption.
 * It will encrypt the message using the public key.
 * Also it will decrypt (testing decryption) the encrypted message using the private key.
 *
 * @brief Control encryption
 * @param message Message to encrypt
 */
void Controller::controlEncryption(const std::string& message) {
    // Generate prime numbers
    helper.sieveOfEratosthenes(helper);

    // ======== Generate prime candidates ========
    PrimeCandidate p_candidate = PrimeCandidate();
    PrimeCandidate q_candidate = PrimeCandidate();

    while (true) {
        // Generate prime candidate
        std::bitset<MAX_BIT_LENGTH> p_candidate_bits = helper.generatePrimeCandidate();

        // Convert prime candidate to cpp_int
        p_candidate.setCandidate(helper.bitsetToCppInt(p_candidate_bits));

        // Check if prime candidate is prime
        if (rsa.isLowLevelPrimeCandidate(helper, p_candidate.getCandidate()) && rsa.isHighLevelPrimeCandidate(p_candidate.getCandidate())) {
            std::cout << "Prime candidate P is: " << p_candidate.getCandidate() << std::endl;
            p_candidate.setIsPrime(true);
            break;
        }
    }

    while (true) {
        // Generate prime candidate
        std::bitset<MAX_BIT_LENGTH> q_candidate_bits = helper.generatePrimeCandidate();

        // Convert prime candidate to cpp_int
        q_candidate.setCandidate(helper.bitsetToCppInt(q_candidate_bits));

        // Check if prime candidate is prime
        if (rsa.isLowLevelPrimeCandidate(helper, q_candidate.getCandidate()) && rsa.isHighLevelPrimeCandidate(q_candidate.getCandidate())) {
            std::cout << "Prime candidate Q is: " << q_candidate.getCandidate() << std::endl;
            q_candidate.setIsPrime(true);
            break;
        }
    }


    // Additional check to ensure that P and Q are not equal
    if (p_candidate.getCandidate() == q_candidate.getCandidate()) {
        std::cout << "P and Q are equal, generating new prime candidates..." << std::endl;
        controlEncryption(message);
    }

    // ======== Compute modulus N, phi N and public exponent E ========
    if (p_candidate.getIsPrime() && q_candidate.getIsPrime()) {
        rsa.computeModulusN(p_candidate.getCandidate(), q_candidate.getCandidate());
        rsa.computePhiN(p_candidate.getCandidate(), q_candidate.getCandidate());
        rsa.setPublicExponentE();
    }

    std::cout << "Modulus N is: " << rsa.getModulusN() << std::endl;
    std::cout << "Phi N is: " << rsa.getPhiN() << std::endl;
    std::cout << "Public exponent E is: " << rsa.getPublicExponentE() << std::endl;

    // Encrypt message
    std::cout << "Message to encrypt is: " << message << std::endl;

    // ======== Encryption ========
    RSAEncryptor rsaEncryptor = RSAEncryptor(rsa, message);

    auto e_start = std::chrono::high_resolution_clock::now();
    std::vector<boost::multiprecision::cpp_int> encrypted =  rsaEncryptor.encryptMessage();
    auto e_end = std::chrono::high_resolution_clock::now();

    std::cout << "Encrypted message is: ";
    for (auto & i : encrypted) std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Encryption took: " << to_ms(e_end - e_start).count() << "ms" << std::endl;

    std::cout << std::endl;

    // ======== Decryption ========
    std::cout << "Initializing testing decryption..." << std::endl;

    // Decrypt message - compute private exponent D
    RSADecryptor rsaDecryptor = RSADecryptor(rsa);

    // Compute private exponent D
    rsaDecryptor.findPrivateKeyD();

    std::cout << "Private exponent D is: " << rsaDecryptor.getPrivateKeyD() << std::endl;

    auto d_start = std::chrono::high_resolution_clock::now();
    // Decrypt message
    std::string decrypted = rsaDecryptor.decryptMessage(encrypted);
    auto d_end = std::chrono::high_resolution_clock::now();

    std::cout << "Decrypted message is: " << decrypted << std::endl;
    std::cout << std::endl;

    std::cout << "Decryption took: " << to_ms(d_end - d_start).count() << "ms" << std::endl;

    // ======== Outro ========
    std::cout << std::endl;
    std::cout << "For decryption of your encrypted message, use the following parameters: " << std::endl;
    std::cout << "Encrypted message: ";
    for (auto & i : encrypted) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "Private exponent D: " << rsaDecryptor.getPrivateKeyD() << std::endl;
    std::cout << "Modulus N: " << rsa.getModulusN() << std::endl;
    std::cout << std::endl;
}

/**
 * Control decryption
 *
 * This function is responsible for controlling the decryption. It will decrypt the encrypted message using the
 * private key.
 *
 * @brief Control decryption
 */
void Controller::controlDecryption(const std::string &message, const boost::multiprecision::cpp_int &privateKeyD,
                                   const boost::multiprecision::cpp_int &modulusN) {
    std::cout << "Initializing decryption..." << std::endl;

    auto d_start = std::chrono::high_resolution_clock::now();
    std::string decrypted = RSADecryptor::decryptMessage(message, privateKeyD, modulusN);
    auto d_end = std::chrono::high_resolution_clock::now();

    std::cout << "Decrypted message is: " << decrypted << std::endl;

    std::cout << "Decryption took: " << to_ms(d_end - d_start).count() << "ms" << std::endl;

    std::cout << std::endl;
}

/**
 * Get RSA object
 * @return RSA object
 */
const RSA & Controller::getRsa() const { return rsa; }

/**
 * Get Helper object
 * @return Helper object
 */
Helper Controller::getHelper() const { return helper; }

/**
 * Get Menu object
 * @return Menu object
 */
const Menu &Controller::getMenu() const { return menu; }
