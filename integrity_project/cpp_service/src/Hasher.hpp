#pragma once
#include<string>
#include<filesystem>
class Hasher{
public:
  std::string generate_hash(const std::string& filepath);
};
