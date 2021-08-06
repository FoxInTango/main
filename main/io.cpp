#include <libarguments/libarguments.h>
#include <libioevent/libioevent.h>
#include <libmodule/libmodule.h>
#include <libmodel/libmodel.h>
#include <libcpp/libcpp.h>
using namespace foxintango;
#include <iostream>

int main(int argc,char** argv) {
    Model ioModel(ME::MET_MAP);
    ME engines(ME::MET_ARRAY);
    ioModel.insertSubelement(&engines,"engines");
    ioModel.echo(0);
    std::cout << "IO Model subelement count : " << ioModel.subelementCount() << std::endl;
    libioevent_startup(ioModel);

    libioevent_shutdown();
    return 0;
}
