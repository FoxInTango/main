#include <libarguments/libarguments.h>

using namespace foxintango;

int main(int argc,char** argv) {
    arguments args(argc,argv);
    args.echo();
    return 0;
}
