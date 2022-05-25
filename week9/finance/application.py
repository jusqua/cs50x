import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    shares = db.execute("SELECT * FROM shares WHERE user_id = ?", session["user_id"])
    total = 0
    for share in shares:
        total += share["total"]
    total += cash
    return render_template("index.html", shares=shares, total=total, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Get symbol from user
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol")

        # Get info parsing symbol
        quoted = lookup(symbol)
        if not quoted:
            return apology("unknown symbol")

        shares = request.form.get("shares")
        if not shares:
            return apology("missing shares")
        if not shares.isdigit() or float(shares) < 1:
            return apology("shares must be a positive integer")
        shares = int(shares)

        # Check cash disponibility
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if cash < quoted["price"] * shares:
            return apology("can't afford")

        # Save changes
        data = db.execute("SELECT amount, total FROM shares WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if data:
            db.execute("UPDATE shares SET amount = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                       shares + data[0]["amount"], quoted["price"], data[0]["total"] + shares * quoted["price"], session["user_id"], symbol)
        else:
            db.execute("INSERT INTO shares (user_id, symbol, name, amount, price, total) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], symbol, quoted["name"], shares, quoted["price"], shares * quoted["price"])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - quoted["price"] * shares, session["user_id"])

        # Append to history
        db.execute("INSERT INTO histories (user_id, symbol, amount, price, date_time) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, shares, quoted["price"])

        # Show info
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history_data = db.execute("SELECT * FROM histories WHERE user_id = ?", session["user_id"])
    return render_template("history.html", history=history_data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    """Log user out or delete account"""
    if request.method == "POST":
        option = request.form.get("option")

        if option == "change":
            # Check password fields
            old_password = request.form.get("old_password")
            if not old_password:
                return apology("missing old password", 403)

            old_hash = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"]
            print(old_hash)
            if not check_password_hash(old_hash, old_password):
                return apology("invalid old password", 403)

            new_password = request.form.get("new_password", 403)
            if not new_password:
                return apology("missing new password", 403)

            confirmation = request.form.get("confirmation")
            if new_password != confirmation:
                return apology("passwords don't match", 403)

            if old_password == new_password:
                return apology("new password should be different")

            # Save to database
            db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_password), session["user_id"])

        if option == "delete":
            db.execute("DELETE FROM histories WHERE user_id = ?", session["user_id"])
            db.execute("DELETE FROM shares WHERE user_id = ?", session["user_id"])
            db.execute("DELETE FROM users WHERE id = ?", session["user_id"])
            session.clear()

        if option == "logout":
            session.clear()

        # Forget any user_id
        return redirect("/")

    else:
        # Redirect user to settings
        return render_template("settings.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Get symbol from user
        symbol = request.form.get("symbol")

        # Get info parsing symbol
        quoted = lookup(symbol)
        if not quoted:
            return apology("unknown symbol")

        # Show info
        return render_template("quoted.html", info=quoted)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Check username field
        username = request.form.get("username")
        if not username:
            return apology("missing username", 400)
        if db.execute("SELECT username FROM users WHERE username = ?", username):
            return apology("username is not available", 400)
        password = request.form.get("password")

        # Check password fields
        if not password:
            return apology("missing password", 400)
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("passwords don't match", 400)

        # Save to database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = user[0]["id"]

        # Redirect user
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Get symbol from user
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol", 400)

        # Get info parsing symbol
        quoted = lookup(symbol)
        if not quoted:
            return apology("unknown symbol", 400)

        shares = int(request.form.get("shares"))
        if not shares:
            return apology("missing shares", 400)

        data = db.execute("SELECT symbol, amount, total FROM shares WHERE user_id = ?", session["user_id"])[0]
        if shares > data["amount"]:
            return apology("too many shares", 400)

        # Save changes
        if data["amount"] != shares:
            db.execute("UPDATE shares SET amount = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                       data["amount"] - shares, quoted["price"], data["total"] - shares * quoted["price"], session["user_id"], symbol)
        else:
            db.execute("DELETE FROM shares VALUES user_id = ? AND symbol = ?", session["user_id"], symbol)

        # Append to history
        db.execute("INSERT INTO histories (user_id, symbol, amount, price, date_time) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, -shares, quoted["price"])

        # Show info
        return redirect("/")

    else:
        symbols = [data["symbol"] for data in db.execute("SELECT symbol FROM shares WHERE user_id = ?", session["user_id"])]
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
