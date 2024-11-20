#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

enum Specialization { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_EDUCATION };
string specializationStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
    int number;               // Порядковий номер студента
    string surname;           // Прізвище студента
    int course;               // Курс
    Specialization spec;      // Спеціальність
    int physics;              // Оцінка з фізики
    int mathematics;          // Оцінка з математики
    union {                   // Об’єднання для третьої оцінки
        int programming;      // Оцінка з програмування
        int numerical_methods; // Оцінка з чисельних методів
        int pedagogy;         // Оцінка з педагогіки
    };
};

// Прототипи функцій
void InputStudents(Student* students, int N);
void PrintStudents(const Student* students, int N);
int GetProfileGrade(const Student& student);
double CalculateAverageGrade(const Student& student);
void PhysicalSort(Student* students, int N);
void IndexSort(const Student* students, int N, int* indexArray);
int BinarySearch(const Student* students, const int* indexArray, int N, const string& surname, int profileGrade, double avgGrade);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];
    int* indexArray = new int[N];

    int menuItem;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Введення даних студентів\n";
        cout << "2 - Вивід даних студентів\n";
        cout << "3 - Фізичне сортування студентів\n";
        cout << "4 - Індексне сортування студентів\n";
        cout << "5 - Пошук студента\n";
        cout << "0 - Вихід\n";
        cout << "Виберіть дію: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            InputStudents(students, N);
            break;
        case 2:
            PrintStudents(students, N);
            break;
        case 3:
            PhysicalSort(students, N);
            cout << "Список студентів фізично відсортовано.\n";
            break;
        case 4:
            IndexSort(students, N, indexArray);
            cout << "Список студентів індексно відсортовано.\n";
            break;
        case 5: {
            string surname;
            int profileGrade;
            double avgGrade;
            cout << "Введіть прізвище для пошуку: ";
            cin >> surname;
            cout << "Введіть оцінку з профільного предмету для пошуку: ";
            cin >> profileGrade;
            cout << "Введіть середній бал для пошуку: ";
            cin >> avgGrade;

            int result = BinarySearch(students, indexArray, N, surname, profileGrade, avgGrade);
            if (result != -1)
                cout << "Студент знайдений за індексом: " << result << "\n";
            else
                cout << "Студент не знайдений.\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    delete[] indexArray;
    return 0;
}

void InputStudents(Student* students, int N) {
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":\n";
        students[i].number = i + 1;
        cin.ignore();
        cout << " Прізвище: ";
        getline(cin, students[i].surname);
        cout << " Курс: ";
        cin >> students[i].course;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        int spec;
        cin >> spec;
        students[i].spec = static_cast<Specialization>(spec);
        cout << " Оцінка з фізики: ";
        cin >> students[i].physics;
        cout << " Оцінка з математики: ";
        cin >> students[i].mathematics;

        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << " Оцінка з програмування: ";
            cin >> students[i].programming;
        }
        else if (students[i].spec == INFORMATICS) {
            cout << " Оцінка з чисельних методів: ";
            cin >> students[i].numerical_methods;
        }
        else {
            cout << " Оцінка з педагогіки: ";
            cin >> students[i].pedagogy;
        }
    }
}

void PrintStudents(const Student* students, int N) {
    cout << "=================================================================================================================================\n";
    cout << "| № | Прізвище           | Курс | Спеціальність           | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << students[i].number
            << " | " << setw(18) << left << students[i].surname
            << " | " << setw(4) << students[i].course
            << " | " << setw(21) << specializationStr[students[i].spec]
            << " | " << setw(6) << students[i].physics
            << " | " << setw(10) << students[i].mathematics;

        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << " | " << setw(14) << students[i].programming << " | " << setw(15) << "N/A" << " | " << setw(9) << "N/A";
        }
        else if (students[i].spec == INFORMATICS) {
            cout << " | " << setw(14) << "N/A" << " | " << setw(15) << students[i].numerical_methods << " | " << setw(9) << "N/A";
        }
        else {
            cout << " | " << setw(14) << "N/A" << " | " << setw(15) << "N/A" << " | " << setw(9) << students[i].pedagogy;
        }
        cout << " |\n";
    }
    cout << "=================================================================================================================================\n";
}

int GetProfileGrade(const Student& student) {
    if (student.spec == COMPUTER_SCIENCE)
        return student.programming;
    else if (student.spec == INFORMATICS)
        return student.numerical_methods;
    else
        return student.pedagogy;
}

double CalculateAverageGrade(const Student& student) {
    return (student.physics + student.mathematics + GetProfileGrade(student)) / 3.0;
}

void PhysicalSort(Student* students, int N) {
    sort(students, students + N, [](const Student& a, const Student& b) {
        int profileA = GetProfileGrade(a);
        int profileB = GetProfileGrade(b);
        if (profileA != profileB)
            return profileA > profileB;
        double avgA = CalculateAverageGrade(a);
        double avgB = CalculateAverageGrade(b);
        if (avgA != avgB)
            return avgA > avgB;
        return a.surname < b.surname;
        });
}

void IndexSort(const Student* students, int N, int* indexArray) {
    for (int i = 0; i < N; i++) {
        indexArray[i] = i;
    }
    sort(indexArray, indexArray + N, [&](int a, int b) {
        int profileA = GetProfileGrade(students[a]);
        int profileB = GetProfileGrade(students[b]);
        if (profileA != profileB)
            return profileA > profileB;
        double avgA = CalculateAverageGrade(students[a]);
        double avgB = CalculateAverageGrade(students[b]);
        if (avgA != avgB)
            return avgA > avgB;
        return students[a].surname < students[b].surname;
        });
}

int BinarySearch(const Student* students, const int* indexArray, int N, const string& surname, int profileGrade, double avgGrade) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        const Student& student = students[indexArray[mid]];
        int midProfileGrade = GetProfileGrade(student);
        double midAvgGrade = CalculateAverageGrade(student);

        if (student.surname == surname && midProfileGrade == profileGrade && abs(midAvgGrade - avgGrade) < 1e-9) {
            return indexArray[mid];
        }
        else if (midProfileGrade > profileGrade || (midProfileGrade == profileGrade && midAvgGrade > avgGrade) ||
            (midProfileGrade == profileGrade && abs(midAvgGrade - avgGrade) < 1e-9 && student.surname > surname)) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}
