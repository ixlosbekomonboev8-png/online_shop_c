#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QStatusBar>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1100, 750);
    
    sm.loadData();

    // Initialize layout using tabs from UI file
    setupProductTab();
    setupCustomerTab();
    setupOrdersTab();
    setupReportTab();
    
    // Status Bar
    QStatusBar* bar = ui->statusBar;
    statProducts = new QLabel(" Mahsulot: 0 ");
    statCustomers = new QLabel(" Mijoz: 0 ");
    statOrders = new QLabel(" Buyurtma: 0 ");
    statIncome = new QLabel(" Daromad: 0 so'm ");
    bar->addPermanentWidget(statProducts);
    bar->addPermanentWidget(statCustomers);
    bar->addPermanentWidget(statOrders);
    bar->addPermanentWidget(statIncome);

    applyStyle();
    
    updateProductTable();
    updateCustomerTable();
    updateOrderTable();
    updateCombos();
    updateStats();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));
}

MainWindow::~MainWindow() {
    sm.saveData();
    delete ui;
}

void MainWindow::setupProductTab() {
    QWidget* tab = ui->tab_products;
    if (tab->layout()) {
        delete tab->layout();
    }
    // Hide old widgets from UI file to prevent overlapping
    for (auto child : tab->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
        child->hide();
    }

    QHBoxLayout* layout = new QHBoxLayout(tab);
    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    QGroupBox* addBox = new QGroupBox("Mahsulot Qo'shish");
    QVBoxLayout* addLayout = new QVBoxLayout(addBox);
    QFormLayout* form = new QFormLayout();
    prodTypeCombo = new QComboBox();
    prodTypeCombo->addItems({"📱 Elektronika", "👕 Kiyim", "🍎 Oziq-ovqat"});
    prodNameEdit = new QLineEdit();
    prodPriceEdit = new QDoubleSpinBox();
    prodPriceEdit->setRange(0, 1000000000);
    prodQtyEdit = new QSpinBox();
    prodQtyEdit->setRange(0, 10000);
    prodBrandEdit = new QLineEdit();
    prodWarrantyEdit = new QSpinBox();

    form->addRow("Turi:", prodTypeCombo);
    form->addRow("Nomi:", prodNameEdit);
    form->addRow("Narxi:", prodPriceEdit);
    form->addRow("Soni:", prodQtyEdit);
    form->addRow("Brend:", prodBrandEdit);
    form->addRow("Kafolat:", prodWarrantyEdit);
    addLayout->addLayout(form);

    QPushButton* btnAdd = new QPushButton(" Qo'shish");
    btnAdd->setObjectName("btnAdd");
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(onAddProductClicked()));
    addLayout->addWidget(btnAdd);
    addLayout->addStretch();

    QGroupBox* listBox = new QGroupBox("Mahsulotlar Ro'yxati");
    QVBoxLayout* listLayout = new QVBoxLayout(listBox);
    prodSearchEdit = new QLineEdit();
    prodSearchEdit->setPlaceholderText("Qidirish...");
    connect(prodSearchEdit, SIGNAL(textChanged(QString)), this, SLOT(onSearchProduct(QString)));
    listLayout->addWidget(prodSearchEdit);

    productTable = new QTableWidget(0, 5);
    productTable->setHorizontalHeaderLabels({"ID", "Nomi", "Narxi", "Soni", "Turi"});
    productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    productTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productTable->setSelectionMode(QAbstractItemView::SingleSelection);
    listLayout->addWidget(productTable);

    splitter->addWidget(addBox);
    splitter->addWidget(listBox);
    splitter->setStretchFactor(1, 3);
    layout->addWidget(splitter);
}

void MainWindow::setupCustomerTab() {
    QWidget* tab = ui->tab_customers;
    if (tab->layout()) {
        delete tab->layout();
    }
    for (auto child : tab->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
        child->hide();
    }
    QHBoxLayout* layout = new QHBoxLayout(tab);
    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    QGroupBox* addBox = new QGroupBox("Yangi Mijoz");
    QFormLayout* form = new QFormLayout(addBox);
    custNameEdit = new QLineEdit();
    custEmailEdit = new QLineEdit();
    custPhoneEdit = new QLineEdit();
    custPhoneEdit->setPlaceholderText("+998");
    custBalanceEdit = new QDoubleSpinBox();
    custBalanceEdit->setRange(0, 1000000000);
    form->addRow("Ism:", custNameEdit);
    form->addRow("Email:", custEmailEdit);
    form->addRow("Tel:", custPhoneEdit);
    form->addRow("Balans:", custBalanceEdit);
    QPushButton* btn = new QPushButton("➕ Qo'shish");
    btn->setObjectName("btnAdd");
    connect(btn, SIGNAL(clicked()), this, SLOT(onAddCustomerClicked()));
    form->addRow(btn);

    customerTable = new QTableWidget(0, 5);
    customerTable->setHorizontalHeaderLabels({"ID", "Ismi", "Email", "Tel", "Balans"});
    customerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    customerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    customerTable->setSelectionMode(QAbstractItemView::SingleSelection);

    splitter->addWidget(addBox);
    splitter->addWidget(customerTable);
    splitter->setStretchFactor(1, 3);
    layout->addWidget(splitter);
}

