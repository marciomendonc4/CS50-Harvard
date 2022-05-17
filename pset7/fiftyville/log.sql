-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking the descriptions of crimes reporteds day 28 on the Humphrey Street
SELECT csr.description
FROM crime_scene_reports csr
WHERE csr.day = 28 AND csr.street LIKE "%Humphrey%";

-- Reading the transcriptions of the witnesses
SELECT i.name, i.transcript
FROM interviews i
WHERE i.day = 28 AND i.month = 7 AND year = 2021
ORDER BY i.transcript;

-- Checking the security log of the bakery
SELECT bsl.hour, bsl.minute, bsl.activity, bsl.license_plate
FROM bakery_security_logs bsl
WHERE bsl.day = 28 AND bsl.month = 7 AND bsl.hour = 10 AND bsl.year = 2021
ORDER by bsl.hour;

--Searching for the license plates owners, to start my suspect list
SELECT p.name, p.license_plate
FROM people p
JOIN bakery_security_logs bsl USING(license_plate)
WHERE bsl.activity = "exit"
AND bsl.day = 28
AND bsl.month = 7
AND bsl.hour = 10
AND bsl.year = 2021;

/*
SUSPECT LIST
+---------+---------------+
|  name   | license_plate |
+---------+---------------+
| Vanessa | 5P2BI95       |
| Bruce   | 94KL13X       |
| Barry   | 6P58WS2       |
| Luca    | 4328GD8       |
| Sofia   | G412CB7       |
| Iman    | L93JTIZ       |
| Diana   | 322W7JE       |
| Kelsey  | 0NTHK55       |
| Taylor  | 1106N58       |
+---------+---------------+
*/

-- Checking the log of atm transactions on the morning of the crime
SELECT p.name
FROM people p
WHERE id in (
    SELECT ba.person_id
    FROM bank_accounts ba
    JOIN atm_transactions atm USING(account_number)
    WHERE atm.atm_location = "Leggett Street"
    AND atm.transaction_type = "withdraw"
    AND atm.day = 28
    AND atm.month = 7
    AND atm.year = 2021
);

-- Crossing the results with my SUSPECT LIST
SELECT p.name
FROM people p
JOIN bakery_security_logs bsl USING(license_plate)
WHERE bsl.activity = "exit"
AND bsl.day = 28
AND bsl.month = 7
AND bsl.hour = 10
AND bsl.year = 2021
INTERSECT
SELECT p.name
FROM people p
WHERE id in (
    SELECT ba.person_id
    FROM bank_accounts ba
    JOIN atm_transactions atm USING(account_number)
    WHERE atm.atm_location = "Leggett Street"
    AND atm.transaction_type = "withdraw"
    AND atm.day = 28
    AND atm.month = 7
    AND atm.year = 2021
);
/*
UPDATED SUSPECT LIST:
+--------+
|  name  |
+--------+
| Bruce  |
| Diana  |
| Iman   |
| Luca   |
| Taylor |
+--------+
*/

-- Checking the phone calls register to further narrow the suspect list
SELECT p.name
FROM people p
WHERE p.phone_number IN (
    SELECT pc.caller
    FROM phone_calls pc
    WHERE pc.day = 28
    AND pc.month = 7
    AND pc.year = 2021
    AND pc.duration < 60
);

-- Crossing again the query result with the UPDATED LIST
SELECT p.name
FROM people p
WHERE p.phone_number IN (
    SELECT pc.caller
    FROM phone_calls pc
    WHERE pc.day = 28
    AND pc.month = 7
    AND pc.year = 2021
    AND pc.duration < 60
)
INTERSECT
SELECT p.name
FROM people p
JOIN bakery_security_logs bsl USING(license_plate)
WHERE bsl.activity = "exit"
AND bsl.day = 28
AND bsl.month = 7
AND bsl.hour = 10
AND bsl.year = 2021
INTERSECT
SELECT p.name
FROM people p
WHERE id in (
    SELECT ba.person_id
    FROM bank_accounts ba
    JOIN atm_transactions atm USING(account_number)
    WHERE atm.atm_location = "Leggett Street"
    AND atm.transaction_type = "withdraw"
    AND atm.day = 28
    AND atm.month = 7
    AND atm.year = 2021
);

