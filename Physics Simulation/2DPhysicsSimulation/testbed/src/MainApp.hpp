#pragma once
#include "BaseApp.hpp"
#include "ResourceManager.hpp"

class MainApp : public BaseApp
{
public:
    MainApp(int width, int height, const char* title);
    ~MainApp();

    STATE init() override;
    STATE run() override;
    STATE shutdown() override;

private:
    // window pointer is provided by the BaseApp class

    ResourceManager _ResourceManager;
};