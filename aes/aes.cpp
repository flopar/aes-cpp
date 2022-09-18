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
	//until here works
	math::matrix<uint8_t> stateMatrix(this->createStateMatrix());
	for(uint8_t i=0; i<this->Nr; i++){
		this->addRoundKey(i, keyList, stateMatrix);
	}
	//stateMatrix.print();
	return "";
}

void AES::addRoundKey(const uint8_t round, const std::vector<unsigned int>& keyList, const math::matrix<uint8_t>& stateMatrix){
	// Key is a list of words, stateMatrix is a list of bytes
	// TODO: Combine them in a way
	int keyIndex = round*4;
	std::array<uint8_t, 4> keyBytes;
	for(int i=keyIndex; i<(keyIndex+4); i++){
			
	}
}

// work with words as it makes the substitution easier
void AES::expandKey(std::vector<unsigned int>& wordList){
	if(!this->mKeySize){
		throw std::length_error("Wrong key size!");
	}	

	/* @Description: for each 4 bytes create one word and add it to the list, they words will be
	 *		 arranged column wise. Therefore words will also be column wise as well.
	 *		 This is due to the addRoundKey-Function used later by the
	 *		 encryption/decryption algorithms.
	 * key layout: 
	 *
	 *
	 *		 |-----|-----|-----|-----|
	 *		 | K00 | K04 | K08 | K12 |
	 *		 |-----|-----|-----|-----|
	 *		 | K01 | K05 | K09 | K13 |  , where KXX -> K = short for Key-Byte
	 *		 |-----|-----|-----|-----|              -> XX = Byte number (position in the
	 *		 | K02 | K06 | K10 | K14 |                      passed key)
	 *		 |-----|-----|-----|-----|
	 *		 | K03 | K07 | K11 | K15 |
	 *		 |-----|-----|-----|-----|
	 *
	 *
	 */
	std::array<uint8_t, 4> arr;

	for(size_t i=0; i<this->Nk; i++){
		// no need to reset the array as it will be overwritten
		for(int j=0; j<4;j++){
			arr[j] = this->mKey[(i*4)+(3-j)];
		}
		wordList.push_back(bytesToWord(arr));
	}	
	uint32_t tempWord=0;
	// expand key
	for(int i=this->Nk; i<(this->Nb*(this->Nr+1)); i++){
		tempWord = wordList.back();
		if(!(i%this->Nk)){
			//check if these work and move on
			this->rotateWord(tempWord);
			this->substituteWord(tempWord);
			// until here works
			tempWord ^= Rcon[i/4];
		}
		wordList.push_back(*(&(wordList.back())-3) ^ tempWord);
	}
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
	std::array<uint8_t, 4> arr = wordToByteArray(word);
	for(uint8_t i=0; i<4; i++){
		this->substituteByte(arr[i]);
	}
	word = bytesToWord(arr);
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

// Works
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
	return stateMatrix;
}





