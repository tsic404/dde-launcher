#ifndef BLURBOXWIDGET_H
#define BLURBOXWIDGET_H

#include <dblureffectwidget.h>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "src/global_util/constants.h"
#include  "src/global_util/calculate_util.h"
#include "qapplication.h"

DWIDGET_USE_NAMESPACE

class BlurBoxWidget : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit BlurBoxWidget(QWidget *parent = nullptr);
    Q_PROPERTY(AppsListModel::AppCategory category READ getCategory WRITE setCategory)

    void setMaskVisible(bool visible);
    void setMaskSize(QSize size);
    QVBoxLayout *m_vLayout ;
    QWidget *m_maskLayer = nullptr;

public :
    void initconnect();
    void layoutAddWidget(QWidget *child);
    void layoutAddWidget(QWidget *, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
    void setCategory(AppsListModel::AppCategory setcategory) {category = setcategory;}
    AppsListModel::AppCategory getCategory() {return category;}

signals:
    void maskClick(AppsListModel::AppCategory category, int nNext);


protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    CalculateUtil *m_calcUtil;
    AppsListModel::AppCategory category;

private:
    QPoint mousePos;
};

#endif // BLURBOXWIDGET_H
