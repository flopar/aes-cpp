#include "aes.hpp"

AES::AES() noexcept {}
AES::AES(const std::string key, std::string message){
	this->mKey = key;
	this->mMessage = message;
	this->mKeyLength = mKey.size();
	this->mMessageLength = mMessage.size(); 
}

std::string AES::getKey() const{
	return this->mKey;
}
void AES::setKey(const std::string key){
	this->mKey = key;
}
std::string AES::getMessage() const{
	return this->mMessage;
}
void AES::setMessage(const std::string message){
	this->mMessage = message;
}

// here begins the fun T_T
std::string AES::encrypt(){
	std::vector<unsigned int> wordList;
	transformKeyToWordList(this->mKey, wordList);
}