void MainWindow::setupOrdersTab() {
    QWidget* tab = ui->tab_orders;
    if (tab->layout()) {
        delete tab->layout();
    }
    for (auto child : tab->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
        child->hide();
    }
    QHBoxLayout* layout = new QHBoxLayout(tab);
    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    QGroupBox* addBox = new QGroupBox("Buyurtma");
    QFormLayout* form = new QFormLayout(addBox);
    orderCustCombo = new QComboBox();
    orderProdCombo = new QComboBox();
    orderQtyEdit = new QSpinBox();
    form->addRow("Mijoz:", orderCustCombo);
    form->addRow("Mahsulot:", orderProdCombo);
    form->addRow("Soni:", orderQtyEdit);
    QPushButton* btn = new QPushButton("Buyurtma Berish");
    btn->setObjectName("btnAdd");
    connect(btn, SIGNAL(clicked()), this, SLOT(onPlaceOrderClicked()));
    form->addRow(btn);

    QPushButton* btnPay = new QPushButton("To'lov Qilish");
    btnPay->setObjectName("btnAdd");
    connect(btnPay, SIGNAL(clicked()), this, SLOT(onPayOrderClicked()));
    form->addRow(btnPay);

    orderTable = new QTableWidget(0, 5);
    orderTable->setHorizontalHeaderLabels({"ID", "Mijoz", "Jami", "Holat", "Sana/Vaqt"});
    orderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderTable->setSelectionMode(QAbstractItemView::SingleSelection);

    splitter->addWidget(addBox);
    splitter->addWidget(orderTable);
    splitter->setStretchFactor(1, 2);
    layout->addWidget(splitter);
}

void MainWindow::setupReportTab() {
    QWidget* tab = ui->tab_report;
    if (tab->layout()) {
        delete tab->layout();
    }
    for (auto child : tab->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
        child->hide();
    }
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QGroupBox* box = new QGroupBox("Hisobot");
    QFormLayout* form = new QFormLayout(box);
    reportTotalRevenue = new QLabel("0 so'm");
    reportTotalOrders = new QLabel("0");
    form->addRow("Jami tushum:", reportTotalRevenue);
    form->addRow("Buyurtmalar:", reportTotalOrders);
    layout->addWidget(box);
    layout->addStretch();
}

void MainWindow::updateProductTable() {
    productTable->setRowCount(0);
    for (auto* p : sm.getWarehouse().getAllProducts()) {
        int r = productTable->rowCount();
        productTable->insertRow(r);
        productTable->setItem(r, 0, new QTableWidgetItem(QString::number(p->getId())));
        productTable->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(p->getName())));
        productTable->setItem(r, 2, new QTableWidgetItem(QString("%1 so'm").arg(p->getPrice(), 0, 'f', 0)));
        productTable->setItem(r, 3, new QTableWidgetItem(QString("%1 %2").arg(p->getQuantity()).arg(QString::fromStdString(p->getUnit()))));
        productTable->setItem(r, 4, new QTableWidgetItem(QString::fromStdString(p->getTypeName())));
    }
}

void MainWindow::updateCustomerTable() {
    customerTable->setRowCount(0);
    for (const auto& c : sm.getCustomers()) {
        int r = customerTable->rowCount();
        customerTable->insertRow(r);
        customerTable->setItem(r, 0, new QTableWidgetItem(QString::number(c->getId())));
        customerTable->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(c->getName())));
        customerTable->setItem(r, 2, new QTableWidgetItem(QString::fromStdString(c->getEmail())));
        customerTable->setItem(r, 3, new QTableWidgetItem(QString::fromStdString(c->getPhone())));
        customerTable->setItem(r, 4, new QTableWidgetItem(QString("%1 so'm").arg(c->getBalance(), 0, 'f', 0)));
    }
}

void MainWindow::updateOrderTable() {
    orderTable->setRowCount(0);
    for (const auto& o : sm.getOrders()) {
        int r = orderTable->rowCount();
        orderTable->insertRow(r);
        Customer* c = sm.findCustomer(o->getCustomerId());
        orderTable->setItem(r, 0, new QTableWidgetItem(QString::number(o->getId())));
        orderTable->setItem(r, 1, new QTableWidgetItem(c ? QString::fromStdString(c->getName()) : "-"));
        orderTable->setItem(r, 2, new QTableWidgetItem(QString("%1 so'm").arg(o->getTotal(), 0, 'f', 0)));
        orderTable->setItem(r, 3, new QTableWidgetItem(QString::fromStdString(orderStatusToString(o->getStatus()))));
        orderTable->setItem(r, 4, new QTableWidgetItem(QString::fromStdString(o->getCreatedAt())));
    }
}

