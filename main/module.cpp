#include <libioevent/libioevent.h>
#include <libmodule/libmodule.h>
using namespace foxintango;
#include <iostream>
#include <string>
/** module
 *      -c module.json [-p path]
 *      -l pathA pathB pathC
 * */

int main(int argc,char** argv) {

    Module* module = new Module("/usr/local/lib/IOEngineLWS.so");

    ModuleInterface* interface = module->interface();
    if(interface) {
        std::cout << "Module : IOEngineLWS - Interface loaded." << std::endl;

        if(interface->containClass("IOEngineLWS")){
            std::cout << "Module : IOEngineLWS - Class : IOEngineLWS Exists." << std::endl;
        } else {
            std::cout << "Module : IOEngineLWS - Class : IOEngineLWS NOT Exists." << std::endl;
        }
        IOEngine* engine = static_cast<IOEngine*>(interface->createObject("engine"));
        if(engine) {
             std::cout << "Module : IOEngineLWS - IOEngine created." << std::endl;
             delete engine;
        } else {
             std::cout << "Module : IOEngineLWS - IOEngine create failed." << std::endl;
        }
    }
    return 0;
}
