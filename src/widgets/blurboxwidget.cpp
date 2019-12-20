/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     niecheng <niejiashan@163.com>
 *
 * Maintainer: niecheng <niejiashan@163.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "blurboxwidget.h"
#include "src/global_util/calculate_util.h"

#include <QPainter>

DWIDGET_USE_NAMESPACE
BlurBoxWidget::BlurBoxWidget(AppsListModel::AppCategory curCategory, char *name, QWidget *parent)
    : DBlurEffectWidget(parent)
    , m_vLayout(new QVBoxLayout(this))
    , m_maskLayer(new MaskQWidget(this))
    , m_calcUtil(CalculateUtil::instance())
    , m_category(curCategory)
    , m_name(name)
    , m_categoryMultiPagesView(new MultiPagesView(curCategory))
    , m_categoryTitle(new CategoryTitleWidget(QApplication::translate("MiniCategoryWidget", name)))
{
    setMaskColor(LightColor);
    setMaskAlpha(DLauncher::APPHBOX_ALPHA);
    setBlurRectXRadius(DLauncher::APPHBOX_RADIUS);
    setBlurRectYRadius(DLauncher::APPHBOX_RADIUS);
    setFixedWidth(m_calcUtil->getAppBoxSize().width());

    setLayout(m_vLayout);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_vLayout->setAlignment(Qt::AlignTop);
    layoutAddWidget(m_categoryTitle, m_calcUtil->getAppBoxSize().width() / 2, Qt::AlignHCenter);
    m_vLayout->addWidget(m_categoryMultiPagesView);
}

void BlurBoxWidget::layoutAddWidget(QWidget *child)
{
    m_vLayout->addWidget(child);
}

void BlurBoxWidget::layoutAddWidget(QWidget *child, int stretch, Qt::Alignment alignment)
{
    m_vLayout->addWidget(child, stretch, alignment);
}

MultiPagesView *BlurBoxWidget::getMultiPagesView()
{
    return m_categoryMultiPagesView;
}

void BlurBoxWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePos = e->pos();
    }
}

void BlurBoxWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && e->pos() == mousePos) {
        int nNext = 0;
        if (m_calcUtil->getScreenSize().width() / 2 < e->globalX()) {
            nNext = 1;
        } else {
            nNext = -1;
        }
        emit maskClick(m_category, nNext);
    }
}

void BlurBoxWidget::setMaskSize(QSize size)
{
    m_maskLayer->setFixedSize(size);
    m_maskLayer->raise();
    m_maskLayer->move(0, -5);
}

void BlurBoxWidget::setDataDelegate(QAbstractItemDelegate *delegate)
{
    m_categoryMultiPagesView->setAccessibleName(m_name);
    m_categoryMultiPagesView->setDataDelegate(delegate);
    m_categoryMultiPagesView->updatePageCount(m_category);
}

void BlurBoxWidget::setMaskVisible(bool visible)
{
    m_maskLayer->setVisible(visible);
}


