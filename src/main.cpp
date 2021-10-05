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
void bad_vector(Clock& clock, std::size_t size, int izbor) {
    SArray<double> x(size, ir), y(size, ir), z(size, ir);
    std::cout << "Bad vector test(average) size(" << size << "): ";
    double sum = 0;
    if(izbor == 1){
        for (int i = 0; i < 100; ++i) {
             // prvi izraz z = 1.2*x + x*y
            clock.start();
            z = 1.2 * x + x * y;
            sum += clock.stop();
        }
    }
    else{
        for (int i = 0; i < 100; ++i) {
            // drugi izraz  z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z)
            clock.start();
            z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);
            sum += clock.stop();
        }
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// petlja po komponentama - vektor
void loop_test(Clock& clock, std::size_t size, int izbor) {
    Vector<double> x(size, ir), y(size, ir), z(size, ir);
    std::cout << "Array test(average) size(" << size << "): ";
    double sum = 0;
    if(izbor == 1){
        for (int i = 0; i < 100; ++i) {
             // prvi izraz z = 1.2*x + x*y
            clock.start();
            for (std::size_t idx = 0; idx < size; ++idx) {
                z[idx] = 1.2 * x[idx] + x[idx] * y[idx];
            }
            sum += clock.stop();
        }
    }
    else{
        for (int i = 0; i < 100; ++i) {
             // drugi izraz  z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);
            clock.start();
            for (std::size_t idx = 0; idx < size; ++idx) {
                z[idx] = 1.2 * z[idx] * (x[idx] + y[idx]) + 2.3 * y[idx] * (x[idx] + z[idx]) + 3.4 * x[idx] * (y[idx] + z[idx]);
            }
            sum += clock.stop();
        }
    }

    std::cout << sum / 100 << " us" << std::endl;
}

// predlozni izrazi - vektor
void good_vector(Clock& clock, std::size_t size, int izbor) {
    Vector<double> x(size, ir), y(size, ir), z(size, ir);
    std::cout << "Good vector test(average) size(" << size << "): ";
    double sum = 0;
    if(izbor == 1){
        for (int i = 0; i < 100; ++i) {
            // prvi izraz z = 1.2*x + x*y
            clock.start();
            z = 1.2 * x + x * y;
            sum += clock.stop();
        }
    }
    else{
        for (int i = 0; i < 100; ++i) {
            // drugi izraz z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z)
            clock.start();
            z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);
            sum += clock.stop();
        }
    }
    std::cout << sum / 100 << " us" << std::endl;
}

