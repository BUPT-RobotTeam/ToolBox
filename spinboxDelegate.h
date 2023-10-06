/**
 * @author liny2
 * @brief 表格spinbox编辑器代理头文件
 */

#ifndef CMAKELISTS_TXT_SPINBOXDELEGATE_H
#define CMAKELISTS_TXT_SPINBOXDELEGATE_H

#include <QObject>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QItemDelegate>
#include <QApplication>
#include <QStyledItemDelegate>
#include <QStyleOption>
#include <QMouseEvent>
#include <QPainter>
#include <QDateTimeEdit>
/**
 * 表格spinbox编辑器代理头文件
 */
class SpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SpinBoxDelegate(QObject *parent = nullptr,double min=0.00,
                             double max=99.99,double step=0.1,
                             double defaultVal=0.5,int prec=3);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void setSpinBoxMin(double spinBoxMin) {
        spinBox_Min = spinBoxMin;
    }

    void setSpinBoxMax(double spinBoxMax) {
        spinBox_Max = spinBoxMax;
    }

    void setSpinBoxSingleStep(double spinBoxSingleStep) {
        spinBox_SingleStep = spinBoxSingleStep;
    }

    void setSpinBoxDefaultVal(double spinBoxDefaultVal) {
        spinBox_defaultVal = spinBoxDefaultVal;
    }

    void setSpinBoxPrec(int spinBoxPrec) {
        spinBox_prec = spinBoxPrec;
    }

private:
    double spinBox_Min{},spinBox_Max{},spinBox_SingleStep{},spinBox_defaultVal{};
    int spinBox_prec{};
};

#endif //CMAKELISTS_TXT_SPINBOXDELEGATE_H
