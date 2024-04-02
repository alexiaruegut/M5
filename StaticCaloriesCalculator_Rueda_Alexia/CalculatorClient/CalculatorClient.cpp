// CalculatorClient.cpp
// compile with: cl /EHsc CalculatorClient.cpp /link CalculatorLibrary.lib

#include <iostream>
#include <string>
#include <iomanip> // para poder poner un número de decimales exactos
#include "CaloriesCalculator/CalculatorLibrary.h"

using namespace std;
using namespace CalculatorLibrary;

int main()
{
    // inicialización de variables
    string user;
    double weight{}, height{}, activityLevel;
    int age{}, choice;
    char gender;
    bool isMale;

    cout << "Welcome to the Kobi Fitness Calculator!\n";
    cout << "Enter your name: ";
    cin >> user;

    // preguntas iniciales para recopilar los datos necesarios del usuario
    cout << "\nEnter your weight (kg): ";
    while (!(cin >> weight) || weight <= 0) {
        cout << "\nInvalid input. Please enter a valid weight." << endl;
        cin.clear(); // esto es para resetear cualquier error que haya salido en el input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // se usa para que el programa no pete si, por ejemplo, el usuario introduce una letra en vez de un números. numeric_limits<streamsize>::max() -> esto se encarga de poner un número de carácteres máximo a ignorar, al poner max, estás diciéndole al cin que no hay límite. '\n' -> actúa de delimitador
        cout << "\nEnter your weight (kg): ";
    }

    cout << "\nEnter your height (cm): ";
    while (!(cin >> height) || height <= 0) {
        cout << "\nInvalid input. Please enter a valid height." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your height (cm): ";
    }

    cout << "\nEnter your age: ";
    while (!(cin >> age) || age <= 0) {
        cout << "\nInvalid input. Please enter a valid age." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your age: ";
    }

    cout << "\nEnter your gender (M/F): ";
    while (!(cin >> gender) || (toupper(gender) != 'M' && toupper(gender) != 'F')) {
        cout << "\nInvalid input. Please enter 'M' for male or 'F' for female." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your gender (M/F): ";
    }
    gender = toupper(gender); // Convertir a mayúsculas

    // un bucle do para que se vaya repitiendo el menú inicial hasta que el usuario decida salir
    do {
        cout << "\n";
        cout << "Menu:\n";
        cout << "1. Calculate calories burned\n";
        cout << "2. Calculate BMI\n";
        cout << "3. Calculate recommended daily calorie intake\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";

        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "\nInvalid input. Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // inicialización de otras variables
        int exercise;
        int reps;
        double caloriesBurned;
        double bmi;
        double recommendedCalories;

        // un switch para manejar la respuesta del usuario del menú inicial
        switch (choice) {
            case 1: // calculadora de calorías perdidas según el ej y las reps
                cout << "\nList of exercises:\n";
                cout << "1. Squat\n";
                cout << "2. Pull up\n";
                cout << "3. Push up\n";
                cout << "4. Burpees\n";
                cout << "5. Hip-thrust\n";
                cout << "6. Abdominal crunch\n";
                cout << "Select an exercise: ";

                while (!(cin >> exercise) || exercise < 1 || exercise > 6) {
                    cout << "\nInvalid input. Please enter a number between 1 and 6: ";
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "\nEnter the number of repetitions you've done: ";

                while (!(cin >> reps) || reps < 0) {
                    cout << "\nInvalid input. Please enter a non-negative number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // otro switch para manejar el ej escogido por el usuario
                switch (exercise) {
                    case 1: // squat
                        caloriesBurned = Calories::calculateCalories(1, reps, height, weight);
                        break;
                    case 2: // pull up
                        caloriesBurned = Calories::calculateCalories(2, reps, height, weight);
                        break;
                    case 3: // push up
                        caloriesBurned = Calories::calculateCalories(3, reps, height, weight);
                        break;
                    case 4: // burpees
                        caloriesBurned = Calories::calculateCalories(4, reps, height, weight);
                        break;
                    case 5: // hip-thrust
                        caloriesBurned = Calories::calculateCalories(5, reps, height, weight);
                        break;
                    case 6: // abdominal crunch
                        caloriesBurned = Calories::calculateCalories(6, reps, height, weight);
                        break;
                    default:
                        cout << "\nInvalid exercise option, choose another one.\n";
                        continue; // para que vuelva a salir el listado de ejs
                }
                cout << "\nDoing this exercise " << reps << " times, you have burned " << fixed << setprecision(2) << caloriesBurned << " calories.";
                break;

            case 2: // calculadora del BMI (Índice de Masa Corporal, es el contenido de grasa corporal en relación a la estatura y el peso)
                bmi = Calories::calculateBMI(height, weight);
                cout << "\nYour BMI is: " << fixed << setprecision(2) << bmi;
                cout << "\n";

                if (bmi < 18.5) {
                    cout << "Your weight status is: Underweight." << endl;
                }
                else if (bmi >= 18.5 && bmi <= 24.9) {
                    cout << "Your weight status is: Healthy Weight." << endl;
                }
                else if (bmi >= 25.0 && bmi <= 29.9) {
                    cout << "Your weight status is: Overweight." << endl;
                }
                else {
                    cout << "Your weight status is: Obesity." << endl;
                }
                break;

            case 3: // calculadora del BMR (Tasa Metabólica Basal, es la cantidad de calorías que necesitas comer al día para que tu cuerpo realice sus funciones esenciales con normalidad)
                cout << "\nTypes of activity level:" << endl;
                cout << "1. Sedentary (little or no exercise)" << endl;
                cout << "2. Lightly active (light exercise/sports | 1 - 3 days/week)" << endl;
                cout << "3. Moderately active (moderate exercise/sports | 3 - 5 days/week)" << endl;
                cout << "4. Active (hard exercise/sports | 6 - 7 days/week)" << endl;
                cout << "5. Very active (very hard exercise/sports | 2 or more times a day/week)" << endl;
                cout << "Select your activity level: ";

                while (!(cin >> activityLevel) || activityLevel < 1 || activityLevel > 5) {
                    cout << "\nInvalid input. Please enter a number between 1 and 5: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                isMale = (gender == 'M');
                recommendedCalories = Calories::calculateCalorieIntake(weight, height, age, isMale, activityLevel);
                cout << "\nYour recommended daily calorie intake is: " << recommendedCalories << " calories. Take care of your body!\n";
                break;

            case 4:
                break;

            default:
                cout << "\nInvalid input. Please enter a number between 1 and 4: \n";
                break;
        }
    } while (choice != 4);

    cout << "Goodbye, " << user << ". I hope I see you soon!";
}
