#include <vector>
#include <vector.hpp>

namespace math{
template<class T>
class matrix
{
	private:
		uint32_t mRows;
		uint32_t mColumns;
		std::vector<std::vector<T>> mValues; 
	public:
		matrix();
		matrix(uint32_t rows, uint32_t columns);

		uint32_t getNumberOfRows();
		uint32_t getNumberOfColumns();

		void print();
		void addRow(std::vector<T> row);
		void addRow(math::vector<T> row);
		void addColumn(std::vector<T> column);
		void addColumn(math::vector<T> column);

};
}
