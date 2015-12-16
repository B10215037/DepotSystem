Connector用法
=====
	connector = new Connector();
	connect(connector, SIGNAL(finished(QNetworkReply*)),
            connector, SLOT(replyFinished(QNetworkReply*)));
    connect(connector, SIGNAL(sendReceivedMessage(QString)),
            this, SLOT(receiveMessage(QString)));

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

* void registerAccount(QString userName, QString password);

IP/login
=====
* 使用:POST
* 格式:{"username": "dolan", "password":"xyz"}

* void logIn(QString userName, QString password);

IP/logout
=====
* 使用:GET
* 格式:沒有

* void logOut();

IP/products
=====
1 使用:POST(需要cookie，管理員限定，一般使用者無法使用)

* 格式:{"productname": "toast", "stock":30, "price": 100}
* 說明:管理員新增一筆產品，stock表示進貨數量，如果新增了一筆已經在資料庫上的商品，會出現錯誤，請使用put更新資料庫

* void postNewProducts(Product *products, int size);

2 使用:GET

* 格式:沒有格式
* 說明:會回傳所有產品的清單(json)

* void getProductsInfo()

3 使用:PUT(需要cookie，管理員限定，一般使用者無法使用)

* 格式:{"productname": "toast", "stock":30, "price": 100}或{"productname": "toast", "stock":30}或{"productname": "toast", "price":30}
* 說明:管理員更新一筆產品，stock表示進貨數量，productname必填，stock進貨數量或price價錢選填，進貨數量stock會跟原本的商品數量stock相加

* void putEditedProducts(Product *products, int size);
