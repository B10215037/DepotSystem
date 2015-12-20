//db.getCollectionNames()
//db.accounts.find()
//db.products.remove({"name":"toastA"})
var restify  = require('restify');
var server   = restify.createServer();
server.use(restify.bodyParser());

var sessions = require("client-sessions");
server.use(sessions({
    cookieName: 'depotSession', // cookie name dictates the key name added to the request object
    secret: 'DolanGooby', // should be a large unguessable string
    duration: 3 * 24 * 60 * 60 * 1000 // how long the session will stay valid in ms
}));

var mongoose = require('mongoose');
var Schema   = mongoose.Schema;
mongoose.connect('mongodb://localhost/test1');
//mongoose.connect('mongodb://localhost/depot');

var AccountSchema = new Schema({
    username: String,
    password: String,
    orders  : [Schema.Types.ObjectId],
    orders_taken: [Schema.Types.ObjectId],
    type: String
});

var OrderSchema = new Schema({
    state: String,
    items: [{
        product: Schema.Types.ObjectId,
        amount: Number
    }],
    submitted: Boolean,
    ordered_by: [Schema.Types.ObjectId],
    taken_by: [Schema.Types.ObjectId]
});

var ProductSchema = new Schema({
    name: String,
    stock: Number,
    price: Number
});

//AccountSchema.static('findByUsername', function (name, callback) {
//    return this.find({ username: name }, callback);
//});

var Account = mongoose.model('Accounts', AccountSchema);
var Order   = mongoose.model('Order', OrderSchema);
var Product = mongoose.model('Product', ProductSchema);

server.pre(function (request, response, next) {
    request.headers.accept = 'application/json';
    return next();
});

server.post('/register', function (request, response, next) {

    console.log("username = " + request.params.username);
    console.log("password = " + request.params.password);

    if (request.params.username && request.params.password) {
        Account.findOne({username: request.params.username}, function (err, user) {
            if (err)
            {
                console.log("error:" + err);
                response.send(500, {message: "sorry gooby, I don't know what's going on. contact me pls"});
            } else {
                console.log(" user = " + user);
                if (user) {
                    response.send(500, {message: "fuck you gooby, this username is already used!!"});
                }
                else
                {
                    var newUser = new Account({
                        username: request.params.username,
                        password: request.params.password,
                        type:"customer"
                    });
                    newUser.save(function(error){
                        if (error) {
                            response.send(500, {message: "sorry gooby, database server is down!!"});
                        } else {
                            response.send(200, {message: "Successful, very good gooby, that's my good dog."});
                        }
                    });
                }
            }
        });

    } else {
        response.send(400, {message: "fuck you gooby, input the right format!!!"});
    }

    return next();
});

server.post('/login', function(request, response, next) {

    console.log("username = " + request.params.username);
    console.log("password = " + request.params.password);

    if(request.params.username && request.params.password){
        Account.findOne({username: request.params.username}, function (err, user) {
            if (err)
            {
                console.log("error:" + err);
                response.send(500, {message: "sorry gooby, I don't know what's going on. contact me pls"});
            }else{
                console.log(" user = " + user);
                if(user){
                    if(user.username === request.params.username && user.password === request.params.password){
                        request.depotSession.username = user.username;
                        console.log(request.depotSession.username);
                        if( user.type == "admin" ){
                            response.send(200, {message: "Admin login successfully, gooby!!"});
                        }else{
                            response.send(200, {message: "User login successfully, gooby!!"});
                        }
                    }else{
                        response.send(500, {message: "Wrong password, stupid gooby!!"});
                    }
                }else{
                    response.send(500, {message: "fuck you gooby, this username doesn't exist!!"});
                }
            }
        });

    }else{
        response.send(400, {message: "fuck you gooby, input the right format!!!"});
    }

    return next();
});

server.get('/logout', function(request, response, next){
    if(request.depotSession.username){
        request.depotSession.reset();
        request.depotSession = null;
    }
    response.send(200, {message: "Log out successfully, good gooby"});
    return next();
});

server.post('/products', function(request, response, next){
    if (!request.depotSession.username) {
        response.send(400, {message: "fuck you gooby!!!, you didn't login or you are not an admin!!"});
    } else {
        Account.findOne({username: request.depotSession.username}, function (err, user) {
            if(err){
                response.send(400, {message: "Sorry gooby!!!, Account Error!!!"});
            }
            if(user.type == "admin"){
                request.params.forEach(function(item) {
                    if(item.productname){
                        Product.findOne({name: item.productname}, function (err, existed) {
                            if(err)
                            {
                                console.log("error:" + err);
                                response.send(500, {message: "sorry gooby, I don't know what's going on. contact me pls"});
                            }
                            else
                            {
                                console.log(" product = " + existed);
                                if(existed){
                                    response.send(400, {message: "fuck you gooby!!!, this product has already been added!!"});
                                }else{
                                    var product = new Product({
                                        name: item.productname,
                                        stock: item.stock,
                                        price: item.price
                                    });
                                    product.save(function(error){
                                        if(error){
                                            response.send(500, {message: "Sorry gooby, database server is down!!"});
                                        }else{
                                            response.send(200, {message: "Successful, very good gooby, You add a product."});
                                        }
                                    });
                                }
                            }
                        });
                    }else{
                        response.send(400, {message: "fuck you gooby, send the right format!!!"});
                    }
                });
            }else if(user.type == "customer"){
                response.send(500, {message: "fuck you gooby, you are not an admin!!!"});
            }else{
                response.send(500, {message: "fuck you gooby, sth wrong in user accounts type!!!"});
            }
        });
    }
    return next();
});

