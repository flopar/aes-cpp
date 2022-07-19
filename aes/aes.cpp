#include "aes.hpp"

AES::AES() noexcept {}
AES::AES(const std::string key, std::string message){
	this->mKey = key;
	this->mMessage = message;
	this->mKeySize = mKey.size();
	this->mMessageSize = mMessage.size();
	this->Nk = mKeySize/4;
	// according to the aes standard Nb must be 4
	this->Nb = 4;
	// the number of rounds depends on the size of the key
	if(this->mMessageSize == 4){
		this->Nr = 10;
	}
	if(this->mMessageSize == 6){
		this->Nr = 12;
	}
	if(this->mMessageSize == 8){
		this->Nr = 14;
	}

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
	this->expandKey(wordList);
}

int AES::expandKey(std::vector<unsigned int>& wordList){
	if(!this->mKeySize){
		return -1;
	}	

	// for each 4 bytes create one word and add it to the list
	unsigned int tempWord = 0;
	for(size_t i=0; i<this->Nk; i++){
		for(int j=0; j<4;j++){
			tempWord |= (unsigned int)(mKey[(i*4)+j]<<(j*8));
		}
		wordList.push_back(tempWord);
		// reset for the next 4 bytes
		tempWord = 0;
	}
	// expand key
	for(int i=4; i<(this->Nb*(this->Nr+1)); i++){
		tempWord = wordList.back();
		if(!(i%this->Nk)){
			this->rotateWord(tempWord);
			this->substituteWord(tempWord);
			tempWord ^= Rcon[i/4];
		}
		wordList.push_back(wordList.back() ^ tempWord);
	}
	return 0;
}

void AES::rotateWord(unsigned int& word){
	/* @Description:	get the first byte of the word, shift the byte to the back, delete the first byte from
	 *			the word, shift all bytes by 8 and add the masked byte to the word
	 *			back again */
	unsigned int mask = 0xFF000000, temp = 0;
	temp = word & mask;
	temp >>= 24;
	word &= 0x00FFFFFF;
	word <<= 8;
	word |= temp;
	
}

void AES::substituteWord(unsigned int& word){
	unsigned int mask = 0xFF;
	uint8_t byte = 0;
	for(int i=0; i<4; i++){
		byte = static_cast<uint8_t>((word&mask)>>(i*8));
		this->substituteByte(byte);
		word = ((~mask)&word)|| static_cast<unsigned int>(byte<<(8*i));
		mask <<= 8;
	}
}

// utility function
void AES::substituteByte(uint8_t& byte){
	/* @Description: substitute the passed byte with its sBlock equivalent
	 *	->alternatively to the upperByte shift by 4 to the left, one could define another
	 *	variable for the uppermask = 0xF0 and use that instead, but it would take up one more
	 *	byte of memory 
	 */
	uint8_t mask = 0x0F;
	byte = sBlock[int((byte&(mask<<4))>>4)][int(mask&byte)];
}



