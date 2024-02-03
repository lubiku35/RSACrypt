#include "controller.h"
#include "menu.h"
#include "rsa.h"
#include "helper.h"


int main(int argc, char *argv[]) {
    // Initialize necessary objects
    Menu menu = Menu();
    RSA rsa = RSA();
    Helper helper = Helper();

    // Initialize controller
    Controller controller = Controller(rsa, helper, menu);

    // Handle user parameters
    controller.handleUserParameters(argc, argv);
}