server.get('/products', function(request, response, next)
{
    Product.find({}, function (err, products) {
        response.send(200, products);
    });
    return next();
});

server.put('/products', function(request, response, next)
{
    if (!request.depotSession.username) {
        response.send(400, {message: "fuck you gooby!!!, you didn't login or you are not an admin!!"});
    } else {
        Account.findOne({username: request.depotSession.username}, function (err, user) {
            if(user.type == "admin"){
                request.params.forEach(function(item)
                {
                    if(item.id){
                        Product.findOne({_id: item.id}, function (err, product) {
                            if(err){
                                console.log("error:" + err);
                                response.send(500, {message: "sorry gooby, I don't know what's going on. contact me pls"});
                            }else{
                                console.log("product = " + product);
                                Product.findOne({name: item.productname}, function (err, productWithNewName) {
                                    if(productWithNewName){
                                        response.send(500, {message: "fuck you gooby, use different product name!!"});
                                        return next();
                                    }
                                    if(product){
                                        if(item.productname){
                                            product.name = item.productname;
                                        }
                                        if(item.stock){
                                            product.stock = item.stock;
                                        }
                                        if(item.price){
                                            product.price = item.price;
                                        }
                                        product.save(function(error) {
                                            if(error){
                                                response.send(500, {message: "Sorry gooby, database server is down!!"});
                                            }else{
                                                response.send(200, {message: "Successful, very good gooby, You update a product."});
                                            }
                                        });
                                    }else{
                                        response.send(500, {message: "fuck you gooby, this product doesn't exist !!"});
                                    }
                                });
                            }
                        });
                    }else{
                        response.send(400, {message: "fuck you gooby, send the right format!!!"});
                    }
                });
            }else if(user.type == "customer"){
                response.send(400, {message: "fuck you gooby, you are not a admin!!!"});
            }else{
                response.send(500, {message: "fuck you gooby, sth wrong in user accounts type!!!"});
            }
        });
    }
    return next();
});

server.del('/products', function(request, response, next)
{
    if (!request.depotSession.username) {
        response.send(400, {message: "fuck you gooby!!!, you didn't login or you are not an admin!!"});
    } else {
        Account.findOne({username: request.depotSession.username}, function (err, user) {
            if(user.type == "admin"){
                request.params.forEach(function(item)
                {
                    if(item.id)
                    {
                        Product.findOne({_id: item.id}).remove().exec();
                    }
                });
                response.send(200, {message: "delete successfully, gooby!!!"});
            } else if (user.type == "customer") {
                response.send(400, {message: "fuck you gooby, you are not a admin!!!"});
            } else {
                response.send(500, {message: "fuck you gooby, sth wrong in user accounts type!!!"});
            }
        });
    }
    return next();
});

server.get('/orders', function(request, response, next)
{
    if (!request.depotSession.username) {
        request.send(400, { message: "fuck you gooby!!!, you didn't login or you are not an admin!!" });
    } else {
        Account.findOne({ username: request.depotSession.username }, function (err, user) {
//            var orders = [];
//            for (order of user.orders) {
//                Order.findOne({ _id: mongoose.Types.ObjectId(order._id) }, function(err, order) {
//                    orders.push(order);
//                });
//            }
            response.send(200, user.orders);
        });
    }
});

server.post('/orders', function(request, response, next) {
    if ( !request.depotSession.username) {
        response.send(400, { message: "fuck you gooby!!!, you didn't login or you are not an admin!!" });
    } else {
        Account.findOne({ username: request.depotSession.username }, function (err, user) {
            var totalPrice = 0;
            if ( request.params.state )
            {
                var order = new Order({
                    state: request.params.state,
                    price: 0,
                    items: [],
                    ordered_by: user.username
                });
            } else {
                response.send(500, {message: "fuck you gooby, wrong format!!!"});
                return next();
            }
            for (item of request.params.items)
            {
                if(item.id) {
                    Product.findOne({_id: item.id}, function (err, product) {
                        if (!product){
                            response.send(500, {message: "fuck you gooby, product not found!!!"});
                        } else {
                            console.log(item);
                            product.stock -= item.amount;
                            totalPrice += item.amount * product.price;
                            order.items.push({
                                product: item.id,
                                amount:  item.amount
                            });
                        }
                    });
                } else {
                    response.send(500, {message: "fuck you gooby, wrong format!!!"});
                }
            }
            console.log("totalPrice:" + totalPrice);
            order.price = totalPrice;
            order.save(function(error){
                if(error){
                    response.send(500, {message: "Sorry gooby, database server is down!!"});
                }else{
                    response.send(200, {message: "Successful, very good gooby, You add a order."});
                }
            });
            console.log(order);
            user.orders.push(order._id);
            response.send(200, {message: "Add orders successfully, gooby!!!"});
        });
    }
    return next();
});

server.listen(80, function() {
    console.log(server.name + ' listening at ' +  server.url);
});
