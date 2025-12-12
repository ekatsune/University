cmake_minimum_required(VERSION 3.30)
project(Minimarket)

set(CMAKE_CXX_STANDARD 20)

add_executable(ThePostMachine main.cpp
        src/Banking/BYN.cpp
        src/Banking/CashRegister.cpp
        src/Banking/CardPayment.cpp
        src/Banking/CashPayment.cpp
        src/Banking/Discount.cpp
        src/Banking/TotalPriceDiscount.cpp
        src/Banking/ProductDiscount.cpp
        src/Banking/Receipt.cpp
        src/Banking/PaymentMethod.cpp

        src/Construction/FridgeShelf.cpp
        src/Construction/Shelf.cpp
        src/Construction/Shkaf.cpp
        src/Construction/TradingFloor.cpp
        src/Construction/Minimarket.cpp

        src/Customer/Customer.cpp
        src/Customer/Cart.cpp

        src/Documentation/Documentation.cpp

        src/Employee/Cashier.cpp
        src/Employee/Cleaner.cpp
        src/Employee/CleaningSchedule.cpp
        src/Employee/ContactInformation.cpp
        src/Employee/Director.cpp
        src/Employee/Employee.cpp
        src/Employee/StaffDatabase.cpp
        src/Employee/WorkSchedule.cpp
        src/Employee/WarehouseWorker.cpp

        src/Products/Alcohol.cpp
        src/Products/Beverage.cpp
        src/Products/Date.cpp
        src/Products/MilkProduct.cpp
        src/Products/Product.cpp

        src/Shipment/DeliveryTransport.cpp
        src/Shipment/ProductsDelivery.cpp
        src/Shipment/Provider.cpp
        src/Shipment/PurchaseOrder.cpp

        src/Warehouse/ProductsInWarehouse.cpp
        src/Warehouse/Warehouse.cpp)

add_subdirectory(Google_tests)

if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Enabling GCC coverage flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

find_program(GCOVR_PATH gcovr)

if (GCOVR_PATH)
    add_custom_target(coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            COMMAND ${GCOVR_PATH} -r ${CMAKE_SOURCE_DIR} --txt --exclude 'Google_tests/lib'
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running tests and generating coverage report..."
    )
endif()