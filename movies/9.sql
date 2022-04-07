SELECT DISTINCT(name) FROM people INNER JOIN stars on id = person_id WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2004) ORDER BY birth;