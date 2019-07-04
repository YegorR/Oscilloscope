#include "signalsmoothing.h"

QVector<double> signalSmoothing::threePoints(QVector<QVariant> data){
    int S = data.size();
    QVector<double> out;
    for(int i=1;i<S-1;i++){
        out.push_back(0.25 * data.value(i-1).toDouble()+ 0.5 * data.value(i).toDouble()+ 0.25 * data.value(i+1).toDouble());
    }
    return out;
}

QVector<double> signalSmoothing::expFilter(QVector<QVariant> data, double coef){
    int S = data.size();
    QVector<double> out;
    out.push_back(data.value(0).toDouble());
    for(int i=1;i<S;i++){
        out.push_back(coef * data.value(i-1).toDouble() + (1 - coef) * out[i - 1]);
    }
    return out;
}

QVector<double> signalSmoothing::movAverage(QVector<QVariant> data, int order){
    int S = data.size();
    double sum1=0, sum2=0;
    QVector<double> out;
    int bufOrder = order / 2;
    if (order % 2 == 0){

        for(int i = bufOrder;i<S-bufOrder;i++){
            for (int j=-bufOrder;j<=order-bufOrder-1;j++){
                sum1+=data.value(i+j).toDouble();
            }
            for(int j=-order+bufOrder+1;j<=bufOrder;j++){
                sum2+=data.value(i+j).toDouble();
            }
            out.push_back((sum1/order + sum2/order)/2);
            sum1=0;
            sum2=0;
        }
    }
    else{
        for(int i = bufOrder;i<S-bufOrder;i++){
            for(int j=-bufOrder;j<=bufOrder;j++){
                sum1+=data.value(i+j).toDouble();
            }

            out.push_back(sum1/order);
            sum1 = 0;
        }
    }
    return out;
}
