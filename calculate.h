#ifndef CALCULATE_H
#define CALCULATE_H

#include <QWidget>
 #include <QStack>
 #include <QLabel>
 #include <QPushButton>
 #include <QGridLayout>
#include <QRegularExpression>
#include <QPalette>

 class Calculator : public QWidget {
  Q_OBJECT
  private:
   QLabel *displaystring;
   QStack <QString> stack;
  public:
   Calculator (QWidget* pwgt = 0);
   QPushButton* createButton (const QString& str);
   void calculate ();
  public slots:
   void slotButtonClicked ();
 };

#endif // CALCULATE_H
