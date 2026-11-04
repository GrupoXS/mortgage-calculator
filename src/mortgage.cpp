#include "mortgage.hpp"

#include <cmath>

namespace mortgage {

std::optional<CalculationError> validateInputs(Gender gender, int age, double salary) {
    if (gender != Gender::Male && gender != Gender::Female) {
        return CalculationError::InvalidGender;
    }
    if (age < 18 || age > 55) {
        return CalculationError::InvalidAge;
    }
    if (!std::isfinite(salary) || salary < 0.0 || salary > 10000.0) {
        return CalculationError::InvalidSalary;
    }
    return std::nullopt;
}

std::optional<double> selectFactor(Gender gender, int age) {
    if (gender == Gender::Male) {
        if (age >= 18 && age <= 35) {
            return 75.0;
        }
        if (age >= 36 && age <= 45) {
            return 55.0;
        }
        if (age >= 46 && age <= 55) {
            return 30.0;
        }
    } else if (gender == Gender::Female) {
        if (age >= 18 && age <= 30) {
            return 70.0;
        }
        if (age >= 31 && age <= 40) {
            return 50.0;
        }
        if (age >= 41 && age <= 50) {
            return 35.0;
        }
    }
    return std::nullopt;
}

double calculateMortgage(double salary, double factor) {
    return salary * factor;
}

CalculationResult calculate(Gender gender, int age, double salary) {
    if (const auto validation_error = validateInputs(gender, age, salary)) {
        return *validation_error;
    }

    const auto factor = selectFactor(gender, age);
    if (!factor) {
        return CalculationError::FactorNotDefined;
    }

    return calculateMortgage(salary, *factor);
}

}  // namespace mortgage