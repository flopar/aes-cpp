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
	if(this->Nk == 4){
		this->Nr = 10;
	}
	else if(this->Nk == 6){
		this->Nr = 12;
	}
	else if(this->Nk == 8){
		this->Nr = 14;
	}
	else{
		throw std::runtime_error("Only fixed size keys are supported for now...");
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
	std::vector<unsigned int> keyList;
	this->expandKey(keyList);
	std::vector<std::vector<uint8_t>> stateMatrix = this->createStateMatrix();
	this->addRoundKey(0, keyList, stateMatrix);
	return "";
}


// maybe keep it at bytes instead of words
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

std::vector<std::vector<uint8_t>> AES::createStateMatrix(){
	/* @Description: this function will take the passed message and create a a 4x4 state matrix
	 *		 as described in the aes-standard. The matrix has the following layout:
	 *		 
	 *		 |-----|-----|-----|-----|
	 *		 | B00 | B04 | B8  | B12 |
	 *		 |-----|-----|-----|-----|
	 *		 | B01 | B05 | B9  | B13 |  , where BXX -> B  = short for Byte
	 *		 |-----|-----|-----|-----|              -> XX = Byte number (position in the
	 *		 | B02 | B06 | B10 | B14 |                      passed message)
	 *		 |-----|-----|-----|-----|
	 *		 | B03 | B07 | B11 | B15 |
	 *		 |-----|-----|-----|-----|		 
	 */
	std::vector<std::vector<uint8_t>> stateMatrix;
	std::vector<uint8_t> column;
	for(int i=0; i<4; i++){
		for(int j=0; j<Nb; j++){
			column.emplace_back(std::move(this->mMessage[(j*4)+i]));
		}
		stateMatrix.emplace_back(std::move(column));
	}
	/*for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			std::cout << (char)stateMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	return stateMatrix;
}

void AES::addRoundKey(uint8_t round, std::vector<unsigned int>& keyList, std::vector<std::vector<uint8_t>>& stateMatrix){
	// Key is a list of words, stateMatrix is a list of bytes
	// TODO: Combine them in a way
	for(int i=round*4; i<4; i++){

						
	}
}

// Utility

// For this function we should use std::array instead of the normal C-Pointers
// therefore we rule out possible stack overflows where someone tries to increase
// the adress of the iterator and access unauthorized memory
std::array<uint8_t, 4> AES::wordToBytes(uint32_t word){
	std::array<uint8_t, 4> bytes;
	for(int i=0; i<4; i++){
		bytes[i] = static_cast<uint8_t>(word&0xFF);
		word >>=8;
	}
	return bytes;
}
uint32_t AES::bytesToWord(std::array<uint8_t, 4> bytes){
	uint32_t word = 0;
	for(int i=3; i>=0; i--){
		word |= (bytes[i]<<8*i);
	}
	return word;
}

