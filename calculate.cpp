#include "calculate.h"

Calculator::Calculator (QWidget *parent) : QWidget(parent) {
 displaystring = new QLabel("");
 displaystring->setMinimumSize (150, 50);
 QChar aButtons[4][4] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'0', '.', '=', '+'}
 };

 QGridLayout *myLayout = new QGridLayout;
 myLayout->addWidget(displaystring, 0, 0, 1, 4);
 myLayout->addWidget(createButton("D"), 1, 3);
 myLayout->addWidget(createButton("C"), 1, 0);
 myLayout->addWidget(createButton(""), 1, 1);
 myLayout->addWidget(createButton(""), 1, 2);
 for (int i = 0; i < 4; ++i) {
  for (int j = 0; j < 4; ++j) {
   myLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
  }
 }
 setLayout(myLayout);
}

QPushButton* Calculator::createButton (const QString& str) {
 QPushButton* pcmd = new QPushButton(str);
 pcmd->setMinimumSize(40, 40);
 if(str == "C" || str == "D" || str == ""){
     QPalette pal = pcmd->palette();
     pal.setColor(QPalette::Button,Qt::red);
     pcmd->setPalette(pal);
 }
 else{
     QPalette pal = pcmd->palette();
     pal.setColor(QPalette::Button,Qt::magenta);
     pcmd->setPalette(pal);
 }
 connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
 return pcmd;
}

void Calculator::calculate() {
 double dOperand2 = stack.pop().toDouble();
 QString strOperation = stack.pop();
 double dOperand1 = stack.pop().toDouble();
 double dResult = 0;
 if (strOperation == "+") { dResult = dOperand1 + dOperand2; }
 else if (strOperation == "-") { dResult = dOperand1 - dOperand2; }
 else if (strOperation == "/") { dResult = dOperand1 / dOperand2; }
 else if (strOperation == "*") { dResult = dOperand1 * dOperand2; }
 displaystring->setText(QString("%1").arg(dResult, 0, 'f', 3));
}

void Calculator::slotButtonClicked() {
 QString str = ((QPushButton*)sender())->text();
 if (str == "C") {
  stack.clear(); displaystring->setText("");
    return;
 }
 else if(str == "D"){
     QString text = displaystring->text();
     if(!text.isEmpty()){
         text.chop(1);
         displaystring->setText(text);
     }
     return;
 }
 QString text = displaystring->text();
 int len = text.length();
 QString last = "";
 if (len>0) last = text.right(1);

 if (((len==0 && stack.count()==0) ||
      ((stack.count()==2 && len>1 && (last=="+"||last=="-"||last=="*"||last=="/")))) &&
     (str.contains(QRegularExpression("[0-9]")) || str=="-")) {

  text=str;
 }
 else if ((text+str).contains(QRegularExpression("^-?[0-9]+\\.?[0-9]*$")))
  text+=str;
  else if (text.contains(QRegularExpression("^-?[0-9]+\\.?[0-9]*$"))) {
  if (str=="*"||str=="/"||str=="+"||str=="-"||str=="=") {
   if (stack.count()==2) {
    stack.push(text);
    calculate();
    text=displaystring->text();
   }
   if (str!="=") {
    stack.push(text);
    text+=str;
    stack.push(str);
   }
  }
 }
 displaystring->setText(text);
}
