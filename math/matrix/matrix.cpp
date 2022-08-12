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
	std::cout << "Size: " << this->mColumns <<"x"<<this->mRows<<"\n";
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
	this->mRows++;
}

template<class T>
void math::matrix<T>::addRow(math::vector<T> row){
	if(!row.getTranspose()){
		throw std::logic_error("Wrong vector format");
	}
	if(row.getDimension() != this->mColumns){
		throw std::length_error("Wrong row size, expected: "+std::to_string(this->mColumns)+", actual: "+std::to_string(row.getDimension())+"\n");
	}
	this->mValues.push_back(row.getValues());
	this->mRows++;
}

template<class T>
void math::matrix<T>::removeRow(uint32_t row){
	if(row > this->mRows){
		throw std::out_of_range("Passed row does not exist in the given matrix, max rows: "+std::to_string(this->mRows)+"\n");
	}
	this->mValues.erase(this->mValues.begin()+(row-1));
	this->mRows--;
}

template<class T>
void math::matrix<T>::addColumn(std::vector<T> column){
	if(column.size() != this->mRows){
		throw std::length_error("Wrong coulmn size, expected: "+std::to_string(this->mRows)+", actual: "+std::to_string(column.size())+"\n");
	}
	for(size_t i = 0; i<this->mValues.size(); i++){
		this->mValues[i].push_back(column[i]);
	}
	this->mColumns++;
}

template<class T>
void math::matrix<T>::addColumn(math::vector<T> column){
	if(column.getTranspose()){
		throw std::logic_error("Wrong vector format");
	}
	if(column.getDimension() != this->mRows){
		throw std::length_error("Wrong column size, expected: "+std::to_string(this->mRows)+", actual: "+std::to_string(column.getDimension())+"\n");
	}
	for(size_t i = 0; i<this->mValues.size(); i++){
		this->mValues[i].push_back(column.getValues().at(i));
	}
	this->mColumns++;
}

template<class T>
void math::matrix<T>::removeColumn(uint32_t column){
	if(column > this->mColumns){
		throw std::out_of_range("Passed column does not exist in the given matrix, max columns: "+std::to_string(this->mColumns)+"\n");
	}
	for(size_t i=0; i<this->mValues.size(); i++){
		this->mValues[i].erase(this->mValues[i].begin()+column-1);
	}
	this->mColumns--;
}

template<class T>
std::vector<T> math::matrix<T>::getColumn(uint32_t column){
	if(column > this->mColumns){
		throw std::out_of_range("Passed column does not exist in the given matrix, max columns: "+std::to_string(this->mColumns)+"\n");
	}
	std::vector<T> col;
	for(size_t i=0; i<this->mValues.size(); i++){
		col.push_back(this->mValues[i][column]);
	}
	return col;
}

template<class T>
std::vector<T> math::matrix<T>::getRow(uint32_t row){
	if(row > this->mRows){
		throw std::out_of_range("Passed row does not exist in the given matrix, max rows: "+std::to_string(this->mRows)+"\n");
	}
	return this->mValues[row];
}

