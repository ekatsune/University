#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "src/Banking/CashRegister.hpp"
#include "src/Banking/CardPayment.hpp"
#include "src/Banking/CashPayment.hpp"
#include "src/Banking/Discount.hpp"
#include "src/Banking/TotalPriceDiscount.hpp"
#include "src/Banking/ProductDiscount.hpp"
#include "src/Banking/Receipt.hpp"
#include "src/Banking/PaymentMethod.hpp"

#include "src/Construction/FridgeShelf.hpp"
#include "src/Construction/Shelf.hpp"
#include "src/Construction/Shkaf.hpp"
#include "src/Construction/TradingFloor.hpp"
#include "src/Construction/Minimarket.hpp"

#include "src/Customer/Customer.hpp"
#include "src/Customer/Cart.hpp"

#include "src/Documentation/Documentation.hpp"

#include "src/Employee/Cashier.hpp"
#include "src/Employee/Cleaner.hpp"
#include "src/Employee/CleaningSchedule.hpp"
#include "src/Employee/ContactInformation.hpp"
#include "src/Employee/Director.hpp"
#include "src/Employee/StaffDatabase.hpp"
#include "src/Employee/WorkSchedule.hpp"
#include "src/Employee/WarehouseWorker.hpp"

#include "src/Exceptions/MinimarketException.hpp"

#include "src/Products/Alcohol.hpp"
#include "src/Products/Beverage.hpp"
#include "src/Products/MilkProduct.hpp"
#include "src/Products/Product.hpp"

#include "src/Shipment/DeliveryTransport.hpp"
#include "src/Shipment/ProductsDelivery.hpp"
#include "src/Shipment/Provider.hpp"
#include "src/Shipment/PurchaseOrder.hpp"

#include "src/Warehouse/ProductsInWarehouse.hpp"
#include "src/Warehouse/Warehouse.hpp"
/**
 * @file test1.cpp
 * @brief Unit тесты.
 * @details
 * Этот файл содержит 168 Unit-tects.
 * Покрытие тестами составляет 85-95%
 *
 * @author Ekatsune
 */
TEST(BYNTest, ArithmeticOperators) {
    BYN a(150);
    BYN b(75);

    BYN sum = a + b;
    BYN diff = a - b;

    EXPECT_EQ(sum.GetRubles(), 2);
    EXPECT_EQ(sum.GetKopecks(), 25);

    EXPECT_EQ(diff.GetRubles(), 0);
    EXPECT_EQ(diff.GetKopecks(), 75);

    a += b;
    EXPECT_EQ(a.GetRubles(), 2);
    EXPECT_EQ(a.GetKopecks(), 25);

    a -= b;
    EXPECT_EQ(a.GetRubles(), 1);
    EXPECT_EQ(a.GetKopecks(), 50);
}

TEST(BYNTest, ComparisonOperators) {
    BYN a(100);
    BYN b(200);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);

    BYN c(100);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a != c);
}

TEST(BYNTest, MultiplyDivide) {
    BYN a(100); // 1.00 BYN

    BYN b = a * 2.5;
    EXPECT_EQ(b.GetRubles(), 2);
    EXPECT_EQ(b.GetKopecks(), 50);

    BYN c = b / 2.0;
    EXPECT_EQ(c.GetRubles(), 1);
    EXPECT_EQ(c.GetKopecks(), 25);
}

TEST(BYNTest, OutputOperator) {
    BYN a(123);
    std::ostringstream os;
    os << a;
    EXPECT_EQ(os.str(), "1,23 BYN");

    BYN b(5);
    std::ostringstream os2;
    os2 << b;
    EXPECT_EQ(os2.str(), "0,05 BYN");
}

TEST(BYNTest, InputOperator) {
    BYN a(0);
    std::istringstream is("1.50");
    is >> a;
    EXPECT_EQ(a.GetRubles(), 1);
    EXPECT_EQ(a.GetKopecks(), 50);

    BYN b(0);
    std::istringstream is2("2,75");
    is2 >> b;
    EXPECT_EQ(b.GetRubles(), 2);
    EXPECT_EQ(b.GetKopecks(), 75);

    BYN c(0);
    std::istringstream is3("abc");
    is3 >> c;
    EXPECT_TRUE(is3.fail());
}