/*
UPDATED LIST
+--------+
|  name  |
+--------+
| Bruce  |
| Diana  |
| Taylor |
+--------+
*/


-- Checking the earliest flight for the next day
SELECT *
FROM flights f
JOIN airports a ON a.id = f.origin_airport_id
WHERE a.city = "Fiftyville"
AND f.day = 29
AND f.month = 7
AND f.year = 2021
ORDER BY f.hour
LIMIT 1;

-- Using the query above, tracking the destination AKA city where the ESCAPED to:
SELECT a.full_name, a.city
FROM airports a
WHERE id in (
    SELECT destination_airport_id
    FROM flights f
    JOIN airports a ON a.id = f.origin_airport_id
    WHERE a.city = "Fiftyville"
    AND f.day = 29
    AND f.month = 7
    AND f.year = 2021
    ORDER BY f.hour
    LIMIT 1
);

-- List of the passengers from the earliest July 29th flight
SELECT p.name
FROM people p
JOIN passengers ps USING(passport_number)
WHERE ps.flight_id IN (
    SELECT f.id
    FROM flights f
    JOIN airports a ON a.id = f.origin_airport_id
    WHERE a.city = "Fiftyville"
    AND f.day = 29
    AND f.month = 7
    AND f.year = 2021
    ORDER BY f.hour ASC
    LIMIT 1
);

-- Crossing the query result with the newest updated SUSPECT LIST
SELECT p.name
FROM people p
WHERE p.phone_number IN (
    SELECT pc.caller
    FROM phone_calls pc
    WHERE pc.day = 28
    AND pc.month = 7
    AND pc.year = 2021
    AND pc.duration < 60
)
INTERSECT
SELECT p.name
FROM people p
JOIN bakery_security_logs bsl USING(license_plate)
WHERE bsl.activity = "exit"
AND bsl.day = 28
AND bsl.month = 7
AND bsl.hour = 10
AND bsl.year = 2021
INTERSECT
SELECT p.name
FROM people p
WHERE id in (
    SELECT ba.person_id
    FROM bank_accounts ba
    JOIN atm_transactions atm USING(account_number)
    WHERE atm.atm_location = "Leggett Street"
    AND atm.transaction_type = "withdraw"
    AND atm.day = 28
    AND atm.month = 7
    AND atm.year = 2021
)
INTERSECT
SELECT p.name
FROM people p
JOIN passengers ps USING(passport_number)
WHERE ps.flight_id IN (
    SELECT f.id
    FROM flights f
    JOIN airports a ON a.id = f.origin_airport_id
    WHERE a.city = "Fiftyville"
    AND f.day = 29
    AND f.month = 7
    AND f.year = 2021
    ORDER BY f.hour ASC
    LIMIT 1
);
/*
SUSPECT LIST
+--------+
|  name  |
+--------+
| Bruce  |
| Taylor |
+--------+
*/

-- Tracking Bruce and Taylor's activities to see if they match with the theft timeframe
-- Taylor
SELECT bs.hour, bs.minute, bs.activity
FROM bakery_security_logs bs
JOIN people p USING (license_plate)
WHERE p.name = "Taylor";
-- Bruce
SELECT bs.hour, bs.minute, bs.activity
FROM bakery_security_logs bs
JOIN people p USING (license_plate)
WHERE p.name = "Bruce";

/*
After this check is safe to assume that Bruce is the thief, because Taylor didn't leave the
bakery's parking lot till 10:35 AM
*/
-- To find the accomplice we just need to check Bruce's phonecalls register for phonecalls uns 60s duration
SELECT p.name
FROM people p
WHERE p.phone_number IN (
    SELECT pc.receiver
    FROM phone_calls pc
    JOIN people p ON p.phone_number = pc.caller
    WHERE p.name = "Bruce"
    AND duration < 60
    AND day = 28
    AND month = 7
    AND year = 2021
);
/*
Result of the query:
+-------+
| name  |
+-------+
| Robin |
+-------+
*/