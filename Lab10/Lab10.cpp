
#include <iostream>
#include <iomanip>
using namespace std;


void displayMatrix(int matrix[][9], int N) {
	cout << "\n\n----Displaying Matrix----\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double k = matrix[i][j] / 10;
			if (k < 10 || k>0) {
				cout << matrix[i][j] << "  ";
			}
			else if (k < 0) {
				cout << matrix[i][j] << " ";
			}
			else {
				cout << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
}

bool isSudoku(int arr[9][9]) {

	for (int i = 0; i < 9; i++) {
		bool digits[9] = { false };
		for (int j = 0; j < 9; j++) {
			int num = arr[i][j];
			if (num < 1 || num > 9) {
				return false;
			}
			if (digits[num - 1] == true) {
				return false;
			}
			digits[num - 1] = true;
		}
	}

	for (int i = 0; i < 9; i++) {
		bool digits[9] = { false };
		for (int j = 0; j < 9; j++) {
			int num = arr[j][i];
			if (num < 1 || num > 9) {
				return false;
			}
			if (digits[num - 1] == true) {
				return false;
			}
			digits[num - 1] = true;
		}
	}

	for (int rows = 0; rows < 9; rows = rows + 3) {
		for (int cols = 0; cols < 9; cols = cols + 3) {
			bool digits[9] = { false };

			for (int i = rows; i < (rows + 3); i++) {
				for (int j = cols; j < (cols + 3); j++) {
					int num = arr[i][j];
					if (num < 1 || num > 9) {
						return false;
					}
					if (digits[num - 1] == true) {
						return false;
					}
					digits[num - 1] == true;
				}
			}
		}
	}
	return true;
}

void inputMatrix(int matrix[][5], int N) {
	cout << "\n\n-----Input Matrix-----\n";
	cout << "\nPlease enter what you'd like to insert at\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "Row (" << i << ") Col (" << j << ") : ";
			cin >> matrix[i][j];
		}
	}
}

void displayMatrix(int matrix[][5], int N) {
	cout << "\n\n----Displaying Matrix----\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void rotateClockwise(int matrix[][5], int N)
{
	int temp[5][5];
	cout << "\n\n----Rotating Clockwise----";
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			temp[r][c] = matrix[N - c - 1][r];
		}
	}
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			matrix[r][c] = temp[r][c];
		}
	}
}

void inputcharMatrix(char matrix[][5], int N) {
	cout << "\n\n-----Input Matrix-----\n";
	cout << "\nPlease enter what you'd like to insert at\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "Row (" << i << ") Col (" << j << ") : ";
			cin >> matrix[i][j];
		}
	}
}

void replaceVowels(char matrix[][5], int N) {
	cout << "\n\n----Replacing Vowels----";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matrix[i][j] == 'A' || matrix[i][j] == 'E' || matrix[i][j] == 'I' || matrix[i][j] == 'O' || matrix[i][j] == 'U' || matrix[i][j] == 'a' || matrix[i][j] == 'e' || matrix[i][j] == 'i' || matrix[i][j] == 'o' || matrix[i][j] == 'u')
				matrix[i][j] = '?';
		}
	}
}
void rotateClockwise(char matrix[][5], int N)
{
	char temp[5][5];
	cout << "\n\n----Rotating Clockwise----";
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			temp[r][c] = matrix[N - c - 1][r];
		}
	}
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			matrix[r][c] = temp[r][c];
		}
	}
}

void displayMatrix(char matrix[][5], int N) {
	cout << "\n\n----Displaying Matrix----\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void rotate(int matrix[][5], int N) {
	int temp[5][5];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[i][j] = matrix[i][j];
		}
	}

	cout << "\n----Rotating boundary----\n";
	temp[0][0] = matrix[0][1];
	temp[0][4] = matrix[1][4];
	temp[4][0] = matrix[3][0];
	temp[4][4] = matrix[4][3];

	for (int i = 1; i < 4; i++) {
		temp[0][i] = matrix[0][i + 1];
		temp[4][i] = matrix[4][i - 1];
		temp[i][0] = matrix[i - 1][0];
		temp[i][4] = matrix[i + 1][4];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = temp[i][j];
		}
	}
}

int main() {

	int matrix[5][5] = { 0 };
	char matrixchar[5][5] = { 0 };
	int sudokuMatrix[9][9] = {
		{ 5,3,4,6,7,8,9,1,2 },
		{ 6,7,2,1,9,5,3,4,8 },
		{ 1,9,8,3,4,2,5,6,7 },
		{ 8,5,9,7,6,1,4,2,3 },
		{ 4,2,6,8,5,3,7,9,1 },
		{ 7,1,3,9,2,4,8,5,6 },
		{ 9,6,1,5,3,7,2,8,4 },
		{ 2,8,7,4,1,9,6,3,5 },
		{ 3,4,5,2,8,6,1,7,5 }
	};
	cout << "Please enter N: ";
	int N;
	cin >> N;
	/*-----Q1-------
	inputMatrix(matrix, N);
	displayMatrix(matrix, N);
	rotateClockwise(matrix, N);
	displayMatrix(matrix, N);*/

	//-----Q2-------
	//inputcharMatrix(matrixchar, N);
	//displayMatrix(matrixchar, N);
	//replaceVowels(matrixchar, N);
	//displayMatrix(matrixchar, N);
	//rotateClockwise(matrixchar, N);
	//displayMatrix(matrixchar, N);

	//-----Q3------
	//inputMatrix(matrix, N);
	//displayMatrix(matrix, N);
	//rotate(matrix, N);
	//displayMatrix(matrix, N);
	//

	//-----Q4------

	/*displayMatrix(sudokuMatrix, N);
	if (isSudoku(sudokuMatrix) == 1) {
		cout << "\nIt is a Sudoku Matrix!\n";
	}
	else {
		cout << "\nIt is not a Soduku Matrix!\n";
	}
*/




	return 0;
}