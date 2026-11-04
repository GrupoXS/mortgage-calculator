#include "mortgage.hpp"

#include <array>
#include <limits>
#include <string>
#include <tuple>
#include <variant>

#include <gtest/gtest.h>

namespace {

using mortgage::CalculationError;
using mortgage::Gender;

struct FactorCase {
    Gender gender;
    int age;
    double expected_factor;
};

TEST(ValidateInputsTest, AcceptsInclusiveGeneralBounds) {
    EXPECT_EQ(mortgage::validateInputs(Gender::Male, 18, 0.0), std::nullopt);
    EXPECT_EQ(mortgage::validateInputs(Gender::Male, 55, 10000.0), std::nullopt);
    EXPECT_EQ(mortgage::validateInputs(Gender::Female, 18, 1.0), std::nullopt);
    EXPECT_EQ(mortgage::validateInputs(Gender::Female, 55, 9999.0), std::nullopt);
}

TEST(ValidateInputsTest, RejectsUnknownGender) {
    EXPECT_EQ(
        mortgage::validateInputs(static_cast<Gender>(999), 30, 5000.0),
        CalculationError::InvalidGender
    );
}

TEST(ValidateInputsTest, RejectsAgeOutsideInclusiveBounds) {
    EXPECT_EQ(mortgage::validateInputs(Gender::Male, 17, 5000.0), CalculationError::InvalidAge);
    EXPECT_EQ(mortgage::validateInputs(Gender::Male, 56, 5000.0), CalculationError::InvalidAge);
}

TEST(ValidateInputsTest, RejectsSalaryOutsideInclusiveBounds) {
    EXPECT_EQ(mortgage::validateInputs(Gender::Male, 30, -1.0), CalculationError::InvalidSalary);
    EXPECT_EQ(mortgage::validateInputs(Gender::Male, 30, 10001.0), CalculationError::InvalidSalary);
}

TEST(ValidateInputsTest, RejectsNonFiniteSalary) {
    EXPECT_EQ(
        mortgage::validateInputs(Gender::Male, 30, std::numeric_limits<double>::quiet_NaN()),
        CalculationError::InvalidSalary
    );
    EXPECT_EQ(
        mortgage::validateInputs(Gender::Male, 30, std::numeric_limits<double>::infinity()),
        CalculationError::InvalidSalary
    );
}

TEST(SelectFactorTest, SelectsExpectedFactorsAtEveryRangeBoundary) {
    constexpr std::array<FactorCase, 12> cases{{
        {Gender::Male, 18, 75.0},
        {Gender::Male, 35, 75.0},
        {Gender::Male, 36, 55.0},
        {Gender::Male, 45, 55.0},
        {Gender::Male, 46, 30.0},
        {Gender::Male, 55, 30.0},
        {Gender::Female, 18, 70.0},
        {Gender::Female, 30, 70.0},
        {Gender::Female, 31, 50.0},
        {Gender::Female, 40, 50.0},
        {Gender::Female, 41, 35.0},
        {Gender::Female, 50, 35.0},
    }};

    for (const auto& test_case : cases) {
        SCOPED_TRACE("age=" + std::to_string(test_case.age));
        const auto factor = mortgage::selectFactor(test_case.gender, test_case.age);
        ASSERT_TRUE(factor.has_value());
        EXPECT_DOUBLE_EQ(*factor, test_case.expected_factor);
    }
}

TEST(SelectFactorTest, ReportsNoFactorForFemaleAgesFiftyOneThroughFiftyFive) {
    for (int age = 51; age <= 55; ++age) {
        EXPECT_FALSE(mortgage::selectFactor(Gender::Female, age).has_value()) << "age=" << age;
    }
}

TEST(SelectFactorTest, ReturnsNoFactorForInvalidAgeOrGender) {
    EXPECT_FALSE(mortgage::selectFactor(Gender::Male, 17).has_value());
    EXPECT_FALSE(mortgage::selectFactor(Gender::Female, 56).has_value());
    EXPECT_FALSE(mortgage::selectFactor(static_cast<Gender>(999), 30).has_value());
}

TEST(CalculateMortgageTest, MultipliesSalaryByFactor) {
    EXPECT_DOUBLE_EQ(mortgage::calculateMortgage(5000.0, 75.0), 375000.0);
    EXPECT_DOUBLE_EQ(mortgage::calculateMortgage(0.0, 70.0), 0.0);
}

TEST(CalculateTest, ReturnsExpectedResultsForRequirementsExamples) {
    const std::array<std::tuple<Gender, int, double, double>, 4> cases{{
        {Gender::Male, 18, 5000.0, 375000.0},
        {Gender::Male, 40, 5000.0, 275000.0},
        {Gender::Female, 30, 5000.0, 350000.0},
        {Gender::Female, 45, 5000.0, 175000.0},
    }};

    for (const auto& [gender, age, salary, expected] : cases) {
        const auto result = mortgage::calculate(gender, age, salary);
        ASSERT_TRUE(std::holds_alternative<double>(result));
        EXPECT_DOUBLE_EQ(std::get<double>(result), expected);
    }
}

TEST(CalculateTest, ReturnsExplicitErrorsInsteadOfAValue) {
    const auto expect_error = [](const auto& result, CalculationError expected) {
        ASSERT_TRUE(std::holds_alternative<CalculationError>(result));
        EXPECT_EQ(std::get<CalculationError>(result), expected);
    };

    expect_error(mortgage::calculate(Gender::Male, 17, 5000.0), CalculationError::InvalidAge);
    expect_error(mortgage::calculate(Gender::Male, 30, -1.0), CalculationError::InvalidSalary);
    expect_error(
        mortgage::calculate(static_cast<Gender>(999), 30, 5000.0),
        CalculationError::InvalidGender
    );
    expect_error(
        mortgage::calculate(Gender::Female, 51, 5000.0),
        CalculationError::FactorNotDefined
    );
}

TEST(CalculateTest, ZeroSalaryDoesNotHideMissingFactor) {
    const auto result = mortgage::calculate(Gender::Female, 55, 0.0);
    ASSERT_TRUE(std::holds_alternative<CalculationError>(result));
    EXPECT_EQ(std::get<CalculationError>(result), CalculationError::FactorNotDefined);
}

}  // namespace