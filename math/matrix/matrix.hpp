#include <vector>
#include <vector.hpp>

namespace math{
template<class T>
class matrix
{
	private:
		uint32_t mRows;
		uint32_t mColumns;
		bool mTranspose;
		std::vector<std::vector<T>> mValues;
	public:
		matrix();
		matrix(const uint32_t rows, const uint32_t columns, bool transpose = false);
		matrix(const std::vector<std::vector<T>> matrix, bool transpose = false);

		uint32_t getNumberOfRows() const;
		uint32_t getNumberOfColumns() const;
	
		
		std::vector<T> getRow(const uint32_t row) const;
		std::vector<T> getColumn(const uint32_t column) const;
		std::vector<std::vector<T>> getValues() const;
		void setValues(std::vector<std::vector<T>> value);
		bool getTranspose() const;
		math::vector<T> getMathRow(const uint32_t row) const;
		math::vector<T> getMathColumn(const uint32_t column) const;
		
		void addRow(const std::vector<T> row);
		void addRow(const math::vector<T> row);
		void replaceRow(const std::vector<T> row, const uint32_t index);
		void replaceRow(const math::vector<T> row, const uint32_t index);
		void removeRow(const uint32_t row);
		void addColumn(const std::vector<T> column);
		void addColumn(const math::vector<T> column);
		void replaceColumn(const std::vector<T> column, const uint32_t index);
		void replaceColumn(const math::vector<T> column, const uint32_t index);
		void removeColumn(const uint32_t column);
		void print();
		
		math::matrix<T> operator^ (math::matrix<T> matrix);
};
}
