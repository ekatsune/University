 Минимаркет + 5 3 2 -> StaffDatabase, store_status
 полка (бд товаров в магазине) 1 2 1 -> Product
 шкаф 3 1 1 полка
 торговый зал 5 8 2 шкаф покупатель
 полка холодильника 1 1 1 -> Product
    покупатель 4 5 4 -> BYN cashier Cart category_age+
   поставщик 9 7 2 -> ProductsDelivery PurchaseOrder
    бд работников + 1 2
    Работник + 6 0 3  -> WorkSchedule, ContactInformation, sex
        директор 5 10 5 -> Minimarket StaffDatabase Shelf Product Provider
        кассир + 1 9 5 -> cart, receipt, paymentmethod, cashregister, byn
        уборщик + 2 2 2 -> cleaningschedule day
        расписание уборки + 1 0 2 -> CleaningType Day
        складской рабочий + 1 5 4 -> Shelf Warehouse Data BYN
 товары 10 1 2 -> BYN Date
    дата + 5 0 0
        напитки + 2 1 0
        молочные продукты + 2 1 0
        алкоголь + 2 1 0
 склад 4  3 3 -> работник статус бд
    БД товаров на складе 1 1 1 -> product
 поставка + 3 2 4 -> PurchaseOrder DeliveryTransport Product ProductsInWarehouse
     Транспорт доставки + 6 5 0
    заказ поставки + 7 8 4 -> Product Status Date BYN Provider
 валюта + 1 0 0
    кассовый аппарат 4 5 3 -> BYN Receipt cart
    корзина покупок 1 0 1 -> Product
    чек + 8 (5) 3 -> Date Byn Product
    скидки + 4 2 2 -> Date Receipt
    скидка на набранную сумму + 1 1 1 -> BYN
    скидка на конктретный товар + 1 1 0
     способ оплаты 1 0 0
    оплата картой 3 2 2 -> Date BYN
  +  оплата наличными 2 2 1-> BYN
 документация 1 4 2 -> cashier warehouseworker
   + график работы + 1 0 1 -> Day
  +  контактная информация + 3 0 0
+ enum store_status 4 0 0 +
+ enum sex у работника 2 0 0  +
+ enum warehouse_status 4 0 0 +
+ enum category_age у покупателя 3 0 0 +
+ enum day в расписании 8 0 0 +
+ enum CleaningType в расписании уборки 5 0 0 +
+ enum class Status 5 0 0 +


        150 100