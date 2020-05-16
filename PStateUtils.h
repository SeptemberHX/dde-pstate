//
// Created by septemberhx on 2020/5/13.
//

#ifndef DDE_PSTATE_PSTATEUTILS_H
#define DDE_PSTATE_PSTATEUTILS_H


#include <QJsonObject>
#include <QProcess>

class PStateUtils {

public:
    const static QString SCRIPT;
    const static QJsonObject readAll();

    const static void setCpuGovPerformance();
    const static void setCpuGovPowersave();
    const static void setCpuGovOndemand();

    const static void setCpuTurbo(bool enabled);
    const static void setCpuMinPerf(int cpuPerf);
    const static void setCpuMaxPerf(int cpuPerf);

    const static void setEnergyDefault();
    const static void setEnergyPerformance();
    const static void setEnergyBalancePerformance();
    const static void setEnergyBalancePowersave();
    const static void setEnergyPowersave();

    const static void setGpuMinFreq(int gpuFreq);
    const static void setGpuMaxFreq(int gpuFreq);
    const static void setGpuBoostFreq(int gpuFreq);
};


#endif //DDE_PSTATE_PSTATEUTILS_H
