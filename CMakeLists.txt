cmake_minimum_required (VERSION 3.8)

project ("SudokuSolver")

add_executable (SudokuSolver "SudokuSolver/SudokuSolver.cpp"  "SudokuSolver/Sudoku.h")

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "bin"
)
