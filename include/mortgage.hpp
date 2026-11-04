#pragma once

#include <optional>
#include <variant>

namespace mortgage {

enum class Gender {
    Male = 1,
    Female = 2,
};

enum class CalculationError {
    InvalidGender,
    InvalidAge,
    InvalidSalary,
    FactorNotDefined,
};

using CalculationResult = std::variant<double, CalculationError>;

std::optional<CalculationError> validateInputs(Gender gender, int age, double salary);
std::optional<double> selectFactor(Gender gender, int age);
double calculateMortgage(double salary, double factor);
CalculationResult calculate(Gender gender, int age, double salary);

}  // namespace mortgage