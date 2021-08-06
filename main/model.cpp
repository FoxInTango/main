
/** tests:
# load file 
# save file
# encode to   string
# decode from string
# convert to bool,char,char*,int,etc...
# load from bool,char,etc...
# model foreach
*/

#include <libmodel/libmodel.h>
#include <iostream>
using namespace foxintango;
/** 
 * 构造测试
 *     布尔
 *     字节
 *     数值
 *     字符串
 *     :
 * 拷贝测试
 * 赋值测试
 * 转换测试
 * */

int main(int argc,char** argv){
    Model array;
    Model map;

    bool           b   = true;
    char           c   = 'c';
    unsigned char  uc  = 'u';
    short          s   = -3;
    unsigned short us  = 3;
    int            i   = -100;
    unsigned int   ui  = 100;
    long           l   = -100000;
    unsigned long  ul  = 10000;
    float          f   = 100.2f;
    double         d   = 1000000000.02;
    const char*    str = "this is a string.";
    const void*    p   = str;

    ModelElement eb(b);
    ModelElement ec(c);
    ModelElement euc(uc);
    ModelElement es(s);
    ModelElement eus(us);
    ModelElement ei(i);
    ModelElement eui(ui);
    ModelElement el(l);
    ModelElement eul(ul);
    ModelElement ef(f);
    ModelElement ed(d);
    ModelElement estr(str);
    ModelElement ep(p);

    array.setType(ME::MET_ARRAY);
    map.setType(ME::MET_MAP);

    array.appendSubelement(&eb);
    array.appendSubelement(&ec);
    array.appendSubelement(&euc);
    array.appendSubelement(&es);
    array.appendSubelement(&eus);
    array.appendSubelement(&ei);
    array.appendSubelement(&eui);
    array.appendSubelement(&el);
    array.appendSubelement(&eul);
    array.appendSubelement(&ef);
    array.appendSubelement(&ed);
    array.appendSubelement(&estr);
    array.appendSubelement(&ep);

    map.insertSubelement(&eb,"1");
    map.insertSubelement(&ec,"2");
    map.insertSubelement(&euc,"3");
    map.insertSubelement(&es,"4");
    map.insertSubelement(&eus,"5");
    map.insertSubelement(&ei,"6");
    map.insertSubelement(&eui,"7");
    map.insertSubelement(&el,"8");
    map.insertSubelement(&eul,"9");
    map.insertSubelement(&ef,"0");
    map.insertSubelement(&ed,"11");
    map.insertSubelement(&estr,"12");
    map.insertSubelement(&ep,"13");

    array.echo(0);
    map.echo(0);
    return 0;
}