void eigen_vector(Clock& clock, std::size_t size, int izbor) {
    Eigen::ArrayXd x(size), y(size), z(size);
    std::cout << "Eigen vector test(average) size(" << size << "): ";
    double sum = 0;
    if(izbor == 1){
        for (int i = 0; i < 100; ++i) {
            // prvi izraz z = 1.2*x + x*y
            clock.start();
            z = 1.2 * x + x * y;
            sum += clock.stop();
        }
    }
    else{
        for (int i = 0; i < 100; ++i) {
            // drugi izraz z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z)
            clock.start();
            z = 1.2*z*(x+y) + 2.3*y*(x+z) + 3.4*x*(y+z);
            sum += clock.stop();
        }
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// naivna impl. - matrica
void bad_matrix(Clock& clock, std::size_t size, int izbor) {
    SDoubleArray<double> M(size,size), N(size,size), P(size,size);
    SArray<double> x(size), y(size), z(size), w(size);
    std::cout << "Bad matrix test(average) size(" << size << "): ";
    double sum = 0;
    switch(izbor){
        case 1:
            for (int i = 0; i < 100; ++i) {
                // prvi izraz x = (M+M)*(y+y);
                clock.start();
                x = (M+M)*(y+y);
                sum += clock.stop();
            }
            break;
        case 2:
            for (int i = 0; i < 100; ++i) {
                // drugi izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                clock.start();
                w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                sum += clock.stop();
            }
            break;
        case 3:
            for (int i = 0; i < 100; ++i) {
                // treci izraz P = M + M + N + N;
                clock.start();
                P = M + M + N + N;
                sum += clock.stop();
            }
            break;
        case 4:
            for (int i = 0; i < 100; ++i) {
                // cetvrti izraz P = (M+M)*(N+N);
                clock.start();
                P = (M+M)*(N+N);
                sum += clock.stop();
            }
            break;
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// petlja po komponentama - matrica
void loop_test_mat(Clock& clock, std::size_t size, int izbor) {
    SDoubleArray<double> M(size, size), N(size, size), P(size,size);
    SArray<double> y(size), x(size), z(size), w(size);
    std::cout << "Double Array test(average) size(" << size << "): ";
    double sum = 0;
    switch(izbor){
        case 1:
            for (int i = 0; i < 100; ++i) {
                // prvi izraz x = (M+M)*(y+y);
                clock.start();
                for(int idx = 0; idx < size; ++idx){
                    x[idx] = 0;
                    for(int j = 0; j < size; ++j){
                        x[idx] += (M(idx,j) + M(idx,j)) * (y[j] + y[j]); 
                    }
                }
                sum += clock.stop();
            }
            break;
        case 2:
            for (int i = 0; i < 100; ++i) {
                // drugi izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                clock.start();
                for (std::size_t idx = 0; idx < size; ++idx) {
                    w[idx] = 0;
                    for (std::size_t idy = 0; idy < size; ++idy) {
                        w[idx] += 1.2* M(idx,idy) * x[idy] + 
                            2.3*(M(idx,idy) + N(idx,idy)) * (3.4*y[idy] + 4.5*z[idy]);;
                    }
                }
                sum += clock.stop();
            }
            break;
        case 3:
            for (int i = 0; i < 100; ++i) {
                // treci izraz P = M + M + N + N;
                clock.start();
                for (std::size_t idx = 0; idx < size; ++idx) {
                    for (std::size_t idz = 0; idz < size; ++idz) {
                        P(idx,idz) = M(idx,idz) + M(idx,idz) + N(idx,idz) + N(idx,idz);
                    }
                }
                sum += clock.stop();
            }
            break;
        case 4:
            for (int i = 0; i < 100; ++i) {
                // cetvrti izraz P = (M+M)*(N+N);
                clock.start();
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
            break;
        
    }
    std::cout << sum / 100 << " us" << std::endl;
}

// predlozni izraz - matrica
void good_matrix(Clock& clock, std::size_t size, int izbor) {
    Matrix<double> M(size,size), N(size,size), P(size,size);
    Vector<double> y(size), x(size), z(size), w(size);
    std::cout << "Good matrix test(average) size(" << size << "): ";
    double sum = 0;
    switch(izbor){
        case 1:
            for (int i = 0; i < 100; ++i) {
                // prvi izraz x = (M+M)*(y+y);
                clock.start();
                x = (M+M)*(y+y);
                sum += clock.stop();
            }
            break;
        case 2:
            for (int i = 0; i < 100; ++i) {
                // drugi izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                clock.start();
                w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                sum += clock.stop();
            }
            break;
        case 3:
            for (int i = 0; i < 100; ++i) {
                // treci izraz P = M + M + N + N;
                clock.start();
                P = M + M + N + N;
                sum += clock.stop();
            }
            break;
        case 4:
            for (int i = 0; i < 100; ++i) {
                // cetvrti izraz P = (M+M)*(N+N);
                clock.start();
                P = (M+M)*(N+N);
                sum += clock.stop();
            }
            break;
    }
    std::cout << sum / 100 << " us" << std::endl;
}

void eigen_matrix(Clock& clock, std::size_t size, int izbor) {
    Eigen::MatrixXd M(size,size), N(size,size), P(size,size);
    Eigen::VectorXd y(size), x(size), z(size), w(size);
    std::cout << "Eigen matrix test(average) size(" << size << "): ";
    double sum = 0;
    switch(izbor){
        case 1:
            for (int i = 0; i < 100; ++i) {
                // prvi izraz x = (M+M)*(y+y);
                clock.start();
                x = (M+M)*(y+y);
                sum += clock.stop();
            }
            break;
        case 2:
            for (int i = 0; i < 100; ++i) {
                // drugi izraz w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                clock.start();
                w = 1.2*M*x + 2.3 * (M+N) * (3.4*y + 4.5*z);
                sum += clock.stop();
            }
            break;
        case 3:
            for (int i = 0; i < 100; ++i) {
                // treci izraz P = M + M + N + N;
                clock.start();
                P = M + M + N + N;
                sum += clock.stop();
            }
            break;
        case 4:
            for (int i = 0; i < 100; ++i) {
                // cetvrti izraz P = (M+M)*(N+N);
                clock.start();
                P = (M+M)*(N+N);
                sum += clock.stop();
            }
            break;
    }
    std::cout << sum / 100 << " us" << std::endl;
}

void menu_vect(){
    std::cout << "-------------------------" << std::endl;
    std::cout << "Odaberi tezinu testa: " << std::endl;
    std::cout << "0) Izlaz" << std::endl;
    std::cout << "1) Kratak izraz" << std::endl;
    std::cout << "2) Dug izraz" << std::endl;
}

void menu_mat(){
    std::cout << "-------------------------" << std::endl;
    std::cout << "Odaberi tezinu testa: " << std::endl;
    std::cout << "0) Izlaz" << std::endl;
    std::cout << "1) Kratak izraz (vektori + matrice)" << std::endl;
    std::cout << "2) Dug izraz (vektori + matrice)" << std::endl;
    std::cout << "3) Zbrajanje matrica" << std::endl;
    std::cout << "4) Množenje i zbrajanje matrice" << std::endl;
}

// vektori - knp
void option1(){
    Clock clock;
    int odabir;

    while(true){
        menu_vect();
        std::cin >> odabir;
        if(odabir < 0 || odabir > 2){
            std::cout << "Greška. Pokušajte ponovno." << std::endl; 
            continue;
        }

        loop_test(clock, 1000, odabir);
        bad_vector(clock, 1000, odabir);
        good_vector(clock, 1000, odabir);

        loop_test(clock, 10000, odabir);
        bad_vector(clock, 10000, odabir);
        good_vector(clock, 10000, odabir);

        loop_test(clock, 100000, odabir);
        bad_vector(clock, 100000, odabir);
        good_vector(clock, 100000, odabir);
        return;
    }
}

// matrice - knp
void option2(){
    Clock clock;
    int odabir;

    while(true){
        menu_mat();
        std::cin >> odabir;
        if(odabir < 0 || odabir > 4){
            std::cout << "Greška. Pokušajte ponovno." << std::endl; 
            continue;
        }

        loop_test_mat(clock, 32, odabir);
        bad_matrix(clock, 32, odabir);
        good_matrix(clock, 32, odabir);

        loop_test_mat(clock, 100, odabir);
        bad_matrix(clock, 100, odabir);
        good_matrix(clock, 100, odabir);

        loop_test_mat(clock, 320, odabir);
        bad_matrix(clock, 320, odabir);
        good_matrix(clock, 320, odabir);
        return;
        
    }
}

// vektori - kep
void option3(){
    Clock clock;
    int odabir;

    while(true){
        menu_vect();
        std::cin >> odabir;
        if(odabir < 0 || odabir > 2){
            std::cout << "Greška. Pokušajte ponovno." << std::endl; 
            continue;
        }

        loop_test(clock, 1000, odabir);
        eigen_vector(clock, 1000, odabir);
        good_vector(clock, 1000, odabir);

        loop_test(clock, 10'000, odabir);
        eigen_vector(clock, 10'000, odabir);
        good_vector(clock, 10'000, odabir);

        loop_test(clock, 100'000, odabir);
        eigen_vector(clock, 100'000, odabir);
        good_vector(clock, 100'000, odabir);
        return;
    }
}

// matrice - kep
void option4(){
    Clock clock;
    int odabir;

    while(true){
        menu_mat();
        std::cin >> odabir;
        if(odabir < 0 || odabir > 4){
            std::cout << "Greška. Pokušajte ponovno." << std::endl; 
            continue;
        }

        loop_test_mat(clock, 32, odabir);
        eigen_matrix(clock, 32, odabir);
        good_matrix(clock, 32, odabir);

        loop_test_mat(clock, 100, odabir);
        eigen_matrix(clock, 100, odabir);
        good_matrix(clock, 100, odabir);

        loop_test_mat(clock, 320, odabir);
        eigen_matrix(clock, 320, odabir);
        good_matrix(clock, 320, odabir);
        return;
    }
}

void menu(){
    std::cout << "-------------------------" << std::endl;
    std::cout << "Odaberi vrstu testa: " << std::endl;
    std::cout << "0) Izlaz" << std::endl;
    std::cout << "1) Vektori (komponente, naivna, predlozni)" << std::endl;
    std::cout << "2) Matrice (komponente, naivna, predlozni)" << std::endl;
    std::cout << "3) Vektori (komponente, predlozni, eigen)" << std::endl;
    std::cout << "4) Matrice (komponente, predlozni, eigen)" << std::endl;
}

int main() {

    int odabir;
    while(true){
        menu();
        std::cin >> odabir;
        switch(odabir){
            case 1: option1(); break;
            case 2: option2(); break;
            case 3: option3(); break;
            case 4: option4(); break;
            case 0: return 0;
            default: std::cout << "Greška. Pokušajte ponovno." << std::endl;
        }
    }
    return 0;
}
