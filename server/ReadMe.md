IP/register
=====
* 使用:POST
* 格式:{"username": "dolan", "password":"xyz"}

IP/login
=====
* 使用:POST
* 格式:{"username": "dolan", "password":"xyz"}

IP/logout
=====
* 使用:GET
* 格式:沒有

IP/products
=====
1 使用:POST(需要cookie，管理員限定，一般使用者無法使用)

* 格式:{"productname": "toast", "stock":"30", "price", "100"}
* 說明:管理員新增一筆產品，stock表示進貨數量

2 使用:GET

* 格式:沒有格式
* 說明:會回傳所有產品的清單(json)

3 使用PUT

* 格式:{"productname": "toast", "stock":"30", "price", "100"}或{"productname": "toast", "stock":"30"}或{"productname": "toast", "price":"30"}
* 說明:管理員更新一筆產品，stock表示進貨數量，productname必填，stock進貨數量或price價錢選填