TEST(BYNTest, ZeroAndNegative) {
    BYN zero(0);
    EXPECT_EQ(zero.GetRubles(), 0);
    EXPECT_EQ(zero.GetKopecks(), 0);

    BYN neg(-250);
    EXPECT_EQ(neg.GetRubles(), -2);
    EXPECT_EQ(neg.GetKopecks(), -50);
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST(PaymentMethodCoverageTest, CardPayment_PayCallsValidate) {
    Date future(1, 1, 2030);
    CardPayment card("1234", "Holder", future);
    BYN amount(50);

    EXPECT_TRUE(card.Pay(amount));
}


///////////////////////////////////////////////////////////////////////////////////

TEST(CardPaymentTest, ValidateCard_Valid)
{
    Date future(1, 1, 2030);
    CardPayment card("1234567890123456", "Test User", future);
    EXPECT_EQ(card.GetName(), "Card");
    EXPECT_FALSE(card.IsCash());
    EXPECT_NO_THROW({
                        bool ok = card.ValidateCard();
                        EXPECT_TRUE(ok);
                    });
}

TEST(CardPaymentTest, ValidateCard_Expired)
{
    Date past(2000, 1, 1);
    CardPayment card("9999999999999999", "User", past);

    EXPECT_THROW(card.ValidateCard(), CardExpiredException);
}

TEST(CardPaymentTest, Pay_Valid)
{
    Date future(15, 5, 2030);
    CardPayment card("1234", "Valid User", future);

    BYN amount(50);

    EXPECT_TRUE(card.Pay(amount));
}

TEST(CardPaymentTest, Pay_Expired_Throws)
{
    Date old(1999, 12, 31);
    CardPayment card("0000", "Expired", old);

    BYN amount(10);

    EXPECT_THROW(card.Pay(amount), CardExpiredException);
}

TEST(CardPaymentTest, Pay_CallsValidate)
{
    Date future(10, 10, 2035);
    CardPayment card("2222", "Holder", future);

    BYN amount(1);

    bool result = card.Pay(amount);
    EXPECT_TRUE(result);
}

////////////////////////////////////////////////////////////////////////////////////////////////

TEST(CashPaymentTest, Pay_NotEnoughCash)
{
    BYN given(20);
    CashPayment payment(given);

    BYN price(50);

    EXPECT_THROW(payment.Pay(price), NotEnoughCashException);
}

TEST(CashPaymentTest, GetGiven_ReturnsCorrectAmount)
{
    BYN given = BYN::FromRubles(75);
    CashPayment payment(given);

    BYN result = payment.GetGiven();
    EXPECT_EQ(result.GetRubles(), 75);
}

TEST(CashPaymentTest, GetChange_AfterPay)
{
    BYN given = BYN::FromRubles(100);
    CashPayment payment(given);

    BYN price = BYN::FromRubles(40);
    payment.Pay(price);

    BYN change = payment.GetChange();
    EXPECT_EQ(change.GetRubles(), 60);
}

TEST(CashPaymentTest, Change_DefaultZero)
{
    BYN given(10);
    CashPayment payment(given);

    BYN change = payment.GetChange();
    EXPECT_EQ(change.GetRubles(), 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////

TEST(CashRegisterTest, OpenShift_Success)
{
    CashRegister reg;
    EXPECT_NO_THROW(reg.OpenShift("10"));
}

TEST(CashRegisterTest, OpenShift_AlreadyOpen)
{
    CashRegister reg;
    reg.OpenShift("10");

    EXPECT_THROW(reg.OpenShift("5"), ShiftAlreadyOpenException);
}

TEST(CashRegisterTest, CloseShift_Success)
{
    CashRegister reg;
    reg.OpenShift("10");

    EXPECT_NO_THROW(reg.CloseShift());
}

TEST(CashRegisterTest, CloseShift_NotOpen)
{
    CashRegister reg;
    EXPECT_THROW(reg.CloseShift(), ShiftNotOpenException);
}

TEST(CashRegisterTest, CreateReceipt_Success)
{
    CashRegister reg;
    reg.OpenShift("10");

    Cart cart;
    Product p("Milk", BYN(2,50));
    cart.AddItem(&p);

    Receipt receipt = reg.CreateReceipt(cart);
    const auto& receipts = reg.GetReceipts();

    EXPECT_EQ(receipts.size(), 1);
}

TEST(CashRegisterTest, CreateReceipt_WhenClosed)
{
    CashRegister reg;

    Cart cart;
    Product p("Apple", BYN(1,0));
    cart.AddItem(&p);

    EXPECT_THROW(reg.CreateReceipt(cart), CashRegisterClosedException);
}

TEST(CashRegisterTest, CreateReceipt_EmptyCart)
{
    CashRegister reg;
    reg.OpenShift("10");

    Cart cart;

    EXPECT_THROW(reg.CreateReceipt(cart), EmptyCartException);

}

TEST(CashRegisterTest, CreateReceipt_NullProduct)
{
    CashRegister reg;
    reg.OpenShift("10");

    Cart cart;
    cart.AddItem(nullptr);

    EXPECT_THROW(reg.CreateReceipt(cart), EmptyCartException);

}

TEST(CashRegisterTest, AddCash_Success)
{
    CashRegister reg;
    reg.OpenShift("10");

    reg.AddCash(BYN(10,0));

    BYN total = reg.GetTotalCash();
    EXPECT_EQ(total.GetRubles(), 10);
}

TEST(CashRegisterTest, AddCash_WhenClosed)
{
    CashRegister reg;
    EXPECT_THROW(reg.AddCash(BYN(5,0)), CashRegisterClosedException);
}

TEST(CashRegisterTest, HasEnoughCash_True)
{
    CashRegister reg;
    reg.OpenShift("10");
    reg.AddCash(BYN(20,0));

    EXPECT_TRUE(reg.HasEnoughCash(BYN(15,0)));
}

TEST(CashRegisterTest, HasEnoughCash_False)
{
    CashRegister reg;
    reg.OpenShift("10");
    reg.AddCash(BYN(5,0));

    EXPECT_FALSE(reg.HasEnoughCash(BYN(10,0)));
}

TEST(CashRegisterTest, GetReceipts_EmptyInitially)
{
    CashRegister reg;
    reg.OpenShift("10");

    EXPECT_TRUE(reg.GetReceipts().empty());
}

TEST(TotalPriceDiscountTest, DiscountNotActive) {
    Date start(1,1,2025), end(1,1,2030);
    TotalPriceDiscount discount(BYN(50), "Promo", 10.0, start, end);

    Receipt r(1, Date(31,12,2024)); // до начала скидки
    r.AddItem(new Product("Milk", BYN(100)));

    discount.Apply(r);

    EXPECT_EQ(r.GetTotal(), BYN(100));
}

TEST(TotalPriceDiscountTest, DiscountBelowThreshold) {
    Date start(1,1,2025), end(1,1,2030);
    TotalPriceDiscount discount(BYN(200), "Promo", 10.0, start, end);

    Receipt r(1, Date(1,6,2025));
    r.AddItem(new Product("Milk", BYN(100)));

    discount.Apply(r);

    EXPECT_EQ(r.GetTotal(), BYN(100));
}

TEST(TotalPriceDiscountTest, DiscountUpdatesReceipt) {
    Date start(1,1,2025), end(1,1,2030);
    TotalPriceDiscount discount(BYN(50), "Promo", 20.0, start, end);

    Receipt r(1, Date(1,6,2025));
    r.AddItem(new Product("Milk", BYN(100)));

    discount.Apply(r);

    EXPECT_EQ(r.GetTotal().GetKopecks(), 80);
}

#include <cmath>

TEST(TotalPriceDiscountTest, DiscountAppliedWithFractionalTotal) {
    Date start(1,1,2025), end(1,1,2030);
    TotalPriceDiscount discount(BYN(50, 50), "Promo", 10.0, start, end); // threshold 50.50 BYN

    Receipt r(1, Date(1,6,2025));
    r.AddItem(new Product("Milk", BYN(30, 25)));  // 30.25 BYN
    r.AddItem(new Product("Bread", BYN(25, 25))); // 25.25 BYN → total 55.50 BYN > threshold

    EXPECT_EQ(r.GetTotal(), BYN(55,50));

    discount.Apply(r);

    long long expected_kopecks = static_cast<long long>(std::round(55.50 * 100 * 0.9));
    EXPECT_EQ(r.GetTotal().GetRubles()*100 + r.GetTotal().GetKopecks(), expected_kopecks);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(ProductDiscountTest, Apply_Success)
{
    Receipt r(1, Date(10,1,2025));

    Product p1("Milk", BYN(10, 0));
    Product p2("Bread", BYN(5, 0));

    r.AddItem(&p1);
    r.AddItem(&p2);
    r.CalculateTotals(); // total = 15 BYN

    ProductDiscount disc("Milk", "MilkSale", 10,
                         Date(1,1,2025), Date(31,1,2025));

    disc.Apply(r);
    EXPECT_EQ(r.GetTotal(), BYN(14, 0));

}

TEST(ProductDiscountTest, Apply_NoProduct)
{
    Receipt r(1, Date(2025,1,10));

    Product p1("Bread", BYN(5, 0));
    r.AddItem(&p1);

    r.CalculateTotals();

    ProductDiscount disc("Milk", "MilkSale", 10,
                         Date(2025,1,1), Date(2025,1,31));

    disc.Apply(r);
    EXPECT_EQ(r.GetTotal(), BYN(5, 0));
}

TEST(ProductDiscountTest, Apply_Inactive)
{
    Receipt r(1, Date(10,2,2025));
    Product p("Milk", BYN(10, 0));
    r.AddItem(&p);

    r.CalculateTotals();

    ProductDiscount disc("Milk", "MilkSale", 10,
                         Date(1,1,2025), Date(31,1,2025));

    disc.Apply(r);
    EXPECT_EQ(r.GetTotal(), BYN(10, 0));
}

////////////////////////////////////////////////////////////////////////////

TEST(ReceiptTest, ConstructorAndGetters)
{
    Receipt r(42, Date(2025,1,15));

    EXPECT_EQ(r.GetId(), "42");
    EXPECT_EQ(r.GetDate(), Date(2025,1,15));
    EXPECT_EQ(r.GetTotal(), BYN(0,0));
    EXPECT_TRUE(r.GetItems().empty());
}

TEST(ReceiptTest, AddItemIncreasesTotal)
{
    Receipt r(1, Date(2025,1,10));

    Product p1("Milk", BYN(10,0));
    Product p2("Bread", BYN(5,0));

    r.AddItem(&p1);
    r.AddItem(&p2);

    EXPECT_EQ(r.GetItems().size(), 2);
    EXPECT_EQ(r.GetTotal(), BYN(15,0));
}

TEST(ReceiptTest, DeleteItemReducesTotal)
{
    Receipt r(1, Date(2025,1,10));

    Product p1("Milk", BYN(10,0));
    Product p2("Bread", BYN(5,0));

    r.AddItem(&p1);
    r.AddItem(&p2);

    r.DeleteItem("Bread");

    EXPECT_EQ(r.GetItems().size(), 1);
    EXPECT_EQ(r.GetTotal(), BYN(10,0));
}

TEST(ReceiptTest, DeleteItemThrows)
{
    Receipt r(1, Date(2025,1,10));

    Product p1("Milk", BYN(10,0));
    r.AddItem(&p1);

    EXPECT_THROW(r.DeleteItem("Bread"), ProductNotFoundException);
}

TEST(ReceiptTest, CalculateTotalsRecomputesCorrectly)
{
    Receipt r(1, Date(2025,1,10));

    Product p1("Milk", BYN(10,0));
    Product p2("Bread", BYN(5,0));

    r.AddItem(&p1);
    r.AddItem(&p2);

    r.SetTotal(BYN(999,0));

    int total_rubles = r.CalculateTotals();

    EXPECT_EQ(total_rubles, 15);
    EXPECT_EQ(r.GetTotal(), BYN(15,0));
}

TEST(ReceiptTest, CalculateTotalsWithDiscount)
{
    Receipt r(1, Date(10,1,2025));

    Product p1("Milk", BYN(10,0));
    Product p2("Bread", BYN(10,0));

    r.AddItem(&p1);
    r.AddItem(&p2);

    r.CalculateTotals();
    r.AddDiscount(10.0);
    EXPECT_EQ(r.GetTotal(), BYN(20,0));
}

TEST(ReceiptTest, SubtractFromTotalWorks)
{
    Receipt r(1, Date(2025,1,10));

    Product p("Milk", BYN(10,0));
    r.AddItem(&p);

    EXPECT_EQ(r.GetTotal(), BYN(10,0));

    r.SubtractFromTotal(BYN(3,0));

    EXPECT_EQ(r.GetTotal(), BYN(7,0));
}

TEST(ShelfTest, AddAndRemoveProduct) {
    Shelf s;
    Product* p1 = new Product("Milk", BYN(300));
    Product* p2 = new Product("Bread", BYN(300));

    s.AddProduct(p1);
    s.AddProduct(p2);

    EXPECT_EQ(s.GetProductCount(), 2);
    EXPECT_EQ(s.FindByName("Milk"), p1);

    auto removed = s.RemoveProduct("Milk");
    EXPECT_EQ(removed, p1);
    EXPECT_EQ(s.GetProductCount(), 1);
    delete removed;

    EXPECT_EQ(s.RemoveProduct("NonExisting"), nullptr);

    delete p2;
}

TEST(ReceiptTest, AddItemWithNullptrDoesNothing) {
    Receipt r(1, Date(2025,1,10));
    r.AddItem(nullptr);
    EXPECT_TRUE(r.GetItems().empty());
    EXPECT_EQ(r.GetTotal(), BYN(0,0));
}

TEST(ReceiptTest, PrintOutputsCorrectly) {
    Receipt r(1, Date(2025,1,10));
    Product p("Milk", BYN(10,0));
    r.AddItem(&p);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    r.Print();

    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Чек №1"), std::string::npos);
    EXPECT_NE(output.find("Milk"), std::string::npos);
    EXPECT_NE(output.find("Сумма: 10 BYN"), std::string::npos);
}

TEST(ReceiptTest, AddDiscountStoresValue) {
    Receipt r(1, Date(2025,1,10));
    r.AddDiscount(15.0);

    EXPECT_EQ(r.GetTotal(), BYN(0,0));
}

#include <string>

TEST(ReceiptTest, SaveToFileCreatesCorrectContent) {
    Date date(11, 12, 2025);
    Receipt receipt(1, date);
    auto* p1 = new Product("Bread", BYN(150,0));
    auto* p2 = new Product("Milk", BYN(100,0));

    receipt.AddItem(p1);
    receipt.AddItem(p2);
    receipt.SetTotal(BYN(250,0));

    std::string filename = "test_receipt.txt";
    receipt.SaveToFile(filename);
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    EXPECT_NE(content.find("Чек №1"), std::string::npos);
    EXPECT_NE(content.find("Дата: 11.12.2025"), std::string::npos);
    EXPECT_NE(content.find("Bread"), std::string::npos);
    EXPECT_NE(content.find("150 BYN"), std::string::npos);
    EXPECT_NE(content.find("Milk"), std::string::npos);
    EXPECT_NE(content.find("100 BYN"), std::string::npos);
    EXPECT_NE(content.find("Сумма: 250 BYN"), std::string::npos);

    file.close();

    std::remove(filename.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST(FridgeShelfTest, AddProduct) {
    FridgeShelf fs;
    Product* p = new Product("Yogurt", BYN(150));
    fs.AddProduct(p);
    EXPECT_EQ(fs.GetProductCount(), 1);
    delete p;
}

TEST(FridgeShelfTest, AddNullProductThrows) {
    FridgeShelf fs;
    Product* p = nullptr;
    EXPECT_THROW(fs.AddProduct(p), NullProductException);
}

TEST(FridgeShelfTest, AddMilkProductTooWarmThrows) {
    FridgeShelf fs;
    fs.SetTemperature(2);
    Date dom(1,1,2025), doe(1,1,2026), shelf(1,1,2025);
    MilkProduct* p = new MilkProduct("Cheese", dom, doe, BYN(100), 0.0,
                                     "DairyCo", "Keep cool", "Milk", 0.5,
                                     5, shelf);

    EXPECT_NO_THROW(fs.AddProduct(p));
    delete p;
}

TEST(FridgeShelfTest, AddMilkProductSuccess) {
    FridgeShelf fs;
    fs.SetTemperature(4);
    Date dom(1,1,2025), doe(1,1,2026), shelf(1,1,2025);
    MilkProduct* p = new MilkProduct("Yogurt", dom, doe, BYN(150), 0.0,
                                     "DairyCo", "Keep cool", "Milk", 0.5,
                                     4, shelf);

    EXPECT_NO_THROW(fs.AddProduct(p));
    EXPECT_EQ(fs.GetProductCount(), 1);
    delete p;
}

TEST(ShkafTest, AddAndRemoveShelf) {
    Shkaf* shk = new Shkaf("Dairy");
    auto* s1 = new Shelf();
    auto* s2 = new Shelf();

    shk->AddShelf(s1);
    shk->AddShelf(s2);

    EXPECT_EQ(shk->GetShelfCount(), 2);
    EXPECT_EQ(shk->GetShelf(0), s1);

    shk->RemoveShelf(0);
    EXPECT_EQ(shk->GetShelfCount(), 1);
    EXPECT_EQ(shk->GetShelf(0), s2);
    shk->RemoveShelf(10);

    delete shk;
}

TEST(ShkafTest, CannotAddMoreThanMaxShelves) {
    Shkaf shk("MaxTest");
    for (int i = 0; i < 5; ++i) {
        shk.AddShelf(new Shelf());
    }

    EXPECT_EQ(shk.GetShelfCount(), 5);
    shk.AddShelf(new Shelf());
    EXPECT_EQ(shk.GetShelfCount(), 5);
}

TEST(ShkafTest, GetShelfInvalidIndexReturnsNullptr) {
    Shkaf shk;
    EXPECT_EQ(shk.GetShelf(-1), nullptr);
    EXPECT_EQ(shk.GetShelf(0), nullptr);
    EXPECT_EQ(shk.GetShelf(100), nullptr);
}

TEST(ShkafTest, SetAndGetName) {
    Shkaf shk;
    shk.SetName("Beverages");
    EXPECT_EQ(shk.GetName(), "Beverages");
}

TEST(ShkafTest, ShowShelvesDoesNotThrow) {
    Shkaf shk("EmptyShelf");
    EXPECT_NO_THROW(shk.ShowShelves());
    shk.AddShelf(new Shelf());
    EXPECT_NO_THROW(shk.ShowShelves());
}

TEST(TradingFloorTest, AddRemoveShkafAndCustomer) {
    TradingFloor tf;
    auto* shk = new Shkaf("Dairy");
    tf.AddShkaf(shk);
    EXPECT_EQ(tf.GetShkafs().size(), 1);

    Customer* c1 = new Customer(100, Customer::category_age::after_18);
    tf.AddCustomer(c1);
    EXPECT_EQ(tf.GetShkafs().size(), 1);

    tf.RemoveCustomer(c1);
    delete c1;
}

TEST(TradingFloorTest, MoveAndFindProduct) {
    TradingFloor tf;
    auto* shk = new Shkaf("Dairy");
    auto* shelf1 = new Shelf();
    auto* shelf2 = new Shelf();
    shk->AddShelf(shelf1);
    shk->AddShelf(shelf2);
    tf.AddShkaf(shk);

    auto* p = new Product("Cheese", BYN(200));
    shelf1->AddProduct(p);

    EXPECT_EQ(tf.FindProduct("Cheese"), p);
    bool moved = tf.MoveProduct("Cheese", shelf1, shelf2);
    EXPECT_TRUE(moved);
    EXPECT_EQ(shelf1->GetProductCount(), 0);
    EXPECT_EQ(shelf2->GetProductCount(), 1);

    delete p;
    delete shk;
}

TEST(TradingFloorTest, MoveProductFailsForInvalidInputs) {
    TradingFloor tf;
    auto* shk = new Shkaf("Dairy");
    auto* shelf1 = new Shelf();
    auto* shelf2 = new Shelf();
    shk->AddShelf(shelf1);
    shk->AddShelf(shelf2);
    tf.AddShkaf(shk);

    auto* p = new Product("Butter", BYN(150));
    shelf1->AddProduct(p);
    EXPECT_FALSE(tf.MoveProduct("Cheese", shelf1, shelf2));
    EXPECT_FALSE(tf.MoveProduct("Butter", nullptr, shelf2));
    EXPECT_FALSE(tf.MoveProduct("Butter", shelf1, nullptr));

    delete p;
    delete shk;
}

TEST(TradingFloorTest, FindProductReturnsNullptrWhenMissing) {
    TradingFloor tf;
    auto* shk = new Shkaf("Dairy");
    tf.AddShkaf(shk);
    EXPECT_EQ(tf.FindProduct("Nonexistent"), nullptr);
    delete shk;
}

TEST(TradingFloorTest, MultipleCustomersAndShowCustomers) {
    TradingFloor tf;
    Customer* c1 = new Customer(10, Customer::category_age::up_to_15);
    Customer* c2 = new Customer(16, Customer::category_age::after_15_up_to_18);
    Customer* c3 = new Customer(25, Customer::category_age::after_18);

    tf.AddCustomer(c1);
    tf.AddCustomer(c2);
    tf.AddCustomer(c3);

    EXPECT_EQ(tf.GetShkafs().size(), 0);
    tf.RemoveCustomer(c2);
    tf.RemoveCustomer(c1);
    tf.RemoveCustomer(c3);

    delete c1;
    delete c2;
    delete c3;
}

TEST(TradingFloorTest, ShowAllShelvesAndShowCustomersOutputs) {
    TradingFloor tf;
    auto* shk = new Shkaf("Fruits");
    auto* shelf = new Shelf();
    shk->AddShelf(shelf);
    tf.AddShkaf(shk);

    Customer* c = new Customer(20, Customer::category_age::after_18);
    tf.AddCustomer(c);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    tf.ShowAllShelves();
    tf.ShowCustomers();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Шкаф"), std::string::npos);
    EXPECT_NE(output.find("Покупатели"), std::string::npos);

    std::cout.rdbuf(old);

    delete c;
    delete shk;
}

TEST(MinimarketTest, HireEmployeeTest) {
    Minimarket market("Kopeechka", "Semashko_90_A");
    std::istringstream input("John\nDoe\n123\n0\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    market.HireEmployee();

    std::string result = output.str();
    EXPECT_NE(result.find("Сотрудник нанят!"), std::string::npos);

    auto* emp = market.GetStaffDatabase().FindEmployeeByID("123");
    ASSERT_NE(emp, nullptr);
    EXPECT_EQ(emp->GetName(), "John");
    EXPECT_EQ(emp->GetSurname(), "Doe");
    EXPECT_EQ(emp->GetSex(), Employee::male);
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);
}

TEST(MinimarketTest, FireEmployeeTest) {
    Minimarket market("Kopeechka", "Semashko_90_A");
    market.GetStaffDatabase().AddEmployee(new Employee("John", "Doe", "123", Employee::male));
    auto* emp_before = market.GetStaffDatabase().FindEmployeeByID("123");
    ASSERT_NE(emp_before, nullptr);
    std::istringstream input("123\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    market.FireEmployee();

    std::string result = output.str();
    EXPECT_NE(result.find("Сотрудник уволен."), std::string::npos);
    auto* emp_after = market.GetStaffDatabase().FindEmployeeByID("123");
    EXPECT_EQ(emp_after, nullptr);

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);
}



TEST(MinimarketTest, StatusAndTradingFloor) {
    Minimarket m("MiniMart", "Main Street");
    EXPECT_NE(m.GetStatus(), Minimarket::OPEN);
}

TEST(MinimarketTest, DefaultStatusIsClose) {
    Minimarket market("MyMarket", "Some address");
    EXPECT_EQ(market.GetStatus(), Minimarket::CLOSE);
}

TEST(MinimarketTest, SetAndGetStatus) {
    Minimarket market("MyMarket", "Some address");
    market.SetStatus(Minimarket::OPEN);
    EXPECT_EQ(market.GetStatus(), Minimarket::OPEN);

    market.SetStatus(Minimarket::LUNCH_BREAK);
    EXPECT_EQ(market.GetStatus(), Minimarket::LUNCH_BREAK);

    market.SetStatus(Minimarket::SANITARY_DAY);
    EXPECT_EQ(market.GetStatus(), Minimarket::SANITARY_DAY);
}

TEST(MinimarketTest, ShowTradingFloorDoesNotThrow) {
    Minimarket market("MyMarket", "Some address");
    EXPECT_NO_THROW(market.ShowTradingFloor());
}

TEST(MinimarketTest, AddAndRemoveEmployeeViaStaffDatabase) {
    Minimarket market("MyMarket", "Some address");

    auto* emp = new Employee("John", "Doe", "1", Employee::male);
    market.GetStaffDatabase().AddEmployee(emp);

    EXPECT_EQ(market.GetStaffDatabase().GetEmployeeCount(), 1);

    market.GetStaffDatabase().RemoveEmployee("1");
    EXPECT_EQ(market.GetStaffDatabase().GetEmployeeCount(), 0);
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST(CartTest, AddAndGetItems) {
    Cart cart;
    auto* p1 = new Product("Milk", BYN(100));
    auto* p2 = new Product("Bread", BYN(150));

    cart.AddItem(p1);
    cart.AddItem(p2);

    const auto& items = cart.GetItems();
    EXPECT_EQ(items.size(), 2);
    EXPECT_EQ(items[0], p1);
    EXPECT_EQ(items[1], p2);

    delete p1;
    delete p2;
}

TEST(CartTest, RemoveItem) {
    Cart cart;
    auto* p1 = new Product("Milk", BYN(100));
    auto* p2 = new Product("Bread", BYN(150));
    cart.AddItem(p1);
    cart.AddItem(p2);
    cart.RemoveItem("Milk");
    const auto& items = cart.GetItems();
    EXPECT_EQ(items.size(), 1);
    EXPECT_EQ(items[0], p2);
}

TEST(CartTest, ClearCart) {
    Cart cart;
    auto* p1 = new Product("Milk", BYN(100));
    cart.AddItem(p1);
    cart.Clear();
    EXPECT_TRUE(cart.GetItems().empty());
    delete p1;
}

/////////////////////////////////////////////////////////////////////////////////////

TEST(CustomerTest, AddAndRemoveProductInCart) {
    Customer c(100, Customer::category_age::after_18);
    auto* p1 = new Product("Cheese", BYN(200));
    auto* p2 = new Product("Butter", BYN(150));

    c.AddProductToCart(p1);
    c.AddProductToCart(p2);
    const auto& items = c.GetCartItems();
    EXPECT_EQ(items.size(), 2);

    c.RemoveProductFromCart("Cheese");
    const auto& items_after = c.GetCartItems();
    EXPECT_EQ(items_after.size(), 1);
    EXPECT_EQ(items_after[0], p2);

    c.RemoveProductFromCart("NonExisting");

    delete p1;
    delete p2;
}

///////////////////////////////////////////////////////////////////////////////////////

TEST(CashierTest, AskPaymentMethodCard) {
    Cashier cashier("John","Doe","1", Employee::male);

    std::istringstream input("1\n1234567890123456\nJohn Doe\n01 12 2025\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    PaymentMethod* method = cashier.AskPaymentMethod();

    CardPayment* card = dynamic_cast<CardPayment*>(method);
    ASSERT_NE(card, nullptr);

    std::string out = output.str();
    EXPECT_NE(out.find("Как вы будете оплачивать?"), std::string::npos);
    EXPECT_NE(out.find("Введите номер карты:"), std::string::npos);

    delete method;
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);
}

TEST(CashierTest, CustomerServiceCashPayment) {
    Cashier cashier("John", "Doe", "1", Employee::male);

    Cart cart;
    Product* p = new Product("Milk", BYN(100));
    cart.AddItem(p);
    std::istringstream input("1\n2\n200\n");
    auto* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    auto* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    EXPECT_NO_THROW({
                        cashier.CustomerService(cart);
                    });

    std::string out = output.str();
    EXPECT_NE(out.find("Здравствуйте! Пакетик нужен?"), std::string::npos);
    EXPECT_NE(out.find("Держите! *протягивает пакет*"), std::string::npos);
    EXPECT_NE(out.find("Сумма к оплате:"), std::string::npos);
    EXPECT_NE(out.find("До свидания! Приходите к нам ещё"), std::string::npos);

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    delete p;
}

TEST(CashierTest, CashReport_WithReceipts)
{

    Cashier cashier("Ivan", "Petrov", "10", Employee::male);
    cashier.OpenShift();
    Cart cart1;
    cart1.AddItem(new Product("Milk", BYN(100,0)));
    Cart cart2;
    cart2.AddItem(new Product("Bread", BYN(150,0)));
    cashier.CreatingReceipt(cart1);
    cashier.CreatingReceipt(cart2);
    std::string report = cashier.CashReportText();
    EXPECT_NE(report.find("Количество чеков: 2"), std::string::npos);
    size_t pos1 = report.find("Чек №");
    ASSERT_NE(pos1, std::string::npos);

    size_t pos2 = report.find("Чек №", pos1 + 1);
    ASSERT_NE(pos2, std::string::npos);
    EXPECT_NE(report.find("100 BYN"), std::string::npos);
    EXPECT_NE(report.find("150 BYN"), std::string::npos);
    EXPECT_NE(report.find("ИТОГО ЗА СМЕНУ: 250 BYN"), std::string::npos);
}

TEST(CashierTest, CancellationOfProduct) {
    Cashier cashier("Alice", "Smith", "2", Employee::female);
    Receipt r(1, Date(1,1,2024));
    Product* p1 = new Product("Milk", BYN(50));
    Product* p2 = new Product("Bread", BYN(30));
    r.AddItem(p1);
    r.AddItem(p2);

    std::istringstream input("\nBread\n");
    auto* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    auto* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    EXPECT_NO_THROW({
                        cashier.CancellationOfProduct(r);
                    });

    const auto& items = r.GetItems();
    ASSERT_EQ(items.size(), 1);
    EXPECT_EQ(items[0]->GetName(), "Milk");

    std::string out = output.str();
    EXPECT_NE(out.find("удаляет товар из чека"), std::string::npos);

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    delete p1;
    delete p2;
}

TEST(CashierTest, OpenShiftTest) {
    Cashier cashier("Mark", "Lee", "5", Employee::male);

    std::ostringstream output;
    auto* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    EXPECT_NO_THROW(cashier.OpenShift());

    std::string out = output.str();
    EXPECT_NE(out.find("Смена открыта"), std::string::npos);

    std::cout.rdbuf(cout_backup);
}



TEST(CashierTest, AskPaymentMethodCash) {
    Cashier cashier("John","Doe","1", Employee::male);

    std::istringstream input("2\n200\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    PaymentMethod* method = cashier.AskPaymentMethod();
    CashPayment* cash = dynamic_cast<CashPayment*>(method);
    ASSERT_NE(cash, nullptr);
    EXPECT_EQ(cash->GetGiven(), 200);

    std::string out = output.str();
    EXPECT_NE(out.find("Как вы будете оплачивать?"), std::string::npos);
    EXPECT_NE(out.find("Введите сумму полученную от клиента:"), std::string::npos);

    delete method;
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);
}

TEST(CashierTest, CreationAndCashReport) {
    Cashier cashier("John","Doe", "1", Employee::sex_type::male);
    std::string report_text = cashier.CashReportText();
    EXPECT_FALSE(report_text.empty());
    EXPECT_NO_THROW(cashier.CashReport());
}

TEST(CashierTest, CreatingReceiptAndCustomerService) {
    Cashier cashier("John","Doe", "1", Employee::sex_type::male);
    Cart cart;

    auto* p1 = new Product("Milk", BYN(100));
    auto* p2 = new Product("Bread", BYN(150));
    cart.AddItem(p1);
    cart.AddItem(p2);
    cashier.OpenShift();
    EXPECT_NO_THROW({
                        Receipt receipt = cashier.CreatingReceipt(cart);
                    });

    delete p1;
    delete p2;
}

TEST(CashierTest, PaymentMethods) {
    Cashier cashier("John","Doe", "1", Employee::sex_type::male);
    BYN total = 100;
    cashier.OpenShift();
    CashPayment cash_method(total);
    CardPayment card_method("12345","InstsntCard",Date(13,02,2027));

    EXPECT_NO_THROW(cashier.CashPaymentMethod(total, cash_method));
    EXPECT_NO_THROW(cashier.CardPaymentMethod(total, card_method));
}

TEST(CashierTest, ProcessPaymentAndCancellation) {
    Cashier cashier("John","Doe", "1", Employee::sex_type::male);
    cashier.OpenShift();
    Cart cart;
    auto* p1 = new Product("Milk", BYN(100));
    cart.AddItem(p1);
    Receipt receipt = cashier.CreatingReceipt(cart);

    CashPayment cash_method(50);
    bool result = cashier.ProcessPayment(receipt, cash_method);
    EXPECT_FALSE(result);

    delete p1;
}

TEST(CashierTest, ProcessPaymentWithUnknownMethod) {
    Cashier cashier("John","Doe","1", Employee::sex_type::male);
    cashier.OpenShift();

    Cart cart;
    auto* p = new Product("Milk", BYN(100));
    cart.AddItem(p);
    Receipt receipt = cashier.CreatingReceipt(cart);
    class DummyPayment : public PaymentMethod {
    public:
        DummyPayment() : PaymentMethod("Unknown") {}
        bool Pay(const BYN&) override { return true; }
    } dummy;

    bool result = cashier.ProcessPayment(receipt, dummy);
    EXPECT_FALSE(result);

    delete p;
}

TEST(CashierTest, CashPaymentMethodNotEnoughCash) {
    Cashier cashier("John","Doe","1", Employee::sex_type::male);
    cashier.OpenShift();

    BYN total(100);
    CashPayment cash_method(50);

    bool result = cashier.CashPaymentMethod(total, cash_method);
    EXPECT_FALSE(result);
}

TEST(CashierTest, CardPaymentMethodExpiredCard) {
    Cashier cashier("John","Doe","1", Employee::sex_type::male);
    cashier.OpenShift();

    BYN total(100);
    Date past(1,1,2000);
    CardPayment expired_card("1234","User",past);

    EXPECT_THROW({
                     cashier.CardPaymentMethod(total, expired_card);
                 }, CardExpiredException);
}

TEST(CashierTest, CancellationOfProductNonExisting) {
    Cashier cashier("John","Doe","1", Employee::sex_type::male);
    cashier.OpenShift();

    Cart cart;
    auto* p = new Product("Milk", BYN(100));
    cart.AddItem(p);
    Receipt receipt = cashier.CreatingReceipt(cart);
    EXPECT_THROW(receipt.DeleteItem("Bread"), ProductNotFoundException);

    delete p;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

TEST(CashierTest, ConstructorAndCashReport) {
    Cashier cashier("John", "Doe", "1", Employee::sex_type::male);
    std::string report = cashier.CashReportText();
    EXPECT_FALSE(report.empty());
    EXPECT_NO_THROW(cashier.CashReport());
}

TEST(CashierTest, CreatingReceipt) {
    Cashier cashier("John", "Doe", "1", Employee::sex_type::male);
    Cart cart;
    cashier.OpenShift();
    auto* p = new Product("Milk", BYN(100));
    cart.AddItem(p);
    EXPECT_NO_THROW({
                        Receipt receipt = cashier.CreatingReceipt(cart);
                        EXPECT_EQ(receipt.GetTotal().GetRubles(), 1);
                    });
    delete p;
}

TEST(CashierTest, CashAndCardPaymentMethods) {
    Cashier cashier("John", "Doe", "1", Employee::sex_type::male);
    BYN total(100);
    cashier.OpenShift();
    CashPayment cash(total + 50);
    CardPayment card("1234", "John Doe", Date(1,1,2030));

    EXPECT_TRUE(cashier.CashPaymentMethod(total, cash));
    EXPECT_TRUE(cashier.CardPaymentMethod(total, card));
}

TEST(CashierTest, ProcessPayment) {
    Cashier cashier("John", "Doe", "1", Employee::sex_type::male);
    Cart cart;
    cashier.OpenShift();
    auto* p = new Product("Milk", BYN(100));
    cart.AddItem(p);
    Receipt receipt = cashier.CreatingReceipt(cart);

    CashPayment cash(150);
    EXPECT_TRUE(cashier.ProcessPayment(receipt, cash));

    CardPayment card("1234", "John Doe", Date(1,1,2030));
    EXPECT_TRUE(cashier.ProcessPayment(receipt, card));

    delete p;
}

TEST(CustomerTest, ConstructorAndGetAge) {
    Customer c(25, Customer::category_age::after_18);
    EXPECT_EQ(c.GetAge(), Customer::category_age::after_18);
}

TEST(CustomerTest, AddProductToCart) {
    Customer c(20, Customer::category_age::after_18);
    Product* p = new Product("Milk", BYN(100));

    c.AddProductToCart(p);
    const auto& items = c.GetCart().GetItems();
    EXPECT_EQ(items.size(), 1);
    EXPECT_EQ(items[0], p);
    delete p;
}

TEST(CustomerTest, AddNullProductToCart) {
    Customer c(20, Customer::category_age::after_18);
    EXPECT_NO_THROW(c.AddProductToCart(nullptr));
    EXPECT_TRUE(c.GetCart().GetItems().empty());
}

TEST(CustomerTest, RemoveProductFromCart) {
    Customer c(20, Customer::category_age::after_18);
    Product* p = new Product("Bread", BYN(50));
    c.AddProductToCart(p);

    EXPECT_NO_THROW(c.RemoveProductFromCart("Bread"));
    EXPECT_TRUE(c.GetCart().GetItems().empty());

    delete p;
}

TEST(CustomerTest, RemoveNonexistentProduct) {
    Customer c(20, Customer::category_age::after_18);
    EXPECT_NO_THROW(c.RemoveProductFromCart("Nonexistent"));
}

TEST(CustomerTest, ShowCartWithProducts) {
    Customer c(20, Customer::category_age::after_18);
    Product* p = new Product("Cheese", BYN(200));
    c.AddProductToCart(p);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    c.ShowCart();
    std::string output = buffer.str();
    EXPECT_NE(output.find("Cheese"), std::string::npos);
    std::cout.rdbuf(old);
    delete p;
}

TEST(CustomerTest, ShowEmptyCart) {
    Customer c(20, Customer::category_age::after_18);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    c.ShowCart();
    std::string output = buffer.str();
    EXPECT_NE(output.find("(пусто)"), std::string::npos);
    std::cout.rdbuf(old);
}


TEST(CustomerTest, PaymentWithEmptyCart) {
    Customer c(20, Customer::category_age::after_18);
    Cashier cashier("John", "Doe", "1", Employee::sex_type::male);
    c.SetCashier(&cashier);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    c.Payment();
    std::string output = buffer.str();
    EXPECT_NE(output.find("Корзина пуста"), std::string::npos);
    std::cout.rdbuf(old);
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST(CleaningScheduleTest, SetAndGetTask) {
    CleaningSchedule schedule;
    for (int i = 0; i < (int)WorkSchedule::Day::Count; i++) {
        EXPECT_EQ(schedule.GetTask(static_cast<WorkSchedule::Day>(i)), CleaningSchedule::CleaningType::None);
    }

    schedule.SetTask(WorkSchedule::Day::Monday, CleaningSchedule::CleaningType::Wet);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Monday), CleaningSchedule::CleaningType::Wet);

    schedule.SetTask(WorkSchedule::Day::Tuesday, CleaningSchedule::CleaningType::Garbage);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Tuesday), CleaningSchedule::CleaningType::Garbage);
}

TEST(CleaningScheduleTest, DefaultConstructor) {
    CleaningSchedule schedule;
    for (int i = 0; i < (int)WorkSchedule::Day::Count; ++i) {
        EXPECT_EQ(schedule.GetTask(static_cast<WorkSchedule::Day>(i)),
                  CleaningSchedule::CleaningType::None);
    }
}

TEST(CleaningScheduleTest, SetAllCleaningTypes) {
    CleaningSchedule schedule;
    using CT = CleaningSchedule::CleaningType;

    schedule.SetTask(WorkSchedule::Day::Monday, CT::Wet);
    schedule.SetTask(WorkSchedule::Day::Tuesday, CT::Dry);
    schedule.SetTask(WorkSchedule::Day::Wednesday, CT::Garbage);
    schedule.SetTask(WorkSchedule::Day::Thursday, CT::Full);
    schedule.SetTask(WorkSchedule::Day::Friday, CT::None);

    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Monday), CT::Wet);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Tuesday), CT::Dry);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Wednesday), CT::Garbage);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Thursday), CT::Full);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Friday), CT::None);
}

