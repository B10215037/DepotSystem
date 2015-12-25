'use strict';
var restify = require('restify');
var server = restify.createServer();
server.use(restify.bodyParser());

var sessions = require('client-sessions');
server.use(sessions({
    cookieName: 'depotSession',
    secret: 'DolanGooby',
    duration: 3 * 24 * 60 * 60 * 1000
}));

var mongoose = require('mongoose');
var Schema = mongoose.Schema;
mongoose.connect('mongodb://admin:admin@ds056688.mongolab.com:56688/depot');

var AccountSchema = new Schema({
    username: String,
    password: String,
    orders: [Schema.Types.ObjectId],
    orders_taken: [Schema.Types.ObjectId],
    type: String
});

var OrderSchema = new Schema({
    state: String,
    items: [{
        productId: Schema.Types.ObjectId,
        amount: Number
    }],
    ordered_by: String,
    taken_by: String
});

var ProductSchema = new Schema({
    name: String,
    stock: Number,
    price: Number
});

var Account = mongoose.model('Accounts', AccountSchema);
var Order = mongoose.model('Order', OrderSchema);
var Product = mongoose.model('Product', ProductSchema);

server.pre(function (req, res, next) {
    req.headers.accept = 'application/json';
    return next();
});

function checkLoginned(req, res, next) {
    if (! req.depotSession.username) return next(new restify.UnauthorizedError('NOT YET LOGINNED'));
    return next();
}

function checkAdmin(req, res, next) {
    Account.findOne({ username: req.depotSession.username }, function (err, user) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (! user) return next(new restify.UnauthorizedError('USER NOT EXIST'));
        if (user.type != 'admin') return next(new restify.ForbiddenError('CUSTOMER NOT ALLOWED'));
        return next();
    });
}

server.post('/register', function(req, res, next) {
    if (! req.params.username || ! req.params.password) return next(new restify.BadRequestError('WRONG FORMAT'));

    Account.findOne({ username: req.params.username }, function(err, user) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (user) return next(new restify.ForbiddenError('USERNAME EXISTED'));

        var user = new Account({
            username: req.params.username,
            password: req.params.password,
            type: 'customer'
        });
        user.save(function(err) {
            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
            res.send(200);
        });
    });
});

server.post('/login', function(req, res, next) {
    if (! req.params.username || ! req.params.password) return next(new restify.BadRequestError('WRONG FORMAT'));

    Account.findOne({ username: req.params.username }, function(err, user) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (! user) return next(new restify.UnautorizedError('USER NOT EXISTED'));
        if (user.password != req.params.password) return next(new restify.UnauthorizedError('WRONG PASSWORD'));

        req.depotSession.username = req.params.username;
        if (user.type == 'admin') {
            res.send(200, { type: 'Admin' });
        } else if (user.type == 'customer'){
            res.send(200, { type: 'User' });
        } else {
            return next(new restify.UnautorizedError('WHICH TYPE ARE YOU OF'));
        }
    });
});

server.get('/logout', checkLoginned, function(req, res, next) {
    req.depotSession.reset();
    res.send(200);
});

server.get('/products/:id', function(req, res, next) {
    Product.findOne({ _id: req.params.id }, function(err, product) {
        res.send(200, product);
    });
});

server.get('/products', function(req, res, next) {
    Product.find({}, function(err, products) {
        res.send(200, products);
    });
});

server.post('/products', checkLoginned, checkAdmin, function(req, res, next) {
    if (! req.params._DELETE) {
        for (let item of req.params) if (! item.name) return next(new restify.BadRequestError('WRONG FORMAT'));

        let saved = 0;
        for (let item of req.params) {
            Product.findOne({ name: item.name }, function(err, product) {
                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                if (product) return next(new restify.ForbiddenError('PRODUCT DEFINED'));

                product = new Product({
                    name: item.name,
                    stock: item.stock,
                    price: item.price
                });
                product.save(function(err) {
                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                    if (++saved == req.params.length) res.send(200);
                });
            });
        }
    } else {
        let saved = 0;
        req.params.data.forEach(function(productId) {
            Product.findOne({ _id: productId }, function(err, product) {
                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                if (! product) return next(new restify.ForbiddenError('NO SUCH PRODUCT'));

                product.remove(function(err) {
                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                    if (++saved == req.params.data.length) {
                        res.send(200);
                    }
                });
            });
        });
    }
});

