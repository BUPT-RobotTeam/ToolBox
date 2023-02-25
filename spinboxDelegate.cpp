//
// Created by LiNY2 on 2023/02/20 0020.
//

#include "spinboxDelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *parent ,double min,
                                 double max,double step,
                                 double defaultVal,int prec)
    : QStyledItemDelegate(parent),
    spinBox_Min(min),spinBox_Max(max),
    spinBox_SingleStep(step),spinBox_defaultVal(defaultVal),spinBox_prec(prec)
{

}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    auto *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setRange(spinBox_Min,spinBox_Max);
    editor->setDecimals(spinBox_prec);
    editor->setSingleStep(spinBox_SingleStep);
    editor->setValue(spinBox_defaultVal);
    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();

    auto *spinBox = dynamic_cast<QDoubleSpinBox*>(editor);

    spinBox->setValue(value);
    spinBox->setDecimals(spinBox_prec);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    auto *spinBox = dynamic_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    auto value = spinBox->value();

    model->setData(index, value, Qt::EditRole);

}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
