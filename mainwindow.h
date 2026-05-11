#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include "shop_manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onAddProductClicked();
    void onAddCustomerClicked();
    void onPlaceOrderClicked();
    void onPayOrderClicked();
    void onSearchProduct(const QString &text);
    void onDeleteProduct();
    void onDeleteCustomer();
    void onTabChanged(int index);
    void loadDemoData();

private:
    Ui::MainWindow *ui;
    ShopManager sm;

    // UI Elements (Manually managed items within tabs)
    QTableWidget* productTable;
    QLineEdit*    prodNameEdit;
    QDoubleSpinBox* prodPriceEdit;
    QSpinBox*     prodQtyEdit;
    QComboBox*    prodTypeCombo;
    QLineEdit*    prodBrandEdit;
    QSpinBox*     prodWarrantyEdit;
    QLineEdit*    prodSearchEdit;

    QTableWidget* customerTable;
    QLineEdit*    custNameEdit;
    QLineEdit*    custEmailEdit;
    QLineEdit*    custPhoneEdit;
    QDoubleSpinBox* custBalanceEdit;

    QTableWidget* orderTable;
    QComboBox*    orderCustCombo;
    QComboBox*    orderProdCombo;
    QSpinBox*     orderQtyEdit;

    QLabel* reportTotalRevenue;
    QLabel* reportTotalOrders;
    QLabel* reportTopProduct;

    QLabel* statProducts;
    QLabel* statCustomers;
    QLabel* statOrders;
    QLabel* statIncome;

    void setupProductTab();
    void setupCustomerTab();
    void setupOrdersTab();
    void setupReportTab();
    
    void updateProductTable();
    void updateCustomerTable();
    void updateOrderTable();
    void updateCombos();
    void updateStats();
    void updateReport();
    void applyStyle();
};

#endif // MAINWINDOW_H
