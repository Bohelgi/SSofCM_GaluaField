#include "Galua_Field.h"
#include <iostream>
#include <chrono>

int main() {
    std::string binaryInput1, binaryInput2;

    std::cout << "Enter the first binary number: ";
    std::cin >> binaryInput1;

    std::cout << "Enter the second binary number: ";
    std::cin >> binaryInput2;
    std::cout << std::endl;

    Galua a = toPol(binaryInput1);
    Galua b = toPol(binaryInput2);

    std::cout << "Sum: " << Add(a, b).toBin() << std::endl;
    std::cout << std::endl;
    std::cout << "Mul: " << Mul(a, b).toBin() << std::endl;
    std::cout << std::endl;
    std::cout << "Square: " << Mul(a, a).toBin() << std::endl;
    std::cout << std::endl;

    std::string n;
    std::cout << "Enter the exponent for power operation: ";
    std::cin >> n;
    std::cout << std::endl;
    std::cout << "Pow (a^n): " << Pow(a, n).toBin() << std::endl;
    std::cout << std::endl;

    std::cout << "Trace: " << Trace(a).toBin() << std::endl;
    std::cout << "Inverse: " << Inverse(a).toBin() << std::endl;
    std::cout << std::endl;

    // Some test

    std::string binary_a = "00100010110111101010001110010000011011000000000001001011100111100010010000101001101011111101101011100110001001111100101100011101000011101010111000101010100110100011000111010100100010110010101011111001011011010010111010100101001000010010011000100011000011000111001000100100011110101000110110100";
    std::string binary_b = "00011010110111011111111010000001001011011110100110010110000110010001001110101011111101011011010011111000011011101011010000111011110001111111101111010101101100011110011001011011101010110100001101111010110110110001001101111011010100010111111110111101110111101101001101011000001100100110101011010";
    std::string binary_c = "00010110110111110111100111101111101011010011110001001110100001011100000001111110001101110011101110011000000001011110111101110110110101001010110010111011001101101101010110011010110001010111001100001111111010010111111010011110001110010011111011000010100110011111101010110111000010010011110000001010111001100110101";

    Galua poly_a = toPol(binary_a);
    Galua poly_b = toPol(binary_b);
    Galua poly_c = toPol(binary_c);

    Galua left_side = Mul(Add(poly_a, poly_b), poly_c);
    Galua right_side = Add(Mul(poly_b, poly_c), Mul(poly_c, poly_a));

    if (comparePol(left_side, right_side) == 0) {
        std::cout << "Equal in true: (a + b) * c = b * c + c * a" << std::endl;
    }
    else {
        std::cout << "Equal in not true: (a + b) * c ≠ b * c + c * a" << std::endl;
    }

    std::cout << std::endl;


    std::cout << "Measuring time for operations..." << std::endl;

    const int iter = 25;

    long long total_add_time = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Galua result_add = Add(a, b);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        total_add_time += duration.count();
    }
    double average_add_time = static_cast<double>(total_add_time) / iter;
    std::cout << "Average time add: " << average_add_time << " nanoseconds\n";


    long long total_mul_time = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Galua result_mul = Mul(a, b);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        total_mul_time += duration.count();
    }
    double average_mul_time = static_cast<double>(total_mul_time) / iter;
    std::cout << "Average time mul: " << average_mul_time << " nanoseconds\n";


    long long total_square_time = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Galua result_square = Mul(a, a);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        total_square_time += duration.count();
    }
    double average_square_time = static_cast<double>(total_square_time) / iter;
    std::cout << "Average time square: " << average_square_time << " nanoseconds\n";


    long long total_pow_time = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Galua result_pow = Pow(a, n);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        total_pow_time += duration.count();
    }
    double average_pow_time = static_cast<double>(total_pow_time) / iter;
    std::cout << "Average time pow: " << average_pow_time << " nanoseconds\n";

    long long total_trace_time = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Galua result_trace = Trace(a);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        total_trace_time += duration.count();
    }
    double average_trace_time = static_cast<double>(total_trace_time) / iter;
    std::cout << "Average time trace: " << average_trace_time << " nanoseconds\n";


    long long total_inverse_time = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Galua result_inverse = Inverse(a);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        total_inverse_time += duration.count();
    }
    double average_inverse_time = static_cast<double>(total_inverse_time) / iter;
    std::cout << "Average time inverse: " << average_inverse_time << " nanoseconds\n";


    return 0;
}