TEST(CleaningScheduleTest, PrintCleaningDoesNotCrash) {
    CleaningSchedule schedule;
    schedule.SetTask(WorkSchedule::Day::Monday, CleaningSchedule::CleaningType::Wet);
    schedule.SetTask(WorkSchedule::Day::Friday, CleaningSchedule::CleaningType::Garbage);
    EXPECT_NO_THROW(schedule.PrintCleaning());
}

TEST(CleaningScheduleTest, OverwriteTask) {
    CleaningSchedule schedule;

    schedule.SetTask(WorkSchedule::Day::Wednesday, CleaningSchedule::CleaningType::Dry);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Wednesday), CleaningSchedule::CleaningType::Dry);

    schedule.SetTask(WorkSchedule::Day::Wednesday, CleaningSchedule::CleaningType::Full);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Wednesday), CleaningSchedule::CleaningType::Full);
}

TEST(CleanerTest, GarbageRemoval) {
    Cleaner cleaner("John", "Doe", "1", Employee::sex_type::male);

    cleaner.GarbageRemoval();
    cleaner.GarbageRemoval();
    cleaner.GarbageRemoval();
}

TEST(CleanerTest, CleaningTasks) {
    Cleaner cleaner("John", "Doe", "1", Employee::sex_type::male);

    CleaningSchedule& schedule = cleaner.GetCleaningSchedule();
    schedule.SetTask(WorkSchedule::Day::Monday, CleaningSchedule::CleaningType::Wet);
    schedule.SetTask(WorkSchedule::Day::Tuesday, CleaningSchedule::CleaningType::Dry);
    schedule.SetTask(WorkSchedule::Day::Wednesday, CleaningSchedule::CleaningType::Garbage);
    schedule.SetTask(WorkSchedule::Day::Thursday, CleaningSchedule::CleaningType::Full);
    schedule.SetTask(WorkSchedule::Day::Friday, CleaningSchedule::CleaningType::None);

    EXPECT_NO_THROW(cleaner.Cleaning(WorkSchedule::Day::Monday));
    EXPECT_NO_THROW(cleaner.Cleaning(WorkSchedule::Day::Tuesday));
    EXPECT_NO_THROW(cleaner.Cleaning(WorkSchedule::Day::Wednesday));
    EXPECT_NO_THROW(cleaner.Cleaning(WorkSchedule::Day::Thursday));
    EXPECT_NO_THROW(cleaner.Cleaning(WorkSchedule::Day::Friday));
}

