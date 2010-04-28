#include "selectcalldialog.h"
#include <QFileInfo>

SelectCallDialog::SelectCallDialog(QContentFilter filter, QWidget *parent, Qt::WFlags f)
	: QDialog( parent, f )
{

    documentSelector = new QDocumentSelector;
    documentSelector->setFilter( filter );
    QFileInfo file(".");
    qDebug() << file.absolutePath ();

    

    connect( documentSelector, SIGNAL(documentSelected(QContent)),
                 this, SLOT(openDocument(QContent)) );

    layout = new QStackedLayout( this );

    layout->addWidget( documentSelector );

}

SelectCallDialog::~SelectCallDialog(){
}

void SelectCallDialog::openDocument(QContent document){
    emit documentSelected(document);
}