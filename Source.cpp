#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <map>
#include <windows.h>

enum specialization {
    COMPUTER_SCIENCE,
    IT,
    MATH_ECONOMICS,
    PHYSICS_IT,
    HANDICRAFT
};

union third_grade {
    int programmingGrade;
    int chMGrade;
    int pedagogicGrade;
};

struct student_s {
    char surname[10];
    int course;
    specialization spec;
    int physicsGrade;
    int mathGrade;
    third_grade thirdGrade;
};

/*
 * Return number of saved students
 */
int getUserInput(std::string filename);

void saveToFile(std::string filename, student_s* student, int amount);

void readFromFile(std::string filename, int size);

int sizeOfExcellentStudents(student_s* students, int total);

std::string findBestSubject(student_s* students, int total);

void printStudents(student_s* students, int total);

int main() {

    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    int studentsSize = getUserInput(filename);

    readFromFile(filename, studentsSize);

    return 0;
}

int getUserInput(std::string filename) {

    int amount;
    std::cout << "Enter number of students: ";
    std::cin >> amount;

    student_s* students = new student_s[amount];

    for (int i = 0; i < amount; ++i) {

        std::string surname;
        std::cout << "Enter student name = ";
        std::cin >> surname;
        #pragma warning(suppress : 4996)
        strcpy(students[i].surname, surname.c_str());
        int course;
        std::cout << "Enter course number = ";
        std::cin >> course;
        students[i].course = course;

        int specialization;
        std::cout << "COMPUTER_SCIENCE = 1,\n"
            "IT = 2,\n"
            "MATH_ECONOMICS = 3,\n"
            "PHYSICS_IT = 4,\n"
            "HANDICRAFT = 5" << std::endl;
        std::cout << "Choose specialization = ";
        std::cin >> specialization;

        int thirdGrade;
        switch (specialization) {
        case 1:
            students[i].spec = COMPUTER_SCIENCE;
            std::cout << "Enter programming grade = ";
            std::cin >> thirdGrade;
            students[i].thirdGrade.programmingGrade = thirdGrade;
            break;
        case 2:
            students[i].spec = IT;
            std::cout << "Enter chM grade = ";
            std::cin >> thirdGrade;
            students[i].thirdGrade.chMGrade = thirdGrade;
            break;
        case 3:
            students[i].spec = MATH_ECONOMICS;
            std::cout << "Enter pedagogic grade = ";
            std::cin >> thirdGrade;
            students[i].thirdGrade.pedagogicGrade = thirdGrade;
            break;
        case 4:
            students[i].spec = PHYSICS_IT;
            std::cout << "Enter pedagogic grade = ";
            std::cin >> thirdGrade;
            students[i].thirdGrade.pedagogicGrade = thirdGrade;
            break;
        case 5:
            students[i].spec = HANDICRAFT;
            std::cout << "Enter pedagogic grade = ";
            std::cin >> thirdGrade;
            students[i].thirdGrade.pedagogicGrade = thirdGrade;
            break;
        }

        int physicsGrade;
        std::cout << "Enter physics grade = ";
        std::cin >> physicsGrade;
        students[i].physicsGrade = physicsGrade;

        int mathGrade;
        std::cout << "Enter math grade = ";
        std::cin >> mathGrade;
        students[i].mathGrade = mathGrade;

        saveToFile(filename, students, amount);
        return amount;
    }
}

void saveToFile(std::string filename, student_s* student, int total) {
    std::ofstream out(filename, std::ios::binary);

    out.write((char*)&student, sizeof(student_s) * total);

    out.close();
}

void readFromFile(std::string filename, int size) {

    student_s* students = new student_s[size];

    std::ifstream in(filename, std::ios::binary);

    in.read((char*)&students, sizeof(students));

    printStudents(students, size);

    std::cout << "Size of students with average grade above 4.5 = " << sizeOfExcellentStudents(students, size)
        << std::endl;
    std::cout << "Subject with the best average grade = " << findBestSubject(students, size);

    in.close();
}

