#include "menu.h"

/**
 * printBanner
 *
 * @brief Print banner
 */
void Menu::printBanner() {
    std::string banner =
            "    ____  _____  ___    ______ ____ __  __ ____  ______\n"
            "   / __ \\/ ___/ /   |  / ____// __ \\ \\/ / / __ \\/_  __/\n"
            "  / /_/ /\\__ \\/ /| | / /    / /_/ /\\  / / /_/ / / /   \n"
            " / _, _/___/ // ___ |/ /___ / _, _/ / / / ____/ / /    \n"
            "/_/ |_|/____//_/  |_|\\____//_/ |_| /_/ /_/     /_/     \n\n";

    // Boost format for blue text
    boost::format blueText("\033[1;34m%s\033[0m");

    std::cout << blueText % banner;
}

/**
 * Print welcome menu
 *
 * @brief Print welcome menu
 */
void Menu::printWelcomeMessage() {
    std::cout << "Welcome to RSAcrypt | RSA Encryption and Decryption program" << std::endl;
    std::cout << std::endl;
}


/**
 * Print help menu
 *
 * @brief Print help menu
 */
void Menu::printHelpMenu() {
    std::cout << "-e \t[--encrypt] \"input\"\t\t\t\t\t Encrypt message" << std::endl;
    std::cout << "-d \t[--decrypt] \"input\" <private key D> <modulus N>\t\t Decrypt message" << std::endl;
}