Warehouse 4 4 -> WarehouseStatus, ProductsInWarehouse, Product

ProductsInWarehouse 1 1 -> Product

WarehouseStatus 4 0 -> 

DeliveryTransport 6 5 -> 

ProductsDelivery 3 2 -> PurchaseOrder, DeliveryTransport, ProductsInWarehouse

Provider 9 7 -> PurchaseOrder, ProductsDelivery, Product

PurchaseOrder 7 6 -> Product, Status, Provider, BYN, Date

Status 5 0 ->

Alcohol 2 1 -> 

Beverage 2 1 ->

Date 5 0 -> 

MilkProduct 2 1 -> Date

Product 10 2 -> Date, BYN 

Cashier 1 11 -> Receipt, PaymentMethod, CashPayment, CardPayment, Cart, CashRegister

Cleaner 2 2 -> CleaningSchedule, WorkSchedule

CleaningSchedule 1 1 -> CleaningType, Day

CleaningType 5 0 ->

ContactInformation 3 0 -> 

Director 5 11 -> Minimarket, StaffDatabase, Product, Provider, PurchaseOrder, Shkaf

Employee 6 0 -> WorkSchedule, SexType, ContactInformation

SexType 2 0 -> 

StaffDatabase 1 3 -> Employee

WarehouseWorker 1 4 -> Warehouse, Date, BYN, Shelf

WorkSchedule 1 1 -> Day

Day 8 0 -> 

Documentation 1 3 -> WarehouseWorker, Cashier

BYN 1 0 -> 

TotalPriceDiscount 1 1 -> BYN, Date, Receipt

Receipt 8 5 -> Date, Product, BYN

ProductDiscount 1 1 -> Date, Receipt

PaymentMethod 1 2 -> BYN

Discount 4 2 -> Date, Receipt

CashRegister 4 4 -> BYN, Receipt, Cart

CashPayment 2 1 -> BYN

CardPayment 3 2 -> BYN, Date

Cart 1 3 -> Product

Customer 4 4 -> Product, CategoryAge, BYN, Cashier, Cart

CategoryAge 3 0 ->

Minimarket 5 3 -> StoreStatus, StaffDatabase, TradingFloor

StoreStatus 4 0 ->

Shelf 1 3 -> Product

FridgeShelf 1 1 -> Product

Shkaf 3 1 -> Shelf

TradingFloor 5 8 -> Shkaf, Customer

Exceptions(14):

MinimarketException 1 0 -> 

CardExpiredException 0 0 ->

NotEnoughCashException 0 0 ->

CashRegisterClosedException 0 0 ->

EmptyCartException 0 0 ->

ProductNotFoundException 0 0 ->

NullProductException 0 0 ->

UnauthorizedProviderException 0 0 ->

EmptyPurchaseListException 0 0 ->

InvalidSupplierException 0 0 ->

ExpiredProductException 0 0 ->

ShiftAlreadyOpenException 0 0 ->

ShiftNotOpenException 0 0 ->

ReceiptCreationException 0 0 ->


Поля : 150 Поведения : 107 Ассоциации : 75 Классы : 58 
