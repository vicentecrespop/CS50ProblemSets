import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        # Check if all fields were filled
        if not name or not month or not day:
            birthdays = db.execute("SELECT * FROM birthdays")
            return render_template("index.html", message="Please fill all fields!", birthdays=birthdays)

        # Check if date is valid
        birthdays = db.execute("SELECT * FROM birthdays")
        try:
            if int(month) > 12 or int(month) <= 0 or int(day) > 31 or int(day) <= 0:
                return render_template("index.html", message="Invalid date!!", birthdays=birthdays)
        except ValueError:
            return render_template("index.html", message="Invalid date!!", birthdays=birthdays)

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    else:
        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

# Deletes birthday from database
@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")

# Goes to new page to edit the birthday
@app.route("/edit", methods=["POST"])
def edit():
    id = request.form.get("id")
    if id:
        name = db.execute("SELECT name FROM birthdays WHERE id = ?", id)
    return render_template("edit.html", name=name[0]['name'], id=id)

# Updates the birthday on the database
@app.route("/send-edit", methods=["POST"])
def send_edit():
    id = request.form.get("id")
    month = request.form.get("month")
    day = request.form.get("day")

    # Check if date is valid
    if int(month) > 12 or int(month) <= 0 or int(day) > 31 or int(day) <= 0:
        name = db.execute("SELECT name FROM birthdays WHERE id = ?", id)
        return render_template("edit.html", name=name[0]['name'], id=id, message="Invalid date!!")

    # Check if filled all fields then updates birthday
    if id and month and day:
        db.execute("UPDATE birthdays SET month = ?, day = ? WHERE id = ?", month, day, id)
    return redirect("/")






