#ifndef ONENODE_H
#define ONENODE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OneNode; }
QT_END_NAMESPACE

class OneNode : public QMainWindow
{
    Q_OBJECT

public:
    OneNode(QWidget *parent = nullptr);
    ~OneNode();

private:
    Ui::OneNode *ui;
};
#endif // ONENODE_H
