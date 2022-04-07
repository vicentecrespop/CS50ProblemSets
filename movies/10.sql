SELECT DISTINCT(name) FROM people INNER JOIN directors ON id = person_id WHERE movie_id IN
(SELECT movie_id FROM ratings WHERE rating >= 9.0);