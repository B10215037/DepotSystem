目前的使用者(帳號：密碼)
=====
1. admin: admin
2. dolan: gooby

所有的運送狀態 ENUM
=====
* archived
* submitted
* processing
* shipping
* arrived

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

2. GET /products/:id

    * 說明：可以拿單獨 id 查詢

2. POST --cookie（管理員限定）

    * 格式：[{ "name": "STRING", "stock": "NUMBER", "price": "NUMBER"}]
    * 說明：管理員新增數筆產品。

3. PUT --cookie（管理員限定）

    * 格式：[{ "id": "ID_STRING", "name": "STRING", "stock": "NUMBER", "price": "NUMBER" }]
    * 說明：管理員更新數筆產品。id 可從 GET /products 中獲取。

4. DELETE /products/:id --cookie（管理員限定）

    * 說明：管理員刪除數筆產品
    * 若要批次刪除，請用 POST /products 並標記 "_DELETE": "true"，格式為 { "data": ["ID"], "_DELETE": "true" }。

/orders
=====

1. GET --cookie

    * 說明：回傳用戶的所有訂單。如果是管理員，還會回傳負責的訂單及尚未處理的訂單。
    * 回傳格式：if admin => { "MY_ORDERS": [{}], "NOT_TAKEN": [{}], "I_TAKE": [{}] } or { "MY_ORDERS": [{}] }

2. GET /orders/:id --cookie

    * 說明：可以拿單獨 id 查詢。但如果使用者與該訂單無關則會被回絕。

2. POST --cookie

    * 格式：{ "items": [{ "productId": "ID_STRING", "amount": "NUMBER" }] }
    * 說明：用戶新增一筆訂單在他的帳戶裡。產品的剩餘數量會減少。SERVER 會計算總價錢並回傳。
    * 回傳格式：{ "total": "NUMBER" }

3. PUT --cookie

    * 格式：[{ "id": "ID", "state": "ENUM", "taken_by": "STRING", "items": [{ "productId": "ID", "amount": "NUMBER" }] }]
    * 說明：id 是必要的。若有 items，其中每項也必備 productId。如果要刪除一項 item，請加入 "cancelled": "true"。

4. DELETE /orders/:id --cookie

    * 說明：只有當訂單還是 archived 時（意即還在購物車）才能刪除，並且必須是由下訂單的人才能執行。
    * 若要批次刪除，請用 POST /orders 並標記 "_DELETE": "true"，格式為 { "data": ["ID"], "_DELETE": "true" }。