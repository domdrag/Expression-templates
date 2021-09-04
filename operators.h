#pragma once

template <typename T, typename R1, typename R2, bool M1, bool M2>
Vector<T, Add<T, R1, R2>, M1+M2> operator+ (const Vector<T, R1, M1>& a, const Vector<T, R2, M2>& b) {
    return Vector<T, Add<T, R1, R2>, M1+M2>(Add<T, R1, R2>(a.rep(), b.rep()));
}

template <typename T, typename R1, typename R2, bool M1, bool M2>
Vector<T, Mult<T, R1, R2>, M1+M2> operator* (const Vector<T, R1, M1>& a, const Vector<T, R2, M2>& b) {
    return Vector<T, Mult<T, R1, R2>, M1+M2 >(Mult<T, R1, R2>(a.rep(), b.rep()));
}

template <typename T, typename R2, bool M2>
Vector<T, Mult<T, Scalar<T>, R2>, M2 > operator* (const T& s, const Vector<T, R2, M2>& b) {
    return Vector<T, Mult<T, Scalar<T>, R2>, M2>(Mult<T, Scalar<T>, R2>(Scalar<T>(s), b.rep()));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename R1, typename R2>
Matrix<T, Add<T, R1, R2> > operator+ (const Matrix<T, R1>& a, const Matrix<T, R2>& b) {
    return Matrix<T, Add<T, R1, R2> >(Add<T, R1, R2>(a.rep(), b.rep()));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename R1, typename R2>
Matrix<T> operator* (const Matrix<T, R1>& a, const Matrix<T, R2>& b) {
    Matrix<T> new_a(a);
    Matrix<T> new_b(b);

    Matrix<T> result(a.rows(), b.columns());
    for(int idx = 0; idx < a.rows(); ++idx){
        for(int idz = 0; idz < a.columns(); ++idz){
            for(int idy = 0; idy < b.columns(); ++idy){
                result(idx,idy) += new_a(idx,idz) * new_b(idz,idy);
            }
        }
    } 

    return result;
}

template <typename T, typename R2>
Matrix<T> operator* (const Matrix<T, SMatrix<T>>& a, const Matrix<T, R2>& b) {
    Matrix<T> new_b(b);

    Matrix<T> result(a.rows(), b.columns());
    for(int idx = 0; idx < a.rows(); ++idx){
        for(int idz = 0; idz < a.columns(); ++idz){
            for(int idy = 0; idy < b.columns(); ++idy){
                result(idx,idy) += a(idx,idz) * new_b(idz,idy);
            }
        }
    }

    return result;
}

template <typename T, typename R1>
Matrix<T> operator* (const Matrix<T, R1>& a, const Matrix<T, SMatrix<T>>& b) {
    Matrix<T> new_a(a);

    Matrix<T> result(a.rows(), b.columns());
    for(int idx = 0; idx < a.rows(); ++idx){
        for(int idz = 0; idz < a.columns(); ++idz){
            for(int idy = 0; idy < b.columns(); ++idy){
                result(idx,idy) += new_a(idx,idz) * b(idz,idy);
            }
        }
    }

    return result;
}

template <typename T>
Matrix<T> operator* (const Matrix<T, SMatrix<T> >& a, const Matrix<T, SMatrix<T> >& b) {
    Matrix<T> result(a.rows(), b.columns());

    for(int idx = 0; idx < a.rows(); ++idx){
        for(int idz = 0; idz < a.columns(); ++idz){
            for(int idy = 0; idy < b.columns(); ++idy){
                result(idx,idy) += a(idx,idz) * b(idz,idy);
            }
        }
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename R2>
Matrix<T, Mult<T, Scalar<T>, R2> > operator* (const T& s, const Matrix<T, R2>& b) {
    return Matrix<T, Mult<T, Scalar<T>, R2> >
        (Mult<T, Scalar<T>, R2>(Scalar<T>(s), b.rep()));
}

template <typename T, typename R1, typename R2, bool M2>
Vector<T, Mat_Mult<T, R1, R2>, true> operator* (const Matrix<T, R1>& a, const Vector<T, R2, M2>& b) {
    return Vector<T, Mat_Mult<T, R1, R2>, true>(Mat_Mult<T, R1, R2>(a.rep(), b.rep()));
}
