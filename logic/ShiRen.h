#ifndef SHIREN_H
#define SHIREN_H
#include "Role.h"

class ShiRen: public Role{
    Q_OBJECT
public:
    ShiRen();
    void normal();
    void askForSkill(network::Command* cmd);
    void ChenLunXieZouQu();
    void XiWangFuGeQu(int id);
    void BuXieHeXianTarget();
public slots:
    void onOkClicked();
    void onCancelClicked();
    void cardAnalyse();
    void BuXieHeXian();
private:
    int chenLunNum;
};
#endif // SHIREN_H
