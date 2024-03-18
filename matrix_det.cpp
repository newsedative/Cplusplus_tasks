#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <time.h>
using namespace std;

// ввод матрицы с клавиатуры
void userInput(vector <vector <long double>>& mas, int size);
// заполнение генератором вещественных чисел
void randomInput(vector <vector <long double>>& mas, int size);
// заполнение натуральным рядом чисел по строкам
void naturalInput(vector <vector <long double>>& mas, int size);
// вывод матрицы
void printMatrix(vector <vector <long double>>& mas, int size);
// вчисление определителя по столбцу
long double det_rec(vector <vector <long double>> mas, int size, int col);
// преобразование исходной матрицы в треугольную
float triangularMatrix(vector <vector <long double>>& mas,int size);


int main() {
  const int max_size = 10;
  int N;
  clock_t start, finish;

  cout << "Введите размер массива: ";
  while (!(cin >> N)) {
    cout << "Неверный формат. Введите число: ";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  if (N > max_size) {
    N = max_size;
  }

  vector <vector <long double>> matrix(N, vector<long double>(N));

  cout << "\nВыберите вариант ввода матрицы: вручную (1), генератором случайных вещественных чисел (2), натуральным рядом чисел (3): ";
  int var_of_gener;
  while (!(cin >> var_of_gener)) {
    cout << "\nНеверный формат. Введите число: ";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  if (var_of_gener == 1) {
    userInput(matrix, N);
  } else if (var_of_gener == 2) {
    randomInput(matrix, N);
  } else if (var_of_gener == 3) {
    naturalInput(matrix, N);
  }

  printMatrix(matrix, N);

  cout << "\nВведите номер столбца для разложения: ";
  int column;
  while (!(cin >> column)) {
    cout << "\nНеверный формат. Введите число: ";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  start = clock();
  cout << "\nОпределитель матрицы: " << det_rec(matrix, N, column) << endl;
  finish = clock();
  cout << "\nВремя выполнения: " << (double)(finish - start) / 1000 << endl;
  cout << "" << endl;
  cout << "----------------------------------------" << endl;
  cout << "\nТреугольная матрица" << endl;
  start = clock();
  cout << "\nОпределитель матрицы: " << triangularMatrix(matrix, N) << endl;
  finish = clock();
  cout << "\nВремя выполнения: " << (double)(finish - start) / 1000 << endl;
  printMatrix(matrix, N);

  return 0;
}

void userInput(vector <vector <long double>>& mas, int size) {
  cout << "\nВведите " << size << " стpок по " << size << " чисел:\n";
  int Elem = 0;
  char Ch;
  while (Elem < size) {
    cout << Elem + 1 << ": ";
    int Row = 0;
    while (Row < size) {
      cin >> mas[Row][Elem];
      Row++;
    }
    do
      cin.get(Ch);
    while (Ch != '\n'); 
    Elem = Elem + 1;    
  }
  cout << endl;
}

void randomInput(vector <vector <long double>>& mas, int size) {
  srand( time(0) );
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      mas[i][j] = rand() % 100;
    }
  }
}

void naturalInput(vector <vector <long double>>& mas, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      mas[i][j] = i * size + j + 1;
    }
  }
}

void printMatrix(vector <vector <long double>>& mas, int size) {
  cout << "\nВывод матрицы:\n";
  int Elem;
  char Ch;
  for (Elem = 1; Elem <= size; Elem++)
    cout << setw(9) << Elem;
  cout << endl;
  int Row = 0;
  do {
    cout << Row + 1 << ":";
    Elem = 0;
    do {
      cout << setw(9) << mas[Row][Elem];
      Elem++;
    } while (Elem < size);
    cout << endl;
    Row++;
  } while (Row < size);
  cin.get(Ch);
}

long double det_rec(vector <vector <long double>> mas, int size, int col) {
  if (size == 1)
    return mas[0][0];
  long double det = 0;
  int k = 1;
  long double m;
  vector <vector <long double>> matrix_temp(size - 1, vector<long double>(size - 1));

  for (int a = 0; a < size; ++a) { 
    for (int i = 1; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (j < a) {
          matrix_temp[i - 1][j] = mas[i][j];
        }
        else {
          if (j > a)
            matrix_temp[i - 1][j - 1] = mas[i][j]; 
        }
      }
    }

    m = mas[0][a] * k * det_rec(matrix_temp, size - 1, col);
    k = -k;
    det += m;  
  }
  return det;
}



float triangularMatrix(vector <vector <long double>>& mas,int size) {
  int	chet=0;
  int n=size;
  long double tmp, det2;
  bool Isnule=false;
  for (int k = 0; (k < size - 1)&& !Isnule; k++) {
        for (int i = k + 1; (i < size)&& !Isnule; i++) {
          if (mas[k][k]==0)
          {
            chet++;
            double max=mas[k][k+1]; 
        int stj=k+1;
            for(int l=k+2;l<size;l++)
            {
              if(abs(mas[k][l])>max)  
               {
             max=mas[k][l];
               stj=l;}
               else
               continue;
              }
        if (abs(max)<1e-8)
          {
          Isnule=true;// обработка нулей
          }
              else
              for (int sw=0;sw<size;sw++)
        swap(mas[sw][k], mas[sw][stj]);
          }
          if (!Isnule) {
        tmp = -mas[i][k] / mas[k][k];
              for (int j = 0; j < size; j++) {
                    mas[i][j] += mas[k][j] * tmp;
                }

            }

        }
    }
    if (Isnule==true)
   {
   return 0;}
    else
    det2 = 1;
    for (int i = 0; i < n; i++) {
        det2 *= mas[i][i];
    }

    return pow(-1,chet)*det2;
}
