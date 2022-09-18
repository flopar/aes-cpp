#include<vector.hpp>

// think of ways to define templates -> the compiler needs it as this can be compiled after the
// main.cpp file, therefore in main an error will be thrown because the compiler cannot define the
// type before compiling this file :S (kinda hard to understand IMO)
// read this: ->https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
//            ->https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

// Define the class for the following data types
// Integers
template class math::vector<int8_t>;
template class math::vector<int16_t>;
template class math::vector<int32_t>;
template class math::vector<int64_t>;
template class math::vector<uint8_t>;
template class math::vector<uint16_t>;
template class math::vector<uint32_t>;
template class math::vector<uint64_t>;

// Floating point
// INFO: this does not work with every operator like XOR
//template class math::vector<double>;
//template class math::vector<float>;

/* --- Constructors --- */

template<class T>
math::vector<T>::vector(){
	this->mDimension = 0;
	this->mTranspose = false;
	this->mValues = {};
}


template<class T>
math::vector<T>::vector(const uint64_t dimension, const bool transpose){
	this->mDimension = dimension;
	this->mTranspose = transpose;
	this->mValues = std::vector<T>(dimension, 0);
}

template<class T>
math::vector<T>::vector(const std::vector<T> values, const bool transpose){
	this->mDimension = values.size();
	this->mTranspose = transpose;
	this->mValues = values;
}

/* --- Setters and Getters --- */

template<class T>
void math::vector<T>::setDimension(const uint64_t dimension){
	this->mDimension = dimension;
}

template<class T>
uint64_t math::vector<T>::getDimension() const{
	return this->mDimension;
}

template<class T>
void math::vector<T>::setTranspose(const bool transpose){
	this->mTranspose = transpose;
}

template<class T>
bool math::vector<T>::getTranspose() const{
	return this->mTranspose;
}

template<class T>
void math::vector<T>::setValues(const std::vector<T> values){
	if(this->mDimension != values.size()){
		throw std::length_error("Passed values don't match the size of the vector");
	}
	this->mValues = values;
}

template<class T>
std::vector<T> math::vector<T>::getValues() const{
	return this->mValues;
}
/* --- Validity check --- */
template<class T>
void math::vector<T>::checkValidity(const math::vector<T>& vec){
	if((this->mTranspose != vec.getTranspose()) || (this->mDimension != vec.getDimension())){
		throw std::invalid_argument("The first vector's form does not match the second vector's form!\n");
	}
}
/* --- Modifiers --- */
template<class T>
void math::vector<T>::push_back(T value){
	if(this->mDimension >= UINT64_MAX){
		throw std::out_of_range("Cannot add any more elements to the vector. Maximum supported length reached");
	}
	this->mValues.emplace_back(value);
	this->mDimension++;
}

/* --- Element access --- */
template<class T>
T& math::vector<T>::at(const size_t pos){
	std::cout << std::ref(this->mValues.at(pos));
	std::cout << "in at function";
	return this->mValues.at(pos);
}


/* --- Arithmetic --- */
template<class T>
math::vector<T> math::vector<T>::operator+(const math::vector<T>& vec){
	this->checkValidity(vec);
	math::vector<T> result(this->mDimension);
	std::vector<T> resVal = result.getValues();
	std::vector<T> vecVal = vec.getValues(); 
	std::cout << "vecVal : " << vecVal.size() <<" and diemnsions: "<< vec.getDimension()<<"\n";
	std::cout << "this size: " << this->mValues.size() << "and diemnsions: " << this->mDimension<<"\n";
	std::cout << "resVal : " << resVal.at(0)<<" and dimensions: " << result.getDimension()<<"\n";
	for(uint64_t index = 0; index < this->mDimension; index++){
		std::cout << "index : " << (unsigned int)index;
		std::cout << this->mValues.at(index) << std::endl << vecVal.at(index);
		resVal.at(index) = this->mValues.at(index) + vecVal.at(index);
	}
	result.setValues(resVal);
	return result;
}

template<class T>
uint64_t math::vector<T>::operator*(const math::vector<T>& vec){
	this->checkValidity(vec);
	uint32_t result = 0;
	std::vector<T> vecVal = vec.getValues();
	for(uint64_t index = 0; index < this->mDimension; index++){
		result += this->mValues.at(index)*vecVal.at(index);
		std::cout << result << std::endl;
	}
	return result;
}

template<class T>
void math::vector<T>::print(){
	std::string separator;
	if(!this->mTranspose){
		std::cout <<"Dimension: [1]x["<<this->mDimension<<"]\n";
		separator = "\n";
	}
	else{
		std::cout <<"Dimension: ["<<this->mDimension<<"]x[1]\n";
		separator = " ";
	}
	std::cout << "Vector:\t";
	for(uint64_t index = 0; index < mDimension; index++){
		std::cout << "[" << (unsigned int)this->mValues[index] << "]"+separator;
	}
	std::cout << std::endl;
	
}

template<class T>
math::vector<T> math::vector<T>::operator^(const math::vector<T>& vec){
	if(this->mTranspose != vec.getTranspose() || this->mDimension != vec.getDimension()){
		throw std::invalid_argument("vector::XOR-Operator(): operands do not match! Check dimension or transpose-flag.\n");
	}
	math::vector<T> ret(this->mDimension, this->mTranspose);
	std::vector<T> retVal = ret.getValues(), vecVal = vec.getValues();
	for(size_t i=0; i<this->mDimension; i++){
		retVal[i] = this->mValues[i]^vecVal[i];
	}
	ret.setValues(retVal);
	return ret;
}
/* IDK why is not working:w
template<class U>
std::ostream& math::operator<<(std::ostream& os, const math::vector<U>& vec){
	std::string separator;
	std::vector<U> values = vec.getValues();
	uint64_t dims = vec.getDimension();
	if(vec.getTranspose()){
		os<<"Dimension: [1]["<<dims<<"]\n";
		separator = " ";
	}
	else{
		os<<"Dimension: ["<<dims<<"][1]\n";
		separator = "\n";
	}
	for(uint64_t index = 0; index < dims; index++){
		os << "[" << values.at(index) << "]"+separator;
	}
	return os;
}
*/