TEST(CleanerTest, GetCleaningSchedule) {
    Cleaner cleaner("Jane", "Smith", "2", Employee::sex_type::female);
    CleaningSchedule& schedule = cleaner.GetCleaningSchedule();
    schedule.SetTask(WorkSchedule::Day::Monday, CleaningSchedule::CleaningType::Dry);
    EXPECT_EQ(schedule.GetTask(WorkSchedule::Day::Monday), CleaningSchedule::CleaningType::Dry);
}

//////////////////////////////////////////////////////////////////////////////

TEST(ContactInformationTest, DefaultConstructor) {
    ContactInformation info;
    EXPECT_EQ(info.GetPhone(), "");
    EXPECT_EQ(info.GetEmail(), "");
    EXPECT_EQ(info.GetAddress(), "");
}

TEST(ContactInformationTest, ParameterizedConstructor) {
    ContactInformation info("123456789", "test@example.com", "Main Street 1");
    EXPECT_EQ(info.GetPhone(), "123456789");
    EXPECT_EQ(info.GetEmail(), "test@example.com");
    EXPECT_EQ(info.GetAddress(), "Main Street 1");
}

TEST(ContactInformationTest, SettersAndGetters) {
    ContactInformation info;
    info.SetPhone("987654321");
    info.SetEmail("hello@example.com");
    info.SetAddress("Broadway 42");

    EXPECT_EQ(info.GetPhone(), "987654321");
    EXPECT_EQ(info.GetEmail(), "hello@example.com");
    EXPECT_EQ(info.GetAddress(), "Broadway 42");
}
////////////////////////////////////////////////////////////////////////////

