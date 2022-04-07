SELECT name FROM people INNER JOIN stars ON id = person_id WHERE movie_id =
(SELECT id FROM movies WHERE title = 'Toy Story');