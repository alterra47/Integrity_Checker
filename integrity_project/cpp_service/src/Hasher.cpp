#include "Hasher.hpp"
#include "SHA256.hpp"  // engine for processing
#include <iostream>
#include <fstream>
#include <vector>
std::string Hasher::generate_hash(const std::string& filepath){
  if(!std::filesystem::exists(filepath)){return "ERROR:file not found";}

  //perform hashing
  //open file in binary mode
  std::ifstream file(filepath, std::ios::binary);
  if(!file)return "ERROR: cannot open file";

  SHA256 sha256; // sha256 engine instance
  
  //read files in chunk (4KB) to save memory
  const size_t buffer_size = 4096;
  std::vector<uint8_t> buffer(buffer_size);

  while(file.good()){
    file.read(reinterpret_cast<char*>(buffer.data()), buffer_size);
    std::streamsize bytes_read = file.gcount();

    if(bytes_read > 0){
      //resize buffer to actual data read for the chunk
      std::vector<uint8_t> chunk(buffer.begin(), buffer.begin()+bytes_read);
      sha256.update(chunk);
    }
  }

  return sha256.final(); 
}