TEST(DirectorTest, CreatePurchaseOrder_Success)
{
    Director director("Ivan", "Petrov", "D1", Employee::male);
    director.AddToShoppingList(Product("Milk", BYN(100,0)),50);
    director.AddToShoppingList(Product("Bread", BYN(150,0)),30);

    Provider provider("MilkCorp", "123", "mail@mail.com");

    director.AddAllowedProvider(&provider);
    EXPECT_NO_THROW({
                        PurchaseOrder order = director.CreatePurchaseOrder(&provider, "MainWarehouse");
                        EXPECT_FALSE(order.GetProducts().empty());
                        EXPECT_EQ(order.GetDestination(), "MainWarehouse");
                        EXPECT_EQ(order.GetSupplier(), &provider);
                        EXPECT_EQ(order.StatusToString(PurchaseOrder::Status::Approved), "Одобрен");
                    });
}

TEST(DirectorTest, CreatePurchaseOrder_UnauthorizedProvider)
{
    Director director("Ivan", "Petrov", "D1", Employee::male);

    Provider provider("EvilCorp", "000", "bad@mail.com");
    director.AddToShoppingList(Product("Milk", BYN(100,0)),30);

    EXPECT_THROW({
                     director.CreatePurchaseOrder(&provider, "Warehouse");
                 }, UnauthorizedProviderException);
}

