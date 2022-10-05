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
	this->mTranspose = false;
}

template<class T>
math::matrix<T>::matrix(const uint32_t rows, const uint32_t columns, bool transpose){
	this->mRows = rows-1;
	this->mColumns = columns-1;
	for(unsigned int i = 0; i < rows; i++){
		this->mValues.push_back(std::vector<T>(columns, 0));
	}
	this->mTranspose = transpose;
}

template<class T>
math::matrix<T>::matrix(const std::vector<std::vector<T>> matrix, bool transpose){
	if(matrix.size() < 1){
		throw std::logic_error("matrix(): Uninitialized matrix passed to the constructor");
	}
	if(matrix.size() == 1){
		throw std::logic_error("matrix(): Matrix rows size is one. Create a vector instead");
	}
	//Check matrix content
	size_t sizeCheck;
	this->mRows = matrix.size()-1;
	for(size_t i = 0; i < matrix.size(); i++){
		if(!i){
			sizeCheck = matrix[0].size();
			this->mColumns = sizeCheck-1;
			if(sizeCheck < 1){
				throw std::logic_error("matrix(): Uninitalized row in the matrix");
			}
			// if this is one, this is not a matrix anymore, it is a vector
			if(sizeCheck == 1){
				throw std::logic_error("matrix(): matrix's row/column size cannot be one");
			}
		}
		else{
			if(matrix[i].size() != sizeCheck){
				throw std::length_error("matrix(): matrix has rows of different size");
			}
		}

	}
	this->mValues = matrix;
	this->mTranspose = transpose;
}

template<class T>
uint32_t math::matrix<T>::getRowsSize() const{
	return this->mRows+1;
}

template<class T>
uint32_t math::matrix<T>::getColumnsSize() const{
	return this->mColumns+1;
}

template<class T>
void math::matrix<T>::print() const{
	std::string separator="|";
	T value;
	size_t rowSize=0;
	std::cout << "Size: " << this->getColumnsSize() <<"x"<<this->getRowsSize()<<"\n";
	for(size_t i = 0; i<this->mValues.size(); i++){
		rowSize = this->mValues[i].size();
		for(size_t j = 0; j<rowSize; j++){
			if(j == rowSize-1){
				separator = "";
			}
			std::cout << std::hex << (unsigned int)this->mValues[i][j] << separator;
		}
		separator="|";
		std::cout << "\n";
	}
}

template<class T>
void math::matrix<T>::addRow(const std::vector<T> row){
	if(row.size() != this->getColumnsSize()){
		throw std::length_error("addRow(): Wrong row size, expected: "+std::to_string(this->getColumnsSize())+", actual: "+std::to_string(row.size())+"\n");
	}
	this->mValues.push_back(row);
	this->mRows++;
}

template<class T>
void math::matrix<T>::addRow(const math::vector<T> row){
	if(!row.getTranspose()){
		throw std::logic_error("addRow(): Wrong vector format");
	}
	if(row.getDimension() != this->getColumnsSize()){
		throw std::length_error("addRow(): Wrong row size, expected: "+std::to_string(this->getColumnsSize())+", actual: "+std::to_string(row.getDimension())+"\n");
	}
	this->mValues.push_back(row.getValues());
	this->mRows++;
}

template<class T>
void math::matrix<T>::replaceRow(const std::vector<T> row, const uint32_t index){
	if(index > this->mRows){
		throw std::out_of_range("replaceRow(): position is out of range");
	}
	if(row.size() != this->getColumnsSize()){
		throw std::length_error("replaceRow(): Wrong row size, expected: "+std::to_string(this->getColumnsSize())+", actual: "+std::to_string(row.size())+"\n");
	}
	this->mValues[index] = row;
}

template<class T>
void math::matrix<T>::replaceRow(const math::vector<T> row, const uint32_t index){
	if(!row.getTranspose()){
		throw std::invalid_argument("replaceRow(): wrong vector format, untransposed vector expected");
	}
	this->replaceRow(row.getValues(), index);
}

template<class T>
void math::matrix<T>::removeRow(const uint32_t row){
	if(row > this->mRows){
		throw std::out_of_range("removeRow(): Passed row does not exist in the given matrix, max rows: "+std::to_string(this->getRowsSize())+"\n");
	}
	this->mValues.erase(this->mValues.begin()+(row-1));
	this->mRows--;
}

template<class T>
void math::matrix<T>::addColumn(const std::vector<T> column){
	if(column.size() != this->getRowsSize()){
		throw std::length_error("addColumn(): Wrong coulmn size, expected: "+std::to_string(this->getRowsSize())+", actual: "+std::to_string(column.size())+"\n");
	}
	for(size_t i = 0; i<this->mValues.size(); i++){
		this->mValues[i].push_back(column[i]);
	}
	this->mColumns++;
}

