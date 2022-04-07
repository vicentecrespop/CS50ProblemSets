SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars INNER JOIN people ON person_id = id
WHERE name = 'Johnny Depp' OR name = 'Helena Bonham Carter' GROUP BY movie_id HAVING COUNT(movie_id) > 1);