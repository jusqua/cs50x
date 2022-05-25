-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get crime description and set start point: witnesses interview
SELECT * FROM crime_scene_reports WHERE description LIKE "%duck%";
-- Witness interview:
-- Ruth = the thief gets its car 10 minutes after the theft,
-- Eugene = the thief withdraw some money at ATM on Fifer Street before the theft,
-- Raymond = the thief called someone, the call takes less than a minute, and purchase a flight ticket to left from Fiftyville tomorrow (7, 29) from the earliest flight.
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%thief%";
-- Get exit logs in a interval of time based on Ruth interview,
-- get the people info who exit in this interval based on licence plate,
-- get the people info who withdraws in the same day, based on Eugene interview,
-- intersected info will show those people have exited from scene and withdraw some money in the day of the theft,
-- using people number to find who call with lass than a minute based on Raymond interview, swithing the variable we finds the caller and receiver
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") INTERSECT
SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw"))));
-- Find flights per passport
SELECT * FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") INTERSECT
SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw")))));
-- Using people passport find who will travel tomorrow (7, 29) from the earliest flight.
SELECT * FROM flights WHERE month = 7 AND day = 29 AND id IN
(SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") INTERSECT
SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw"))))));
-- Ernest is the thief and Berthold is his accomplice, and his escaped to London
SELECT * FROM airports;
