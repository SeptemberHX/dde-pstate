#include "PstateMainWidget.h"
#include "ui_PstateMainWidget.h"
#include "PStateUtils.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


PstateMainWidget::PstateMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PstateMainWidget)
{
    ui->setupUi(this);

    connect(ui->minPerfSlider, &QSlider::valueChanged, this, &PstateMainWidget::setMinPerfLabel);
    connect(ui->maxPerfSlider, &QSlider::valueChanged, this, &PstateMainWidget::setMaxPerfLabel);

    connect(ui->minPerfSlider, &QSlider::sliderReleased, this, &PstateMainWidget::setMinPerf);
    connect(ui->maxPerfSlider, &QSlider::sliderReleased, this, &PstateMainWidget::setMaxPerf);

    connect(ui->turboCheckBox, &QCheckBox::clicked, this, &PstateMainWidget::setTurbo);

    this->m_cpuGovGroup = new QButtonGroup(this);
    this->m_cpuGovGroup->addButton(ui->cpuPerfToolButton);
    this->m_cpuGovGroup->addButton(ui->cpuPowerToolButton);
    this->m_cpuGovGroup->addButton(ui->cpuOndemandToolButton);
    connect(this->m_cpuGovGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &PstateMainWidget::setCpuGov);

    this->m_energyGroup = new QButtonGroup(this);
    this->m_energyGroup->addButton(ui->energyDefaultToolButton);
    this->m_energyGroup->addButton(ui->energyPerfToolButton);
    this->m_energyGroup->addButton(ui->energyBalancePerfToolButton);
    this->m_energyGroup->addButton(ui->energyBalancePowersaveToolButton);
    this->m_energyGroup->addButton(ui->energyPowersaveToolButton);
    connect(this->m_energyGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &PstateMainWidget::setEnergy);

    this->refresh();
}

PstateMainWidget::~PstateMainWidget()
{
    delete ui;
}

void PstateMainWidget::setMinPerfLabel(int cpuPerf) {
    ui->minPerfLabel->setText(QString::number(cpuPerf) + "%");
}

void PstateMainWidget::setMaxPerfLabel(int cpuPerf) {
    ui->maxPerfLabel->setText(QString::number(cpuPerf) + "%");
}

void PstateMainWidget::refresh() {
    QJsonObject dataJson = PStateUtils::readAll();

    ui->cpuPowerToolButton->setHidden(true);
    ui->cpuPerfToolButton->setHidden(true);
    ui->cpuOndemandToolButton->setHidden(true);
    QJsonArray govArray = dataJson["available_gov"].toArray();
    for (auto iter = govArray.begin(); iter != govArray.end(); ++iter) {
        if (iter->toString() == "performance") {
            ui->cpuPerfToolButton->setHidden(false);
        } else if (iter->toString() == "powersave") {
            ui->cpuPowerToolButton->setHidden(false);
        } else if (iter->toString() == "ondemand") {
            ui->cpuOndemandToolButton->setHidden(false);
        }
    }

    QString cpuGov = dataJson["cpu_governor"].toString();
    if (cpuGov == "performance") {
        ui->cpuPerfToolButton->setChecked(true);
    } else if (cpuGov == "powersave") {
        ui->cpuPowerToolButton->setChecked(true);
    } else if (cpuGov == "ondemand") {
        ui->cpuOndemandToolButton->setChecked(true);
    }

    ui->turboCheckBox->setChecked(dataJson["cpu_turbo"].toString() == "true");
    ui->minPerfSlider->setValue(dataJson["cpu_min_perf"].toString().toInt());
    ui->maxPerfSlider->setValue(dataJson["cpu_max_perf"].toString().toInt());

    ui->energyBalancePerfToolButton->hide();
    ui->energyPowersaveToolButton->hide();
    ui->energyBalancePowersaveToolButton->hide();
    ui->energyPerfToolButton->hide();
    ui->energyDefaultToolButton->hide();
    QJsonArray energyArray = dataJson["available_energy"].toArray();
    for (auto iter = energyArray.begin(); iter != energyArray.end(); ++iter) {
        if (iter->toString() == "default") {
            ui->energyDefaultToolButton->show();
        } else if (iter->toString() == "performance") {
            ui->energyPerfToolButton->show();
        } else if (iter->toString() == "balance_performance") {
            ui->energyBalancePerfToolButton->show();
        } else if (iter->toString() == "balance_power") {
            ui->energyBalancePowersaveToolButton->show();
        } else if (iter->toString() == "power") {
            ui->energyPowersaveToolButton->show();
        }
    }

    QString energy = dataJson["energy_perf"].toString();
    if (energy == "default") {
        ui->energyDefaultToolButton->setChecked(true);
    } else if (energy == "performance") {
        ui->energyPerfToolButton->setChecked(true);
    } else if (energy == "balance_performance") {
        ui->energyBalancePerfToolButton->setChecked(true);
    } else if (energy == "balance_power") {
        ui->energyBalancePowersaveToolButton->setChecked(true);
    } else if (energy == "power") {
        ui->energyPowersaveToolButton->setChecked(true);
    }
}

void PstateMainWidget::setCpuGov(int buttonId) {
    if (this->m_cpuGovGroup->id(ui->cpuPowerToolButton) == buttonId) {
        qDebug() << "CPU PowerSave Gov";
        PStateUtils::setCpuGovPowersave();
    } else if (this->m_cpuGovGroup->id(ui->cpuPerfToolButton) == buttonId) {
        qDebug() << "CPU Performance Gov";
        PStateUtils::setCpuGovPerformance();
    } else if (this->m_cpuGovGroup->id(ui->cpuOndemandToolButton) == buttonId) {
        qDebug() << "CPU Ondemand Gov";
        PStateUtils::setCpuGovOndemand();
    }

    this->refresh();
}

void PstateMainWidget::setMinPerf() {
    PStateUtils::setCpuMinPerf(ui->minPerfSlider->value());
    this->refresh();
}

void PstateMainWidget::setMaxPerf() {
    PStateUtils::setCpuMaxPerf(ui->maxPerfSlider->value());
    this->refresh();
}

void PstateMainWidget::setTurbo(bool flag) {
    qDebug() << "CPU Turbo" << flag;
    PStateUtils::setCpuTurbo(flag);
    this->refresh();
}

void PstateMainWidget::setEnergy(int buttonId) {
    if (this->m_energyGroup->id(ui->energyDefaultToolButton) == buttonId) {
        qDebug() << "Energy Default";
        PStateUtils::setEnergyDefault();
    } else if (this->m_energyGroup->id(ui->energyPerfToolButton) == buttonId) {
        qDebug() << "Energy Performance";
        PStateUtils::setEnergyPerformance();
    } else if (this->m_energyGroup->id(ui->energyBalancePerfToolButton) == buttonId) {
        qDebug() << "Energy Balance Performance";
        PStateUtils::setEnergyBalancePerformance();
    } else if (this->m_energyGroup->id(ui->energyBalancePowersaveToolButton) == buttonId) {
        qDebug() << "Energy Balance Power";
        PStateUtils::setEnergyBalancePowersave();
    } else if (this->m_energyGroup->id(ui->energyPowersaveToolButton) == buttonId) {
        qDebug() << "Energy Power";
        PStateUtils::setEnergyPowersave();
    }

    this->refresh();
}
