#include "trigger.h"
#include <QDebug>

namespace oscilloscope {
    QVector<std::complex<double>> Trigger::triggerByForwardFront(QVector<std::complex<double>> data, double level, bool isReal) {
        QVector<std::complex<double>> out;
    int S = data.size();
    for (int i=1; i<S; i++){
        if(isReal){
            if((data[i].real()-data[i-1].real())>0){
                if(data[i].real()>=level){
                    for(int j=i;j<data.size();j++){
                        out.push_back(data[j].real());}
                break;
                }
            }
        }
        else{
            if((data[i].imag()-data[i-1].imag())>0){
                if(data[i].imag()>=level){
                    for(int j=i;j<data.size();j++){
                        out.push_back(data[j].imag());}
                break;
                }
            }
        }

        return out;
    }

    QVector<std::complex<double>> Trigger::triggerByBackFront(QVector<std::complex<double>> data, double level, bool isReal) {
        QVector<std::complex<double>> out;
    int S = data.size();
    for (int i=0; i<S-1; i++){
        if(isReal){
            if((data[i+1].real()-data[i].real())<0){
                if(data[i].real()>=level){
                    for(int j=i;j<data.size();j++){
                        out.push_back(data[j].real());}
                break;
                }
            }
        }
        else{
            if((data[i+1].imag()-data[i].imag())>0){
                if(data[i].imag()>=level){
                    for(int j=i;j<data.size();j++){
                        out.push_back(data[j].imag());}
                break;
                }
            }
        }

        return out;
    }

    QVector<std::complex<double>> Trigger::triggerByTime(QVector<std::complex<double>> data, double time, double step) {
        QVector<std::complex<double>> out;
        int S = data.size(), count = 0;
        double i = 0;

        while (i < time) {
            i += step;
            count++;
        }

        for (int j = count; j < S; j++)
            out.push_back(data[j]);

        return out;
    }
}
