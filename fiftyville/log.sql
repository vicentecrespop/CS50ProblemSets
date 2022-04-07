-- Keep a log of any SQL queries you execute as you solve the mystery.

--Checking the crime scene reports from the day of the event and after
SELECT * FROM crime_scene_reports WHERE month = 7 AND day >= 28;
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street Bakery.
-- Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery.


-- Interviews from the date of the theft
SELECT * FROM interviews WHERE month = 7 AND day = 28;


-- Ruth - "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--         If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
-- Name of people who left the bakery under 15 minutes after the theft.
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 30 AND activity = 'exit');
-- name
-- Vanessa
-- Barry
-- Iman
-- Sofia
-- Luca
-- Diana
-- Kelsey
-- Bruce


-- Eugene - "I don't know the thief's name, but it was someone I recognized.
--           Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
-- Name of people who went to the atm on Leggett Street in the 28th.
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7)));
-- name
-- Kenny
-- Iman
-- Benista
-- Taylor
-- Brooke
-- Luca
-- Diana
-- Bruce
-- Kaelyn

-- Raymond - "As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--            In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--            The thief then asked the person on the other end of the phone to purchase the flight ticket."
-- Name of the people who were in the earliest flight of the 29th
SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = 'Fiftyville') AND day = 29 ORDER BY hour LIMIT 1));
-- name
-- Kenny
-- Sofia
-- Taylor
-- Luca
-- Kelsey
-- Edward
-- Bruce
-- Doris
-- City the thief escaped to is New York City
SELECT city FROM airports WHERE id =
(SELECT destination_airport_id FROM flights WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = 'Fiftyville') AND day = 29 ORDER BY hour LIMIT 1);


--Name of the people who called someone on the 28th and talked for less than a minute
SELECT name FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60);
-- name
-- Kenny
-- Sofia
-- Benista
-- Taylor
-- Diana
-- Kelsey
-- Bruce
-- Carina

-- Only person that went to the ATM on Leggett Street on the 28th,
-- left the bakery with under 15 minutes after the theft,
-- was in the earliest flight on the 29th and made a phone call that was under a minute was Bruce.
-- Bruce is the thief.

-- Name of people who received Calls from Bruce that took less than a minute on the 28th
SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND caller IN
(SELECT phone_number FROM people WHERE name = 'Bruce') AND duration < 60);
-- name
-- Robin
-- Robin is the thief's accomplice.