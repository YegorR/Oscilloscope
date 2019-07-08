#include "signalsmoothing.h"

QVector<std::complex<double>> signalSmoothing::threePoints(QVector<std::complex<double>> data){
    int S = data.size();
    QVector<std::complex<double>> out;
    std::complex<double> buffer;
    for(int i=1;i<S-1;i++){
        buffer.real(0.25 * data[i-1].real()+ 0.5 * data[i].real()+ 0.25 * data[i+1].real());
        buffer.imag(0.25 * data[i-1].imag()+ 0.5 * data[i].imag()+ 0.25 * data[i+1].imag());
        out.push_back(buffer);
    }
    return out;
}

QVector<std::complex<double>> signalSmoothing::expFilter(QVector<std::complex<double>> data, double coef){
    int S = data.size();
    QVector<std::complex<double>> out;
    std::complex<double> buffer;
    buffer.real(data[0].real());
    buffer.imag(data[0].imag());
    out.push_back(buffer);
    for(int i=1;i<S;i++){
        buffer.real(data[i-1].real());
        buffer.imag(data[i-1].imag());
        out.push_back(buffer);
    }
    return out;
}

QVector<std::complex<double>> signalSmoothing::movAverage(QVector<std::complex<double>> data, int order){
    int S = data.size();
    double sum1Re=0, sum2Re=0, sum1Im=0, sum2Im;
    QVector<std::complex<double>> out;
    std::complex<double> buffer;
    int bufOrder = order / 2;
    if (order % 2 == 0){

        for(int i = bufOrder;i<S-bufOrder;i++){
            for (int j=-bufOrder;j<=order-bufOrder-1;j++){
                sum1Re+=data[i+j].real();
                sum1Im+=data[i+j].imag();
            }
            for(int j=-order+bufOrder+1;j<=bufOrder;j++){
                sum2Re+=data[i+j].real();
                sum2Im+=data[i+j].imag();
            }
            buffer.real((sum1Re/order+sum2Re/order)/2);
            buffer.imag((sum1Im/order+sum2Im/order)/2);
            out.push_back(buffer);
            sum1Re=0;
            sum2Re=0;
            sum1Im=0;
            sum2Im=0;
        }
    }
    else{
        for(int i = bufOrder;i<S-bufOrder;i++){
            for(int j=-bufOrder;j<=bufOrder;j++){
                sum1Re+=data[i+j].real();
                sum1Im+=data[i+j].imag();
            }
            buffer.real(sum1Re/order);
            buffer.imag(sum1Im/order);
            out.push_back(buffer);
            sum1Re = 0;
            sum1Im = 0;
        }
    }
    return out;
}
