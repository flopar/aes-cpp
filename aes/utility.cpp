#include "utility.hpp"
#include <bit>

int transformKeyToWordList(const std::string& key, std::vector<unsigned int>& wordList){
	std::vector<unsigned int> list;
	size_t keySize = key.size();
	//empty key
	if(!keySize){
		return -1;
	}
	std::cout << (std::endian:native == std::endian::big) << std::endl;
	unsigned int word = 0, mask = 0xFF;
	for(size_t i = 0; i<keySize; i++){
		word |= (unsigned int)(key[i]<<(i*8));
		std::cout << word <<"\n";
	}
}
