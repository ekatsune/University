
cmake_minimum_required(VERSION 3.14)
project(GoogleTests)

add_subdirectory(lib)

add_executable(MyTests test1.cpp
        ../src/Banking/BYN.cpp
        ../src/Banking/CashRegister.cpp
        ../src/Banking/CardPayment.cpp
        ../src/Banking/CashPayment.cpp
        ../src/Banking/Discount.cpp
        ../src/Banking/TotalPriceDiscount.cpp
        ../src/Banking/ProductDiscount.cpp
        ../src/Banking/Receipt.cpp
        ../src/Banking/PaymentMethod.cpp

        ../src/Construction/FridgeShelf.cpp
        ../src/Construction/Shelf.cpp
        ../src/Construction/Shkaf.cpp
        ../src/Construction/TradingFloor.cpp
        ../src/Construction/Minimarket.cpp

        ../src/Customer/Customer.cpp
        ../src/Customer/Cart.cpp

        ../src/Documentation/Documentation.cpp

        ../src/Employee/Cashier.cpp
        ../src/Employee/Cleaner.cpp
        ../src/Employee/CleaningSchedule.cpp
        ../src/Employee/ContactInformation.cpp
        ../src/Employee/Director.cpp
        ../src/Employee/Employee.cpp
        ../src/Employee/StaffDatabase.cpp
        ../src/Employee/WorkSchedule.cpp
        ../src/Employee/WarehouseWorker.cpp

        ../src/Products/Alcohol.cpp
        ../src/Products/Beverage.cpp
        ../src/Products/Date.cpp
        ../src/Products/MilkProduct.cpp
        ../src/Products/Product.cpp

        ../src/Shipment/DeliveryTransport.cpp
        ../src/Shipment/ProductsDelivery.cpp
        ../src/Shipment/Provider.cpp
        ../src/Shipment/PurchaseOrder.cpp

        ../src/Warehouse/ProductsInWarehouse.cpp
        ../src/Warehouse/Warehouse.cpp)

target_include_directories(MyTests PRIVATE
        lib/googletest/include
        lib/googlemock/include
        ../
)

target_link_libraries(MyTests gtest gtest_main)

enable_testing()
add_test(NAME MyTests COMMAND MyTests)