TEST(DirectorTest, CreatePurchaseOrder_EmptyShoppingList)
{
    Director director("Ivan", "Petrov", "D1", Employee::male);

    Provider provider("GoodCorp", "111", "ok@mail.com");
    director.AddAllowedProvider(&provider);

    EXPECT_THROW(
            {
                director.CreatePurchaseOrder(&provider, "MainWarehouse");
            },
            EmptyPurchaseListException
    );
}


TEST(DirectorTest, SendOrderToProvider_Success)
{
    Director director("Ivan", "Petrov", "D1", Employee::male);

    Provider provider("FoodCorp", "222", "food@mail.com");
    director.AddAllowedProvider(&provider);
    director.AddToShoppingList(
            Product("Cheese", Date(1,1,2025), Date(1,4,2025), BYN(200),
                    "CheeseCo", "Cold", "Cheese", 1.0, 7),
            20
    );
    PurchaseOrder order = director.CreatePurchaseOrder(&provider, "MainWarehouse");
    EXPECT_NO_THROW({
                        ProductsDelivery delivery = director.SendOrderToProvider(order);
                        ASSERT_NE(delivery.GetOrder(), nullptr);
                        EXPECT_EQ(delivery.GetOrder(), &order);
                        EXPECT_FALSE(delivery.IsDelivered());
                    });
}

TEST(DirectorTest, SendOrderToProvider_InvalidSupplier)
{
    Director director("Ivan", "Petrov", "D1", Employee::male);
    std::vector<Product> goods = { Product("Sugar", BYN(50)) };
    PurchaseOrder bad_order(nullptr, goods, "MainWarehouse");

    EXPECT_THROW({
                     director.SendOrderToProvider(bad_order);
                 }, InvalidSupplierException);
}

TEST(DirectorTest, ShoppingListManagement) {
    Director director("John","Doe", "1", Employee::sex_type::male);

    Product p1("Milk", BYN(100));
    Product p2("Bread", BYN(50));
    director.AddToShoppingList(p1, 10);
    director.AddToShoppingList(p2, 5);
    EXPECT_NO_THROW(director.ClearShoppingList());
}

TEST(DirectorTest, AnalyzeWarehouseAndPrepareOrder) {
    Director director("John","Doe", "1", Employee::sex_type::male);

    std::vector<Product> warehouse = {
            Product("Milk", BYN(10)),
            Product("Bread", BYN(30))
    };
    EXPECT_NO_THROW(director.AnalyzeWarehouseAndPrepareOrder(warehouse, 20));
    EXPECT_NO_THROW(director.ClearShoppingList());
}

TEST(DirectorTest, AllowedProviders) {
    Director director("John","Doe", "1", Employee::sex_type::male);
    Provider provider1("Bob","+375293875944", "dhfd@dfvdjv.com"), provider2("Alex","+74583428254", "kdjvnsfkjg@fnvd.com");
    director.AddAllowedProvider(&provider1);

    EXPECT_TRUE(director.CanOrderFrom(&provider1));
    EXPECT_FALSE(director.CanOrderFrom(&provider2));
}

TEST(DirectorTest, DrawingUpStaffWorkSchedule) {
    Director director("John","Doe", "1", Employee::sex_type::male);
    EXPECT_NO_THROW(director.DrawingUpStaffWorkSchedule());
}

TEST(DirectorTest, CheckReadinessForWork) {
    Director director("John","Doe", "1", Employee::sex_type::male);
    EXPECT_NO_THROW(director.CheckReadinessForWork());
}

TEST(DirectorTest, ProductExpirationDateControl) {
    Director director("John", "Doe", "1", Employee::sex_type::male);

    auto *shkaf = new Shkaf();
    auto *shelf = new Shelf();
    auto *p1 = new Product("Milk", BYN(100));

    shelf->AddProduct(p1);
    shkaf->AddShelf(shelf);

    director.AddShkaf(shkaf);

    EXPECT_NO_THROW({
                        director.ProductExpirationDateControl();
                    });

    delete p1;
    delete shkaf;
}

/////////////////////////////////////////////////////////////////////////////////

TEST(StaffDatabaseTest, AddAndGetEmployees) {
    StaffDatabase db;

    Cashier* e1 = new Cashier("John", "Doe", "1", Employee::sex_type::male);
    Cashier* e2 = new Cashier("Jane", "Smith", "2", Employee::sex_type::female);

    db.AddEmployee(e1);
    db.AddEmployee(e2);

    const auto& employees = db.GetEmployees();
    EXPECT_EQ(employees.size(), 2);
    EXPECT_EQ(employees[0], e1);
    EXPECT_EQ(employees[1], e2);

    delete e1;
    delete e2;
}

TEST(StaffDatabaseTest, RemoveEmployee) {
    StaffDatabase db;

    Cashier* e1 = new Cashier("John", "Doe", "1", Employee::sex_type::male);
    Cashier* e2 = new Cashier("Jane", "Smith", "2", Employee::sex_type::female);

    db.AddEmployee(e1);
    db.AddEmployee(e2);

    db.RemoveEmployee("1");
    const auto& employees = db.GetEmployees();
    EXPECT_EQ(employees.size(), 1);
    EXPECT_EQ(employees[0], e2);

    db.RemoveEmployee("nonexistent");
    EXPECT_EQ(employees.size(), 1);

    delete e1;
    delete e2;
}

//////////////////////////////////////////////////////////////////////////////////

TEST(WarehouseWorkerTest, ProductRegistration_CorrectFile_AddsProduct)
{
    Warehouse warehouse;
    WarehouseWorker worker("Ivan", "Petrov", "W1", Employee::male);
    worker.SetWorkPlace(&warehouse);

    std::string filename = "test_product.txt";
    std::ofstream file(filename);

    file << "Milk\n";
    file << "01 01 2025\n";
    file << "01 03 2025\n";
    file << "150\n";
    file << "MilkCorp\n";
    file << "Keep cold\n";
    file << "Milk, vitamins\n";
    file << "1.22\n";
    file << "10\n";
    file.close();
    worker.ProductRegistration(filename);
    const auto& products = warehouse.GetProducts().GetAllProducts();
    ASSERT_EQ(products.size(), 1);

    EXPECT_EQ(products[0].GetName(), "Milk");
    EXPECT_EQ(products[0].GetQuantity(), 10);
    EXPECT_DOUBLE_EQ(products[0].GetWeight(), 12.2);
    std::remove(filename.c_str());
}

TEST(WarehouseWorkerTest, ProductRegistration_InvalidNumbers_NoProductsAdded)
{
    Warehouse warehouse;
    WarehouseWorker worker("Ivan", "Petrov", "W1", Employee::male);
    worker.SetWorkPlace(&warehouse);

    std::string filename = "bad_product.txt";
    std::ofstream file(filename);

    file << "Cheese\n";
    file << "01 01 2025\n";
    file << "01 05 2025\n";
    file << "200\n";
    file << "CheeseCo\n";
    file << "Cool\n";
    file << "Milk\n";
    file << "NOT_A_NUMBER\n";
    file << "ABC\n";
    file.close();

    worker.ProductRegistration(filename);

    const auto& products = warehouse.GetProducts().GetAllProducts();
    EXPECT_TRUE(products.empty());

    std::remove(filename.c_str());
}

TEST(WarehouseWorkerTest, WarehouseBalanceReport_PrintsCorrectData)
{
    Warehouse warehouse;
    WarehouseWorker worker("Ivan", "Petrov", "W1", Employee::male);
    worker.SetWorkPlace(&warehouse);
    warehouse.GetProducts().AddProductToListOfProd(
            Product("Tea", Date(5,1,2025), Date(5,6,2025), BYN(50,0),
                    "TeaCorp", "Dry", "Tea", 0.3, 5)
    );

    testing::internal::CaptureStdout();

    worker.WarehouseBalanceReport();

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("=== Отчёт о остатках на складе ==="), std::string::npos);
    EXPECT_NE(output.find("Tea"), std::string::npos);
    EXPECT_NE(output.find("Кол-во: 5"), std::string::npos);
    EXPECT_NE(output.find("Цена: 50"), std::string::npos);
}

TEST(WarehouseWorkerTest, WarehouseBalanceReport_EmptyWarehouse)
{
    Warehouse warehouse;
    WarehouseWorker worker("Ivan", "Petrov", "W1", Employee::male);
    worker.SetWorkPlace(&warehouse);

    testing::internal::CaptureStdout();
    worker.WarehouseBalanceReport();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Склад пуст."), std::string::npos);
}

TEST(WarehouseWorkerTest, AcceptTheProductAndWarehouseBalance) {
    WarehouseWorker worker("John", "Doe", "1", Employee::sex_type::male);
    Warehouse wh;

    worker.SetWorkPlace(&wh);

    Product p("Milk", Date(1,1,2025), Date(1,2,2025), BYN(200),
              "DairyCo", "Cool storage", "Milk", 1.0, 10);

    worker.AcceptTheProduct(
            p.GetName(),
            p.GetManufactureDate(),
            p.GetExpirationDate(),
            p.GetPrice(),
            p.GetInformationAboutTheManufacturer(),
            p.GetStorageRules(),
            p.GetProductComposition(),
            p.GetWeight(),
            p.GetQuantity()
    );

    const auto& products = wh.GetProducts().GetAllProducts();
    ASSERT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].GetName(), "Milk");
}