server.put('/products', checkLoginned, checkAdmin, function(req, res, next) {
    let saved = 0;
    req.params.forEach(function(item) {
        if (! item.id) return next(new restify.BadRequestError('WRONG FORMAT'));

        Product.findOne({ _id: item.id }, function(err, product) {
            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
            if (! product) return next(new restify.BadRequest('PRODUCT NOT EXISTED'));

            if (item.name) {
                Product.findOne({ name: item.name }, function(err, existed) {
                    if (existed && existed._id != item.id) return next(new restify.ForbiddenError('PRODUCT NAME EXISTED'));

                    product.name = item.name;
                    if (item.stock) product.stock = item.stock;
                    if (item.price) product.price = item.price;
                    product.save(function(err) {
                        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                        if (++saved == req.params.length) res.send(200);
                    });
                });
            } else {
                if (item.stock) product.stock = item.stock;
                if (item.price) product.price = item.price;
                product.save(function(err) {
                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                    if (++saved == req.params.length) res.send(200);
                });
            }
        });
    });
});

server.del('/products/:id', checkLoginned, checkAdmin, function(req, res, next) {
    Product.findOne({ _id: req.params.id }, function(err, product) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (! product) return next(new restify.ForbiddenError('NO SUCH PRODUCT'));

        product.remove(function(err) {
            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

            res.send(200);
        });
    });
});

server.get('/orders/:id', checkLoginned, function(req, res, next) {
    Account.findOne({ username: req.depotSession.username }, function(err, user) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (! user) return next(new restify.UnautorizedError('USER NOT EXISTED'));
        if (order.ordered_by != req.depotSession.username || user.type != 'admin')
            return next(new restify.ForbiddenError('NOT YOUR ORDER'));

        Order.findOne({ _id: req.params.id }, function(err, order) {
            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

            res.send(200, order);
        });
    });
});

server.get('/orders', checkLoginned, function(req, res, next) {
    Account.findOne({ username: req.depotSession.username }, function(err, user) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (! user) return next(new restify.UnautorizedError('USER NOT EXISTED'));

        var response = {};
        Account.findOne({ username: req.depotSession.username }, function(err, user) {
            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

            response.MY_ORDERS = [];
            if (user.type == 'customer') {
                let got = 0;
                for (let orderId of user.orders) {
                    Order.findOne({ _id: orderId }, function(err, order) {
                        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                        response.MY_ORDERS.push(order);
                        if (++got == user.orders.length) res.send(200, response);
                    });
                }
            } else if (user.type == 'admin') {
                response.I_TAKE = [];
                response.NOT_TAKEN = [];
                Order.find({}, function(err, orders) {
                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                    for (let order of orders) {
                        if (order.ordered_by == user.username) {
                            response.MY_ORDERS.push(order);
                        }
                        if (! order.taken_by && order.state == 'submitted') {
                            response.NOT_TAKEN.push(order);
                        }
                        if (order.taken_by == user.username) {
                            response.I_TAKE.push(order);
                        }
                    }
                    res.send(200, response);
                });
            }
        });
    });
});

