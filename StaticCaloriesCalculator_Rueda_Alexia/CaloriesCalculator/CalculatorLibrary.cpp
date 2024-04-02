// CalculatorLibrary.cpp
// compile with: cl /c /EHsc CalculatorLibrary.cpp
// post-build command: lib CalculatorLibrary.obj

#include "CalculatorLibrary.h"
#include <cmath> // para la función pow
#include <iostream>
using namespace std;

namespace CalculatorLibrary
{
    double Calories::calculateCalories(int exercise, int reps, double height, double weight)
    {
        double caloriesPerRep = 0.0;

        switch (exercise) {
        case 1: // ejercicio SQUAT
            caloriesPerRep = 0.1;
            break;
        case 2: // ejercicio PULL UP
            caloriesPerRep = 1;
            break;
        case 3: // ejercicio PUSH UP
            caloriesPerRep = 0.6;
            break;
        case 4: // ejercicio BURPEES
            caloriesPerRep = 0.5;
            break;
        case 5: // ejercicio HIP-THRUST
            caloriesPerRep = 0.5;
            break;
        case 6: // ejercicio ABDOMINAL CRUNCH
            caloriesPerRep = 0.25;
            break;
        default:
            return 0.0; // si se introduce un número de ejercicio no válido, se devolverá un valor de 0 calorías perdidas.
        }

        double totalCaloriesLost = caloriesPerRep * reps;

        // ajuste basado en la altura y el peso: se multiplica por la altura y se divide por el peso.
        totalCaloriesLost *= height / weight;

        return totalCaloriesLost;
    }

    double Calories::calculateBMI(double height, double weight)
    {
        return weight / pow(height / 100, 2); // tengo que pasar los cm a metros para que la formula funciona correctamente.
    }

    double Calories::calculateCalorieIntake(double weight, double height, int age, bool isMale, double activityLevel)
    {
        double bmr = calculateBMR(weight, height, age, isMale);

        // ajustes entre el bmr y el activity level
        double calorieIntake = adjustActivityLevel(bmr, activityLevel);

        return calorieIntake;
    }

    double Calories::calculateBMR(double weight, double height, int age, bool isMale)
    {
        double bmr = 0.0;

        // uso la fórmula de Harris-Benedict, que varia si el usuario es mujer o hombre
        if (isMale) {
            bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
        }
        else {
            bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
        }

        return bmr;
    }

    double Calories::adjustActivityLevel(double bmr, double activityLevel)
    {
        double adjustedBMR;

        if (activityLevel == 1) { // sedentary
            adjustedBMR = bmr * 1.2;
        }
        else if (activityLevel == 2) { // lightly active
            adjustedBMR = bmr * 1.375;
        }
        else if (activityLevel == 3) { // moderately active
            adjustedBMR = bmr * 1.55;
        }
        else if (activityLevel == 4) { // active
            adjustedBMR = bmr * 1.725;
        }
        else if (activityLevel == 5) { // very active
            adjustedBMR = bmr * 1.9;
        }
        else {
            cout << "Invalid activity level option. Default level will be: sedentary.";
            adjustedBMR = bmr * 1.2;
        }

        return adjustedBMR;
    }
};