TEST(WarehouseWorkerTest, ReplenishmentOfShelves) {
    WarehouseWorker worker("John", "Doe", "1", Employee::sex_type::male);
    Warehouse wh;
    worker.SetWorkPlace(&wh);

    auto* shelf = new Shelf();
    Product p("Bread", Date(1,1,2025), Date(1,3,2025), BYN(150),
              "BakeryCo", "Dry storage", "Bread", 0.5, 5);
    wh.AddProductToWarehouse(p);
    EXPECT_NO_THROW(worker.ReplenishmentOfShelvesInMinimarket(*shelf, "Bread", 3));
    EXPECT_EQ(shelf->GetProductCount(), 3);
    const auto& products = wh.GetProducts().GetAllProducts();
    EXPECT_EQ(products[0].GetQuantity(), 2);

    EXPECT_NO_THROW(worker.ReplenishmentOfShelvesInMinimarket(*shelf, "Bread", 5));
    EXPECT_EQ(shelf->GetProductCount(), 3);
    EXPECT_NO_THROW(worker.ReplenishmentOfShelvesInMinimarket(*shelf, "Cheese", 1));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(WorkScheduleTest, DefaultValues) {
    WorkSchedule ws;
    for (int i = 0; i < static_cast<int>(WorkSchedule::Day::Count); ++i) {
        EXPECT_EQ(ws.GetDay(static_cast<WorkSchedule::Day>(i)), "Не указано");
    }
}

TEST(WorkScheduleTest, SetAndGetDay) {
    WorkSchedule ws;
    ws.SetDay(WorkSchedule::Day::Monday, "09:00-18:00");
    ws.SetDay(WorkSchedule::Day::Saturday, "10:00-16:00");

    EXPECT_EQ(ws.GetDay(WorkSchedule::Day::Monday), "09:00-18:00");
    EXPECT_EQ(ws.GetDay(WorkSchedule::Day::Saturday), "10:00-16:00");
}

TEST(WorkScheduleTest, DayToString) {
    EXPECT_EQ(WorkSchedule::DayToString(WorkSchedule::Day::Monday), "Понедельник");
    EXPECT_EQ(WorkSchedule::DayToString(WorkSchedule::Day::Sunday), "Воскресенье");
    EXPECT_EQ(WorkSchedule::DayToString(static_cast<WorkSchedule::Day>(100)), "Неизвестный день");
}

/////////////////////////////////////////////////////////////////////////

TEST(ProductTest, ConstructorAndGetters) {
    BYN price(300);
    Product p("Milk", price);

    EXPECT_EQ(p.GetName(), "Milk");
    EXPECT_EQ(p.GetPrice().GetRubles(), 3);
    EXPECT_EQ(p.GetQuantity(), 1);
}

TEST(ProductTest, QuantityManipulation) {
    Product p("Bread", BYN(150));
    EXPECT_EQ(p.GetQuantity(), 1);

    p.SetQuantity(5);
    EXPECT_EQ(p.GetQuantity(), 5);

    p.DecreaseQuantity(2);
    EXPECT_EQ(p.GetQuantity(), 3);

    p.DecreaseQuantity(10);
    EXPECT_EQ(p.GetQuantity(), 0);
}

TEST(MilkProductTest, TemperatureRequirement) {
    Date dom(1, 12, 2025);
    Date doe(10, 12, 2025);
    Date shelf_after_open(15, 12, 2025);
    MilkProduct milk("Yogurt", dom, doe, BYN(200), 0.0, "Farm", "Cold storage", "Milk", 0.5, 4.0, shelf_after_open);

    EXPECT_EQ(milk.RequiresTemperature(), 4);
}

TEST(AlcoholTest, LegalAgeCheck) {
    Alcohol vodka;
    vodka.SetQuantity(10);
    class TestAlcohol : public Alcohol {
    public:
        TestAlcohol() { alcohol_percent = 40; legal_age = 18; }
    };
    TestAlcohol a;
    EXPECT_TRUE(a.CanBuy(21));
    EXPECT_FALSE(a.CanBuy(16));
}

TEST(BeverageTest, VolumeAndCarbonation) {
    class TestBeverage : public Beverage {
    public:
        TestBeverage() { volume_liters = 1.5; carbonated = true; }
    };
    TestBeverage b;
    EXPECT_EQ(b.GetVolume(), 1.5);
    EXPECT_TRUE(b.IsCarbonated());
}

///////////////////////////////////////////////////////////////////////////////////

TEST(DocumentationTest, AddDocument) {
    Documentation doc;
    doc.AddDocument("Title1", "Content1");
    doc.AddDocument("Title2", "Content2");

    const auto& documents = doc.GetAllDocuments();
    EXPECT_EQ(documents.size(), 2);
    EXPECT_EQ(documents[0].first, "Title1");
    EXPECT_EQ(documents[0].second, "Content1");
    EXPECT_EQ(documents[1].first, "Title2");
    EXPECT_EQ(documents[1].second, "Content2");
}

TEST(DocumentationTest, CollectCashReport) {
    Cashier cashier("John","Doe","1", Employee::sex_type::male);

    Documentation doc;
    EXPECT_NO_THROW(doc.CollectCashReport(cashier));

    const auto& documents = doc.GetAllDocuments();
    EXPECT_FALSE(documents.empty());
    EXPECT_NE(documents.back().second.find("Кассир: John Doe"), std::string::npos);
}

TEST(DocumentationTest, CollectWarehouseBalanceReport) {
    WarehouseWorker worker("Alice","Smith","2", Employee::sex_type::female);
    Warehouse wh;
    worker.SetWorkPlace(&wh);
    Documentation doc;
    EXPECT_NO_THROW(doc.CollectWarehouseBalanceReport(worker));
    const auto& documents = doc.GetAllDocuments();
    EXPECT_FALSE(documents.empty());
    EXPECT_NE(documents.back().second.find("Склад пуст"), std::string::npos);
}

TEST(DocumentationTest, PrintDocuments) {
    Documentation doc;
    doc.AddDocument("Doc1", "Text1");
    doc.AddDocument("Doc2", "Text2");

    EXPECT_NO_THROW(doc.PrintAll());
    EXPECT_NO_THROW(doc.PrintDocument(0));
    EXPECT_NO_THROW(doc.PrintDocument(1));
}

TEST(DocumentationTest, PrintDocumentInvalidIndex) {
    Documentation doc;
    doc.AddDocument("Doc1", "Text1");

    EXPECT_NO_THROW(doc.PrintDocument(-1));
    EXPECT_NO_THROW(doc.PrintDocument(10));
}

TEST(DocumentationTest, CollectWarehouseBalanceReportWithProducts) {
    WarehouseWorker worker("Bob","Brown","3", Employee::sex_type::male);
    Warehouse wh;
    worker.SetWorkPlace(&wh);
    Product p("Bread", Date(1,1,2025), Date(1,3,2025), BYN(150,0),
              "BakeryCo", "Dry storage", "Bread", 0.5, 5);
    wh.AddProductToWarehouse(p);

    Documentation doc;
    EXPECT_NO_THROW(doc.CollectWarehouseBalanceReport(worker));

    const auto& documents = doc.GetAllDocuments();
    EXPECT_FALSE(documents.empty());
    EXPECT_NE(documents.back().second.find("Bread"), std::string::npos);
    EXPECT_NE(documents.back().second.find("цена: 150"), std::string::npos);
}

TEST(DocumentationTest, AddEmptyDocument) {
    Documentation doc;
    doc.AddDocument("", "");
    const auto& documents = doc.GetAllDocuments();

    EXPECT_EQ(documents.size(), 1);
    EXPECT_EQ(documents[0].first, "");
    EXPECT_EQ(documents[0].second, "");
}

TEST(DocumentationTest, MultipleCollectCashReports) {
    Cashier cashier("Jane","Doe","4", Employee::sex_type::female);
    Documentation doc;

    doc.CollectCashReport(cashier);
    doc.CollectCashReport(cashier);

    const auto& documents = doc.GetAllDocuments();
    EXPECT_EQ(documents.size(), 2);
    EXPECT_NE(documents[0].second.find("Jane"), std::string::npos);
    EXPECT_NE(documents[1].second.find("Jane"), std::string::npos);
}


//////////////////////////////////////////////////////////////////////////////////////

TEST(DeliveryTransportTest, BasicOperations) {
    DeliveryTransport truck("Ford Transit", "1234 AB-7", 1000.0);

    EXPECT_TRUE(truck.IsAvailable());
    EXPECT_EQ(truck.GetModel(), "Ford Transit");
    EXPECT_EQ(truck.GetLicensePlate(), "1234 AB-7");
    EXPECT_EQ(truck.GetMaxLoad(), 1000.0);

    EXPECT_TRUE(truck.LoadCargo(500));
    EXPECT_FALSE(truck.LoadCargo(600));

    EXPECT_TRUE(truck.StartTrip());
    EXPECT_FALSE(truck.StartTrip());
    truck.EndTrip(50.0);
    EXPECT_TRUE(truck.IsAvailable());

    truck.UnloadCargo();
}

TEST(ProviderTest, GetBasicInfo) {
    Provider p("FoodCorp", "123-456", "contact@food.com");

    EXPECT_EQ(p.GetName(), "FoodCorp");
    EXPECT_EQ(p.GetPhone(), "123-456");
    EXPECT_EQ(p.GetEmail(), "contact@food.com");
}

TEST(ProviderTest, AddProductCategory) {
    Provider p("FoodCorp", "123-456", "contact@food.com");

    p.AddProductCategory("Dairy");
    p.AddProductCategory("Bakery");
    EXPECT_NO_THROW(p.AddProductCategory("Vegetables"));
}

TEST(ProviderTest, TrackSupply) {
    Provider p("FoodCorp", "123-456", "contact@food.com");
    EXPECT_EQ(p.TrackSupply(0), nullptr);
    EXPECT_EQ(p.TrackSupply(10), nullptr);

    PurchaseOrder order(nullptr, {}, "Warehouse");
    DeliveryTransport transport("Truck", "AAA111", 100.0);
    ProductsDelivery delivery(order, transport);
}

TEST(ProviderTest, CreateOrderAndDelivery) {
    Provider prov("SupplierInc", "1234567", "supplier@example.com");

    Product p1("Milk", BYN(100));
    Product p2("Bread", BYN(50));
    std::vector<Product> products = {p1, p2};

    PurchaseOrder order = prov.CreateOrder(products, "Warehouse1");
    EXPECT_EQ(order.GetProducts().size(), 2);
    EXPECT_EQ(order.GetDestination(), "Warehouse1");
    EXPECT_EQ(order.GetSupplier(), &prov);
    EXPECT_TRUE(prov.IsAvailable());

    ProductsDelivery delivery = prov.StartDelivery(order);
    EXPECT_EQ(delivery.GetOrder(), &order);
    EXPECT_FALSE(prov.IsAvailable());
}

TEST(ProductsDeliveryTest, LoadCargoAndAlreadyDeliveredChecks) {
    Product light("LightItem", Date(1,1,2025), Date(1,3,2025), BYN(100), "Co", "Store", "Item", 10.0, 1);
    Product heavy("HeavyItem", Date(1,1,2025), Date(1,3,2025), BYN(100), "Co", "Store", "Item", 50.0, 1);

    std::vector<Product> heavyProducts = {heavy};
    std::vector<Product> lightProducts = {light};

    PurchaseOrder heavyOrder(nullptr, heavyProducts, "Warehouse");
    PurchaseOrder lightOrder(nullptr, lightProducts, "Warehouse");

    DeliveryTransport smallTransport("SmallTruck", "AAA111", 20.0);
    DeliveryTransport bigTransport("BigTruck", "BBB222", 100.0);

    ProductsInWarehouse warehouse;
    ProductsDelivery heavyDelivery(heavyOrder, smallTransport);
    testing::internal::CaptureStdout();
    heavyDelivery.MarkDelivered(warehouse);
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output1.find("Невозможно выполнить доставку: превышение массы!"), std::string::npos);
    ProductsDelivery lightDelivery(lightOrder, bigTransport);
    lightDelivery.MarkDelivered(warehouse);

    testing::internal::CaptureStdout();
    lightDelivery.MarkDelivered(warehouse);
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output2.find("Поставка уже была выполнена!"), std::string::npos);
    const DeliveryTransport& t = lightDelivery.GetTransport();
    EXPECT_EQ(t.GetModel(), "BigTruck");
    EXPECT_EQ(t.GetLicensePlate(), "BBB222");
    EXPECT_DOUBLE_EQ(t.GetMaxLoad(), 100.0);
}

