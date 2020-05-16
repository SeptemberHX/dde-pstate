//
// Created by septemberhx on 2020/5/13.
//

#include "PStateUtils.h"
#include <QJsonDocument>
#include <QDebug>

const QString PStateUtils::SCRIPT = "/opt/dde-dock/scripts/set_prefs.sh";

const QJsonObject PStateUtils::readAll() {
    QProcess m_process;
    m_process.start(SCRIPT, QStringList() << "-read-all");
    m_process.waitForFinished();
    QByteArray result = m_process.readAll();
    return QJsonDocument::fromJson(result).object();
}

const void PStateUtils::setCpuGovPerformance() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-cpu-governor" << "performance");
    m_process.waitForFinished();
}

const void PStateUtils::setCpuGovPowersave() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-cpu-governor" << "powersave");
    m_process.waitForFinished();
}

const void PStateUtils::setCpuMinPerf(int cpuPerf) {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-cpu-min-perf" << QString::number(cpuPerf));
    m_process.waitForFinished();
}

const void PStateUtils::setCpuMaxPerf(int cpuPerf) {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-cpu-max-perf" << QString::number(cpuPerf));
    m_process.waitForFinished();
}

const void PStateUtils::setCpuGovOndemand() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-cpu-governor" << "ondemand");
    m_process.waitForFinished();
}

const void PStateUtils::setCpuTurbo(bool enabled) {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-cpu-turbo" << (enabled ? "true" : "false"));
    m_process.waitForFinished();
}

const void PStateUtils::setEnergyDefault() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-energy-perf" << "default");
    m_process.waitForFinished();
}

const void PStateUtils::setEnergyPerformance() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-energy-perf" << "performance");
    m_process.waitForFinished();
}

const void PStateUtils::setEnergyBalancePerformance() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-energy-perf" << "balance_performance");
    m_process.waitForFinished();
}

const void PStateUtils::setEnergyBalancePowersave() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-energy-perf" << "balance_power");
    m_process.waitForFinished();
}

const void PStateUtils::setEnergyPowersave() {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-energy-perf" << "power");
    m_process.waitForFinished();
}

const void PStateUtils::setGpuMinFreq(int gpuFreq) {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-gpu-min-freq" << QString::number(gpuFreq));
    m_process.waitForFinished();
}

const void PStateUtils::setGpuMaxFreq(int gpuFreq) {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-gpu-max-freq" << QString::number(gpuFreq));
    m_process.waitForFinished();
}

const void PStateUtils::setGpuBoostFreq(int gpuFreq) {
    QProcess m_process;
    m_process.start("pkexec", QStringList() << SCRIPT << "-gpu-boost-freq" << QString::number(gpuFreq));
    m_process.waitForFinished();
}
