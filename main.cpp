#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>


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

Random<double> ir(1.00, 100.00);

// naivna impl. - vektor
void bad_vector(Clock& clock, std::size_t size) {
    SArray<double> x(size, ir), y(size, ir), z(size, ir);
    std::cout << "Bad vector test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // prvi izraz  z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z)
        z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);

        // drugi izraz z = 1.2*x + x*y
        //z = 1.2 * x + x * y;
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// petlja po komponentama - vektor
void loop_test(Clock& clock, std::size_t size) {
    Vector<double> x(size, ir), y(size, ir), z(size, ir);
    std::cout << "Array test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        for (std::size_t idx = 0; idx < size; ++idx) {
            // prvi izraz  z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);
             z[idx] = 1.2 * z[idx] * (x[idx] + y[idx]) + 2.3 * y[idx] * (x[idx] + z[idx]) + 3.4 * x[idx] * (y[idx] + z[idx]);

            // drugi izraz z = 1.2*x + x*y
            //z[idx] = 1.2 * x[idx] + x[idx] * y[idx];
        }
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// predlozni izrazi - vektor
void good_vector(Clock& clock, std::size_t size) {
    Vector<double> x(size, ir), y(size, ir), z(size, ir);
    std::cout << "Good vector test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // prvi izraz z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z)
        z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);

        // drugi izraz z = 1.2*x + x*y
        //z = 1.2 * x + x * y;
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

void eigen_vector(Clock& clock, std::size_t size) {
    Eigen::ArrayXd x(size), y(size), z(size);
    std::cout << "Eigen vector test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // prvi izraz  z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);
        z = 1.2 * x * (x + y) + 2.3 * y * (y + z) + 3.4 * z * (x + z);

        // drugi izraz z = 1.2*x + x*y
        //z = 1.2 * x + x * y;
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// naivna impl. - matrica
void bad_matrix(Clock& clock, std::size_t size) {
    SDoubleArray<double> M(size,size), N(size,size), P(size,size);
    SArray<double> x(size), y(size), z(size), w(size);
    std::cout << "Bad matrix test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // izraz x = (M+M)*(y+y);
        x = (M+M)*(y+y);

        // izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
        //w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);

        // izraz P = M + M + N + N;
        //P = M + M + N + N;

        // izraz P = (M+M)*(N+N);
        //P = (M+M)*(N+N);

        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// petlja po komponentama - matrica
void loop_test_mat(Clock& clock, std::size_t size) {
    SDoubleArray<double> M(size, size), N(size, size), P(size,size);
    SArray<double> y(size), x(size), z(size), w(size);
    std::cout << "Double Array test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        // izraz x = (M+M)*(y+y);
        /*for(int i = 0; i < size; ++i){
            x[i] = 0;
            for(int j = 0; j < size; ++j){
                x[i] += (M(i,j) + M(i,j)) * (y[j] + y[j]); 
            }
        }*/

         // izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
         /*for (std::size_t idx = 0; idx < size; ++idx) {
            w[idx] = 0;
            for (std::size_t idy = 0; idy < size; ++idy) {
                 w[idx] += 1.2* M(idx,idy) * x[idy] + 
                    2.3*(M(idx,idy) + N(idx,idy)) * (3.4*y[idy] + 4.5*z[idy]);;
             }
        }*/

        // izraz P = M + M + N + N;
        /*for (std::size_t idx = 0; idx < size; ++idx) {
            for (std::size_t idz = 0; idz < size; ++idz) {
                P(idx,idz) = M(idx,idz) + M(idx,idz) + N(idx,idz) + N(idx,idz);
            }
        }*/

        // izraz P = (M+M)*(N+N);
        for (std::size_t idx = 0; idx < size; ++idx) {
            for (std::size_t idz = 0; idz < size; ++idz) {
                M(idx,idz) += M(idx,idz);
                N(idx,idz) += N(idx,idz);
            }
        }
        for (std::size_t idx = 0; idx < size; ++idx) {
            for (std::size_t idz = 0; idz < size; ++idz) {
                 for (std::size_t idy = 0; idy < size; ++idy) {
                    P(idx,idy) += M(idx,idz)*N(idz,idy);
                }
            }
        }

   
        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// predlozni izraz - matrica
void good_matrix(Clock& clock, std::size_t size) {
    Matrix<double> M(size,size), N(size,size), P(size,size);
    Vector<double> y(size), x(size), z(size), w(size);
    std::cout << "Good matrix test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        //izraz x = (M+M)*(y+y);
        //x = (M+M)*(y+y);

        // izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z); (bez potrebe temp. objekta)
        //w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);

        // izraz P = M + M + N + N;
        //P = M + M + N + N;

        // izraz P = (M+M)*(N+N);
        P = (M+M)*(N+N);

        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
}

void eigen_matrix(Clock& clock, std::size_t size) {
    Eigen::MatrixXd M(size,size), N(size,size), P(size,size);
    Eigen::VectorXd y(size), x(size), z(size), w(size);
    std::cout << "Eigen matrix test(average) size(" << size << "): ";
    double sum = 0;
    clock.start();
    for (int i = 0; i < 100; ++i) {
        clock.start();
        //izraz x = (M+M)*(y+y);
        //x = (M+M)*(y+y);

        // izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z); (bez potrebe temp. objekta)
        //w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);

        // izraz P = M + M + N + N;
        //P = M + M + N + N;

        // izraz P = (M+M)*(N+N);
        P = (M+M)*(N+N);

        sum += clock.stop();
    }
    std::cout << sum / 100 << " us" << std::endl;
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
    /////////////////////////////////////////

    /*loop_test_mat(clock, 10);
    bad_matrix(clock, 10);
    good_matrix(clock, 10);
    
    /////////////////////////////////////////

    loop_test_mat(clock, 100);
    bad_matrix(clock, 100);
    good_matrix(clock, 100);

    /////////////////////////////////////////

    loop_test_mat(clock, 320);
    bad_matrix(clock, 320);
    good_matrix(clock, 320);*/

    ////////////////////////////////////////
    ///////////////////////////////////////// 

    /*loop_test(clock, 1000);
    good_vector(clock, 1000);
    eigen_vector(clock, 1000);

    ////////////////////////////////////////

    loop_test(clock, 10'000);
    good_vector(clock, 10'000);
    eigen_vector(clock, 10'000);

    ///////////////////////////////////////////

    loop_test(clock, 100'000);
    good_vector(clock, 100'000);
    eigen_vector(clock, 100'000);*/

    /////////////////////////////////////////
    /////////////////////////////////////////

    /*loop_test_mat(clock, 32);
    good_matrix(clock, 32);
    eigen_matrix(clock, 32);

    ////////////////////////////////////////

    loop_test_mat(clock, 100);
    good_matrix(clock, 100);
    eigen_matrix(clock, 100);

    ///////////////////////////////////////////

    loop_test_mat(clock, 320);
    good_matrix(clock, 320);
    eigen_matrix(clock, 320);*/

    /////////////////////////////////////////

    return 0;
}
