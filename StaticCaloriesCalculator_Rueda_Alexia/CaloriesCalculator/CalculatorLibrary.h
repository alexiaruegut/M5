// CalculatorLibrary.h
#pragma once

namespace CalculatorLibrary
{
    class Calories
    {
    public:
        // para calcular las calor�as perdidas seg�n el ej, las reps, el peso y la altura.
        static double calculateCalories(int exercise, int reps, double height, double weight);

        // para calcular el BMI
        static double calculateBMI(double height, double weight);

        // para calcular las calor�as diarias recomendadas seg�n el bmr y la actividad f�sica
        static double calculateCalorieIntake(double weight, double height, int age, bool isMale, double activityLevel);

    private:
        // para calcular el BMR
        static double calculateBMR(double weight, double height, int age, bool isMale);

        // para ajustar el nivel de actividad f�sica
        static double adjustActivityLevel(double bmr, double activityLevel);
    };
}