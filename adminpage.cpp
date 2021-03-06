#include "adminpage.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QIntValidator>
AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    // Sets default page to be the home page
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
    setupConnections();

    // Sets the items for item combo box
    ShowItemsInComboBox(databaseObj.loadItemsOnly());
    ShowQuantityInComboBox();   // sets the number of quantities for qty combo box
    ShowCustomerTypeInComboBox();   // sets the types of customers in customer combo box
}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::setupConnections()
{
    connect(ui->addCustomersBttn, &QPushButton::clicked, this, &AdminPage::ChangeToaddCustomers);
    connect(ui->addItemBttn,&QPushButton::clicked, this, &AdminPage::ChangeToaddItem);
    connect(ui->createPurchasesBtn, &QPushButton::clicked, this, &AdminPage::ChangeToCreatePurchasesPage);
    connect(ui->createPurchaseBackBtn, &QPushButton::clicked, this, &AdminPage::ChangeToAdminHomePage);

}

void AdminPage::ChangeToaddCustomers()
{
    ui->stackedWidget->setCurrentWidget(ui->addCustomer);
}

void AdminPage::ChangeToaddItem()
{
     ui->stackedWidget->setCurrentWidget(ui->addItem);
}


void AdminPage::on_deleteCustomersBttn_clicked()
{
    QSqlQuery data;
    QString deleteCustomer = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                   tr("Customer name:"), QLineEdit::Normal,
                                                   QDir::home().dirName());

   data.prepare("DELETE FROM Customers WHERE name == '"+deleteCustomer+"'");
    data.exec();

    QMessageBox::about(this, "", "The customer was deleted. double check if error occured");
}

void AdminPage::on_addButton_clicked()
{
    QSqlQuery data;
    QString name = ui->addName ->text();
    QString ID = ui->addID->text();
    QString customerType = ui->addType->text();
    QString expDay = ui->addDay->text();
    QString expMonth = ui->addMonth->text();
    QString expYear = ui->addYear->text();

    data.prepare("INSERT INTO Customers (name, ID, type, expMonth, expDay, expYear) VALUES('"+name+"', '"+ID+"', '"+customerType+"', '"+expMonth+"', '"+expDay+"', '"+expYear+"')");

    if(data.exec())
    {
        QMessageBox::about(this, "", "The Customer was added. be sure to double check if added correctly");

    }

    else
    {
        QMessageBox::about(this, "Error", "Database not found. double check connection");
    }
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);

}

void AdminPage::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}


void AdminPage::on_addItemConfirm_clicked()
{
    QSqlQuery data;
    QString itemName = ui->addItemName->text();
    QString itemPrice = ui->addItemPrice->text();
    QString itemQuantity = ui->addItemQty->text();

    data.prepare("INSERT INTO inventory (item, price, quantity) VALUES ('"+itemName+"', '"+itemPrice+"', '"+itemQuantity+"')");

    if(data.exec())
    {
        QMessageBox::about(this, "", "The item was added. double check if error occured");
    }
    else
    {
        QMessageBox::about(this, "Error", "Database not found. double check connection");
    }
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}


void AdminPage::on_cancelButton_3_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}

void AdminPage::on_deleteItemBttn_clicked()
{
    QSqlQuery data;
    QString deleteItem = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                               tr("Item to be deleted:"), QLineEdit::Normal,
                                               QDir::home().dirName());

    data.prepare("DELETE FROM inventory WHERE item == '"+deleteItem+"'");
    data.exec();

    QMessageBox::about(this, "", "The item was deleted. double check if error occured");

}

void AdminPage::on_addCustomersBttn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addCustomer);
}

void AdminPage::on_addItemBttn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addItem);
}

void AdminPage::on_Close_clicked()
{
    this->close();
}


void AdminPage::ChangeToAdminHomePage()             // changes to admin home page
{
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}


// -------------------------STORY 7 CODE-------------------------------//

