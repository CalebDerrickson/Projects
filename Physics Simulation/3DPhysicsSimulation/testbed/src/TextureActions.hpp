#include "utils.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace textures{



    inline FILE_EXTENSION assignFileExension(const std::string& str ){
        if (str.compare("png") == 0) {
            return FILE_EXTENSION::PNG;
        }else if (str.compare("jpg") == 0) {
            return FILE_EXTENSION::JPG;
        }
        else {
            std::cout<<"File Extension "<<str<<" not implemented!"<<std::endl;
            return FILE_EXTENSION::UNKNOWN;
        }
    }



};