int sizeOfExcellentStudents(student_s* students, int total) {
    int size = 0;

    for (int i = 0; i < total; ++i) {
        double average = double(students[i].physicsGrade + students[i].mathGrade);

        switch (students[i].course) {
        case COMPUTER_SCIENCE:
            average += students[i].thirdGrade.programmingGrade;
            break;
        case IT:
            average += students[i].thirdGrade.chMGrade;
            break;
        default:
            average += students[i].thirdGrade.pedagogicGrade;
            break;

        }

        if (average / 3 >= 4.5) {
            size++;
        }
    }

    return size;
}

std::string findBestSubject(student_s* students, int total) {

    double physicsGrade = 0;
    double mathGrade = 0;
    double programmingGrade = 0;
    double chMGrade = 0;
    double pedagogicGrade = 0;

    int physicsGradeK = total;
    int mathGradeK = total;
    int programmingGradeK = 0;
    int chMGradeK = 0;
    int pedagogicGradeK = 0;

    for (int i = 0; i < total; ++i) {
        physicsGrade += students[i].physicsGrade;
        mathGrade += students[i].physicsGrade;

        switch (students[i].spec) {
        case COMPUTER_SCIENCE:
            programmingGrade += students[i].thirdGrade.programmingGrade;
            programmingGradeK++;
            break;
        case IT:
            chMGrade += students[i].thirdGrade.chMGrade;
            chMGradeK++;
            break;
        default:
            pedagogicGrade += students[i].thirdGrade.pedagogicGrade;
            pedagogicGradeK++;
            break;
        }
    }

    double arr[5];
    arr[0] = physicsGrade / physicsGradeK;
    arr[1] = mathGrade / mathGradeK;
    arr[2] = programmingGrade / programmingGradeK;
    arr[3] = chMGrade / chMGradeK;
    arr[4] = pedagogicGrade / pedagogicGradeK;

    double max = arr[0];
    std::string subjectName = "Physics";
    for (int i = 0; i < 5; ++i) {
        if (arr[i] > max) {
            max = arr[i];
            if (i == 0) {
                subjectName = "Physics";
            }
            else if (i == 1) {
                subjectName = "Math";
            }
            else if (i == 2) {
                subjectName = "Programming";
            }
            else if (i == 3) {
                subjectName = "Numerical Methods";
            }
            else {
                subjectName = "Pedagogic";
            }
        }
    }

    return subjectName;
}

void printStudents(student_s* p, int total) {

    std::map<int, std::string> spec;

    spec[0] = "COMP";
    spec[1] = "IT";
    spec[2] = "MATH";
    spec[3] = "PHYS";
    spec[4] = "HAND";

    std::cout << "=============================================================="
        << std::endl;
    std::cout
        << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка"
        << std::endl;
    std::cout << "--------------------------------------------------------------"
        << std::endl;
    for (int i = 0; i < total; i++) {
        std::cout << "| " << std::setw(3) << std::right << i + 1 << " ";
        std::cout << "| " << std::setw(10) << std::left << p[i].surname
            << "| " << std::setw(4) << std::right << p[i].course << " "
            << "| " << std::setw(5) << std::left << spec[p[i].spec] << " "
            << "| " << std::setw(5) << std::right << p[i].physicsGrade << " "
            << "| " << std::setw(5) << std::left << p[i].mathGrade;

        switch (p[i].spec) {
        case COMPUTER_SCIENCE:
            std::cout << "| " << std::setw(9) << std::setprecision(2) << std::fixed << std::right
                << p[i].thirdGrade.programmingGrade << " |" << std::setw(13) << std::right << "|"
                << std::endl;
            break;
        case IT:
            std::cout << "| " << std::setw(9) << std::setprecision(2) << std::fixed << std::right
                << p[i].thirdGrade.chMGrade << " |" << std::setw(13) << std::right << "|" << std::endl;
            break;
        case MATH_ECONOMICS:
        case PHYSICS_IT:
        case HANDICRAFT:
            std::cout << "| " << std::setw(11) << std::right << "|"
                << " " << std::setw(8) << std::right
                << p[i].thirdGrade.pedagogicGrade << " |" << std::endl;
            break;
        }
    }
    std::cout << "========================================================================="
        << std::endl;
    std::cout << std::endl;
}