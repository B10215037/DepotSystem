重要事項
=====
感謝OQ花了浪費一堆時間讓server端得到了一些心得

如果出現了Bad Request或者Internal Server Error，表示你連進來了，不過因為一些原因被server擋下操作，

我這邊會回傳post錯誤時的訊息，你們Qt應該有辦法拿到那個訊息才對，不應該只是出現Bad Request或者Internal Server Error，

正常來說會出現被server reject的原因，例如:"fuck you gooby!!!, you didn't login or you are not an admin!!"

所以你們應該要想辦法找出怎麼用Qt噴出這些訊息，不然就會像OQ那樣Debug半天 :D


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

* 格式:{"productname": "toast", "stock":30, "price": 100}
* 說明:管理員新增一筆產品，stock表示進貨數量，如果新增了一筆已經在資料庫上的商品，會出現錯誤，請使用put更新資料庫

2 使用:GET

* 格式:沒有格式
* 說明:會回傳所有產品的清單(json)

3 使用:PUT(需要cookie，管理員限定，一般使用者無法使用)

* 格式:{"productname": "toast", "stock":30, "price": 100}或{"productname": "toast", "stock":30}或{"productname": "toast", "price":30}
* 說明:管理員更新一筆產品，stock表示進貨數量，productname必填，stock進貨數量或price價錢選填，進貨數量stock會跟原本的商品數量stock相加
