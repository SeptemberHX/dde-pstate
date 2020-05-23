//
// Created by septemberhx on 2020/5/13.
//

#include "DDEPstatePlugin.h"
#include "PStateUtils.h"
#include <QJsonObject>

#define PLUGIN_STATE_KEY "enable"

DDEPstatePlugin::DDEPstatePlugin(QObject *parent) : QObject(parent) {

}

const QString DDEPstatePlugin::pluginName() const {
    return QStringLiteral("dde_pstate");
}

void DDEPstatePlugin::init(PluginProxyInterface *proxyInter) {
    this->m_proxyInter = proxyInter;

    switch (QLocale::system().language()) {
        case QLocale::Chinese:
            this->m_translator = new QTranslator(this);
            this->m_translator->load(":/translations/app_zh.qm");
            qApp->installTranslator(this->m_translator);
            break;
        case QLocale::Spanish:
            this->m_translator = new QTranslator(this);
            this->m_translator->load(":/translations/app_es.qm");
            qApp->installTranslator(this->m_translator);
            break;
        default:
            break;
    }

    this->m_pluginWidget = new DDEPstateWidget();
    this->m_tipsWidget = new QLabel();
    this->m_appletWidget = new PstateMainWidget();

    if (!pluginIsDisable()) {
        this->m_proxyInter->itemAdded(this, this->pluginName());
    }
}

QWidget *DDEPstatePlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey)
    return this->m_pluginWidget;
}

bool DDEPstatePlugin::pluginIsAllowDisable() {
    return true;
}

bool DDEPstatePlugin::pluginIsDisable() {
    return !(m_proxyInter->getValue(this, PLUGIN_STATE_KEY, true).toBool());
}

void DDEPstatePlugin::pluginStateSwitched() {
    m_proxyInter->saveValue(this, PLUGIN_STATE_KEY, pluginIsDisable());

    if (pluginIsDisable()) {
        m_proxyInter->itemRemoved(this, pluginName());
        return;
    }

    if (m_pluginWidget) {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

const QString DDEPstatePlugin::pluginDisplayName() const {
    return QStringLiteral("DDE Pstate");
}

QWidget *DDEPstatePlugin::itemTipsWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);
    QJsonObject allData = PStateUtils::readAll();

    QString gov = allData["cpu_governor"].toString();
    if (gov == "performance") {
        m_tipsWidget->setText(tr("performance"));
    } else if (gov == "powersave") {
        m_tipsWidget->setText(tr("powersave"));
    } else {
        m_tipsWidget->setText("DDE Pstate");
    }

    return m_tipsWidget;
}

QWidget *DDEPstatePlugin::itemPopupApplet(const QString &itemKey) {
    Q_UNUSED(itemKey)

    this->m_appletWidget->refresh();
    return this->m_appletWidget;
}

int DDEPstatePlugin::itemSortKey(const QString &itemKey) {
    Q_UNUSED(itemKey)

    const QString key = QString("pos_%1").arg(Dock::Efficient);
    return m_proxyInter->getValue(this, key, 5).toInt();
}

void DDEPstatePlugin::setSortKey(const QString &itemKey, const int order) {
    Q_UNUSED(itemKey)

    const QString key = QString("pos_%1").arg(Dock::Efficient);
    m_proxyInter->saveValue(this, key, order);
}

void DDEPstatePlugin::pluginSettingsChanged() {
    if (pluginIsDisable()) {
        m_proxyInter->itemRemoved(this, pluginName());
        return;
    }

    if (m_pluginWidget) {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

void DDEPstatePlugin::refreshIcon(const QString &itemKey) {
    Q_UNUSED(itemKey)

    this->m_pluginWidget->updateIcon();
}
