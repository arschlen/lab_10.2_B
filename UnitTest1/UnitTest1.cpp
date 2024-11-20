#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10.2_B/10.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestPhysicalSort)
        {
            Student students[3];

            // Студенти до сортування
            students[0] = { 1, "Ivanov", 2, COMPUTER_SCIENCE, 90, 85, 95 }; // programming = 95
            students[1] = { 2, "Petrov", 1, INFORMATICS, 75, 80, 85 };      // numerical_methods = 85
            students[2] = { 3, "Sidorov", 3, LABOR_EDUCATION, 80, 90, 70 }; // pedagogy = 70

            // Сортуємо студентів
            PhysicalSort(students, 3);

            // Очікуваний порядок після сортування
            Assert::AreEqual(string("Ivanov"), students[0].surname);
            Assert::AreEqual(string("Petrov"), students[1].surname);
            Assert::AreEqual(string("Sidorov"), students[2].surname);
        }

        TEST_METHOD(TestCalculateAverageGrade)
        {
            Student student = { 1, "Ivanov", 2, COMPUTER_SCIENCE, 90, 80, 95 }; // programming = 95
            double expectedAverage = (90 + 80 + 95) / 3.0;

            // Обчислення середнього балу
            double average = CalculateAverageGrade(student);

            // Перевірка результату
            Assert::AreEqual(expectedAverage, average, 1e-9);
        }
    };
}