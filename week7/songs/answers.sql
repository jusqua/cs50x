-- This is a copy of all 8 files this this one, for a better visualization
-- 1.sql
SELECT name FROM songs;

-- 2.sql
SELECT name FROM songs ORDER BY tempo;

-- 3.sql
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- 4.sql
SELECT name FROM songs WHERE (danceability > 0.75 AND energy > 0.75 AND valence > 0.75);

-- 5.sql
SELECT AVG(energy) FROM songs;

-- 6.sql
SELECT name FROM songs WHERE artist_id IN (SELECT id from artists WHERE name = "Post Malone");

-- 7.sql
SELECT AVG(energy) FROM songs WHERE artist_id IN (SELECT id from artists WHERE name = "Drake");

-- 8.sql
SELECT name from songs WHERE name LIKE "%feat.%";

