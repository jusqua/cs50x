-- This is a copy of all 13 files this this one, for a better visualization
-- 1.sql
SELECT title FROM movies WHERE year = 2008;

-- 2.sql
SELECT birth FROM people WHERE name = "Emma Stone";

-- 3.sql
SELECT title FROM movies WHERE year > 2017 ORDER BY title;

-- 4.sql
SELECT COUNT(title) FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10.0);

-- 5.sql
SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year;

-- 6.sql
SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

-- 7.sql
SELECT title, rating FROM movies INNER JOIN ratings ON id = movie_id WHERE year = 2010 ORDER BY rating DESC, title LIMIT 10;

-- 8.sql
SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE title = "Toy Story"));

-- 9.sql
SELECT DISTINCT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004)) ORDER BY birth;

-- 10.sql
SELECT name FROM people WHERE id IN (SELECT person_id FROM directors WHERE movie_id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0));

-- 11.sql
SELECT title FROM movies LEFT JOIN ratings ON movie_id = id WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Chadwick Boseman")) ORDER BY rating DESC LIMIT 5;

-- 12.sql
SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Johnny Depp")) INTERSECT SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter"));

-- 13.sql
SELECT DISTINCT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958))) EXCEPT SELECT name FROM people WHERE name = "Kevin Bacon" AND birth = 1958;

