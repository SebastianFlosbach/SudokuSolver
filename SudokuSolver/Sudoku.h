#pragma once

#include <algorithm>
#include <string>

class Sudoku {
public:
	Sudoku() {
		numbers_ = new unsigned short[9*9];
	}

	Sudoku( const unsigned short* numbers ) {
		numbers_ = new unsigned short[9 * 9];
		std::copy( numbers, numbers + (9 * 9), numbers_ );
	}

	Sudoku( const Sudoku& other ) {
		*this = other;
	}

	Sudoku& operator=( const Sudoku& other ) {
		if( &other == this ) {
			return *this;
		}

		numbers_ = new unsigned short[9 * 9];
		std::copy( other.numbers_, other.numbers_ + (9 * 9), numbers_ );

		return *this;
	}

	~Sudoku() {
		delete[] numbers_;
	}

	inline short getNumber( unsigned int x, unsigned int y ) const {
		return numbers_[y * 9 + x];
	}

	inline bool setNumber( unsigned int x, unsigned int y, unsigned short number, bool check = true ) {
		if( check ) {
			for( unsigned short i = 0; i < 9; i++ ) {
				if( getNumber( i, y ) == number ) {
					return false;
				}
				if( getNumber( x, i ) == number ) {
					return false;
				}

				unsigned short a = (x / 3) * 3 + i % 3;
				unsigned short b = (y / 3) * 3 + i / 3;
				if( getNumber( a, b ) == number ) {
					return false;
				}
			}
		}

		numbers_[y * 9 + x] = number;

		return true;
	}

	std::string toString() const {
		std::string str = "";

		for( unsigned short y = 0; y < 9; y++ ) {
			for( unsigned short x = 0; x < 9; x++ ) {
				str += std::to_string( getNumber( x, y ) ) + " ";
				if( x != 0 && x != 8 && x % 3 == 2 ) {
					str += "| ";
				}
			}
			str += "\n";
			if( y != 0 && y != 8 && y % 3 == 2 ) {
				str += "----------------------\n";
			}
		}

		return str;
	}

private:
	unsigned short* numbers_;

};
