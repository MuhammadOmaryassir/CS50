from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    # select each symbol owned by the user and it's amount
    portfolio_symbols = db.execute("SELECT shares, symbol \
                                    FROM Portfolios WHERE id = :id", \
                                    id=session["user_id"])
    
    # create a temporary variable to store TOTAL worth ( cash + share)
    total_cash = 0
    
    # update each symbol prices and total
    for portfolio_symbol in portfolio_symbols:
        symbol = portfolio_symbol["symbol"]
        shares = portfolio_symbol["shares"]
        stock = lookup(symbol)
        total = shares * stock["price"]
        total_cash += total
    # update user's cash in portfolio
    updated_cash = db.execute("SELECT cash FROM users \
                               WHERE id=:id", id=session["user_id"])
    
    # update total cash -> cash + shares worth
    total_cash += updated_cash[0]["cash"]    
    
    #the amount of money any account start with
    #total_cash = 10000
    
    # display the Portfolio table
    Portfolios_table = db.execute("SELECT * FROM Portfolios WHERE id = :id",id = session["user_id"])
    
    # display the updated cash
    cashes = db.execute("SELECT cash FROM users WHERE id=:id",id = session["user_id"])
    
    return render_template("index.html", shares = Portfolios_table, \
    cash = usd(cashes[0]["cash"]), total=usd(total_cash) )

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    # if user reached route via POST
    if request.method == "POST":
       
        # ensure proper symbol
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Invalid Symbol")
        
        # ensure proper number of shares
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("Shares must be positive integer")
        except:
            return apology("Shares must be positive integer")
        
        # select user's cash
        money = db.execute("SELECT cash FROM users WHERE id = :id",id=session["user_id"])
        
        # check if enough money to buy
        if not money or float(money[0]["cash"]) < stock["price"] * shares:
            return apology("Not enough money")
            
        # update user cash               
        db.execute("UPDATE users SET cash = cash - :purchase WHERE id = :id", \
                    id=session["user_id"], \
                    purchase=stock["price"] * float(shares))
                    
                   
        
        # update history
        db.execute("INSERT INTO History (symbol, shares, price, id) \
                    VALUES(:symbol, :shares, :price, :id)", \
                    symbol=stock["symbol"], shares=shares, \
                    price=usd(stock["price"]), id=session["user_id"])
                       
        
        # Select user shares of that symbol
        userShares = db.execute("SELECT shares FROM Portfolios \
                           WHERE id = :id AND symbol=:symbol", \
                           id=session["user_id"], symbol=stock["symbol"])
                           
        # if user doesn't has shares of that symbol
        if not userShares:
            db.execute("INSERT INTO Portfolios (name, shares, price, total, symbol, id) \
                        VALUES(:name, :shares, :price, :total, :symbol, :id)", \
                        name=stock["name"], shares=shares, price=usd(stock["price"]), \
                        total=usd(shares * stock["price"]), \
                        symbol=stock["symbol"], id=session["user_id"])
                        
        
        else:
            
            TotalShares = userShares[0]["shares"] + shares
            TotalCost = usd(TotalShares * stock["price"])
            
            db.execute("UPDATE Portfolios SET shares=:shares WHERE id=:id AND symbol=:symbol", \
                        shares=TotalShares, id=session["user_id"], \
                        symbol=stock["symbol"])
                        
            db.execute("UPDATE Portfolios SET total=:total WHERE id=:id AND symbol=:symbol",\
            total=TotalCost, id=session["user_id"], symbol=stock["symbol"])
                    
        
        # return to index
        return redirect(url_for("index"))
        
    else:
        return render_template("buy.html")
        

@app.route("/history")
@login_required
def history():
    """Show history of historytransactions."""
    
    #select all the content in the history database
    History  = db.execute("SELECT * FROM History WHERE id = :id",id = session["user_id"])    
    
    return render_template("history.html", histories = History )


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if user reached route via POST 
    if request.method == "POST":
        
    #use the lookup function to search on a symbol
        quoted = lookup(request.form.get("symbol"))
        
        #check if it's a valid symbol
        if quoted:
            return render_template("quoteing.html", stocks = quoted)
        else:    
            return apology("Invalid Symbol")
        
        
    else:    
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # if user reached route via POST 
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("You must provide a username")
            
        # ensure password was submitted
        if not request.form.get("password"):
            return apology("You must provide a Password")
            
        # ensure confirmation password  is matched the original one
        if request.form.get("password") != request.form.get("password1"):
            return apology("The Passwords isn't Matching")
     
        #query for the Database     
        result = db.execute("INSERT INTO users(username,hash)\
        VALUES(:username, :hash)",\
        username=request.form.get("username"), hash=pwd_context.encrypt(request.form.get("password")))
            
        # if the db query return failer    
        if not result:
            return apology("username  is already exist")
            
              
        #remember which user has logged in
        session["user_id"] = result

        #redirect user to home page
        return redirect(url_for("index"))
        
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    # if user reached route via POST
    if request.method == "POST":
       
        # ensure proper symbol
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Invalid Symbol")
        
        # ensure proper number of shares
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("Shares must be positive integer")
        except:
            return apology("Shares must be positive integer")
            
        # select user's shares
        Shares = db.execute("SELECT shares FROM Portfolios WHERE id = :id",id=session["user_id"])
        
        # check if enough shares to sel to buy
        if not Shares or int(Shares[0]["shares"]) < shares:
            return apology("You dont have this share to see!!")
            
        #update user's cash    
        db.execute("UPDATE users SET cash = cash + :purchase WHERE id = :id", \
                    id=session["user_id"], \
                    purchase=stock["price"] * float(shares))
                    
         
        # update history
        db.execute("INSERT INTO History (symbol, shares, price, id) \
                    VALUES(:symbol, :shares, :price, :id)", \
                    symbol=stock["symbol"], shares =- shares, \
                    price=usd(stock["price"]), id=session["user_id"])
                    
        #calculate the currnt amont of shares            
        TotalShares= Shares[0]["shares"] - shares  
        
        #update the Total cost
        TotalCost = usd(TotalShares * stock["price"])
        
        #chech if the user dosn't have share to sell
        #Delete the share from the portofolio table
        if TotalShares == 0:
            db.execute("DELETE FROM Portfolios WHERE id=:id AND symbol=:symbol", \
            id=session["user_id"],symbol=stock["symbol"])
        
        else:
            
            
            db.execute("UPDATE Portfolios SET shares=:shares WHERE id=:id AND symbol=:symbol", \
                        shares=TotalShares, id=session["user_id"], \
                        symbol=stock["symbol"])
                        
            db.execute("UPDATE Portfolios SET total=:total WHERE id=:id AND symbol=:symbol",\
            total=TotalCost, id=session["user_id"], symbol=stock["symbol"])
            
        # return to index
        return redirect(url_for("index"))
        
    else:
        return render_template("sell.html")
        
        
@app.route("/withdraw", methods=["GET","POST"])
@login_required
def withdraw():
    """withdraw From The Bank"""
    # if user reached route via POST 
    if request.method == "POST":
        
        try:
            withdraw = int(request.form.get("amount"))
        
            #couple if checks
            if withdraw <= 0:
                apology("You can't withdraw that amount")
            elif withdraw > 2000:
                apology("You can't withdraw More than 2000$ at once")
        except:
            apology("You can't withdraw that amount")    
        
        
        #update user's cash
        db.execute("UPDATE users SET cash = cash + :withdraw WHERE id = :id", \
        withdraw=withdraw,id=session["user_id"])
        
        
        return redirect(url_for("index"))
        
    else:    
        return render_template("withdraw.html")
        