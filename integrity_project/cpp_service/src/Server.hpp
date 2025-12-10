#pragma once
#include "Hasher.hpp"

class Server
{
private:
    Hasher hasher;
public:
    void start(int port);//wait for connection
};
