#include "AutomaticDifferentiation.hpp"
#include "Minimization.hpp"

int main(int argc, char** argv)
/**
    solve Y=L*U,
    where L is a lower triagle matrix, U is a upper one.
*/
{
    using namespace AutomaticDifferentiation;

    /// define Y
    MatFuncPtr<double> Y(2,2);
    Y(0,0)=FuncPtr<double>(new Constant(1.0));
    Y(0,1)=FuncPtr<double>(new Constant(1.0));
    Y(1,0)=FuncPtr<double>(new Constant(1.1));
    Y(1,1)=FuncPtr<double>(new Constant(2.2));

    auto e=createVariables<double>(6);

    MatFuncPtr<double> L(2,2);
    L(0,0)=e[0];
    L(0,1)=FuncPtr<double>(new Constant(0.0));
    L(1,0)=e[1];
    L(1,1)=e[2];

    MatFuncPtr<double> U(2,2);
    U(0,0)=e[3];
    U(0,1)=e[4];
    U(1,0)=FuncPtr<double>(new Constant(0.0));
    U(1,1)=e[5];

    auto f=(L*U-Y).norm2();

    std::cout << toString(f) << std::endl;

    Eigen::VectorXd x_val(6);
    x_val << 1.0,1.0,1.0,1.0,1.0,1.0;
//    Minimization::gradient_descent(f,x_val);
    Minimization::newton(f,x_val);
    std::cout << "x_val:" << std::endl << x_val << std::endl;
}
