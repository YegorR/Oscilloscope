#include "fft.h"

QVector<double> FFT::goFFT(QVector<QVariant> data){
    int S = data.size();
    QVector<double> doubleData;
    for (int i=0;i<S;i++){
        doubleData.push_front(data.value(i).toDouble());
    }
    QVector<std::complex<double>> buffer(S,0);
    QVector<double> out(S,0);
    for (int i = 0; i < S; i++){
        buffer[i] = std::complex<double>(0.0, 0.0);
        for (int j = 0; j < S; j++){
            buffer[i] += doubleData[j] * std::complex<double>(cos(2 * M_PI * i * j / S), sin(2 * M_PI * i * j / S));
        }
        out[i] = sqrt(pow(buffer[i].real(),2)+pow(buffer[i].imag(),2));
    }
    return out;
}
