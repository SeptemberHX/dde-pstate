//
// Created by septemberhx on 2020/5/13.
//

#ifndef DDE_PSTATE_DDEPSTATEWIDGET_H
#define DDE_PSTATE_DDEPSTATEWIDGET_H


#include <QLabel>
#include <QIcon>

// If we inherit from QWidget, we will get QWidget::setMinimumSize negative sizes are not possible warning,
//  and the tray widget will disappears
class DDEPstateWidget : public QLabel {
    Q_OBJECT

public:
    explicit DDEPstateWidget(QWidget *parent = nullptr);
    void updateIcon();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_icon;
    QIcon m_defaultIcon;
};


#endif //DDE_PSTATE_DDEPSTATEWIDGET_H
