#include <iostream>
#include <Eigen/Dense>

#include "vector.h"
#include "mult.h"
#include "add.h"
#include "svector.h"
#include "clock.h"
#include "random.h"
#include "matrix.h"
#include "operators.h"

#include "bad_vector.h"
#include "bad_matrix.h"

using Eigen::MatrixXd;

Random<double> ir(1.00, 100.00);

// petlja po komponentama - vektor
void loop_test(Clock& clock, std::size_t size) {
    Vector<double> x(size), y(size), z(size);
    std::cout << "Array test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        for (std::size_t idx = 0; idx < size; ++idx) {
            // prvi izraz  z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);
            // z[idx] = 1.2 * x[idx] * (x[idx] + y[idx]) + 2.3 * y[idx] * (y[idx] + z[idx]) + 3.4 * z[idx] * (x[idx] + z[idx]);

            // drugi izraz z = 1.2*x + x*y
            z[idx] = 1.2 * x[idx] + x[idx] * y[idx];
        }
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// predlozni izrazi - vektor
void good_vector(Clock& clock, std::size_t size) {
    Vector<double> x(size), y(size), z(size);
    std::cout << "Good vector test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // prvi izraz  z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);
        // z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);

        // drugi izraz z = 1.2*x + x*y
        z = 1.2 * x + x * y;
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// naivna impl. - vektor
void bad_vector(Clock& clock, std::size_t size) {
    SArray<double> x(size), y(size), z(size);
    std::cout << "Bad vector test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // prvi izraz  z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);
        // z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);

        // drugi izraz z = 1.2*x + x*y
        z = 1.2 * x + x * y;
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// petlja po komponentama - matrica
void loop_test_mat(Clock& clock, std::size_t size) {
    SDoubleArray<double> M(size, size), N(size, size);
    SArray<double> y(size), x(size), z(size), w(size);
    std::cout << "Double Array test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
         // izraz w = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z); (bez potrebe temp. objekta)
         /*for (std::size_t idx = 0; idx < size; ++idx) {
            for (std::size_t idy = 0; idy < size; ++idy) {
                 w[idx] += 1.2* M(idx,idy) * x[idy] 
                     + 2.3*(M(idx,idy) + N(idx,idy)) * (2.3*y[idy] + 3.4*z[idy]);
             }
        }*/

        // slican izraz x = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z); (potreban temp. objekt)
        SArray<double> temp(size);
        for (std::size_t idx = 0; idx < size; ++idx) {
            for (std::size_t idy = 0; idy < size; ++idy) {
                 temp[idx] += 1.2* M(idx,idy) * x[idy] 
                     + 2.3*(M(idx,idy) + N(idx,idy)) * (2.3*y[idy] + 3.4*z[idy]);
             }
        }
        for (std::size_t idx = 0; idx < size; ++idx) {
            x[idx] = temp[idx];
        }
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// predlozni izraz - matrica
void good_matrix(Clock& clock, std::size_t size) {
    Matrix<double> M(size,size), N(size,size);
    Vector<double> y(size), x(size), z(size), w(size);
    std::cout << "Good matrix test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // izraz w = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z); (bez potrebe temp. objekta)
        //w = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z);

        // slican izraz x = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z); (potreban temp. objekt)
        x = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z);
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// naivna impl. - matrica
void bad_matrix(Clock& clock, std::size_t size) {
    SDoubleArray<double> M(size,size), N(size,size);
    SArray<double> x(size), y(size), z(size), w(size);
    std::cout << "Bad matrix test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // izraz w = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z);
        //w = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z);

        // slican izraz x = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z);
        x = 1.2*M*x + 2.3 * (M+N) * (2.3*y + 3.4*z);

        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

void eigen_matrix(Clock& clock) {
    std::size_t size = 10000;
    Eigen::MatrixXf m1(size,size);
    Eigen::VectorXf v1(size), v2(size);
    std::cout << "Eigen matrix: ";
    clock.start();
    v1 = m1 * v1;
    std::cout << clock.stop() << std::endl;
}

void eigen_vector(Clock& clock) {
    std::size_t size = 100'000;
    double* arr = new double[size];
    Vector<double> x(size), y(size);

    double HI = 100.00;
    double LO = 1.00;
    double range = HI - LO;

    Eigen::VectorXf a = Eigen::VectorXf::Random(size);
    //a = (a + Eigen::VectorXf::Constant(size, 1.)) * range / 2;
    a = (a + Eigen::VectorXf::Constant(size, LO));


    Eigen::VectorXf b = Eigen::VectorXf::Random(size);
    //b = (b + Eigen::VectorXf::Constant(size, 1.)) * range / 2;
    b = (b + Eigen::VectorXf::Constant(size, LO));
    std::cout << "Eigen vector: ";

    clock.start();
    a = a + b;
    std::cout << clock.stop() << std::endl;
}

int main() {
    Clock clock;

    ///////////////////////////////

    /*loop_test(clock, 1000);
    bad_vector(clock, 1000);
    good_vector(clock, 1000);
    
    /////////////////////////////////////////

    loop_test(clock, 10000);
    bad_vector(clock, 10000);
    good_vector(clock, 10000);

    /////////////////////////////////////////

    loop_test(clock, 100000);
    bad_vector(clock, 100000);
    good_vector(clock, 100000);*/

    /////////////////////////////////////////

    loop_test_mat(clock, 10);
    bad_matrix(clock, 10);
    good_matrix(clock, 10);
    
    /////////////////////////////////////////

    loop_test_mat(clock, 100);
    bad_matrix(clock, 100);
    good_matrix(clock, 100);

    /////////////////////////////////////////

    loop_test_mat(clock, 1000);
    bad_matrix(clock, 1000);
    good_matrix(clock, 1000);

    ////////////////////////////////////////

    /*eigen_vector(clock);
    eigen_vector(clock);
    eigen_vector(clock);

    ////////////////////////////////////////

    good_matrix(clock);
    good_matrix(clock);
    good_matrix(clock);

    ///////////////////////////////////////////

    eigen_matrix(clock);
    eigen_matrix(clock);
    eigen_matrix(clock);*/

    /////////////////////////////////////////

    return 0;
}