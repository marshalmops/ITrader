#include "SettingsView.h"

SettingsView::SettingsView(QWidget *parent)
    : QDialog{parent},
      m_isSettingsChanged{false}
{
    
}

int SettingsView::exec()
{
    QDialog::exec();
    
    return (m_isSettingsChanged 
          ? QDialog::DialogCode::Accepted
          : QDialog::DialogCode::Rejected);
}
