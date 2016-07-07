//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      metadataPoints.cpp
//
//  \brief     GUI to define points
//
//  \author    Stian Broen
//
//  \date      19.12.2013
//
//  \par       Copyright: BroenTech AS
//
//
//
//  \par       Revision History
//
//
//             
//
//
//h-//////////////////////////////////////////////////////////////////////////

// Qt includes
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QCheckBox>
#include <QListWidget>
#include <QHBoxlayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QMap>

// solution includes
#include <ImageProcessing/metaDataKeeper.h>

// local includes
#include "metadataPoints.h"
#include "dialogBase.h"

using namespace guiSpace;
using namespace imageProcessingSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProcMetaPoints ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CImgProcMetaPoints::CImgProcMetaPoints(QWidget *parent)
:QWidget(parent),
m_doTrack(0),
m_nameLine(0),
m_x(0),
m_y(0),
m_addPoint(0),
m_removePoints(0),
m_pointList(0),
m_doShow(0)
{
   initGUI();

   connect(CMetaDataKeeper::getInstance(), SIGNAL(updateCurrPoint(const QPoint &)), 
      this, SLOT(currPoint(const QPoint &)));

   connect(CMetaDataKeeper::getInstance(), SIGNAL(metaSetMouseTracking(bool)), 
      this, SLOT(clickPoint(bool)));

   connect(CMetaDataKeeper::getInstance(), SIGNAL(pointListUpdated()), 
      this, SLOT(updateList()));

   connect(this, SIGNAL(addMetaPoint(const QString &, const QPoint &)), 
      CMetaDataKeeper::getInstance(), SLOT(addMetaPoint(const QString &, const QPoint &)));
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProcMetaPoints dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CImgProcMetaPoints::~CImgProcMetaPoints()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initGUI
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::initGUI()
{
   m_doTrack = new QCheckBox(this);

   connect(m_doTrack, SIGNAL(clicked(bool)), 
      CMetaDataKeeper::getInstance(), SLOT(setMouseTracking(bool)));
   
   m_doTrack->setText("Mouse Tracking");
   m_x = new QLabel("X:", this);
   m_y = new QLabel("Y:", this);
   QHBoxLayout *trackLay = new QHBoxLayout;

   m_doShow = new QCheckBox(this);
   m_doShow->setText("Show points");

   connect(m_doShow, SIGNAL(clicked(bool)), 
      this, SLOT(showPointsChecked(bool)));

   trackLay->addWidget(m_doTrack);
   trackLay->addWidget(m_x);
   trackLay->addWidget(m_y);
   trackLay->addStretch();
   trackLay->addWidget(m_doShow);

   QFrame* line = new QFrame();
   line->setFrameShape(QFrame::HLine);
   line->setFrameShadow(QFrame::Sunken);
   
   m_nameLine = new QLineEdit(this);
   m_nameLine->setPlaceholderText("Some point name");
   m_addPoint = new QToolButton(this);
   m_addPoint->setIcon(QIcon(":/images/plus.png"));

   connect(m_addPoint, SIGNAL(clicked()), 
      this, SLOT(addClicked()));

   m_removePoints = new QToolButton(this);
   m_removePoints->setIcon(QIcon(":/images/minus.png"));

   connect(m_removePoints, SIGNAL(clicked()), 
      this, SLOT(removeClicked()));

   QHBoxLayout *coordLay = new QHBoxLayout;
   coordLay->addWidget(m_nameLine);
   coordLay->addWidget(m_addPoint);
   coordLay->addWidget(m_removePoints);

   m_pointList = new QListWidget(this);

   QVBoxLayout *lay = new QVBoxLayout;
   lay->addLayout(trackLay);
   lay->addWidget(line);
   lay->addLayout(coordLay);
   lay->addWidget(m_pointList);
   this->setLayout(lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	currPoint
//
//
//  \param  const QPoint &pt -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::currPoint(const QPoint &pt)
{
   m_x->setText("X:" + QString::number(pt.x()));
   m_y->setText("Y:" + QString::number(pt.y()));
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	clickPoint
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::clickPoint(bool val)
{
   m_doTrack->setChecked(val);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	addClicked
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::addClicked()
{
   QString name = m_nameLine->text();
   if (name == "")
   {
      name = m_nameLine->placeholderText();
   }
   emit addMetaPoint(name, CMetaDataKeeper::getInstance()->currPoint());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	removeClicked
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::removeClicked()
{
   bool mustUpdate = false;
   QMultiHash<QString, QPoint> points = CMetaDataKeeper::getInstance()->metaPoints();
   for(int i=0; i<m_pointList->count(); i++)
   {
      QListWidgetItem *item = m_pointList->item(i);
      if (0 == item)
      {
         continue;
      }
      if(item->checkState() == Qt::Checked)
      {
         QString name = item->text();
         QStringList splt = name.split(' ');
         QStringList nameParts;
         for(int j=0; j<splt.size(); j++)
         {
            QString spltAt = splt.at(j);
            if (!spltAt.contains("X:") || !spltAt.contains("Y:"))
            {
               nameParts << spltAt;
            }
            else
            {
               if (!spltAt.contains(','))
               {
                  continue;
               }
               QString actualName = nameParts.join(' ');
               int x = spltAt.split(',').at(0).split(':').at(1).toInt();
               int y = spltAt.split(',').at(1).split(':').at(1).toInt();
               QPoint pt(x, y);
               QMutableHashIterator<QString, QPoint> k(points);
               while(k.hasNext())
               {
                  k.next();
                  const QString _name = k.key();
                  const QPoint  _pt = k.value();
                  if (_name != actualName || _pt != pt)
                  {
                     continue;
                  }
                  mustUpdate = true;
                  k.remove();
                  break;
               }
            }
         }
      }
   }

   CMetaDataKeeper::getInstance()->setMetaPoints(points);
   if (mustUpdate)
   {
      updateList();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	updateList
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::updateList()
{
   QStringList checkedIndexes;
   for(int i=0; i<m_pointList->count(); i++)
   {
      QListWidgetItem *item = m_pointList->item(i);
      if (0 == item)
      {
         continue;
      }
      if (item->checkState() == Qt::Checked)
      {
         checkedIndexes << item->text();
      }
   }
   m_pointList->clear();

   QMultiHash<QString, QPoint> points = CMetaDataKeeper::getInstance()->metaPoints();
   QHashIterator<QString, QPoint> i(points);
   while(i.hasNext())
   {
      i.next();
      const QString name = i.key();
      const QPoint pt = i.value();
      QString text = name + " " + "X:" + QString::number(pt.x()) + ",Y:" + QString::number(pt.y());
      QListWidgetItem *item = makeListItem(text, true);
      if (checkedIndexes.contains(text))
      {
         item->setCheckState(Qt::Checked);
      }
      m_pointList->addItem(item);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	showPointsChecked
//
//
//  \param  bool checked -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaPoints::showPointsChecked(bool checked)
{
   CMetaDataKeeper::getInstance()->setShowMetaPoints(checked);
}