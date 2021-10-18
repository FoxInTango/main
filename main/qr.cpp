#include <libqr/libqr.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h> 
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

/** style - 二维码绘制样式
 *  {
 *      "name":"",
 *      "主样式":"不包含其他特殊样式则统一采取此样式",
 *      "main":{},
 *      "texts":[
 *          {
 *              "x":"",
 *              "y":"",
 *              "w":"",
 *              "h":"",
 *              "font-name":"",
 *              "font-size":"",
 *              "font-style":"",
 *              "color":""
 *          }
 *      ],
 *      "slices":[
 *          {
 *              "x":"",
 *              "y":"",
 *              "s":"",
 *              "mask":"path",
 *              "style":"",
 *              "color":"",
 *              "gradient":{}
 *          }
 *      ]
 *  }
 * */

/** model - 二维码图像模型
 *  {
 *      "name":"",
 *      "backgroud":"path",
 *      "texts":[
 *          {
 *              "x":"",
 *              "y":"",
 *              "w":"",
 *              "h":"",
 *              "font-name":"",
 *              "font-size":"",
 *              "font-style":"",
 *              "color":""
 *          }
 *      ],
 *      "slices":[
 *          {
 *              "x":"",
 *              "y":"",
 *              "s":"",
 *              "mask":"path",
 *              "style":"",
 *              "color":"",
 *              "gradient":{}
 *          }
 *      ]
 *  }
 * */

/** 模块加载
 * */
static QRImageLoadFunctionPointer QRImageCreate;
int    QRModuleLoad();

/** 参数解析
 * */

class argument {
public:
   std::string name;
   std::vector<std::string> values;
public:
   argument() {}
  ~argument() {}
public:
   void echo() {
       std::cout << "name : " << this->name <<std::endl;
       for(int i = 0;i < values.size();i ++) {
           std::cout << "value AT : " << i << values[i] << std::endl;
       }
   }

   bool empty() const {
       return 0 == values.size();
   }
};

class arguments {
public:
    std::map<std::string,argument> argumentMap;
public:
    arguments(const int& count,char** content) {
        if(count && content) {
	    int i = 0;// 参数偏移量
	    int o = 1;// 参数值偏移量
	    while(i < count) {
	        char* param = content[i];
		//std::cout << "parse i : " << i << std::endl;
		if('-' == param[0] && strlen(param) > 1) {
		    argument arg;
		    arg.name += &param[1];
		    o = 1;
		    while(i + o < count) {
		        param = content[i + o];
			//std::cout << "parse o : " << o << std::endl;
			if('-' == param[0]) {
			    break;
			} else {
			    std::string value(content[i + o]);

                            arg.values.push_back(value);
			    o ++;
			}
		    }

		    argumentMap.insert(std::pair<std::string,argument>(arg.name,arg));
		}

		i += o;
		o  = 1;
	    }
	}
    }
   ~arguments() {}

public:
   void echo() {
       auto iter = argumentMap.begin();

       while(iter != argumentMap.end()) {
           (*iter).second.echo();

	   iter ++;
       }
   }

   bool contain(const std::string& name) const {
       if(argumentMap.count(name)) return true;

       return false;
   }

   const argument& at(const std::string& name) const {
       if(contain(name)) {
           return argumentMap.at(name);
       }

       return argument();
   }
};

/** 编码
 *  -e contentA contentB contentC -n name -p path [-m model -b background -s size]
 * */

int encode(const arguments& args);

/** 解码
 *  -d path
 * */
int decode(const arguments& args);

int main(int argc,char *argv[]) {

    arguments args(argc,argv);
    if(args.contain("e")) {
        std::cout << "encoding..." << std::endl;
	encode(args);
    }
    else if(args.contain("d")) {
        std::cout << "decoding..." << std::endl;
	decode(args);
    }
    return 0;
    char currentDir[128];
    getcwd(currentDir,sizeof(currentDir));
    printf("current working directory: %s\n",currentDir);   

    QRModuleLoad();
    QRImage* image = (*QRImageCreate)();

    char imagePath[128];
    memset(imagePath,0,sizeof(imagePath));
    strcat(imagePath,currentDir);
    strcat(imagePath,"/");
    strcat(imagePath,"bin/zbar.png");
    printf("image path : %s \n",imagePath);
    if(image) {
        printf("QRImage Loaded!\n");
	image->loadFile(imagePath);
    }

    unsigned int sliceCount = image->sliceCount();
    for(unsigned int i = 0;i < sliceCount;i ++) {
        QRSlice* slice = image->sliceAt(i);

	if(slice) {
	    printf("QRImage Slice At %u content %s \n",i,slice->contentGet());
	}
    }
    return 0;
}

int QRModuleLoad() {
    void* libqr = dlopen("libqr.so",RTLD_LAZY);
    const char* error = dlerror();

    if(error)
    {
        printf("dlopen error : %s \n",error);
        return 0;
    }

    QRImageCreate = (QRImageLoadFunctionPointer)dlsym(libqr,"createQRImage");
    error = dlerror();
    if(error)
    {
        printf("dlopen error : %s \n",error);
        return 0;
    }

    return 1;
}

/** 编码
 *  -e contentA contentB contentC -n name -p path [-m model -b background -s size]
 * */

int encode(const arguments& args) {    
    const argument& arg = args.at("e");
    QRImage* image = new QRImage();
    if(!arg.empty()) {
        for(int i=0;i < arg.values.size();i++) {
	    QRSlice* slice = new QRSlice();

	    if(slice) {
	        slice->contentSet(arg.values[i].c_str());

		slice->saveToFile("./bin","OK",4);
	    }
	}
    }

    return 0;
}

/** 解码
 *  -d path
 * */
int decode(const arguments& args) {
    const argument& arg = args.at("d");
    if(!arg.empty()) {
        for(int i=0;i < arg.values.size();i++) {
            std::string path = arg.values[i];
            QRImage* image = new QRImage();
            if(image) {
                //printf("QRImage Loaded!\n");
                image->loadFile(path.c_str());
            }
            unsigned int sliceCount = image->sliceCount();
            for(unsigned int i = 0;i < sliceCount;i ++) {
                QRSlice* slice = image->sliceAt(i);
                if(slice) {
                    printf("QRImage Slice At %u content %s \n",i,slice->contentGet());
                }
            }

        return sliceCount;
        } 
    }

    return 0;
}
