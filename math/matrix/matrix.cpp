#include<matrix.hpp>

template class math::matrix<int8_t>;
template class math::matrix<int16_t>;
template class math::matrix<int32_t>;
template class math::matrix<int64_t>;
template class math::matrix<uint8_t>;
template class math::matrix<uint16_t>;
template class math::matrix<uint32_t>;
template class math::matrix<uint64_t>;


template<class T>
math::matrix<T>::matrix(){
	this->mRows = 0;
	this->mColumns = 0;
	this->mValues = {};
}

template<class T>
math::matrix<T>::matrix(uint32_t rows, uint32_t columns){
	this->mRows = rows;
	this->mColumns = columns;
	for(unsigned int i = 0; i < rows; i++){
		this->mValues.push_back(std::vector<T>(rows, 0));
	}
}

template<class T>
uint32_t math::matrix<T>::getNumberOfRows(){
	return this->mRows;
}

template<class T>
uint32_t math::matrix<T>::getNumberOfColumns(){
	return this->mColumns;
}

template<class T>
void math::matrix<T>::print(){
	std::string separator="|";
	size_t rowSize=0;
	std::cout << "Size: " << this->mRows <<"x"<<this->mColumns<<"\n";
	for(size_t i = 0; i<this->mValues.size(); i++){
		rowSize = this->mValues[i].size();
		for(size_t j = 0; j<rowSize; j++){
			if(j == rowSize-1){
				separator = "";
			}
			std::cout << (unsigned int)this->mValues[i][j] << separator;
		}
		separator="|";
		std::cout << "\n";
	}
}

template<class T>
void math::matrix<T>::addRow(std::vector<T> row){
	if(row.size() != this->mColumns){
		throw std::length_error("Wrong row size, expected: "+std::to_string(this->mColumns)+", actual: "+std::to_string(row.size())+"\n");
	}
	this->mValues.push_back(row);
}
