#include "repository.h"
#include "fileRepository.h"
#include "service.h"
#include "userService.h"
#include "userInterface.h"
#include "validators.h"
#include <crtdbg.h>
//#include "test/tests.h"


int main() {

    //    run_tests();

   //     Repository repository;
     //   repository.add_10_elements();

    FileRepository fileRepository(R"(C:\Users\Patri-PC\Desktop\MATERII UBB\1\II semester\Object Oriented Programming\Assignment_6\Assignment_6\basket.csv)");

    Service service{ fileRepository };
    UserService userService{ fileRepository };
    Validator validator;
    UserInterface userInterface(service, validator, userService);

    userInterface.start_program();

    _CrtDumpMemoryLeaks();

    return 0;
}