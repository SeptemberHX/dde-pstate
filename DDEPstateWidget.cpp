//
// Created by septemberhx on 2020/5/13.
//

#include "DDEPstateWidget.h"

#include <DStyle>
#include <DGuiApplicationHelper>
#include <constants.h>

DWIDGET_USE_NAMESPACE

DDEPstateWidget::DDEPstateWidget(QWidget *parent)
    : QLabel(parent)
{
    this->setMinimumSize(PLUGIN_BACKGROUND_MIN_SIZE, PLUGIN_BACKGROUND_MIN_SIZE);
    this->m_defaultIcon = QIcon(":/icons/dde-pstate.svg");
}

void DDEPstateWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    this->updateIcon();

    QPainter painter(this);
    const QRectF &rf = QRectF(rect());
    const QRectF &rfp = QRectF(this->m_icon.rect());
    painter.drawPixmap(rf.center() - rfp.center() / this->devicePixelRatioF(), this->m_icon);
}

void DDEPstateWidget::updateIcon() {
    //    int iconSize = PLUGIN_ICON_MAX_SIZE;
//
//
//    if (rect().height() > PLUGIN_BACKGROUND_MIN_SIZE) {
//
//        QColor color;
//        if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
//            color = Qt::black;
//            painter.setOpacity(0.5);
//        } else {
//            color = Qt::white;
//            painter.setOpacity(0.1);
//        }
//
//        painter.setRenderHint(QPainter::Antialiasing, true);
//
//        DStyleHelper dstyle(style());
//        const int radius = dstyle.pixelMetric(DStyle::PM_FrameRadius);
//
//        QPainterPath path;
//
//        int minSize = std::min(width(), height());
//        QRect rc(0, 0, minSize, minSize);
//        rc.moveTo(rect().center() - rc.center());
//
//        path.addRoundedRect(rc, radius, radius);
//        painter.fillPath(path, color);
//    } else if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
//        // 最小尺寸时，不画背景，采用深色图标
//        iconName.append(PLUGIN_MIN_ICON_NAME);
//    }

    int size = std::min(width(), height());
    if (size < PLUGIN_ICON_MIN_SIZE)
        size = PLUGIN_ICON_MIN_SIZE;
    if (size > PLUGIN_BACKGROUND_MAX_SIZE) {
        size *= ((Dock::Fashion == qApp->property(PROP_DISPLAY_MODE).value<Dock::DisplayMode>()) ? 0.8 : 0.7);
        if (size < PLUGIN_BACKGROUND_MAX_SIZE)
            size = PLUGIN_BACKGROUND_MAX_SIZE;
    }

    QIcon icon = QIcon::fromTheme( "dde-pstate.svg", this->m_defaultIcon);

    const auto ratio = devicePixelRatioF();
    this->m_icon = icon.pixmap(size * ratio, size * ratio);
    this->m_icon.setDevicePixelRatio(ratio);
}