server.post('/orders', checkLoginned, function(req, res, next) {
    if (! req.params._DELETE) {
        for (let item of req.params) if (! item.productId) return next(new restify.BadRequestError('WRONG FORMAT'));

        var total = 0;
        var items = [];
        var lookup = {};

        req.params.forEach(function (item) {
            Product.findOne({ _id: item.productId }, function(err, product) {
                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                if (! product) return next(new restify.BadRequestError('PRODUCT NOT EXISTED'));
                if (product.stock < item.amount) return next(new restify.ForbiddenError('STOCK NOT AVAILABLE'));

                product.stock -= item.amount;
                product.save(function(err) {
                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                    total += item.amount * product.price;
                    if (lookupItems[item.productId]) {
                        lookupItems[item.productId].amount += parseInt(item.amount);
                    } else {
                        items.push({
                            productId: item.productId,
                            amount: item.amount
                        });
                        lookup[item.productId] = items[items.length - 1];
                    }

                    if (items.length == req.params.length) {
                        var order = new Order({
                            state: 'archived',
                            items: items,
                            ordered_by: req.depotSession.username
                        });
                        order.save(function(err) {
                            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                            Account.findOne({ username: req.depotSession.username }, function(err, user) {
                                user.orders.push(order._id);
                                user.save(function(err) {
                                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                                    res.send(200, { total: total });
                                });
                            });
                        });
                    }
                });
            });
        });
    } else if (req.params._DELETE == 'true') {
        for (let orderId of req.params.data) if (! orderId) return next(new restify.BadRequestError('WRONG FORMAT'));

        let removed = 0
        for (let orderId of req.params.data) {
            Order.findOne({ _id: orderId }, function(err, order) {
                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                if (order.state != 'archived') return next(new restify.ForbiddenError('HAVE SUBMITTED'));
                if (order.ordered_by != req.depotSession.username) return next(new restify.ForbiddenError('NOT YOUR ORDER'));

                order.remove(function(err) {
                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                    if (++removed == req.params.length) res.send(200);
                });
            });
        }
    }
});

