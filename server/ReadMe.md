目前的使用者(帳號：密碼)
=====
1. admin: admin
2. dolan: xyz

所有的運送狀態 ENUM
=====
* Archived
* Submitted
* Processing
* Shipping
* Arrived

POST /register
=====
* 格式：{ "username": "STRING", "password": "STRING" }

POST /login
=====
* 格式：{ "username": "STRING", "password": "STRING" }
* 會在 HEADER 上回傳 COOKIE

GET /logout --cookie
=====

/products
=====

1. GET

    * 說明：回傳所有產品的清單

2. POST --cookie（管理員限定）

    * 格式：[{ "name": "STRING", "stock": "NUMBER", "price": "NUMBER"}]
    * 說明：管理員新增數筆產品。

3. PUT --cookie（管理員限定）

    * 格式：[{ "id": "ID_STRING", "name": "STRING", "stock": "NUMBER", "price": "NUMBER" }]
    * 說明：管理員更新數筆產品。id 可從 GET /products 中獲取。

4. DELETE --cookie（管理員限定）

    * 格式：[{ "id": "ID_STRING" }]
    * 說明：管理員刪除數筆產品

/orders
=====

1. GET --cookie

    * 說明：回傳用戶的所有訂單。如果是管理員，還會回傳負責的訂單及尚未處理的訂單。
    * 回傳格式：if admin => { "MY_ORDERS": ["ID"], "NOT_TAKEN": ["ID"], "I_TAKE": ["ID"] } or { "MY_ORDERS": ["ID"] }

2. POST --cookie

    * 格式：{ "items": [{ "productId": "ID_STRING", "amount": "NUMBER" }] }
    * 說明：用戶新增一筆訂單在他的帳戶裡。產品的剩餘數量會減少。SERVER 會計算總價錢並回傳。
    * 回傳格式：{ "total": "NUMBER" }