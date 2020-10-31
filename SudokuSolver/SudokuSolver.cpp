#include <chrono>
#include <fstream>
#include <iostream>

#include "Sudoku.h"

bool trySolve( Sudoku& sudoku );
int tries = 0;

constexpr char* usageDescription = 
"\
Usage:\n\
 /SudokuSolver [Path_to_Sudoku]\
";

int main(int argc, char* argv[] )
{
	if( argc != 2 ) {
		std::cout << usageDescription << std::endl;
		return 0;
	}

	std::ifstream fileStream;
	try {
		fileStream.open(argv[1]);
	} catch( const std::exception& ) {
		std::cout << "Could not open file: " << argv[1] << std::endl;
		return -1;
	}

	bool fileOpen = fileStream.is_open();

	Sudoku sudoku = Sudoku();

	int lineCounter = 0;
	std::string line;
	while( std::getline( fileStream, line ) ) {
		if( line.length() != 9 ) {
			std::cout << "Invalid sudoku file! Line " << std::to_string( lineCounter ) << std::endl;
			return -1;
		}

		for( int i = 0; i < 9; i++ ) {
			// Ascii to int
			short number = line[i] - 0x30;
			if( number < 0 || number > 9 ) {
				std::cout << "Invalid sudoku file! Symbol '" << line[i] << "' at line " << std::to_string( lineCounter ) << ", position " << std::to_string( i ) << " is not a number!" << std::endl;
				return -1;
			}

			sudoku.setNumber( i, lineCounter, number, false );
		}

		lineCounter++;

		if( lineCounter > 9 ) {
			std::cout << "Invalid sudoku file! Too many lines!" << std::endl;
			-1;
		}
	}

	if( lineCounter < 9 ) {
		std::cout << "Invalid sudoku file! Too few lines!" << std::endl;
		return -1;
	}

	fileStream.close();

	std::cout << sudoku.toString() << std::endl;
	
	auto start = std::chrono::high_resolution_clock::now();
	bool success = trySolve( sudoku );
	auto end = std::chrono::high_resolution_clock::now();

	if( success ) {
		std::cout << sudoku.toString() << std::endl;
		std::cout << std::endl;
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
		std::cout << "Tries: " << std::to_string( tries ) << std::endl;
	} else {
		std::cout << "Could not find a solution after " << std::to_string( tries ) << " tries!";
	}

	return 0;
}

bool trySolve( Sudoku& sudoku ) {
	Sudoku copy = sudoku;

	for( unsigned short y = 0; y < 9; y++ ) {
		for( unsigned short x = 0; x < 9; x++ ) {
			if( copy.getNumber( x, y ) == 0 ) {
				for( unsigned short i = 1; i <= 9; i++ ) {
					tries++;
					if( copy.setNumber( x, y, i ) ) {
						if( trySolve( copy ) ) {
							sudoku = copy;
							return true;
						}
					}
				}
				return false;
			}
		}
	}

	return true;
}
