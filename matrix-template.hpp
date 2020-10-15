#include <iostream>
#include <vector>
#include <iomanip>

template<typename T> class Matrix{
    public:
        Matrix(const unsigned int rows, const unsigned int columns);
        Matrix(const unsigned int rows, const unsigned int columns, T initValue);
        T& at(const unsigned int row, const unsigned int column);
        int rows() const;
        int columns() const;
    private:
        std::vector< std::vector<T> > data;
};


template <typename T>void printMatrix(Matrix<T>& m);


template <typename T>Matrix<T>::Matrix(const unsigned int rows, const unsigned int columns){
    if ( (rows == 0) || (columns==0) ) { throw std::runtime_error("invalid matrix dimensions"); }
    data.resize(rows);
    for (int r=0; r<rows; r++){
        data.at(r).resize(columns);
    }
}

template <typename T>Matrix<T>::Matrix(const unsigned int rows, const unsigned int columns, T initValue){
    if ( (rows == 0) || (columns==0) ) { throw std::runtime_error("invalid matrix dimensions"); }
    data.resize(rows);
    for (int r=0; r<rows; r++){
        data.at(r).resize(columns, initValue);
    }
}

template <typename T>int Matrix<T>::rows() const { return data.size(); }

template <typename T>int Matrix<T>::columns() const { return data.at(0).size(); }

template <typename T>T& Matrix<T>::at(const unsigned int row, const unsigned int column){
    return data.at(row).at(column);
}

template <typename T>void printMatrix(Matrix<T>& m){
    for (int r=0; r<m.rows(); r++){
        for (int c=0; c<m.columns(); c++){
            std::cout << m.at(r,c) << ' ';
        }
        std::cout << std::endl;
    }
}

template <typename T>void prettyPrintMatrix(Matrix<T>& m){
    if(m.rows() > 0 && m.columns() > 0) {
        std::cout << '-' << std::setfill('-') << std::setw(5 * m.columns()) << "" << std::endl;
    }
    for (int r=0; r<m.rows(); r++){
        std::cout << '|';
        
        for (int c=0; c<m.columns(); c++){

            std::cout << std::setfill(' ') << std::setw(4) << std::right <<  m.at(r,c);
            std::cout << '|';
        
        }
        std::cout << std::endl;
        std::cout << '-' << std::setfill('-') << std::setw(5 * m.columns()) << "" << std::endl;
    }
}