TEST(ProductsDeliveryTest, MarkDelivered) {
    Provider prov("SupplierInc", "1234567", "supplier@example.com");
    Product p("Milk", BYN(100));
    std::vector<Product> products = {p};
    PurchaseOrder order = prov.CreateOrder(products, "Warehouse1");

    DeliveryTransport truck("Mercedes Sprinter", "5555 AA-7", 1500);
    ProductsDelivery delivery(order, truck);
    class FakeWarehouse {
    public:
        std::vector<Product> added;
        void AddProductToListOfProd(const Product& p) { added.push_back(p); }
    } warehouse;

    EXPECT_FALSE(delivery.IsDelivered());
    EXPECT_NO_THROW(delivery.MarkDelivered(*reinterpret_cast<ProductsInWarehouse*>(&warehouse)));
    EXPECT_TRUE(delivery.IsDelivered());
    EXPECT_EQ(order.GetProducts().size(), 1);
}

TEST(ProviderTest, Reliability) {
    Provider prov("SupplierInc", "1234567", "supplier@example.com");
    EXPECT_DOUBLE_EQ(prov.CalculateReliability(), 1.0);
    prov.FinishOrder(true);
    prov.FinishOrder(false);
    EXPECT_DOUBLE_EQ(prov.CalculateReliability(), 0.5);
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST(ProductsInWarehouseTest, AddAndFindProduct) {
    ProductsInWarehouse warehouse;
    Product p1("Milk", BYN(100));
    Product p2("Bread", BYN(50));

    warehouse.AddProductToListOfProd(p1);
    warehouse.AddProductToListOfProd(p2);

    EXPECT_EQ(warehouse.GetAllProducts().size(), 2);

    Product* found = warehouse.FindByName("Milk");
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->GetName(), "Milk");

    Product* not_found = warehouse.FindByName("Cheese");
    EXPECT_EQ(not_found, nullptr);
}

TEST(ProductsInWarehouseTest, DeleteProduct) {
    ProductsInWarehouse warehouse;
    Product p("Milk", BYN(100));
    warehouse.AddProductToListOfProd(p);

    std::istringstream input("Milk\n");
    std::cin.rdbuf(input.rdbuf());

    warehouse.DeleteProductToListOfProd();
    EXPECT_EQ(warehouse.GetAllProducts().size(), 0);
}

TEST(WarehouseTest, AddFindMoveSort) {

    Warehouse wh1;
    Warehouse wh2;

    Product milk("Milk", BYN(100));
    Product bread("Bread", BYN(50));
    Product cheese("Cheese", BYN(200));

    wh1.AddProductToWarehouse(milk);
    wh1.AddProductToWarehouse(bread);
    wh1.AddProductToWarehouse(cheese);

    EXPECT_NE(wh1.FindProductByName("Bread"), nullptr);
    EXPECT_EQ(wh1.FindProductByName("Yogurt"), nullptr);
    EXPECT_TRUE(wh1.MoveProductToOtherWarehouse(wh2, "Bread", 1));
    EXPECT_EQ(wh2.GetProducts().GetAllProducts().size(), 1);
    EXPECT_EQ(wh1.FindProductByName("Bread")->GetQuantity(), bread.GetQuantity() - 1);
    wh1.SortProductsByName();
    const auto& sorted_by_name = wh1.GetProducts().GetAllProducts();
    EXPECT_TRUE(sorted_by_name[0].GetName() <= sorted_by_name[1].GetName());
    Date dom1(1,1,2025), dom2(2,1,2025);
    Date doe1(1,1,2026), doe2(2,1,2026);
    Product p1("A", dom1, doe1, BYN(10), "", "", "", 1.0, 1);
    Product p2("B", dom2, doe2, BYN(20), "", "", "", 1.0, 1);
    wh1.AddProductToWarehouse(p1);
    wh1.AddProductToWarehouse(p2);
    wh1.SortProductsByExpirationDate();
    EXPECT_TRUE(wh1.GetProducts().GetAllProducts()[0].GetExpirationDate() <=
                wh1.GetProducts().GetAllProducts()[1].GetExpirationDate());
}

TEST(PurchaseOrderTest, AddAndRemoveProduct) {
    PurchaseOrder order(nullptr, {}, "Warehouse");

    Product p1("Milk", Date(1,1,2025), Date(1,2,2025), BYN(100,0), "MilkCo", "Cold", "Milk", 1.0, 5);
    Product p2("Bread", Date(1,1,2025), Date(1,2,2025), BYN(50,0), "BreadCo", "Dry", "Bread", 0.5, 10);
    order.AddProduct(p1);
    order.AddProduct(p2);

    EXPECT_EQ(order.GetProducts().size(), 2);
    EXPECT_DOUBLE_EQ(order.GetTotalWeight(), 10); // 1.0 + 0.5
    EXPECT_DOUBLE_EQ(order.GetTotalCost().GetRubles(), 150); // 100 + 50
    bool removed = order.RemoveProduct("Milk");
    EXPECT_TRUE(removed);
    EXPECT_EQ(order.GetProducts().size(), 1);
    EXPECT_DOUBLE_EQ(order.GetTotalWeight(), 5);
    EXPECT_DOUBLE_EQ(order.GetTotalCost().GetRubles(), 50);
    removed = order.RemoveProduct("Cheese");
    EXPECT_FALSE(removed);
}

TEST(PurchaseOrderTest, RecalculateTotal) {
    PurchaseOrder order(nullptr, {}, "Warehouse");
    Product p1("Apple", Date(1,1,2025), Date(1,2,2025), BYN(30,0), "FruitCo", "Cold", "Apple", 0.2, 10);

    order.AddProduct(p1);
    EXPECT_DOUBLE_EQ(order.GetTotalCost().GetRubles(), 30);

    order.RemoveProduct("Apple");
    EXPECT_DOUBLE_EQ(order.GetTotalCost().GetRubles(), 0);
}

TEST(PurchaseOrderTest, SetDestinationAndIsValid) {
    Provider provider("FoodCorp", "123", "contact@food.com");

    PurchaseOrder order(&provider, {}, "Warehouse");
    EXPECT_FALSE(order.IsValid()); // нет продуктов

    Product p("Milk", Date(1,1,2025), Date(1,2,2025), BYN(100,0), "MilkCo", "Cold", "Milk", 1.0, 5);
    order.AddProduct(p);
    EXPECT_TRUE(order.IsValid());

    order.SetDestination("MainWarehouse");
    EXPECT_EQ(order.GetDestination(), "MainWarehouse");
}

TEST(DateTest, SetValidMinutes) {
    Date d;
    d.SetMinutes(30);
    std::stringstream ss;
    ss << d;
    std::string output = ss.str();
    EXPECT_NE(output.find("30"), std::string::npos);
}

TEST(DateTest, SetInvalidMinutes) {
    Date d;
    testing::internal::CaptureStderr();
    d.SetMinutes(70);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("Invalid minutes"), std::string::npos);
}

TEST(DateTest, SetValidHours) {
    Date d;
    d.SetHours(15);
    std::stringstream ss;
    ss << d;
    std::string output = ss.str();
    EXPECT_NE(output.find("15"), std::string::npos);
}

TEST(DateTest, SetInvalidHours) {
    Date d;
    testing::internal::CaptureStderr();
    d.SetHours(25);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("Invalid hours"), std::string::npos);
}

TEST(DateTest, GreaterEqualOperator) {
    Date d1(10, 1, 2025);
    Date d2(5, 1, 2025);
    EXPECT_TRUE(d1 >= d2);
    EXPECT_TRUE(d1 >= d1);
}

TEST(DateTest, NotEqualOperator) {
    Date d1(10, 1, 2025);
    Date d2(5, 1, 2025);
    Date d3(10, 1, 2025);
    EXPECT_TRUE(d1 != d2);
    EXPECT_FALSE(d1 != d3);
}

TEST(ExpiredProductExceptionTest, MessageIsCorrect) {
    ExpiredProductException ex("Молоко", 2, 3);

    EXPECT_STREQ(
            ex.what(),
            "Ошибка: товар \"Молоко\" на шкафу \"2\" на полке \"3\" просрочен."
    );
}

TEST(ReceiptCreationExceptionTest, MessageIsCorrect) {
    ReceiptCreationException ex("не удалось открыть файл");

    EXPECT_STREQ(
            ex.what(),
            "Ошибка создания чека: не удалось открыть файл"
    );
}









