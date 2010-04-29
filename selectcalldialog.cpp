#include "selectcalldialog.h"
#include <QFileInfo>
#include <QDir>
#include <iostream>

SelectCallDialog::SelectCallDialog(QString selected, QString extension, QString defaultName, QWidget *parent, Qt::WFlags f)
	: QDialog( parent, f )
{
    setupUi(this);
    


    dir = QDir::home();
    dir.cd("Documents");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    if(defaultName != ""){
       filesListWidget->item(0)->setText(defaultName);
    }

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                .arg(fileInfo.fileName()));
        if(fileInfo.fileName().endsWith(extension)){
            filesListWidget->addItem( fileInfo.fileName() );
        }
    }
    if(filesListWidget->findItems(selected, Qt::MatchExactly).size()>0) {
        filesListWidget->setCurrentItem(filesListWidget->findItems(selected, Qt::MatchExactly).at(0));
    }
}

SelectCallDialog::~SelectCallDialog(){
}

void SelectCallDialog::on_selectPushButton_clicked(){
    QListWidgetItem * current = filesListWidget->currentItem ();
    emit fileSelected(current->text());
    close();
}

void SelectCallDialog::on_cancelPushButton_clicked(){
    close();
}
