SELECT movies.title, movies.year
FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE stars.person_id = 93;