template<class T>
void math::matrix<T>::addColumn(const math::vector<T> column){
	if(!column.getTranspose()){
		throw std::logic_error("addColumn(): Wrong vector format");
	}
	if(column.getDimension() != this->getRowsSize()){
		throw std::length_error("addColumn(): Wrong column size, expected: "+std::to_string(this->getRowsSize())+", actual: "+std::to_string(column.getDimension())+"\n");
	}
	for(size_t i = 0; i<this->mValues.size(); i++){
		this->mValues[i].push_back(column.getValues().at(i));
	}
	this->mColumns++;
}

template<class T>
void math::matrix<T>::replaceColumn(const std::vector<T> column, uint32_t index){
	if(index > this->mColumns){
		throw std::out_of_range("replaceColumn(): position is out of range! index: " + std::to_string(index) + "\n");
	}
	if(column.size() != this->getRowsSize()){
		throw std::length_error("replaceColumn(); Wrong column size, expected: "+std::to_string(this->getRowsSize())+", actual: "+std::to_string(column.size())+"\n");
	}
	for(uint32_t i=0; i<this->getRowsSize(); i++){
		this->mValues[i][index] = column[i];
	}
}

template<class T>
void math::matrix<T>::replaceColumn(const math::vector<T> column, uint32_t index){
	if(column.getTranspose()){
		throw std::logic_error("replaceColumn(): Wrong vector format!");
	}
	this->replaceColumn(column.getValues(), index);
}

template<class T>
void math::matrix<T>::removeColumn(const uint32_t column){
	if(column > this->mColumns){
		throw std::out_of_range("removeColumn(): Passed column does not exist in the given matrix, max columns: "+std::to_string(this->mColumns)+"\n");
	}
	for(size_t i=0; i<this->mValues.size(); i++){
		this->mValues[i].erase(this->mValues[i].begin()+column-1);
	}
	this->mColumns--;
}

template<class T>
std::vector<T> math::matrix<T>::getColumn(const uint32_t column) const{
	if(column > this->mColumns){
		throw std::out_of_range("getColumn(): Passed column does not exist in the given matrix, max columns: "+std::to_string(this->mColumns)+"\n");
	}
	std::vector<T> col;
	for(size_t i=0; i<this->mValues.size(); i++){
		col.push_back(this->mValues[i][column]);
	}
	return col;
}

template<class T>
std::vector<T> math::matrix<T>::getRow(const uint32_t row) const{
	if(row > this->mRows){
		throw std::out_of_range("getRow(): Passed row does not exist in the given matrix, max rows: "+std::to_string(this->mRows)+"\n");
	}
	return this->mValues[row];
}

template<class T>
math::vector<T> math::matrix<T>::getMathColumn(const uint32_t column) const{
	return math::vector<T>(this->getColumn(column));
}

template<class T>
math::vector<T> math::matrix<T>::getMathRow(const uint32_t row) const{
	return math::vector<T>(this->getRow(row), true);
}

template<class T>
bool math::matrix<T>::getTranspose() const{
	return this->mTranspose;
}

template<class T>
std::vector<std::vector<T>> math::matrix<T>::getValues() const{
	return this->mValues;
}

template<class T>
void math::matrix<T>::setValues(const std::vector<std::vector<T>> values){
	this->mValues = values;
	this->mColumns = values[0].size()-1;
	for(uint32_t i=0; i<values.size(); i++){
		if(values[i].size() != this->getColumnsSize()){
			throw std::length_error("setValues(): cannot set values. Rows have different size.\n");
		}
		else{
			this->mValues[i]=values[i];
		}
	}
}

template<class T>
math::matrix<T> math::matrix<T>::operator^(const math::matrix<T> matrix){
	if(this->getColumnsSize() != matrix.getColumnsSize() || this->getRowsSize() != matrix.getRowsSize()){
		throw std::invalid_argument("XOR Operation: the sizes of the operands do no match!");
	}
	math::matrix<T> ret(this->getRowsSize(), this->getColumnsSize());
	std::vector<std::vector<T>> val = ret.getValues(), matrixVal = matrix.getValues();
	for(uint32_t i=0; i<this->getRowsSize(); i++){
		for(uint32_t j=0; j<this->getColumnsSize(); j++){
			val[i][j] = this->mValues[i][j]^matrixVal[i][j];
		}
	}
	ret.setValues(val);
	return ret;
}
