#include "fft.h"

QVector<std::complex<double>> FFT::goFFT(QVector<std::complex<double>> data){
    int S = data.size();
    QVector<double> doubleData;
    QVector<std::complex<double>> out(S,0);
    for (int i = 0; i < S; i++){
        for (int j = 0; j < S; j++){
            out[i] += data[j] * std::complex<double>(cos(2 * M_PI * i * j / S), sin(2 * M_PI * i * j / S));
        }
    }
    return out;
}
