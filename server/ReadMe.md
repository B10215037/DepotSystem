目前的使用者(帳號 密碼)
=====
* admin     admin
* dolan     xyz
* dolan2    xyz
* dolan3    xyz

所有的運送狀態enum
=====
* Archived
* Submitted
* Processing
* Shipping
* Arrived

http://140.118.175.208/register
=====
* 使用:POST
* 格式:{"username": "dolan", "password":"xyz"}

http://140.118.175.208/login
=====
* 使用:POST
* 格式:{"username": "dolan", "password":"xyz"}

http://140.118.175.208/logout
=====
* 使用:GET
* 格式:沒有

http://140.118.175.208/products
=====
1. 使用:POST(需要cookie，管理員限定，一般使用者無法使用)

* 格式:[{"productname": "toastA", "stock":30, "price": 100}, {"productname": "toastB", "stock":30, "price": 100}]
* 說明:管理員新增數筆產品，stock表示進貨數量，如果新增了一筆已經在資料庫上的商品，會出現錯誤，請使用put更新資料庫

2. 使用:GET

* 格式:沒有格式
* 說明:會回傳所有產品的清單(json)

3. 使用:PUT(需要cookie，管理員限定，一般使用者無法使用)

* 格式:[{"id":"xxxxxxxx", "productname": "toast", "stock":30, "price": 100}, {"id":"xxxxxxxx", "productname": "toastA", "stock":30, "price": 100}]
* 說明:管理員更新數筆產品，stock表示進貨數量，id必填，productname商品名字或stock進貨數量或price價錢選填

4. 使用:DELETE(需要cookie，管理員限定，一般使用者無法使用)

* 格式:[{"id":"xxxxxxxx1"}, {"id":"xxxxxxxx2"}]
* 說明:管理員刪除數筆產品

http://140.118.175.208/orders
=====

1. 使用:GET(管理員限定)

* 格式:沒有格式
* 說明:會回傳所有用戶的所有訂單(json)


http://140.118.175.208/userOrders
=====

1. 使用:GET(需要cookie)

* 格式:沒有格式
* 說明:回傳現在登入的用戶的所有訂單(ID)

2. 使用:POST(需要cookie)
* 格式:{"state": "Shipping","items": [{"id": "566febe0078f5560221a60f5","amount": 3}, {"id": "56710e9395d1572c0525b434","amount": 5}]}
* 說明:用戶新增一筆訂單在他的帳戶裡，產品的剩餘數量會減少，server會計算新訂單的總價錢，使用GET查看訂單和總價錢