void AdminPage::ChangeToCreatePurchasesPage()        // changes to create purchases page
{
    ui->stackedWidget->setCurrentWidget(ui->CreatePurchasesPage);

    QLineEdit *lineEdit = new QLineEdit;             // Item is used for item combo box
    lineEdit->setPlaceholderText("SELECT ITEMS");    // Sets default date for combobox(will turn into lineedit)

    // Changes item combo box to be a line edit in order to set the current text to be empty
    ui->pickItemComboBox->setLineEdit(lineEdit);
    ui->pickItemComboBox->setCurrentText("");

    // Clears all the line edits
    ui->addNameLineEdit->clear();
    ui->addIdLineEdit->clear();
    ui->addMonthLineEdit->clear();
    ui->addDayLineEdit->clear();
    ui->addYearLineEdit->clear();

    // sets new place holder/line edit text for quantity combo box
    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("SELECT QTY");
    ui->pickQtyLComboBox->setLineEdit(lineEdit);
    ui->pickQtyLComboBox->setCurrentText("");

     // sets new place holder/line edit text for customer combo box
    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("SELECT TYPE");
    ui->customerTypeComboBox->setLineEdit(lineEdit);
    ui->customerTypeComboBox->setCurrentText("");
}

void AdminPage::ShowItemsInComboBox(QSqlQueryModel *model)  // sets the item combo box to be the item values from inventory table
{
    ui->pickItemComboBox->setModel(model);
}

// Sets the quantity combo box to be quantities: 1-100
void AdminPage::ShowQuantityInComboBox()
{
    int i;  // used for quantity items
    for(i = 1; i <=100; i++)
    {
        ui->pickQtyLComboBox->addItem(QString::number(i));
    }
}

// Sets the types of customers in customers combo box
void AdminPage::ShowCustomerTypeInComboBox()
{
    QString regular = "Regular";
    QString executive = "Executive";

    ui->customerTypeComboBox->addItem(regular);
     ui->customerTypeComboBox->addItem(executive);

}

// Story 7 slot, will allow purchases to happen after admin clicks on the button
void AdminPage::on_createPurchasePushBtn_clicked()
{
    QString name, item, type, id;
    int month, day, year, quantity;
    bool valid = true;
    QIntValidator v(100000, 200000, this);  // Used for checking id from line edit, will only accept id between 100000 to 200000
    int pos = 0;

    // INPUT - Obtains input from line edits/combo boxes from each variables' respective values
    name = ui->addNameLineEdit->text();
    item = ui->pickItemComboBox->currentText();
    month = ui->addMonthLineEdit->text().toInt();
    day = ui->addDayLineEdit->text().toInt();
    year = ui->addYearLineEdit->text().toInt();
    quantity = ui->pickQtyLComboBox->currentText().toInt();
    type = ui->customerTypeComboBox->currentText();
    id = ui->addIdLineEdit->text();

    // PROCESSING - Checks for valid conditions
    // Validates id, if the value entered does not meet the specifications, then will set valid to false
    if(!v.validate(id, pos))
    {
        valid = false;
    }
    // First check if any of the line edits/combo boxes are empty, if they are then valid is false
    if(name == "" || item == "" || type == "" || ui->addMonthLineEdit->text() == "" ||
       ui->addDayLineEdit->text() == "" || ui->addYearLineEdit->text() == "" ||
       ui->pickQtyLComboBox->currentText() == "" || id == "")
    {
        valid = false;
    }

    // Checks for valid month, if valid month, then will check for valid days of each month
    if(month < 1 || month > 12)
    {
        valid = false;
    }
    else
    {
        if(month == 2)
        {
            if(day < 1 || day > 28)
            {
                valid = false;
            }
        }
        else if(month % 2 == 0)
        {
            if(day < 1 || day > 31)
            {
                valid = false;
            }
        }
        else
        {
            if(day < 1 || day > 30)
            {
                valid = false;
            }
        }
    }

    // Checks for valid year
    if(year < 2019 || year > 2023)
    {
        valid = false;
    }


    // If the final value of valid is false, then it will display an error message
    // Otherwise, the new customer purchase will be stored in the database along with a successful message
    if(valid == false)
    {
       QMessageBox::warning(this, "Invalid", "Please input valid information");
    }
    else
    {
        databaseObj.AddToCustomersTable(name, id, type, month, day, year);  // adds new info to customers table
        databaseObj.AddToDailySalesReport(id, item, quantity);              // adds new info to dailySalesReport table
        QMessageBox::information(this, "Success", "Purchase has been created");
        AdminPage::ChangeToAdminHomePage();
    }
}
//---------------------END of story 7 code ----------------------------------------//
