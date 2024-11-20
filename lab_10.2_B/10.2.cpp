#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

enum Specialization { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_EDUCATION };
string specializationStr[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    int number;               // ���������� ����� ��������
    string surname;           // ������� ��������
    int course;               // ����
    Specialization spec;      // ������������
    int physics;              // ������ � ������
    int mathematics;          // ������ � ����������
    union {                   // �ᒺ������ ��� ������ ������
        int programming;      // ������ � �������������
        int numerical_methods; // ������ � ��������� ������
        int pedagogy;         // ������ � ���������
    };
};

// ��������� �������
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
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* students = new Student[N];
    int* indexArray = new int[N];

    int menuItem;
    do {
        cout << "\n����:\n";
        cout << "1 - �������� ����� ��������\n";
        cout << "2 - ���� ����� ��������\n";
        cout << "3 - Գ����� ���������� ��������\n";
        cout << "4 - �������� ���������� ��������\n";
        cout << "5 - ����� ��������\n";
        cout << "0 - �����\n";
        cout << "������� ��: ";
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
            cout << "������ �������� ������� �����������.\n";
            break;
        case 4:
            IndexSort(students, N, indexArray);
            cout << "������ �������� �������� �����������.\n";
            break;
        case 5: {
            string surname;
            int profileGrade;
            double avgGrade;
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            cout << "������ ������ � ����������� �������� ��� ������: ";
            cin >> profileGrade;
            cout << "������ ������� ��� ��� ������: ";
            cin >> avgGrade;

            int result = BinarySearch(students, indexArray, N, surname, profileGrade, avgGrade);
            if (result != -1)
                cout << "������� ��������� �� ��������: " << result << "\n";
            else
                cout << "������� �� ���������.\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    delete[] indexArray;
    return 0;
}

void InputStudents(Student* students, int N) {
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";
        students[i].number = i + 1;
        cin.ignore();
        cout << " �������: ";
        getline(cin, students[i].surname);
        cout << " ����: ";
        cin >> students[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        int spec;
        cin >> spec;
        students[i].spec = static_cast<Specialization>(spec);
        cout << " ������ � ������: ";
        cin >> students[i].physics;
        cout << " ������ � ����������: ";
        cin >> students[i].mathematics;

        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << " ������ � �������������: ";
            cin >> students[i].programming;
        }
        else if (students[i].spec == INFORMATICS) {
            cout << " ������ � ��������� ������: ";
            cin >> students[i].numerical_methods;
        }
        else {
            cout << " ������ � ���������: ";
            cin >> students[i].pedagogy;
        }
    }
}

void PrintStudents(const Student* students, int N) {
    cout << "=================================================================================================================================\n";
    cout << "| � | �������           | ���� | ������������           | Գ���� | ���������� | ������������� | ������� ������ | ��������� |\n";
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
