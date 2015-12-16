目前的使用者(帳號 密碼)
=====
* admin     admin
* dolan     xyz
* dolan2    xyz
* dolan3    xyz

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

* 格式:[{"productname": "toastA", "stock":30, "price": 100}, {"productname": "toastB", "stock":30, "price": 100}]
* 說明:管理員新增數筆產品，stock表示進貨數量，如果新增了一筆已經在資料庫上的商品，會出現錯誤，請使用put更新資料庫

2 使用:GET

* 格式:沒有格式
* 說明:會回傳所有產品的清單(json)

3 使用:PUT(需要cookie，管理員限定，一般使用者無法使用)

* 格式:[{"id":"xxxxxxxx", "productname": "toast", "stock":30, "price": 100}, {"id":"xxxxxxxx", "productname": "toastA", "stock":30, "price": 100}]
* 說明:管理員更新數筆產品，stock表示進貨數量，id必填，productname商品名字或stock進貨數量或price價錢選填，進貨數量stock會跟原本的商品數量stock相加
