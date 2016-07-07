//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      metadataGeneral.cpp
//
//  \brief     GUI to general metadata operations
//
//  \author    Stian Broen
//
//  \date      06.12.2013
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
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

// solution includes
#include <ImageProcessing/metaDataKeeper.h>

// local includes
#include "metadataGeneral.h"

using namespace guiSpace;
using namespace imageProcessingSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProcMetaGeneral ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CImgProcMetaGeneral::CImgProcMetaGeneral(QWidget *parent)
:QWidget(parent),
m_freezeMeta(0),
m_clearMeta(0),
m_storeMeta(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProcMetaGeneral dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CImgProcMetaGeneral::~CImgProcMetaGeneral()
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
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaGeneral::initGUI()
{
   m_freezeMeta = new QPushButton(this);
   m_freezeMeta->setText("Freeze");
   m_freezeMeta->setCheckable(true);
   m_freezeMeta->setChecked(false);

   connect(m_freezeMeta, SIGNAL(clicked()), 
      this, SLOT(freezeClicked()));

   m_clearMeta = new QPushButton(this);
   m_clearMeta->setText("Clear");

   connect(m_clearMeta, SIGNAL(clicked()), 
      CMetaDataKeeper::getInstance(), SLOT(metaClear()));

   m_storeMeta = new QPushButton(this);
   m_storeMeta->setText("Store");

   connect(m_storeMeta, SIGNAL(clicked()), 
      CMetaDataKeeper::getInstance(), SLOT(metaStore()));

   connect(this, SIGNAL(freeze(bool)), 
      CMetaDataKeeper::getInstance(), SLOT(freeze(bool)));

   QVBoxLayout *blay = new QVBoxLayout;
   blay->addWidget(m_freezeMeta);
   blay->addWidget(m_clearMeta);
   blay->addWidget(m_storeMeta);

   this->setLayout(blay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	freezeClicked
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CImgProcMetaGeneral::freezeClicked()
{
   emit freeze(m_freezeMeta->isChecked());
}