//db.getCollectionNames()
//db.accounts.find({})
var restify  = require('restify');
var server   = restify.createServer();
server.use(restify.bodyParser());

var mongoose = require('mongoose');
var Schema   = mongoose.Schema;
mongoose.connect('mongodb://localhost/test1');
//mongoose.connect('mongodb://localhost/depot');

var AccountSchema = new Schema({
    username: String,
    password: String,
    orders  : [Schema.Types.ObjectId],
    orders_taken: [Schema.Types.ObjectId],
    type:String
});

var OrderSchema = new Schema({
    state: String,
    items: [{
        product:Schema.Types.ObjectId,
        amount:Number
    }],
    submitted: Boolean,
    ordered_by: [Schema.Types.ObjectId],
    taken_by: [Schema.Types.ObjectId]
});

var ProductSchema = new Schema({
    name:String,
    stock:Number,
    price:Number
});

//AccountSchema.static('findByUsername', function (name, callback) {
//    return this.find({ username: name }, callback);
//});

var Account = mongoose.model('Accounts', AccountSchema);
var Order   = mongoose.model('Order', OrderSchema);
var Product = mongoose.model('Product', ProductSchema);

server.pre(function(req, res, next) {
    req.headers.accept = 'application/json';
    return next();
});

server.post('/register', function(request, response, next) {

    console.log("username = " + request.params.username);
    console.log("password = " + request.params.password);

    if(request.params.username && request.params.password){
        Account.findOne({username: request.params.username}, function (err, obj) {
            if(err)
            {
                console.log("error:" + err);
                response.send(500, {message: "sorry gooby, I don't know what's going on. contact me pls"});

            }else{
                console.log(" obj = " + obj);
                if(obj){
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
                        if(error){
                            response.send(500, {message: "sorry gooby, database server is down!!"});
                        }else{
                            response.send(200, {message: "Successful, very good gooby, that's my good dog."});
                        }
                    });
                }
            }
        });

    }else{
        response.send(400, {message: "fuck you gooby, input the right format!!!"});
    }

    return next();
});

server.post('/login', function(request, response, next) {

    console.log("username = " + request.params.username);
    console.log("password = " + request.params.password);

    if(request.params.username && request.params.password){
        Account.findOne({username: request.params.username}, function (err, obj) {
            if(err)
            {
                console.log("error:" + err);
                response.send(500, {message: "sorry gooby, I don't know what's going on. contact me pls"});
            }else{
                console.log(" obj = " + obj);
                if(obj){
                    if(obj.username == request.params.username && obj.password == request.params.password){
                        response.send(200, {message: "Login successfully, gooby!!"});
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

server.listen(80, function() {
    console.log(server.name + ' listening at ' +  server.url);
});