server.put('/orders', checkLoginned, function(req, res, next) {
    for (let order of req.params) if (! order.id) return next(new restify.BadRequestError('WRONG FORMAT'));

    Account.findOne({ username: req.depotSession.username }, function(err, user) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (! user) return next(new restify.BadRequestError('USER NOT EXISTED'));

        for (let order of req.params) {
            Order.findOne({ _id: order.id }, function(err, dbOrder) {
                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                if (! dbOrder) return next(new restify.BadRequestError('ORDER NOT EXISTED'));

                if (order.taken_by) {
                    if (user.type != 'admin')
                        return next(new restify.ForbiddenError('CUSTOMER CAN ONLY MODIFY ORDER ITEMS'));
                    if (dbOrder.state == 'archived')
                        return next(new restify.ForbiddenError('NOT YET SUBMITTED'));
                    if (dbOrder.taken_by && dbOrder.taken_by != order.taken_by)
                        return next(new restify.ForbiddenError('ALREADY TAKEN'));

                    dbOrder.taken_by = order.taken_by;
                }

                if (! order.items) {
                    if (order.state) {
                        if (user.type == 'customer' && order.state != 'archived' && order.state != 'submitted')
                            return next(new restify.ForbiddenError('ONLY ADMIN CAN CHANGE TRANSFER STATE'));
                        if (user.type == 'admin' && dbOrder.taken_by != req.depotSession.username)
                            return next(new restify.ForbiddenError('NOT YOUR BUSINESS'));

                        dbOrder.state = order.state;
                    }

                    dbOrder.save(function(err) {
                        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                        res.send(200);
                    });
                } else {
                    if (dbOrder.state != 'archived' || dbOrder.ordered_by != req.depotSession.username)
                        return next(new restify.ForbiddenError('AFTER SUBMITTED UPDATE ITEMS NOT ALLOWED'));

                    if (order.state) {
                        if (user.type == 'customer' && order.state != 'archived' && order.state != 'submitted')
                            return next(new restify.ForbiddenError('ONLY ADMIN CAN CHANGE TRANSFER STATE'));
                        if (user.type == 'admin' && dbOrder.taken_by != req.depotSession.username)
                            return next(new restify.ForbiddenError('NOT YOUR BUSINESS'));

                        dbOrder.state = order.state;
                    }

                    for (let item of order.items) {
                        if (! item.productId) return next(new restify.BadRequestError('WRONG FORMAT'));
                        Product.findOne({ _id: item.productId }, function(err, product) {
                            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                            if (! product) return next(new restify.BadRequestError('SOME PRODUCTS NOT EXISTED'));
                        });
                    }

                    let saved = 0;
                    let lookupDb = {};
                    let getIndex = {};
                    for (let i in dbOrder.items) {
                        lookupDb[dbOrder.items[i].productId] = dbOrder.items[i];
                        getIndex[dbOrder.items[i].productId] = i;
                    }

                    for (let item of order.items) {
                        if (lookupDb[item.productId]) {
                            if (item.cancelled == 'true') {
                                Product.findOne({ _id: item.productId }, function(err, product) {
                                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                                    product.stock += lookupDb[item.productId].amount;
                                    product.save(function(err) {
                                        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                                        dbOrder.items.splice(getIndex[item.productId], 1);
                                        if (++saved == order.items.length) {
                                            dbOrder.save(function(err) {
                                                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                                                res.send(200);
                                            });
                                        }

                                        lookupDb = {};
                                        getIndex = {};
                                        for (let i in dbOrder.items) {
                                            lookupDb[dbOrder.items[i].productId] = dbOrder.items[i];
                                            getIndex[dbOrder.items[i].productId] = i;
                                        }
                                    });
                                });
                            } else if (item.amount) {
                                let difference = item.amount - lookupDb[item.productId].amount;
                                Product.findOne({ _id: item.productId }, function(err, product) {
                                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                                    if (product.stock < difference) return next(new restify.ForbiddenError('STOCK NOT AVAILABLE'));

                                    product.stock -= difference;
                                    lookupDb[item.productId].amount = item.amount;
                                    product.save(function(err) {
                                        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                                        if (++saved == order.items.length) {
                                            dbOrder.save(function(err) {
                                                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                                                res.send(200);
                                            });
                                        }
                                    });
                                });
                            }
                        } else {
                            if (! item.cancelled && item.amount) {
                                console.log(1);
                                Product.findOne({ _id: item.productId }, function(err, product) {
                                    if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                                    if (! product) return next(new restify.BadRequestError('PRODUCT NOT EXISTED'));
                                    if (product.stock < item.amount) return next(new restify.ForbiddenError('STOCK NOT AVAILABLE'));

                                    product.stock -= item.amount;
                                    product.save(function(err) {
                                        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

                                        dbOrder.items.push({
                                            productId: item.productId,
                                            amount: item.amount
                                        });
                                        lookupDb[item.productId] = dbOrder.items[dbOrder.items.length - 1];
                                        getIndex[item.productId] = dbOrder.items.length - 1;

                                        if (++saved == order.items.length) {
                                            dbOrder.save(function(err) {
                                                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                                                res.send(200);
                                            });
                                        }
                                    });
                                });
                            }
                        }
                    }
                }
            });
        }
        res.send(200);
    });
});

server.del('/orders/:id', function(req, res, next) {
    Order.findOne({ _id: req.params.id }, function(err, order) {
        if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
        if (order.state != 'archived') return next(new restify.ForbiddenError('HAVE SUBMITTED'));
        if (order.ordered_by != req.depotSession.username) return next(new restify.ForbiddenError('NOT YOUR ORDER'));

        order.remove(function(err) {
            if (err) return next(new restify.InternalServerError('DATABASE ERROR'));

            order.remove(function(err) {
                if (err) return next(new restify.InternalServerError('DATABASE ERROR'));
                if (++removed == req.params.length) res.send(200);
            }).exec();;
            res.send(200);
        });
    });
});

server.listen(80);
