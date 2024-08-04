#include "Complex.h"

void testConstructor();
void testAddition();
void testSubtraction();
void testMultiplication();
void testDivision();
void testEqualityOperator();
void testInequalityOperator();
void testGetPhase();
void testGetAmplitude();
void testChainAddition();
void testChainAdditionBraces();
void testChainMultiplication();
void testChainMultiplicationBraces();

int main()
{
    testConstructor();
	testAddition();
	testSubtraction();
	testMultiplication();
	testDivision();
	testEqualityOperator();
	testInequalityOperator();
	testGetPhase();
	testGetAmplitude();
	testChainAddition();
	testChainAdditionBraces();
	testChainMultiplication();
	testChainMultiplicationBraces();
    return 0;
}

void testChainAddition(){
	ComplexNumber a(2, 10);
	ComplexNumber b(3, 6);
	ComplexNumber c(7, -3);
	
	a += b += c;

    ComplexNumber a1(12, 13);
    ComplexNumber b1(10, 3);
    ComplexNumber c1(7, -3);

    if (a == a1 && b == b1 && c == c1) {
        std::cout << "Chain addition: Passed" << std::endl;
    } else {
        std::cout << "Chain addition: Failed" << std::endl;
    }
}

void testChainAdditionBraces(){
	ComplexNumber a(2, 10);
	ComplexNumber b(3, 6);
	ComplexNumber c(7, -3);
	
	(a += b) += c;

    ComplexNumber a1(12, 13);
    ComplexNumber b1(3, 6);
	ComplexNumber c1(7, -3);
	
	if (a == a1 && b == b1 && c == c1) {
        std::cout << "Chain addition (braces): Passed" << std::endl;
    } else {
        std::cout << "Chain addition (braces): Failed" << std::endl;
    }
}

void testChainMultiplication(){
	ComplexNumber a(2, 10);
	ComplexNumber b(3, 6);
	ComplexNumber c(7, -3);
	
	a *= b *= c;

    ComplexNumber a1(-252, 456);
    ComplexNumber b1(39, 33);
    ComplexNumber c1(7, -3);
	
	if (a == a1 && b == b1 && c == c1) {
        std::cout << "Chain multiplication: Passed" << std::endl;
    } else {
        std::cout << "Chain multiplication: Failed" << std::endl;
    }
}

void testChainMultiplicationBraces(){
	ComplexNumber a(2, 10);
	ComplexNumber b(3, 6);
	ComplexNumber c(7, -3);
	
	(a *= b) *= c;

    ComplexNumber a1(-252, 456);
    ComplexNumber b1(3, 6);
	ComplexNumber c1(7, -3);
	
	if (a == a1 && b == b1 && c == c1) {
        std::cout << "Chain multiplication (braces): Passed" << std::endl;
    } else {
        std::cout << "Chain multiplication (braces): Failed" << std::endl;
    }
}

void testConstructor() {
    ComplexNumber a(3.0, 4.0);
    if (a.real == 3.0 && a.imaginary == 4.0) {
        std::cout << "Constructor: Passed" << std::endl;
    } else {
        std::cout << "Constructor: Failed" << std::endl;
    }
}

void testAddition() {
    ComplexNumber a(3.0, 4.0);
    ComplexNumber b(2.0, -1.0);
    ComplexNumber c = a + b;
    if (c.real == 5.0 && c.imaginary == 3.0) {
        std::cout << "Addition: Passed" << std::endl;
    } else {
        std::cout << "Addition: Failed" << std::endl;
    }
}

void testSubtraction() {
    ComplexNumber a(3.0, 4.0);
    ComplexNumber b(2.0, -1.0);
    ComplexNumber result = a - b;
    if (result.real == 1.0 && result.imaginary == 5.0) {
        std::cout << "Subtraction: Passed" << std::endl;
    } else {
        std::cout << "Subtraction: Failed" << std::endl;
    }
}

void testMultiplication() {
    ComplexNumber a(3.0, 4.0);
    ComplexNumber b(2.0, -1.0);
    ComplexNumber result = a * b;
    if (result.real == 10.0 && result.imaginary == 5.0) {
        std::cout << "Multiplication: Passed" << std::endl;
    } else {
        std::cout << "Multiplication: Failed" << std::endl;
    }
}

void testDivision() {
    ComplexNumber a(3.0, 4.0);
    ComplexNumber b(2.0, -1.0);
    ComplexNumber result = a / b;
    if (result.real == 0.4 && result.imaginary == 2.2) {
        std::cout << "Division: Passed" << std::endl;
    } else {
        std::cout << "Division: Failed" << std::endl;
    }
}

void testEqualityOperator() {
    ComplexNumber a(3.0, 4.0);
    ComplexNumber b(3.0, 4.0);
    if (a == b) {
        std::cout << "Equality Operator: Passed" << std::endl;
    } else {
        std::cout << "Equality Operator: Failed" << std::endl;
    }
}

void testInequalityOperator() {
    ComplexNumber a(3.0, 4.0);
    ComplexNumber b(2.0, 4.0);
    if (a != b) {
        std::cout << "Inequality Operator: Passed" << std::endl;
    } else {
        std::cout << "Inequality Operator: Failed" << std::endl;
    }
}

void testGetPhase() {
    ComplexNumber a(3.0, 4.0);
    double phase = a.getPhase();
    double expectedPhase = 0.927295;

    if (std::abs(phase - expectedPhase) < 1e-6) {
        std::cout << "Phase: Passed" << std::endl;
    } else {
        std::cout << "Phase: Failed" << std::endl;
    }
}

void testGetAmplitude() {
    ComplexNumber a(3.0, 4.0);
    double magnitude = a.getAmplitude();
    double expectedAmplitude = 5.0;

    if (std::abs(magnitude - expectedAmplitude) < 1e-6) {
        std::cout << "Magnitude: Passed" << std::endl;
    } else {
        std::cout << "Magnitude: Failed" << std::endl;
    }
}