void MainWindow::updateCombos() {
    orderCustCombo->clear();
    for (const auto& c : sm.getCustomers()) orderCustCombo->addItem(QString::fromStdString(c->getName()), c->getId());
    orderProdCombo->clear();
    for (auto* p : sm.getWarehouse().getAllProducts()) orderProdCombo->addItem(QString::fromStdString(p->getName()), p->getId());
}

void MainWindow::updateStats() {
    statProducts->setText(QString(" Mahsulot: %1 ").arg(sm.getWarehouse().getTotalProductCount()));
    statCustomers->setText(QString(" Mijoz: %1 ").arg(sm.getCustomers().size()));
    statOrders->setText(QString(" Buyurtma: %1 ").arg(sm.getOrders().size()));
    updateReport();
}

void MainWindow::updateReport() {
    double rev = 0;
    for (const auto& o : sm.getOrders()) if (o->getStatus() != OrderStatus::CANCELLED && o->getStatus() != OrderStatus::PENDING) rev += o->getTotal();
    reportTotalRevenue->setText(QString("%1 so'm").arg(rev, 0, 'f', 0));
    reportTotalOrders->setText(QString::number(sm.getOrders().size()));
    statIncome->setText(QString(" Daromad: %1 so'm ").arg(rev, 0, 'f', 0));
}

void MainWindow::onAddProductClicked() {
    try {
        QString name = prodNameEdit->text();
        double price = prodPriceEdit->value();
        int qty = prodQtyEdit->value();
        int type = prodTypeCombo->currentIndex();
        if (type == 0) sm.getWarehouse().addElectronics(name.toStdString(), price, qty, prodBrandEdit->text().toStdString(), prodWarrantyEdit->value());
        else if (type == 1) sm.getWarehouse().addClothing(name.toStdString(), price, qty, "M", "Qora");
        else sm.getWarehouse().addFood(name.toStdString(), price, qty, "2026-01-01", true);
        updateProductTable(); updateCombos(); updateStats();
    } catch (std::exception& e) { QMessageBox::critical(this, "Xato", e.what()); }
}

void MainWindow::onAddCustomerClicked() {
    try {
        Customer* c = sm.addCustomer(custNameEdit->text().toStdString(), custEmailEdit->text().toStdString(), custPhoneEdit->text().toStdString());
        c->deposit(custBalanceEdit->value());
        updateCustomerTable(); updateCombos(); updateStats();
    } catch (std::exception& e) { QMessageBox::critical(this, "Xato", e.what()); }
}

void MainWindow::onPlaceOrderClicked() {
    int cid = orderCustCombo->currentData().toInt();
    int pid = orderProdCombo->currentData().toInt();
    int qty = orderQtyEdit->value();
    try {
        sm.placeOrder(cid, pid, qty);
        updateOrderTable(); updateStats();
    } catch (std::exception& e) { QMessageBox::critical(this, "Xato", e.what()); }
}

void MainWindow::onPayOrderClicked() {
    int row = orderTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Xato", "To'lash uchun buyurtmani tanlang!");
        return;
    }
    int id = orderTable->item(row, 0)->text().toInt();
    if (sm.payOrder(id)) {
        QMessageBox::information(this, "Muvaffaqiyat", "To'lov qabul qilindi!");
        updateOrderTable();
        updateStats();
    } else {
        QMessageBox::critical(this, "Xato", "To'lovni amalga oshirib bo'lmadi.\nSababi: Balans yetarli emas yoki buyurtma allaqachon to'langan.");
    }
}

void MainWindow::onSearchProduct(const QString&) { updateProductTable(); }
void MainWindow::onDeleteProduct() { /* ... */ }
void MainWindow::onDeleteCustomer() { /* ... */ }
void MainWindow::onTabChanged(int i) { if (i == 2) updateCombos(); if (i == 3) updateReport(); }
void MainWindow::loadDemoData() { sm.loadDemoData(); updateProductTable(); updateCustomerTable(); updateCombos(); updateStats(); }

void MainWindow::applyStyle() {
    setStyleSheet(
        "QMainWindow { background-color: #f5f7fa; }"
        "QTabWidget::pane { border: 1px solid #d1d5db; background: white; }"
        "QTabBar::tab { background: #e5e7eb; padding: 12px 25px; margin-right: 2px; }"
        "QTabBar::tab:selected { background: white; color: #0078d4; border-top: 3px solid #0078d4; }"
        "QPushButton#btnAdd { background-color: #0078d4; color: white; padding: 8px; border-radius: 4px; font-weight: bold; }"
        "QHeaderView::section { background-color: #0078d4; color: white; padding: 5px; }"
    );
}
